/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 03:28:28 by amounadi          #+#    #+#             */
/*   Updated: 2022/03/20 04:54:00 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	create_philo(t_philo *philo)
{
	int i;

	i = -1;

	pthread_mutex_init(&philo->table->print, NULL);
	while(++i < philo->table->nbp)
	{
		pthread_mutex_init(&philo->fork, NULL);
		philo = philo->next;
	}
	i = -1;
    struct timeval t;
    gettimeofday(&t,NULL);
	philo->table->t = (t.tv_usec / 1000) + (t.tv_sec * 1000);
	while(++i < philo->table->nbp)
	{
		philo->is_alive = 1;
		philo->ttd = philo->table->ttd;
		pthread_create(&(philo->p), NULL, ft_routine, (void *)philo);
		philo = philo->next;
		if (philo->table->nbp <= 3)
			usleep(60);
		else
			usleep(100);
	}
	i = -1;
	while(++i < philo->table->nbp)
	{
		pthread_join(philo->p, NULL);
		philo = philo->next;
	}
	i = -1;
	while(++i < philo->table->nbp)
	{
		pthread_mutex_destroy(&philo->fork);
		philo = philo->next;
	}
	pthread_mutex_destroy(&philo->table->print);
}

int main (int ac, char **av)
{
	int i;
	t_philo *philo;

	i = 0;
	if (ac != 6 && ac != 5)
		write(2, "Error in argument\n", 18);
	else
	{
		while(++i < ac)
		{
			if (ac == 6)
				if (ft_atoi(av[5]) == 0)
					return (0);
			if (ft_atoi(av[i]) == -1)
			{
				write(2, "Error in argument\n", 18);
				return (0);
			}
		}
		i = 0;
		philo = (t_philo*)malloc(sizeof(t_philo));
		philo->table = (t_var *)malloc(sizeof(t_var));
		philo->table->nbp = ft_atoi(av[1]);
		philo->table->ttd = ft_atoi(av[2]);
		philo->table->tte = ft_atoi(av[3]);
		philo->table->tts = ft_atoi(av[4]);
		philo->table->lock = 1;
		if (ac == 6)
			philo->table->nte = ft_atoi(av[5]);
		else
			philo->table->nte = -1;
		philo = ft_lstnew(1, philo->table, philo->table->nte);
		while (++i < philo->table->nbp)
			ft_lstadd_back(&philo, ft_lstnew(i + 1, philo->table, philo->table->nte));
		ft_lstlast(philo)->next = philo;
		create_philo(philo);
	}
}
