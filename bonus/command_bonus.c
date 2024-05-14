/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:18:17 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/14 19:08:49 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_bonus.h"
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

void	command_set_input(t_command cmd, t_io_handler *io)
{
	if (cmd->type == SIMPLE)
		command_simple_set_input(cmd, io);
	else if (cmd->type == PIPE)
		command_pipe_set_input(cmd, io);
}

void	command_set_output(t_command cmd, t_io_handler *io)
{
	if (cmd->type == SIMPLE)
		command_simple_set_output(cmd, io);
	else if (cmd->type == PIPE)
		command_pipe_set_output(cmd, io);
}

void	command_set_close_pipe_in(t_command cmd, t_io_handler *io)
{
	if (cmd->type == SIMPLE)
		command_simple_set_close_pipe_in(cmd, io);
	else if (cmd->type == PIPE)
		command_pipe_set_close_pipe_in(cmd, io);
}
