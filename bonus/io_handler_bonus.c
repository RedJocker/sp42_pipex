/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_handler_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:19:08 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/15 20:08:50 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include "io_handler_bonus.h"
#include "ft_stdio.h"

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

void	io_handle_heredoc_to_fd(t_io_handler *io_handle)
{
	int		fd;

	if (io_handle->type != HEREDOC)
		return ;
	fd = open("/tmp/heredoc", O_RDWR | O_CREAT, 0666);
	if (fd < 0)
	{
		io_handle->type = ERROR;
		io_handle->error_status = errno;
		io_handle->error = "here_doc";
		return ;
	}
	ft_putendl_fd("from here doc", fd);
	io_handle_set_fd(io_handle, fd);
}

void	io_handle_to_fd(t_io_handler *io_handle)
{
	if (io_handle->type == HEREDOC)
		io_handle_heredoc_to_fd(io_handle);
	else if (io_handle->type == PATH)
		io_handle_path_to_fd(io_handle);
}
