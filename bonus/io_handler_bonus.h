/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_handler_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:19:08 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/14 18:21:29 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_HANDLER_BONUS_H
# define IO_HANDLER_BONUS_H

# include "pipex_bonus.h"

void	io_handle_set_fd(t_io_handler *io_handle, int fd);
void	io_handle_path_to_fd(t_io_handler *io_handle);

#endif
