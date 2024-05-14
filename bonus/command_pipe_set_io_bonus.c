/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pipe_set_io_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:03:06 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/14 19:10:40 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_bonus.h"
#include "ft_memlib.h"

void	command_pipe_set_output(t_command cmd, t_io_handler *io)
{
	ft_memcpy(&cmd->output, io, sizeof(t_io_handler));
	command_set_output(cmd->pipe->after, io);
}

void	command_pipe_set_input(t_command cmd, t_io_handler *io)
{
	ft_memcpy(&cmd->input, io, sizeof(t_io_handler));
	command_set_input(cmd->pipe->before, io);
}

void	command_pipe_set_close_pipe_in(t_command cmd, t_io_handler *io)
{
	command_set_close_pipe_in(cmd->pipe->before, io);
}
