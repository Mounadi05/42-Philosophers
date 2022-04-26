/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 03:28:35 by amounadi          #+#    #+#             */
/*   Updated: 2022/04/26 01:37:03 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MAX_POS 2147483647

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <time.h>
# include <pthread.h>
# include <semaphore.h>      
# include <signal.h>

typedef struct s_var
{
	int					nbp;
	int					ttd;
	int					tte;
	int					tts;
	int					nte;
	int					lock;
	long long unsigned	time;
	long long unsigned	t;
	int					is_alive;
	sem_t				*print;
}t_var;

typedef struct s_philo
{
	pthread_t		p;
	sem_t			*fork;
	int				ttd;
	int				ip;
	int				e;
	t_var			*table;
	pid_t			pid;
	struct s_philo	*next;

}t_philo;

void				delete_philo(t_philo *philo);
long long unsigned	ft_time(t_philo *philo);
int					ft_check(t_philo *philo);
void				ft_sleep(int time, t_philo *philo);
void				*ft_routine(void *var);
void				ft_routine_plus(t_philo *philo);
int					print_message(t_philo *philo, int a);
t_philo				*ft_lstnew(int i, t_var *table, int a);
t_philo				*ft_lstlast(t_philo *lst);
void				ft_lstadd_back(t_philo **lst, t_philo *new);
int					ft_atoi(char *str);
#endif
