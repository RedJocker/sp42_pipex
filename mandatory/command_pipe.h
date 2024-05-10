/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pipe.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:09:52 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/09 19:20:12 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_PIPE_H
# define COMMAND_PIPE_H

# include "pipex.h"
# include "collection/ft_arraylist.h"

void		command_pipe_destroy(t_command_pipe *cmd);
t_command	command_pipe_new(void);
int			command_pipe_execute(t_command cmd, t_arraylist *pids);

#endif 
