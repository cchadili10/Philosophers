/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 20:00:21 by hchadili          #+#    #+#             */
/*   Updated: 2024/11/15 19:03:26 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct s_program	t_program;
typedef struct s_philo		t_philo;
struct s_philo
{
	pid_t				proc;
	size_t				last_meal;
	size_t				start_time;
	int					philo_id;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					how_many_meals;
	int					cont;
	int					done_eat;
	struct s_program	*program;
};

struct s_program
{
	pthread_t		prog;
	sem_t			*write;
	sem_t			*var_sem;
	sem_t			*start_sem;
	int				can_pick_up_fork;
	int				dead_flag;
	size_t			start_time;
	int				how_many_meals;
	int				num_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				done_eat;
	char			sem_name[20];
	char			sem_write[20];
	char			sem_var[20];
	int				status;
	int				cont;
	struct s_philo	*philos;
};

int		check_for_error(char const **str, int argc);
int		ft_usleep(size_t milliseconds);
size_t	get_current_time(void);
size_t	ft_atoi(const char *str);
void	*ft_monitor(void *ptr);
void	ft_print_error(char *str);
void	ft_wait_for_philo(t_program	*monitor);
void	ft_creat_philos(t_program	*monitor, sem_t *forks);
void	ft_set_value_for_pholo(t_program	*monitor, int i);
void	ft_routing(t_program *monitor, t_philo *philo, sem_t *forks);
void	ft_clear_sema(sem_t *forks, t_program *monitor);
void	ft_set_value_for_monitor(t_program	*monitor,
			const char **argv, int argc, sem_t *forks);

#endif