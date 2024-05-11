/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:18:17 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/12 18:50:38 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_bonus.h"
#include "pipex_bonus.h"
#include "ft_string.h"
#include <fcntl.h>
#include <unistd.h>

void	command_destroy(t_command cmd)
{
	if (cmd->type == PIPE)
		command_pipe_destroy(cmd->pipe);
	else if (cmd->type == SIMPLE)
		command_simple_destroy(cmd->simple);
	free(cmd);
}

int	command_execute(t_command cmd, t_arraylist *pids)
{
	if (cmd->type == SIMPLE)
		return (command_simple_execute(cmd, pids));
	else if (cmd->type == PIPE)
		return (command_pipe_execute(cmd, pids));
	return (EXIT_OK);
}

t_command	command_build(const int argc, char *argv[], char *envp[])
{
	t_command	tcmd0;
	char		**command0;
	char		**command1;
	t_command	tcmd1;
	t_command	cmd_pipe;

	(void) argc;
	command0 = ft_split_quote(argv[2], ' ');
	command1 = ft_split_quote(argv[3], ' ');
	tcmd0 = command_simple_new(command0[0], command0, envp);
	tcmd0->input.type = PATH;
	tcmd0->input.path = argv[1];
	tcmd0->input.flags = O_RDONLY;
	tcmd0->input.mode = 0666;
	tcmd1 = command_simple_new(command1[0], command1, envp);
	tcmd1->output.type = PATH;
	tcmd1->output.path = argv[4];
	tcmd1->output.flags = O_CREAT | O_WRONLY | O_TRUNC;
	tcmd1->output.mode = 0666;
	cmd_pipe = command_pipe_new();
	cmd_pipe->pipe->before = tcmd0;
	cmd_pipe->pipe->after = tcmd1;
	return (cmd_pipe);
}
