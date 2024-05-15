/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_simple_execute_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:19:05 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/15 19:42:13 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "command_bonus.h"
#include "util_bonus.h"
#include "io_handler_bonus.h"
#include <stdio.h>
#include <string.h>
#include "ft_string.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

static int	command_simple_log_error_eacces(t_command cmd, int err_num)
{
	int	fd;

	fd = open(cmd->simple->cmd_argv[0], O_DIRECTORY, 0777);
	if (fd >= 0)
	{
		close(fd);
		if (ft_strchr(cmd->simple->cmd_path, '/'))
			log_error(cmd->simple->cmd_argv[0], "Is a directory");
		else
		{
			log_error(cmd->simple->cmd_argv[0], "command not found");
			return (127);
		}
	}
	else
	{
		close(fd);
		if (cmd->simple->cmd_argv[0][0] == '\0')
		{
			log_error(cmd->simple->cmd_argv[0], "command not found");
			return (127);
		}
		log_error(cmd->simple->cmd_argv[0], strerror(err_num));
	}
	return (126);
}

static int	command_simple_log_error_enoent(t_command cmd)
{
	if (ft_strchr(cmd->simple->cmd_path, '/'))
		log_error(cmd->simple->cmd_argv[0], "No such file or directory");
	else
		log_error(cmd->simple->cmd_argv[0], "command not found");
	return (127);
}

static int	command_simple_log_error(t_command cmd, int err_num)
{
	int		drain_in;
	char	ch;

	drain_in = 1;
	while (drain_in > 0)
		drain_in = read(STDIN, &ch, 1);
	if (err_num == ENOENT)
		return (command_simple_log_error_enoent(cmd));
	else if (err_num == EACCES)
		return (command_simple_log_error_eacces(cmd, err_num));
	log_error(cmd->simple->cmd_path, strerror(err_num));
	return (err_num);
}

static int	command_simple_to_execve(t_command cmd)
{
	int	err_num;

	if (cmd->input.type == ERROR)
	{
		log_error(cmd->input.error, strerror(cmd->input.error_status));
		if (cmd->output.type == FD)
			close(cmd->output.fd);
		return (1);
	}
	else if (cmd->output.type == ERROR)
	{
		log_error(cmd->output.error, strerror(cmd->output.error_status));
		if (cmd->input.type == FD)
			close(cmd->input.fd);
		return (1);
	}
	dup2(cmd->output.fd, STDOUT);
	close(cmd->output.fd);
	dprintf(2, "d-close %s %d\n", cmd->debug_id, cmd->output.fd);
	dup2(cmd->input.fd, STDIN);
	close(cmd->input.fd);
	dprintf(2, "d-close %s %d\n", cmd->debug_id, cmd->input.fd);
	execve(cmd->simple->cmd_path, cmd->simple->cmd_argv, cmd->simple->cmd_envp);
	err_num = errno;
	return (command_simple_log_error(cmd, err_num));
}

int	command_simple_execute(t_command cmd, t_arraylist *pids)
{
	pid_t	*pid;

	if (cmd->type != SIMPLE)
		return (0);
	pid = malloc(sizeof(pid_t));
	*pid = fork();
	if (*pid < 0)
		exit(EXIT_FORK_FAIL);
	else if (is_child(*pid))
	{
		free(pid);
		io_handle_to_fd(&cmd->input);
		io_handle_to_fd(&cmd->output);
		if (cmd->close.type == FD)
		{
			dprintf(2, "c-close %s %d\n", cmd->debug_id, cmd->close.fd);
			close(cmd->close.fd);
		}
		return (command_simple_to_execve(cmd));
	}
	else
	{
		*pids = ft_arraylist_add(*pids, pid);
		if (!(*pids))
			exit(EXIT_MALLOC_FAIL);
		return (EXIT_OK);
	}
}
