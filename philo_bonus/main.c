/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:50:44 by hchadili          #+#    #+#             */
/*   Updated: 2024/11/14 21:22:42 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd >= 0)
		write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	x;

	x = 0;
	if (!s)
		return ;
	if (fd >= 0)
	{
		while (s[x])
			ft_putchar_fd(s[x++], fd);
	}
}

void	ft_print_error(char *str)
{
	ft_putstr_fd(str, 2);
}

int	main(int argc, char const *argv[])
{
	sem_t		*forks;
	t_program	monitor;

	if (check_for_error(argv, argc))
		return (1);
	forks = NULL;
	ft_set_value_for_monitor(&monitor, argv, argc, forks);
	forks = sem_open("/fork", O_CREAT, 0644, monitor.num_philo);
	monitor.write = sem_open("/write", O_CREAT, 0644, 1);
	monitor.var_sem = sem_open("/var_sem", O_CREAT, 0644, 1);
	monitor.start_sem = sem_open("/start_sem", O_CREAT, 0644, 1);
	if (forks == SEM_FAILED || monitor.write == SEM_FAILED
		|| monitor.var_sem == SEM_FAILED || monitor.start_sem == SEM_FAILED)
	{
		ft_print_error("sem_open failed\n");
		free(monitor.philos);
		exit(1);
	}
	ft_creat_philos(&monitor, forks);
	ft_wait_for_philo(&monitor);
	ft_clear_sema(forks, &monitor);
	free(monitor.philos);
	return (0);
}
