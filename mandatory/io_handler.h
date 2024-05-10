/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_handler.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:58:30 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/09 19:00:29 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_HANDLER_H
# define IO_HANDLER_H

# include "pipex.h"

void	io_handle_set_fd(t_io_handler *io_handle, int fd);
void	io_handle_path_to_fd(t_io_handler *io_handle);

#endif
