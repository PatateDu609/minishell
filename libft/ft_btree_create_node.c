/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_create_node.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 17:22:37 by gboucett          #+#    #+#             */
/*   Updated: 2020/07/07 17:27:25 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_btree		*ft_btree_create_node(void *item)
{
	t_btree		*node;

	if (!item)
		return (NULL);
	if (!(node = (t_btree *)ft_calloc(1, sizeof(t_btree))))
		return (NULL);
	node->item = item;
	return (node);
}
