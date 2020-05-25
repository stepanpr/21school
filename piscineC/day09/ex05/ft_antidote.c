/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_antidote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emabel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 21:28:54 by emabel            #+#    #+#             */
/*   Updated: 2019/08/08 22:11:18 by emabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_antidote(int i, int j, int k)
{
	if (i == j || i == j || i == k || j == k)
	{
		return (0);
	}
	if (((i < j) && (j < k)) || ((k < j) && (j < i)))
	{
		return (j);
	}
	else if (((j < i) && (i < k)) || ((k < i) && (i < j)))
	{
		return (i);
	}
	else if (((j < k) && (k < i)) || ((i < k) && (k < j)))
	{
		return (k);
	}
	return (0);
}