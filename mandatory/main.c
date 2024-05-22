/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:34:19 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/21 23:36:00 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "util.h"
#include "command.h"
#include <sys/wait.h>

int	main(const int argc, char *argv[], char *envp[])
{
	t_arraylist	pids;
	t_command	cmd;
	int			len_i[2];
	int			status[2];

	if (argc != 5)
	{
		log_error("pipex", "invalid argc");
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
	command_destroy(cmd);
	ft_arraylist_destroy(pids);
	if (status[1] != EXIT_OK)
		return (status[1]);
	return (child_check_exit_status(status[0]));
}
