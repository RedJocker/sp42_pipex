/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_handler_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:19:08 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/21 22:12:56 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include "io_handler_bonus.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include "get_next_line.h"

void	io_handle_set_fd(t_io_handler *io_handle, int fd)
{
	io_handle->type = FD;
	io_handle->fd = fd;
}

void	io_handle_path_to_fd(t_io_handler *io_handle)
{
	int		fd;
	char	*path;

	if (io_handle->type != PATH)
		return ;
	path = io_handle->path;
	fd = open(path, io_handle->flags, io_handle->mode);
	if (fd < 0)
	{
		io_handle->type = ERROR;
		io_handle->error_status = errno;
		io_handle->error = path;
		return ;
	}
	io_handle_set_fd(io_handle, fd);
}

static void	io_handle_prompt_heredoc(int fd, const char *limiter)
{
	char	*input;
	int		len_lim;

	len_lim = ft_strlen(limiter);
	while (1)
	{
		ft_putstr_fd("> ", STDOUT);
		input = get_next_line(STDIN);
		if (!input || ft_strncmp(limiter, input, len_lim) == 0)
			break ;
		ft_putstr_fd(input, fd);
		free(input);
	}
	if (input)
		free(input);
}

void	io_handle_heredoc_to_fd(t_io_handler *io_handle)
{
	int		fd;
	char	*limiter;

	if (io_handle->type != HEREDOC)
		return ;
	limiter = io_handle->heredoc_limiter;
	fd = open("/tmp/heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		io_handle->type = ERROR;
		io_handle->error_status = errno;
		io_handle->error = "here_doc";
		return ;
	}
	io_handle_prompt_heredoc(fd, limiter);
	close(fd);
	fd = open("/tmp/heredoc", O_RDONLY, 0666);
	io_handle_set_fd(io_handle, fd);
}

void	io_handle_to_fd(t_io_handler *io_handle)
{
	if (io_handle->type == HEREDOC)
		io_handle_heredoc_to_fd(io_handle);
	else if (io_handle->type == PATH)
		io_handle_path_to_fd(io_handle);
}
