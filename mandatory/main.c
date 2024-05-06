/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:34:19 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/06 20:01:23 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collection/ft_arraylist.h"
#include "ft_stdio.h"
#include "ft_memlib.h"
#include "ft_string.h"
#include <asm-generic/errno-base.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define STDIN  0
#define STDOUT 1
#define STDERR 2
#define EXIT_OK 0
#define EXIT_PIPE_FAIL 10
#define EXIT_FORK_FAIL 20
#define EXIT_MALLOC_FAIL 30

int	is_child(pid_t pid)
{
	return (pid == 0);
}

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
		char	*path;
		int		fd;
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

char	*envp_find_bin_by_name(char *name, char **envp);

void	free_strarr_null_term(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

t_command	command_simple_new(char *command, char **argv, char **envp)
{
	t_command	cmd;

	cmd = ft_calloc(1, sizeof(struct s_command));
	cmd->type = SIMPLE;
	cmd->simple = ft_calloc(1, sizeof(struct s_command_simple));
	cmd->simple->cmd_path = envp_find_bin_by_name(command, envp);
	cmd->simple->cmd_argv = argv;
	cmd->simple->cmd_envp = envp;
	cmd->input.type = NONE;
	cmd->output.type = NONE;
	cmd->close.type = NONE;
	return (cmd);
}

void	command_simple_destroy(t_command_simple *cmd)
{
	free(cmd->cmd_path);
	free_strarr_null_term(cmd->cmd_argv);
	free(cmd);
}

void	command_destroy(t_command cmd);

void	command_pipe_destroy(t_command_pipe *cmd)
{
	command_destroy(cmd->before);
	command_destroy(cmd->after);
	free(cmd);
}

void	command_destroy(t_command cmd)
{
	if (cmd->type == PIPE)
		command_pipe_destroy(cmd->pipe);
	else if (cmd->type == SIMPLE)
		command_simple_destroy(cmd->simple);
	free(cmd);
}

t_command	command_pipe_new(void)
{
	t_command	cmd;

	cmd = ft_calloc(1, sizeof(struct s_command));
	cmd->type = PIPE;
	cmd->pipe = ft_calloc(1, sizeof(struct s_command_pipe));
	cmd->input.type = NONE;
	cmd->output.type = NONE;
	cmd->close.type = NONE;
	return (cmd);
}

static int	envp_is_path(char *maybe_path)
{
	return (ft_strncmp("PATH=", maybe_path, 5) == 0);
}

// path + 5 -> after PATH=
static char	**envp_path_arr(char *path)
{
	return (ft_split(path + 5, ':'));
}

char	**envp_get_path_arr(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (envp_is_path(envp[i]))
			return (envp_path_arr(envp[i]));
	}
	return (0);
}

char	*envp_find_bin_by_name(char *name, char **envp)
{
	char	*bin;
	char	**path_arr;
	int		i;
	char	*slash_name;
	
	if (access(name, X_OK) == 0 || name[0] == '\0')
		return (ft_strdup(name));
	slash_name = ft_strjoin("/", name);
	path_arr = envp_get_path_arr(envp);
	i = -1;
	while (path_arr[++i])
	{
		bin = ft_strjoin(path_arr[i], slash_name);
		if (access(bin, X_OK) == 0)
			break ;
		free(bin);
		bin = NULL;
	}
	free_strarr_null_term(path_arr);
	free(slash_name);
	if (!bin)
		return (ft_strdup(name));
	else
		return (bin);
}

void	io_handle_set_fd(t_io_handler *io_handle, int fd)
{
	io_handle->type = FD;
	io_handle->fd = fd;
}

void	io_handle_path_to_fd(t_io_handler *io_handle, int flags, mode_t mode)
{
	int		fd;
	char	*path;

	if (io_handle->type != PATH)
		return ;
	path = io_handle->path;
	fd = open(path, flags, mode);
	if (fd < 0)
	{
		io_handle->type = ERROR;
		io_handle->error_status = errno;
		io_handle->error = path;
		return ;
	}
	io_handle_set_fd(io_handle, fd);
}

void	log_error(char *path, char *msg)
{
	ft_putstr_fd(path, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putendl_fd(msg, STDERR);
}
int		command_execute(t_command cmd, t_arraylist *pids);

static int command_simple_log_error(t_command cmd, int err_num)
{
	int fd;

	if (err_num == ENOENT)
	{
		log_error(cmd->simple->cmd_path, strerror(err_num));
		return (127);
	}
	else if (err_num == EACCES)
	{
		fd = open(cmd->simple->cmd_argv[0], O_DIRECTORY, 0777);
		
		if (fd >= 0)
		{
			close(fd);
			if (ft_strchr(cmd->simple->cmd_argv[0], '/'))
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
		ft_putendl_fd("+++++", 2);
		return (126);
	}
	log_error(cmd->simple->cmd_path, strerror(err_num));
	return (err_num);
}

int	command_simple_to_execve(t_command cmd)
{
	int err_num;

	if (cmd->input.type == ERROR)
	{
		log_error(cmd->input.error, strerror(cmd->input.error_status));
		return (1);
	}
	else if (cmd->output.type == ERROR)
	{
		log_error(cmd->output.error, strerror(cmd->output.error_status));
		return (1);
	}
	dup2(cmd->output.fd, STDOUT);
	close(cmd->output.fd);
	dup2(cmd->input.fd, STDIN);
	close(cmd->input.fd);
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
		io_handle_path_to_fd(&cmd->input, O_RDONLY, 0666);
		io_handle_path_to_fd(
			&cmd->output, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		if (cmd->close.type == FD)
			close(cmd->close.fd);
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

//fds[0] read, fds[1] write
int	command_pipe_execute(t_command cmd, t_arraylist *pids)
{
	int	fd_pipe[2];
	int	status;

	if (cmd->type != PIPE)
		return (0);
	if (pipe(fd_pipe) < 0)
		exit(EXIT_PIPE_FAIL);
	if (cmd->input.type == FD)
		io_handle_set_fd(&cmd->pipe->before->input, cmd->input.fd);
	io_handle_set_fd(&cmd->pipe->before->close, fd_pipe[0]);
	io_handle_set_fd(&cmd->pipe->before->output, fd_pipe[1]);
	status = command_execute(cmd->pipe->before, pids);
	if (status != 0)
		return (status);
	io_handle_set_fd(&cmd->pipe->after->close, fd_pipe[1]);
	io_handle_set_fd(&cmd->pipe->after->input, fd_pipe[0]);
	status = command_execute(cmd->pipe->after, pids);
	if (status != 0)
		return (status);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	return (EXIT_OK);
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

	command0 = ft_split(argv[2], ' ');
	command1 = ft_split(argv[3], ' ');
	tcmd0 = command_simple_new(command0[0], command0, envp);
	tcmd0->input.type = PATH;
	tcmd0->input.path = argv[1];
	tcmd1 = command_simple_new(command1[0], command1, envp);
	tcmd1->output.type = PATH;
	tcmd1->output.path = argv[4];
	cmd_pipe = command_pipe_new();
	cmd_pipe->pipe->before = tcmd0;
	cmd_pipe->pipe->after = tcmd1;
	return (cmd_pipe);
}

int	child_check_exit_status(int status)
{
	return (((status) & 0xff00) >> 8);
}

int	main(const int argc, char *argv[], char *envp[])
{
	t_arraylist	pids;
	t_command	cmd;
	int			len;
	int			i;
	int			status[2];

	pids = ft_arraylist_new(free);
	cmd = command_build(argc, argv, envp);
	status[1] = command_execute(cmd, &pids);
	close(STDIN);
	close(STDOUT);
	close(STDERR);
	len = ft_arraylist_len(pids);
	i = -1;
	while (++i < len - 1)
		waitpid(*((pid_t *) ft_arraylist_get(pids, i)), 0, 0);
	if (len > 0)
		waitpid(*((pid_t *)ft_arraylist_get(pids, i)), status, 0);
	command_destroy(cmd);
	ft_arraylist_destroy(pids);
	if (status[1] != EXIT_OK)
		return (status[1]);
	return (child_check_exit_status(status[0]));
}
