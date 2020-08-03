/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 12:31:24 by gboucett          #+#    #+#             */
/*   Updated: 2020/07/25 12:49:37 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_arr(char **arr, char sep)
{
	char	*result;
	char	*tmp;

	if (!arr || !*arr)
		return (0);
	result = ft_strdup(arr[0]);
	arr++;
	while (*arr)
	{
		tmp = result;
		result = ft_strjoin(result, &sep);
		free(tmp);
		tmp = result;
		result = ft_strjoin(result, *arr);
		free(tmp);
		arr++;
	}
	return (result);
}
