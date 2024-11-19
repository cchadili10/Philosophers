/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:40:07 by hchadili          #+#    #+#             */
/*   Updated: 2024/11/14 21:22:56 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_clear_all(t_program *pro)
{
	ft_destroy(pro, pro->num_philo, 4);
	pthread_mutex_destroy(&pro->start_sem);
	free(pro->philos);
	free(pro->fork);
}

void	ft_check_error(int res)
{
	if (res == 1)
		ft_print_error("put valid argument\n");
	else
		ft_print_error("erorr\n");
}

int	main(int argc, char const *argv[])
{
	t_program	pro;
	int			x;
	int			res;

	x = -1;
	if (check_for_error(argv, argc))
		return (1);
	res = set_value((char **)argv, &pro, argc);
	if (res)
		return (ft_check_error(res), 2);
	x = -1;
	pthread_create(&pro.prog, NULL, ft_monitor, &pro);
	pthread_mutex_lock(&pro.start_sem);
	while (++x < pro.num_philo)
		pthread_create(&(pro.philos[x].thread),
			NULL, ft_routing, &pro.philos[x]);
	x = -1;
	pthread_mutex_unlock(&pro.start_sem);
	pthread_join(pro.prog, NULL);
	while (++x < pro.num_philo)
		pthread_join((pro.philos[x].thread), NULL);
	ft_clear_all(&pro);
	return (0);
}
