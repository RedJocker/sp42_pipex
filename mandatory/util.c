/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:30:25 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/21 23:34:49 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "util.h"
#include "ft_stdio.h"

void	free_strarr_null_term(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	close_std_fds(void)
{
	close(STDIN);
	close(STDOUT);
	close(STDERR);
}

int	child_check_exit_status(int status)
{
	return (((status) & 0xff00) >> 8);
}

int	is_child(pid_t pid)
{
	return (pid == 0);
}

void	log_error(char *path, char *msg)
{
	ft_putstr_fd(path, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putendl_fd(msg, STDERR);
}
