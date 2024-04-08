/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:34:19 by maurodri          #+#    #+#             */
/*   Updated: 2024/04/08 13:20:07 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include <fcntl.h>
#include <unistd.h>

int	main(void)
{
	//pid_t pid;
	
	/* pid = fork(); */
	/* if (pid == 0) */
	/* 	ft_printf("hello child pid=%d\n", pid); */
	/* else */
	/* 	ft_printf("hello parent child_pid=%d\n", pid); */
	/* dup2() */
	
	int fd = open("test.txt", O_CREAT | O_RDWR, 0666);
	ft_printf("fd=%d\n", fd);
	dup2(fd, 1); // closes current 1 and make 1 point to fd,
	             // both fd and 1 will point to same file descriptor  
	ft_printf("fd=%d\n", fd);
	write(fd, "heyfd\n", 6);
	write(1, "hey1\n", 5);

	/////////
	int fds[2]; //fds[0] read, fds[1] write
	pipe(fds);

	write(fds[1], "hola\n", 5);
	char out[10];
	read(fds[0], out, 5);
	ft_printf("out=%s\n", out);
	return (0);
}
