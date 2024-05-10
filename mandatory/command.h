/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:38:25 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/09 18:56:20 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "pipex.h"
# include "collection/ft_arraylist.h"
# include "command_simple.h"
# include "command_pipe.h"

int			command_execute(t_command cmd, t_arraylist *pids);
t_command	command_build(const int argc, char *argv[], char *envp[]);
void		command_destroy(t_command cmd);

#endif
