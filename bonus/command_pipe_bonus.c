/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pipe_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:18:58 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/13 07:07:08 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_pipe_bonus.h"
#include "pipex_bonus.h"
#include "command_bonus.h"
#include "io_handler_bonus.h"
#include "ft_memlib.h"
#include <unistd.h>
#include <stdio.h>

void	command_pipe_destroy(t_command_pipe *cmd)
{
	command_destroy(cmd->before);
	command_destroy(cmd->after);
	free(cmd);
}

t_command	command_pipe_new(void)
{
	t_command	cmd;

	cmd = ft_calloc(1, sizeof(struct s_command));
	cmd->type = PIPE;
	cmd->pipe = ft_calloc(1, sizeof(struct s_command_pipe));
	cmd->input.type = NONE;
	cmd->output.type = NONE;
	cmd->close.type = NONE;
	return (cmd);
}

void command_set_input(t_command cmd, t_io_handler *io);
void command_set_output(t_command cmd, t_io_handler *io);
void command_set_close_pipe_in(t_command cmd, t_io_handler *io);

void command_simple_set_close_pipe_in(t_command cmd, t_io_handler *io)
{
	ft_memcpy(&cmd->close, io, sizeof(t_io_handler));
}

void command_pipe_set_close_pipe_in(t_command cmd, t_io_handler *io)
{
	command_set_close_pipe_in(cmd->pipe->before, io);
}

void command_set_close_pipe_in(t_command cmd, t_io_handler *io)
{
	if (cmd->type == SIMPLE)
		command_simple_set_close_pipe_in(cmd, io);
	else if (cmd->type == PIPE)
		command_pipe_set_close_pipe_in(cmd, io);
}

//fds[0] read, fds[1] write
int	command_pipe_execute(t_command cmd, t_arraylist *pids)
{
	int				fd_pipe[2];
	int				status;
	t_io_handler	io;

	if (cmd->type != PIPE)
		return (0);
	if (pipe(fd_pipe) < 0)
		exit(EXIT_PIPE_FAIL);
	dprintf(2, "%s [read:%d write:%d]\n", cmd->debug_id, fd_pipe[0], fd_pipe[1]);
	io.type = FD;
	io.fd = fd_pipe[1];
	command_set_output(cmd->pipe->before, &io);
	io.fd = fd_pipe[0];
	command_set_close_pipe_in(cmd->pipe->before, &io);
	status = command_execute(cmd->pipe->before, pids);
	if (status != 0)
		return (status);
	if (cmd->input.type == FD)
	{
		close(cmd->input.fd);
		dprintf(2, "m3-close %s %d\n", cmd->debug_id, cmd->input.fd);
	}
	close(fd_pipe[1]);
	dprintf(2, "m2-close %s %d\n", cmd->debug_id, fd_pipe[1]);
	command_set_input(cmd->pipe->after, &io);
	status = command_execute(cmd->pipe->after, pids);
	if (status != 0)
		return (status);
	close(fd_pipe[0]);
	dprintf(2, "m-close %s %d\n", cmd->debug_id, fd_pipe[0]);
	return (EXIT_OK);
}
