/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:18:17 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/12 21:05:22 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_bonus.h"
#include "pipex_bonus.h"
#include "ft_string.h"
#include "ft_memlib.h"
#include <fcntl.h>
#include <unistd.h>

void	command_destroy(t_command cmd)
{
	if (cmd->type == PIPE)
		command_pipe_destroy(cmd->pipe);
	else if (cmd->type == SIMPLE)
		command_simple_destroy(cmd->simple);
	free(cmd);
}

int	command_execute(t_command cmd, t_arraylist *pids)
{
	if (cmd->type == SIMPLE)
		return (command_simple_execute(cmd, pids));
	else if (cmd->type == PIPE)
		return (command_pipe_execute(cmd, pids));
	return (EXIT_OK);
}

void command_set_input(t_command cmd, t_io_handler *io);

void command_simple_set_input(t_command cmd, t_io_handler *io)
{
	ft_memcpy(&cmd->input, io, sizeof(t_io_handler));
}

void command_pipe_set_input(t_command cmd, t_io_handler *io)
{
	ft_memcpy(&cmd->input, io, sizeof(t_io_handler));
	command_set_input(cmd->pipe->before, io);
}

void command_set_input(t_command cmd, t_io_handler *io)
{
	if (cmd->type == SIMPLE)
		command_simple_set_input(cmd, io);
	else if (cmd->type == PIPE)
		command_pipe_set_input(cmd, io);
}


void command_set_output(t_command cmd, t_io_handler *io);

void command_simple_set_output(t_command cmd, t_io_handler *io)
{
	ft_memcpy(&cmd->output, io, sizeof(t_io_handler));
}

void command_pipe_set_output(t_command cmd, t_io_handler *io)
{
	ft_memcpy(&cmd->output, io, sizeof(t_io_handler));
	command_set_output(cmd->pipe->after, io);
}

void command_set_output(t_command cmd, t_io_handler *io)
{
	if (cmd->type == SIMPLE)
		command_simple_set_output(cmd, io);
	else if (cmd->type == PIPE)
		command_pipe_set_output(cmd, io);
}


t_command	command_build(const int argc, char *argv[], char *envp[])
{
	t_command		tcmd0;
	char			**command0;
	char			**command1;
	t_command		tcmd1;
	t_command		cmd_pipe;
	t_io_handler	io;

	(void) argc;
	command0 = ft_split_quote(argv[2], ' ');
	command1 = ft_split_quote(argv[3], ' ');
	cmd_pipe = command_pipe_new();
	tcmd0 = command_simple_new(command0[0], command0, envp);
	tcmd1 = command_simple_new(command1[0], command1, envp);
	cmd_pipe->pipe->before = tcmd0;
	cmd_pipe->pipe->after = tcmd1;
	io.type = PATH;
	io.path = argv[1];
	io.flags = O_RDONLY;
	io.mode = 0666;
	command_set_input(cmd_pipe, &io);
	io.type = PATH;
	io.path = argv[4];
	io.flags = O_CREAT | O_WRONLY | O_TRUNC;
	io.mode = 0666;
	command_set_output(cmd_pipe, &io);
	return (cmd_pipe);
}
