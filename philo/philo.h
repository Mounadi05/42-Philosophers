/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 03:28:35 by amounadi          #+#    #+#             */
/*   Updated: 2022/03/20 04:29:05 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MAX_POS 2147483647

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>

typedef struct s_var
{
	int					nbp; //number of philosophers
	int					ttd; //time to die 
	int 				tte; //time to eat
	int 				tts; //time to sleep
	int 				nte; // number of eat
	int 				lock;
	long long  unsigned time;
	long long unsigned  t;
	pthread_mutex_t print;
}t_var;

typedef struct s_philo
{
	pthread_t		p;
	pthread_mutex_t fork;
	int 			ttd; //time to die 
	int 			ip;  //id of philosophers
	int 			e;
	t_var			*table;
	int				is_alive;
	struct s_philo *next;

}t_philo;

long long unsigned	ft_time(t_philo *philo);
int					ft_check(t_philo *philo);
void				ft_sleep(int time);
void				*ft_routine(void *var);
void				ft_routine_plus(t_philo *philo);
void				print_message(t_philo * philo, int a);
t_philo				*ft_lstnew(int i, t_var *table, int a);
t_philo				*ft_lstlast(t_philo *lst);
void				ft_lstadd_back(t_philo **lst, t_philo *new);
int					ft_atoi(char *str);

#endif
