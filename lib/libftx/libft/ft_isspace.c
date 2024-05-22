/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 08:13:11 by maurodri          #+#    #+#             */
/*   Updated: 2024/02/06 08:14:24 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(int ch)
{
	return (ch == ' '
		|| ch == '\n'
		|| ch == '\t'
		|| ch == '\r'
		|| ch == '\f'
		|| ch == '\v');
}
