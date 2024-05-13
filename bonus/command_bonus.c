/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:18:17 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/13 13:31:08 by maurodri         ###   ########.fr       */
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
	if (cmd->debug_id != NULL)
		free(cmd->debug_id);
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
	char			**command0;
	char			**command1;
	char            **command2;
	char			**command3;
	t_command		tcmd0;
	t_command		tcmd1;
	t_command       tcmd2;
	t_command		tcmd3;
	t_command       cmd_pipe0;
	t_command       cmd_pipe1;
	t_command		cmd_pipe2;
	t_io_handler	io;

	(void) argc;
	command0 = ft_split_quote(argv[2], ' ');
	command1 = ft_split_quote(argv[3], ' ');
	command2 = ft_split_quote(argv[4], ' ');
	command3 = ft_split_quote(argv[5], ' ');
	cmd_pipe0 = command_pipe_new();
	cmd_pipe0->debug_id = ft_strdup("pipe0");
	cmd_pipe1 = command_pipe_new();
	cmd_pipe1->debug_id = ft_strdup("pipe1");
	cmd_pipe2 = command_pipe_new();
	cmd_pipe2->debug_id = ft_strdup("pipe2");
	tcmd0 = command_simple_new(command0[0], command0, envp);
	tcmd0->debug_id = ft_strdup("tcmd0");
	tcmd1 = command_simple_new(command1[0], command1, envp);
	tcmd1->debug_id = ft_strdup("tcmd1");
	tcmd2 = command_simple_new(command2[0], command2, envp);
	tcmd2->debug_id = ft_strdup("tcmd2");
	tcmd3 = command_simple_new(command3[0], command3, envp);
	tcmd3->debug_id = ft_strdup("tcmd3");
	cmd_pipe0->pipe->before = tcmd0;
	cmd_pipe0->pipe->after = cmd_pipe1;
	cmd_pipe1->pipe->before = tcmd1;
	cmd_pipe1->pipe->after = cmd_pipe2;
	cmd_pipe2->pipe->before = tcmd2;
	cmd_pipe2->pipe->after = tcmd3;
	io.type = PATH;
	io.path = argv[1];
	io.flags = O_RDONLY;
	io.mode = 0666;
	command_set_input(cmd_pipe0, &io);
	io.type = PATH;
	io.path = argv[6];
	io.flags = O_CREAT | O_WRONLY | O_TRUNC;
	io.mode = 0666;
	command_set_output(cmd_pipe0, &io);
	return (cmd_pipe0);
}
