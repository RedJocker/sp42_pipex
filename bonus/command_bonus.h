/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:18:48 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/11 00:26:44 by maurodri         ###   ########.fr       */
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

#endif
