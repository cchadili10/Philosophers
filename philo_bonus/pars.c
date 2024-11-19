/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:37:54 by hchadili          #+#    #+#             */
/*   Updated: 2024/11/04 19:07:56 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_check_input(char const *str)
{
	int	x;

	x = 0;
	if (!str[x])
		return (1);
	if (str[x] == '+')
	{
		if (!str[x + 1])
			return (1);
		x++;
	}
	while (str[x])
	{
		if (str[x] >= '0' && str[x] <= '9')
			x++;
		else
			return (1);
	}
	return (0);
}

int	check_for_error(char const **str, int argc)
{
	int	x;

	x = 1;
	if (argc != 6 && argc != 5)
	{
		ft_print_error("put valid argument\n");
		return (1);
	}
	while (str[x])
	{
		if (ft_check_input(str[x]))
		{
			ft_print_error("put valid argument\n");
			return (1);
		}
		x++;
	}
	return (0);
}
