/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 02:41:35 by amounadi          #+#    #+#             */
/*   Updated: 2022/03/19 03:52:00 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message_plus(t_philo *philo, int a)
{
	if (a == 3 && philo->table->lock)
	{
		pthread_mutex_lock(&philo->table->print);
		printf("%llu ms : philo %d is sleeping\n", ft_time(philo), philo->ip);
		pthread_mutex_unlock(&philo->table->print);
	}
	else if (a == 4 && philo->table->lock)
	{
		pthread_mutex_lock(&philo->table->print);
		printf("%llu ms : philo %d is thinking\n", ft_time(philo), philo->ip);
		pthread_mutex_unlock(&philo->table->print);
	}
}

void	print_message(t_philo *philo, int a)
{
	if (a == 0 && philo->table->lock)
	{	
		pthread_mutex_lock(&philo->table->print);
		printf("%llu ms : philo %d  has taken a fork %d\n",
			ft_time(philo), philo->ip, philo->ip);
		pthread_mutex_unlock(&philo->table->print);
	}
	else if (a == 1 && philo->table->lock)
	{
		pthread_mutex_lock(&philo->table->print);
		printf("%llu ms : philo %d  has taken a fork %d\n",
			ft_time(philo), philo->ip, philo->next->ip);
		pthread_mutex_unlock(&philo->table->print);
	}
	else if (a == 2 && philo->table->lock)
	{
		pthread_mutex_lock(&philo->table->print);
		printf("%llu ms : philo %d is eating\n", ft_time(philo), philo->ip);
		pthread_mutex_unlock(&philo->table->print);
	}
	else
		print_message_plus(philo, a);
}

void	ft_routine_plus(t_philo *philo)
{
	print_message(philo, 1);
	print_message(philo, 2);
	ft_sleep(philo->table->tte);
	pthread_mutex_unlock(&philo->fork);
	philo->e--;
	pthread_mutex_unlock(&philo->next->fork);
	if (philo->table->tte > philo->table->ttd)
	{
		usleep(30);
		return ;
	}
	print_message(philo, 3);
	ft_sleep(philo->table->tts);
	print_message(philo, 4);
	philo->ttd = ft_time(philo) +  philo->table->ttd
		- philo->table->tts - philo->table->tte;
}

void	*ft_routine(void *var)
{
	t_philo *philo;

	philo = (t_philo *)var;
	while (philo->e && philo->is_alive)
	{
		pthread_mutex_lock(&philo->fork);
		if (ft_check(philo))
		{
			pthread_mutex_unlock(&philo->fork);
			return (0);
		}
		print_message(philo, 0);
		if (ft_check(philo))
		{
			pthread_mutex_unlock(&philo->fork);
			return (0);
		}
		pthread_mutex_lock(&philo->next->fork);
		if (ft_check(philo))
		{
			pthread_mutex_unlock(&philo->fork);
			pthread_mutex_unlock(&philo->next->fork);
			return (0);
		}
		ft_routine_plus(philo);
	}
	return (0);
}
