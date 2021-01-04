/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 02:58:37 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/04 19:21:36 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, size_t len)
{
	char	*result;

	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	if (len)
		ft_memcpy(result, str, sizeof(char) * len);
	return (result);
}
