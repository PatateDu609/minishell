/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:45:52 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/09 00:32:46 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_debug.h"

int		g_tree;
int		g_fd;

void	ft_init_debug(void)
{
	g_fd = open("/dev/pts/2", O_RDWR);
	g_tree = open("/dev/pts/3", O_RDWR);
	write(g_fd, "\033c\033[3J", 6);
	write(g_tree, "\033c\033[3J", 6);
}
