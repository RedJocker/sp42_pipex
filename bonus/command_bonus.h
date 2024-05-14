/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:18:48 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/14 17:51:40 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_BONUS_H
# define COMMAND_BONUS_H

# include "pipex_bonus.h"
# include "collection/ft_arraylist.h"
# include "command_simple_bonus.h"
# include "command_pipe_bonus.h"

int			command_execute(t_command cmd, t_arraylist *pids);
t_command	command_build(const int argc, char *argv[], char *envp[]);
void		command_destroy(t_command cmd);
void		command_set_input(t_command cmd, t_io_handler *io);
void		command_set_output(t_command cmd, t_io_handler *io);
void		command_set_close_pipe_in(t_command cmd, t_io_handler *io);

#endif
