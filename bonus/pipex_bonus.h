/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:19:10 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/11 00:26:42 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# define STDIN  0
# define STDOUT 1
# define STDERR 2
# define EXIT_OK 0
# define EXIT_PIPE_FAIL 10
# define EXIT_FORK_FAIL 20
# define EXIT_MALLOC_FAIL 30

typedef enum e_io_handler_type
{
	NONE,
	FD,
	PATH,
	ERROR
}	t_io_handler_type;

typedef struct s_io_handler
{
	t_io_handler_type	type;
	union
	{
		int		fd;
		struct
		{
			char	*path;
			int		flags;
			int		mode;
		};
		struct
		{
			int		error_status;
			char	*error;
		};
	};
}	t_io_handler;

typedef struct s_command_simple
{
	char	*cmd_path;
	char	**cmd_argv;
	char	**cmd_envp;
}	t_command_simple;

typedef struct s_command	*t_command;

typedef struct s_command_pipe
{
	t_command	before;
	t_command	after;
}	t_command_pipe;

typedef enum e_command_type
{
	SIMPLE,
	PIPE
}	t_command_type;

struct s_command
{
	t_command_type	type;
	t_io_handler	input;
	t_io_handler	output;
	t_io_handler	close;
	union
	{
		t_command_simple	*simple;
		t_command_pipe		*pipe;
	};
};

#endif
