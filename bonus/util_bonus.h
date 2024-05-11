/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:19:11 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/11 00:22:32 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include "pipex_bonus.h"
# include <sys/types.h>

void	free_strarr_null_term(char **arr);
void	close_std_fds(void);
int		child_check_exit_status(int status);
int		is_child(pid_t pid);
void	log_error(char *path, char *msg);

#endif
