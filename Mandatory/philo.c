/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 18:58:54 by hchadili          #+#    #+#             */
/*   Updated: 2024/04/09 03:55:45 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char *argv[])
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 4)
		return (0);
	while (argv[i])
	{
		// if (is_num(argv[i]))
		// 	return(0);
		printf("%d\n",is_num(argv[i]));
		i++;
	}
	return (0);
}

