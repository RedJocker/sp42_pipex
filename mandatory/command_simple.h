/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_simple.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:44:43 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/09 19:17:38 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_SIMPLE_H
# define COMMAND_SIMPLE_H

# include "pipex.h"
# include "collection/ft_arraylist.h"

int			command_simple_execute(t_command cmd, t_arraylist *pids);
void		command_simple_destroy(t_command_simple *cmd);
t_command	command_simple_new(char *command, char **argv, char **envp);

#endif 
