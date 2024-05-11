/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pipe_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:19:01 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/11 00:26:44 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_PIPE_BONUS_H
# define COMMAND_PIPE_BONUS_H

# include "pipex_bonus.h"
# include "collection/ft_arraylist.h"

void		command_pipe_destroy(t_command_pipe *cmd);
t_command	command_pipe_new(void);
int			command_pipe_execute(t_command cmd, t_arraylist *pids);

#endif 
