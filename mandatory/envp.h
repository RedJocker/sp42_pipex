/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:35:23 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/09 18:34:30 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

# include "pipex.h"
# define SPACE_CHARS " \r\n\t\v\f"

char	*envp_find_bin_by_name(char *name, char **envp);
#endif
