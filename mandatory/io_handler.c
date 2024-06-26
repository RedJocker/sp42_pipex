/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:57:10 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/09 19:08:28 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include "io_handler.h"

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
