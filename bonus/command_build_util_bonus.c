/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_build_util_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:45:01 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/21 23:42:21 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_build_util_bonus.h"
#include "command_bonus.h"
#include "ft_string.h"

int	command_debug_id(void)
{
	static int	id = 0;

	return (id++);
}

t_command	command_build_pipe(void)
{
	char		*id_str;
	t_command	cmd;

	id_str = ft_itoa(command_debug_id());
	cmd = command_pipe_new();
	cmd->debug_id = ft_strjoin("pipe", id_str);
	free(id_str);
	return (cmd);
}

t_command	command_build_simple(const char *arg, char *envp[])
{
	char		*id_str;
	t_command	cmd;
	char		**cmd_strarr;

	id_str = ft_itoa(command_debug_id());
	cmd_strarr = ft_split_quote(arg, ' ');
	cmd = command_simple_new(cmd_strarr[0], cmd_strarr, envp);
	cmd->debug_id = ft_strjoin("simple", id_str);
	free(id_str);
	return (cmd);
}

void	command_build_set_io(t_io_handler *io, char *path, int flags)
{
	io->type = PATH;
	io->path = path;
	io->flags = flags;
	io->mode = 0666;
}
