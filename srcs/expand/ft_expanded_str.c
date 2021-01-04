/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expanded_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 02:20:43 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/04 19:20:55 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expand.h"

char	*ft_expanded_str(t_list *lst)
{
	char		*result;
	char		*tmp;
	t_expansion	*expanded;

	result = ft_calloc(1, sizeof(char));
	while (lst)
	{
		expanded = (t_expansion *)lst->content;
		tmp = result;
		result = ft_strjoin(result, expanded->str);
		free(tmp);
		lst = lst->next;
	}
	return (result);
}
