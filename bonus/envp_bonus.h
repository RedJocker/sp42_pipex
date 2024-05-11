/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:19:07 by maurodri          #+#    #+#             */
/*   Updated: 2024/05/11 00:26:43 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_BONUS_H
# define ENVP_BONUS_H

# include "pipex_bonus.h"
# define SPACE_CHARS " \r\n\t\v\f"

char	*envp_find_bin_by_name(char *name, char **envp);
#endif
