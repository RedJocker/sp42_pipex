/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:34:19 by maurodri          #+#    #+#             */
/*   Updated: 2024/04/16 20:54:42 by maurodri         ###   ########.fr       */
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
#define EXIT_OK 0
#define EXIT_PIPE_FAIL 1
#define EXIT_FORK_FAIL 2

void child_0()
{
	char	str[100];
	
	ft_bzero(str, 100);
	read(STDIN, str, 16);
	ft_printf("child0 afer dup2\nmessage: %s\n", str);
}

void child_1()
{
	ft_printf("child1 afer dup2");
}

int is_child(pid_t pid)
{
	return (pid == 0);
}

int	main(int argc, char* argv[])
{
	(void) argc;
	(void) argv;

	pid_t	pid[2];
	int		fds[2]; //fds[0] read, fds[1] write

	//char	*fileIn = argv[1];
	//char	*fileOut = argv[2];
	//char	*command0 = argv[3];
	//char	*command1 = argv[4];
	
	if (pipe(fds) < 0)
		return (EXIT_PIPE_FAIL);
	pid[0] = fork();
	if (pid[0] < 0)
		return (EXIT_FORK_FAIL);
	if (is_child(pid[0]))
	{
		dup2(fds[0], STDIN);
		close(fds[1]);
		child_0();
		return (0);
	}
	pid[1] = fork();
	if (pid[1] < 0)
		return (EXIT_FORK_FAIL);
	if(is_child(pid[1]))
	{
		dup2(fds[1], STDOUT);
		close(fds[0]);
		child_1();
		return (0);
	}
	close(fds[0]);
	close(fds[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	return (0);
}
