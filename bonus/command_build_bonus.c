/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_build_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:12:24 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/15 20:09:16 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_bonus.h"
#include "command_build_util_bonus.h"
#include "ft_string.h"
#include <fcntl.h>

t_command	command_build_heredoc(const int argc, char *argv[], char *envp[])
{
	t_command		cmd_simple;
	t_command		cmd_pipe_root;	
	t_command		cmd_previous_next[2];
	t_io_handler	io;
	int				i;

	cmd_pipe_root = command_build_pipe();
	cmd_previous_next[0] = cmd_pipe_root;
	i = 2;
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
	io.type = HEREDOC;
	io.heredoc_limiter = argv[2];
	command_set_input(cmd_pipe_root, &io);
	command_build_set_io(&io, argv[i], O_CREAT | O_WRONLY | O_APPEND);
	command_set_output(cmd_pipe_root, &io);
	return (cmd_pipe_root);
}

t_command	command_build_normal(const int argc, char *argv[], char *envp[])
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

t_command	command_build(const int argc, char *argv[], char *envp[])
{
	if (ft_strncmp("here_doc", argv[1], 9) == 0)
		return (command_build_heredoc(argc, argv, envp));
	else
		return (command_build_normal(argc, argv, envp));
}
