/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 01:21:59 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/01 01:28:30 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

void	ft_print_error_exec(char *pathname)
{
	ft_printf("%s: %s: %s\n", program_invocation_short_name, pathname,
		strerror(errno));
}
