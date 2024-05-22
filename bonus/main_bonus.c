/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:19:09 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/22 01:03:36 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collection/ft_arraylist.h"
#include "pipex_bonus.h"
#include "util_bonus.h"
#include "command_bonus.h"
#include "ft_string.h"
#include <sys/wait.h>

static int	is_invalid_args(const int argc, char *argv[])
{
	return (argc < 5 || (argc == 5 && ft_strncmp("here_doc", argv[2], 9) == 0));
}

static void	destroy(t_command cmd, t_arraylist pids)
{
	command_destroy(cmd);
	ft_arraylist_destroy(pids);
}

int	main(const int argc, char *argv[], char *envp[])
{
	t_arraylist	pids;
	t_command	cmd;
	int			len_i[2];
	int			status[2];

	if (is_invalid_args(argc, argv))
	{
		log_error("pipex", "invalid argc");
		close_std_fds();
		return (1);
	}
	pids = ft_arraylist_new(free);
	cmd = command_build(argc, argv, envp);
	status[1] = command_execute(cmd, &pids);
	close_std_fds();
	len_i[0] = ft_arraylist_len(pids);
	len_i[1] = -1;
	while (++len_i[1] < len_i[0] - 1)
		waitpid(*((pid_t *) ft_arraylist_get(pids, len_i[1])), 0, 0);
	if (len_i[0] > 0)
		waitpid(*((pid_t *) ft_arraylist_get(pids, len_i[1])), status, 0);
	destroy(cmd, pids);
	if (status[1] != EXIT_OK)
		return (status[1]);
	return (child_check_exit_status(status[0]));
}
