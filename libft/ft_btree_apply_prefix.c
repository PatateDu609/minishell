/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_apply_prefix.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 17:28:37 by gboucett          #+#    #+#             */
/*   Updated: 2020/07/07 18:25:37 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_btree_apply_prefix(t_btree *root, void (*f)(void *))
{
	if (!root || !f)
		return ;
	f(root->item);
	ft_btree_apply_prefix(root->left, f);
	ft_btree_apply_prefix(root->right, f);
}

void disp(void *c)
{
	printf("%c ", ft_toupper(*((char *)c)));
}

int main()
{
	t_btree *root = ft_btree_create_node("f");
	root->left = ft_btree_create_node("b");
	root->left->left = ft_btree_create_node("a");
	root->left->right = ft_btree_create_node("d");
	root->left->right->left = ft_btree_create_node("c");
	root->left->right->right = ft_btree_create_node("e");
	root->right = ft_btree_create_node("g");
	root->right->right = ft_btree_create_node("i");
	root->right->right->left = ft_btree_create_node("h");

	printf("prefix\n");
	ft_btree_apply_prefix(root, disp);
	printf("\ninfix\n");
	ft_btree_apply_infix(root, disp);
	printf("\nsuffix\n");
	ft_btree_apply_suffix(root, disp);
	printf("\n");
	return 0;
}
