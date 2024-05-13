/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:18:17 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/13 14:50:25 by maurodri         ###   ########.fr       */
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
	char			**cmd_strarr;
	t_command		cmd_simple;
	t_command       cmd_pipe_root;
	t_command       cmd_previous_pipe;
	t_command       cmd_next_pipe;
	t_io_handler	io;
	int             i;
	int				id;
	char            *id_str;

	id = 0;
	id_str = ft_itoa(id++);
	cmd_pipe_root = command_pipe_new();
	cmd_pipe_root->debug_id = ft_strjoin("pipe", id_str);
	free(id_str);
	cmd_previous_pipe = cmd_pipe_root;
	i = 1;
	while (++i < argc - 3)
	{
		id_str = ft_itoa(id++);
		cmd_strarr = ft_split_quote(argv[i], ' ');
		cmd_simple = command_simple_new(cmd_strarr[0], cmd_strarr, envp);
		cmd_simple->debug_id = ft_strjoin("simple", id_str);
		free(id_str);
		id_str = ft_itoa(id++);
		cmd_next_pipe = command_pipe_new();
		cmd_next_pipe->debug_id = ft_strjoin("pipe", id_str);
		free(id_str);
		cmd_previous_pipe->pipe->before = cmd_simple;
		cmd_previous_pipe->pipe->after = cmd_next_pipe;
		cmd_previous_pipe = cmd_next_pipe;
	}
	id_str = ft_itoa(id++);
	cmd_strarr = ft_split_quote(argv[i++], ' ');
	cmd_simple = command_simple_new(cmd_strarr[0], cmd_strarr, envp);
	cmd_simple->debug_id = ft_strjoin("simple", id_str);
	free(id_str);
	cmd_previous_pipe->pipe->before = cmd_simple;
	id_str = ft_itoa(id++);
	cmd_strarr = ft_split_quote(argv[i++], ' ');
	cmd_simple = command_simple_new(cmd_strarr[0], cmd_strarr, envp);
	cmd_simple->debug_id = ft_strjoin("simple", id_str);
	free(id_str);
	cmd_previous_pipe->pipe->after = cmd_simple;
	io.type = PATH;
	io.path = argv[1];
	io.flags = O_RDONLY;
	io.mode = 0666;
	command_set_input(cmd_pipe_root, &io);
	io.type = PATH;
	io.path = argv[i];
	io.flags = O_CREAT | O_WRONLY | O_TRUNC;
	io.mode = 0666;
	command_set_output(cmd_pipe_root, &io);
	return (cmd_pipe_root);
}
