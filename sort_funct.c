/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_funct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <skholodn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 16:53:18 by skholodn          #+#    #+#             */
/*   Updated: 2017/06/11 16:53:20 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ft_ls.h"

void	ls_sort_f(t_stack **fin, t_stack **begin)
{
	t_stack *in;

	in = (*begin);
	put_width(fin, begin);
	while (in->next)
		in = in->next;
	in->next = (*fin);
}

void	ls_sort_alpha(t_stack **fin, t_stack **begin)
{
	t_stack *in;

	in = (*begin);
	if (ft_strcmp((*begin)->info->name, (*fin)->info->name) > 0)
	{
		put_width(begin, fin);
		(*fin)->next = (*begin);
		(*begin) = (*fin);
		return ;
	}
	while (in->next && ft_strcmp(in->next->info->name, (*fin)->info->name) <= 0)
		in = in->next;
	if (in->next)
	{
		(*fin)->next = in->next;
		in->next = (*fin);
	}
	else
		in->next = (*fin);
	put_width(fin, begin);
}

void	ls_sort_r(t_stack **fin, t_stack **begin)
{
	t_stack *in;

	in = (*begin);
	if (ft_strcmp((*begin)->info->name, (*fin)->info->name) < 0)
	{
		put_width(begin, fin);
		(*fin)->next = (*begin);
		(*begin) = (*fin);
		return ;
	}
	while (in->next && ft_strcmp(in->next->info->name, (*fin)->info->name) >= 0)
		in = in->next;
	if (in->next)
	{
		(*fin)->next = in->next;
		in->next = (*fin);
	}
	else
		in->next = (*fin);
	put_width(fin, begin);
}

void	ls_sort_t(t_stack **fin, t_stack **begin)
{
	t_stack *in;

	in = *begin;
	if (ft_timecmp((*begin)->info, (*fin)->info) > 0)
	{
		put_width(begin, fin);
		(*fin)->next = (*begin);
		(*begin) = (*fin);
		return ;
	}
	while (in->next && ft_timecmp(in->next->info, (*fin)->info) <= 0)
		in = in->next;
	if (in->next)
	{
		(*fin)->next = in->next;
		in->next = (*fin);
	}
	else
		in->next = (*fin);
	put_width(fin, begin);
}

void	ls_sort_rt(t_stack **fin, t_stack **begin)
{
	t_stack *in;

	in = *begin;
	if (ft_timecmp((*begin)->info, (*fin)->info) < 0)
	{
		put_width(begin, fin);
		(*fin)->next = (*begin);
		(*begin) = (*fin);
		return ;
	}
	while (in->next && ft_timecmp(in->next->info, (*fin)->info) >= 0)
		in = in->next;
	if (in->next)
	{
		(*fin)->next = in->next;
		in->next = (*fin);
	}
	else
		in->next = (*fin);
	put_width(fin, begin);
}
