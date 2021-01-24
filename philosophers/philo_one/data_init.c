/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emabel <emabel@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 06:58:45 by emabel            #+#    #+#             */
/*   Updated: 2021/01/21 21:08:59 by emabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
** ИНИЦИАЛИЗАЦИЯ ФИЛОСОФОВ
** 	присваиваем переменныем объекта философа начальные значения;
*/

int			init_philosopher(t_data *d)
{
	d->i = 0;
	d->id = 1;
	d->left_fork = 0;
	d->right_fork = 1;
	if (!(d->philos = (t_philosopher *)
				malloc(sizeof(t_philosopher) * d->num_of_phil)))
		return (ERR_MALLOC);
	while (d->i < d->num_of_phil)
	{
		if (d->left_fork == d->num_of_phil - 1)
			d->right_fork = 0;
		d->philos[d->i].id = d->id++;
		d->philos[d->i].left_fork = d->left_fork++;
		d->philos[d->i].right_fork = d->right_fork++;
		d->philos[d->i].deadly_timestamp = 0;
		d->philos[d->i].i_am_dead = 0;
		d->philos[d->i].eating_status = 0;
		d->philos[d->i].eat_counter = 0;
		d->i++;
	}
	return (0);
}

/*
** ИНИЦИАЛИЗАЦИЯ МЬЮТЕКСОВ (ВИЛОК)
** инициализация мьютекса table_manager (контролирует доступ к пище);
** выделяем память под массив вилок (мьютексов);
** инициализируем вилки-мьютексы (pthread_mutex_init) согласно
** количеству философов;
*/

int			init_table(t_data *d)
{
	long long count_forks;

	count_forks = 0;
	pthread_mutex_init(&d->table.table_manager, NULL);
	if (!(d->table.forks = (pthread_mutex_t *)
			malloc(sizeof(pthread_mutex_t) * d->num_of_phil)))
		return (ERR_MALLOC);
	while (count_forks < d->num_of_phil)
	{
		pthread_mutex_init(&d->table.forks[count_forks], NULL);
		count_forks++;
	}
	return (0);
}

/*
** ИНИЦИАЛИЗАЦИЯ СТРУКТУРЫ T_DATA
** 	присваиваем переменныем объекта философа начальные значения;
** 	инициализация мьютекса write (контролирует доступ к выводу статуса);
** 	инициализация мьютекса death (контролирует доступ к проверке смерти);
** 	вызываем функцию инициализирующую вилки;
** 	вызываем функцию инициализирующую философов;
** 	выделяем память для массива потоков threads;
*/

int			init_data(t_data *d)
{
	d->is_death = 0;
	d->time = 0;
	d->stop_eat = 0;
	d->i = 0;
	pthread_mutex_init(&d->write, NULL);
	pthread_mutex_init(&d->death, NULL);
	if (init_table(d))
		return (ERR_MALLOC);
	if (init_philosopher(d))
		return (ERR_MALLOC);
	if (!(d->threads = (pthread_t *)malloc(sizeof(pthread_t) * d->num_of_phil)))
		return (ERR_MALLOC);
	return (0);
}

/*
** ЗАПИСЬ АРГУМЕНТОВ В ПЕРЕМЕННЫЕ И ВЫЗОВ ИНИЦИАЛИЗИРУЮЩИХ ФУНКЦИЙ
*/

int			init(t_data *d, int ac, char **av)
{
	d->philos = NULL;
	d->threads = NULL;
	d->table.forks = NULL;
	if ((d->num_of_phil = ft_atoi(av[1])) < 2 || d->num_of_phil > 200)
		return (ERR_ARGS);
	if ((d->time_to_die = ft_atoi(av[2])) < 60)
		return (ERR_ARGS);
	if ((d->time_to_eat = ft_atoi(av[3])) < 60)
		return (ERR_ARGS);
	if ((d->time_to_sleep = ft_atoi(av[4])) < 60)
		return (ERR_ARGS);
	d->time_must_eat = 0;
	if (ac == 6 && (d->time_must_eat = ft_atoi(av[5])) <= 0)
		return (ERR_ARGS);
	return (init_data(d));
}
