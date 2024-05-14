/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_build_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:12:24 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/14 19:10:16 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "command_bonus.h"
#include "ft_string.h"
#include <fcntl.h>

static int	command_debug_id(void)
{
	static int	id = 0;

	return (id++);
}

static t_command	command_build_pipe(void)
{
	char		*id_str;
	t_command	cmd;

	id_str = ft_itoa(command_debug_id());
	cmd = command_pipe_new();
	cmd->debug_id = ft_strjoin("pipe", id_str);
	free(id_str);
	return (cmd);
}

static t_command	command_build_simple(const char *arg, char *envp[])
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

static void	command_build_set_io(t_io_handler *io, char *path, int flags)
{
	io->type = PATH;
	io->path = path;
	io->flags = flags;
	io->mode = 0666;
}

t_command	command_build(const int argc, char *argv[], char *envp[])
{
	t_command		cmd_simple;
	t_command		cmd_pipe_root;	
	t_command		cmd_previous_next[2];
	t_io_handler	io;
	int				i;

	cmd_pipe_root = command_build_pipe();
	cmd_previous_next[0] = cmd_pipe_root;
	i = 1;
	while (++i < argc - 3)
	{
		cmd_simple = command_build_simple(argv[i], envp);
		cmd_previous_next[1] = command_build_pipe();
		cmd_previous_next[0]->pipe->before = cmd_simple;
		cmd_previous_next[0]->pipe->after = cmd_previous_next[1];
		cmd_previous_next[0] = cmd_previous_next[1];
	}
	cmd_previous_next[0]->pipe->before = command_build_simple(argv[i++], envp);
	cmd_previous_next[0]->pipe->after = command_build_simple(argv[i++], envp);
	command_build_set_io(&io, argv[1], O_RDONLY);
	command_set_input(cmd_pipe_root, &io);
	command_build_set_io(&io, argv[i], O_CREAT | O_WRONLY | O_TRUNC);
	command_set_output(cmd_pipe_root, &io);
	return (cmd_pipe_root);
}
