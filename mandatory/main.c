/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:34:19 by maurodri          #+#    #+#             */
/*   Updated: 2024/04/23 23:50:24 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "ft_memlib.h"
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

void cmd_after(char *cmd,  char *argv[], char *envp[])
{
	execve(cmd, argv, envp);
}

void cmd_before(char *cmd, char *argv[], char *envp[])
{
 	execve(cmd, argv, envp);
}

int is_child(pid_t pid)
{
	return (pid == 0);
}

typedef enum e_io_handler_type
{
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
	t_io_handler	input;
	t_io_handler	output;
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
	union
	{
		t_command_simple	*simple;
		t_command_pipe		*pipe;
	};
};

int	main(const int argc, char* argv[], char *envp[])
{
	(void) argc;
	(void) argv;

	pid_t	pid[2];
	int		fds[4]; //fds[0] read, fds[1] write

	char	*fileIn = "input.txt";
	char	*fileOut = "output.txt";
	char	*cmd0 = "/usr/bin/ls";
	char	*command0[] = {"ls" , "-a", 0};
	char	*cmd1 = "/usr/bin/wc";
	char	*command1[] = {"wc", 0};
	
	if (pipe(fds) < 0)
		return (EXIT_PIPE_FAIL);
	pid[0] = fork();
	if (pid[0] < 0)
		return (EXIT_FORK_FAIL);
	if(is_child(pid[0]))
	{
		dup2(fds[1], STDOUT); // out no pipe
		close(fds[0]);
		close(fds[1]);
		fds[3] = open(fileIn, O_RDONLY);
		dup2(fds[3], STDIN); // in do arquivo
		close(fds[3]);
		cmd_before(cmd0, command0, envp);
		return (0);
	}
	pid[1] = fork();
	if (pid[1] < 0)
		return (EXIT_FORK_FAIL);
	if (is_child(pid[1]))
	{
		dup2(fds[0], STDIN); // in do pipe
		fds[2] = open(fileOut, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		dup2(fds[2], STDOUT); // out no arquivo fileOut
		close(fds[2]);
		close(fds[1]);
		close(fds[0]);
		cmd_after(cmd1, command1, envp);
		return (0);
	}
	
	close(fds[0]);
	close(fds[1]);
	close(STDIN);
	close(STDOUT);
	close(STDERR);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	return (0);
}
