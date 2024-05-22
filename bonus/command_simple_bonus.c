/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_simple_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:19:03 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/22 00:22:16 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_simple_bonus.h"
#include "util_bonus.h"
#include "envp_bonus.h"
#include "ft_string.h"
#include "ft_memlib.h"

void	command_simple_set_output(t_command cmd, t_io_handler *io)
{
	ft_memcpy(&cmd->output, io, sizeof(t_io_handler));
}

void	command_simple_set_input(t_command cmd, t_io_handler *io)
{
	ft_memcpy(&cmd->input, io, sizeof(t_io_handler));
}

void	command_simple_set_close_pipe_in(t_command cmd, t_io_handler *io)
{
	ft_memcpy(&cmd->close, io, sizeof(t_io_handler));
}

void	command_simple_destroy(t_command_simple *cmd)
{
	free(cmd->cmd_path);
	free_strarr_null_term(cmd->cmd_argv);
	free(cmd);
}

t_command	command_simple_new(char *command, char **argv, char **envp)
{
	t_command	cmd;

	cmd = ft_calloc(1, sizeof(struct s_command));
	cmd->type = SIMPLE;
	cmd->simple = ft_calloc(1, sizeof(struct s_command_simple));
	if (!command)
		cmd->simple->cmd_path = envp_find_bin_by_name("", envp);
	else
		cmd->simple->cmd_path = envp_find_bin_by_name(command, envp);
	cmd->simple->cmd_argv = argv;
	cmd->simple->cmd_envp = envp;
	cmd->input.type = NONE;
	cmd->output.type = NONE;
	cmd->close.type = NONE;
	return (cmd);
}
