/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pipe_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:18:58 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/22 01:21:54 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_pipe_bonus.h"
#include "pipex_bonus.h"
#include "command_bonus.h"
#include "io_handler_bonus.h"
#include "ft_memlib.h"
#include <unistd.h>

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
	io_handle_set_fd(&io, fd_pipe[1]);
	command_set_output(cmd->pipe->before, &io);
	io.fd = fd_pipe[0];
	command_set_close_pipe_in(cmd->pipe->before, &io);
	status = command_execute(cmd->pipe->before, pids);
	if (status != 0)
		return (status);
	if (cmd->input.type == FD && cmd->input.fd > 0)
		close(cmd->input.fd);
	close(fd_pipe[1]);
	command_set_input(cmd->pipe->after, &io);
	status = command_execute(cmd->pipe->after, pids);
	if (status != 0)
		return (status);
	close(fd_pipe[0]);
	return (EXIT_OK);
}
