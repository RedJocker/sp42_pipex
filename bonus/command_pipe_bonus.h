/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pipe_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:19:01 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/14 17:47:12 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_PIPE_BONUS_H
# define COMMAND_PIPE_BONUS_H

# include "pipex_bonus.h"
# include "collection/ft_arraylist.h"

void		command_pipe_destroy(t_command_pipe *cmd);
t_command	command_pipe_new(void);
int			command_pipe_execute(t_command cmd, t_arraylist *pids);
void		command_pipe_set_output(t_command cmd, t_io_handler *io);
void		command_pipe_set_input(t_command cmd, t_io_handler *io);
void		command_pipe_set_close_pipe_in(t_command cmd, t_io_handler *io);

#endif 
