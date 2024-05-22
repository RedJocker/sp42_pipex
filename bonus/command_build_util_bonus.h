/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_build_util_bonus.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:45:24 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/21 22:12:05 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_BUILD_UTIL_BONUS_H
# define COMMAND_BUILD_UTIL_BONUS_H

# include "pipex_bonus.h"

int			command_debug_id(void);
t_command	command_build_pipe(void);
t_command	command_build_simple(const char *arg, char *envp[]);
void		command_build_set_io(t_io_handler *io, char *path, int flags);

#endif
