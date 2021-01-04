/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:27:56 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/04 15:28:14 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expand.h"

void	ft_free_expansion(void *expv)
{
	t_expansion		*expansion;

	expansion = (t_expansion *)expv;
	free(expansion->str);
	free(expansion);
}
