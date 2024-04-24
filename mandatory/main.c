/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:34:19 by maurodri          #+#    #+#             */
/*   Updated: 2024/04/24 20:41:27 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collection/ft_arraylist.h"
#include "ft_stdio.h"
#include "ft_memlib.h"
#include "ft_string.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define STDIN  0
#define STDOUT 1
#define STDERR 2
#define EXIT_OK 0
#define EXIT_PIPE_FAIL 1
#define EXIT_FORK_FAIL 2
#define EXIT_MALLOC_FAIL 3

int is_child(pid_t pid)
{
	return (pid == 0);
}

typedef enum e_io_handler_type
{
	NONE,
	FD,
	PATH
}	t_io_handler_type;

typedef struct s_io_handler
{
	t_io_handler_type	type;
	union
	{
		char	*path;
		int		fd;
	};
} 	t_io_handler;

typedef struct s_command_simple
{
	char		   	*cmd_path;
	char		   	**cmd_argv;
	char			**cmd_envp;
}	t_command_simple;

typedef struct s_command *t_command;

typedef struct s_command_pipe
{
	t_command 	before;
	t_command	after;
}	t_command_pipe;

typedef enum e_command_type
{
	SIMPLE,
	PIPE
}	t_command_type;

struct s_command
{
	t_command_type type;
	t_io_handler	input;
	t_io_handler	output;
	t_io_handler	close;
	union
	{
		t_command_simple	*simple;
		t_command_pipe		*pipe;
	};
};


t_command command_simple_new(char *command,  char **argv, char **envp)
{
	t_command	cmd;

	cmd = ft_calloc(1, sizeof(struct s_command));
	cmd->type = SIMPLE;
	cmd->simple = ft_calloc(1, sizeof(struct s_command_simple));
	cmd->simple->cmd_path = command;
	cmd->simple->cmd_argv = argv;
	cmd->simple->cmd_envp = envp;
	cmd->input.type = NONE;
	cmd->output.type = NONE;
	cmd->close.type = NONE;
	return cmd;
}

t_command command_pipe_new()
{
	t_command	cmd;

	cmd = ft_calloc(1, sizeof(struct s_command));
	cmd->type = PIPE;
	cmd->pipe = ft_calloc(1, sizeof(struct s_command_pipe));
	cmd->input.type = NONE;
	cmd->output.type = NONE;
	cmd->close.type = NONE;
	return cmd;
}

void	free_strarr_null_term(char **arr)
{
	int i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void io_handle_path_to_fd(t_io_handler *io_handle, int flags, mode_t mode)
{
	int	fd;
	if (io_handle->type != PATH)
		return;
	fd = open(io_handle->path, flags, mode);
	io_handle->type = FD;
	io_handle->fd = fd;
}

void command_execute(t_command cmd, t_arraylist pids);

void command_simple_execute(t_command cmd, t_arraylist pids)
{
	pid_t	*pid;

	if (cmd->type != SIMPLE)
		return ;
	pid = malloc(sizeof(pid_t));
	*pid = fork();
	if (pid < 0)
		exit(EXIT_FORK_FAIL);
	if (is_child(*pid))
	{
		
		if (cmd->input.type == PATH)
			io_handle_path_to_fd(&cmd->input, O_RDONLY, 0666);
		if (cmd->output.type == PATH)
			io_handle_path_to_fd(
				&cmd->output, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		if (cmd->close.type == FD)
			close(cmd->close.fd);
		dup2(cmd->output.fd, STDOUT);
		close(cmd->output.fd);
		dup2(cmd->input.fd, STDIN);
		close(cmd->input.fd);
		execve(cmd->simple->cmd_path, cmd->simple->cmd_argv, cmd->simple->cmd_envp);
	}
	else 
	{
		pids = ft_arraylist_add(pids, pid);
		if (!pids)
			exit(EXIT_MALLOC_FAIL);
	}
}

void command_pipe_execute(t_command cmd, t_arraylist pids)
{
	int		fd_pipe[2]; //fds[0] read, fds[1] write

	if (cmd->type != PIPE)
		return ;
	if (pipe(fd_pipe) < 0)
		exit(EXIT_PIPE_FAIL);
	if (cmd->input.type == FD)
	{
		cmd->pipe->before->input.type = FD;
		cmd->pipe->before->input.fd = cmd->input.fd;	
	}

	cmd->pipe->before->close.type = FD;
	cmd->pipe->before->close.fd = fd_pipe[0];
	cmd->pipe->before->output.type = FD;
	cmd->pipe->before->output.fd = fd_pipe[1];
	command_execute(cmd->pipe->before, pids);

	cmd->pipe->after->close.type = FD;
	cmd->pipe->after->close.fd = fd_pipe[1];
	cmd->pipe->after->input.type = FD;
	cmd->pipe->after->input.fd = fd_pipe[0];
	command_execute(cmd->pipe->after, pids);

	close(fd_pipe[0]);
	close(fd_pipe[1]);
}

void command_execute(t_command cmd, t_arraylist pids)
{
	if (cmd->type == SIMPLE)
		command_simple_execute(cmd, pids);
	else if (cmd->type == PIPE)
		command_pipe_execute(cmd, pids);
}

int	main(const int argc, char* argv[], char *envp[])
{
    char 	**command0 = ft_split(argv[2], ' ');
	char	*cmd0 = command0[0];
	char	**command1 = ft_split(argv[3], ' ');
	char	 *cmd1 = command1[0];
	t_arraylist	pids;

	pids = ft_arraylist_new(free);
	t_command tcmd0 = command_simple_new(cmd0, command0, envp);
	tcmd0->input.type = PATH;
	tcmd0->input.path = argv[1];
	t_command tcmd1 = command_simple_new(cmd1, command1, envp);
	tcmd1->output.type = PATH;
	tcmd1->output.path = argv[4];

	t_command cmd_pipe = command_pipe_new();
	cmd_pipe->pipe->before = tcmd0;
	cmd_pipe->pipe->after = tcmd1;
	
	command_execute(cmd_pipe, pids);
	
	close(STDIN);
	close(STDOUT);
	close(STDERR);

	int len = ft_arraylist_len(pids);
	while (len--)
		waitpid(*((pid_t *)ft_arraylist_get(pids, len)), 0, 0);
	free_strarr_null_term(command0);
	free_strarr_null_term(command1);
	ft_arraylist_destroy(pids);
	return (0);
}
