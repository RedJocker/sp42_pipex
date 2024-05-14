/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_simple_bonus.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:19:04 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/14 17:48:03 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_SIMPLE_BONUS_H
# define COMMAND_SIMPLE_BONUS_H

# include "pipex_bonus.h"
# include "collection/ft_arraylist.h"

int			command_simple_execute(t_command cmd, t_arraylist *pids);
void		command_simple_destroy(t_command_simple *cmd);
t_command	command_simple_new(char *command, char **argv, char **envp);
void		command_simple_set_output(t_command cmd, t_io_handler *io);
void		command_simple_set_input(t_command cmd, t_io_handler *io);
void		command_simple_set_close_pipe_in(t_command cmd, t_io_handler *io);

#endif 
