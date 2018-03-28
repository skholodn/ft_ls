/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_name_validation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <skholodn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 16:51:24 by skholodn          #+#    #+#             */
/*   Updated: 2017/06/11 16:51:26 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ft_ls.h"

t_node	*sort_arg(t_node *begin, char *target)
{
	t_node *tmp;
	t_node *new;

	tmp = begin;
	if (!(new = create_node(target)))
		return (NULL);
	if (ft_strcmp(target, tmp->name) < 0)
	{
		new->next = begin;
		begin = new;
		return (begin);
	}
	while (tmp->next && ft_strcmp(target, tmp->next->name) >= 0)
		tmp = tmp->next;
	if (tmp->next)
	{
		new->next = tmp->next;
		tmp->next = new;
	}
	else
		tmp->next = new;
	return (begin);
}

t_node	*create_name(t_flag *f, int i)
{
	t_node	*begin;

	begin = NULL;
	if (!f->target)
		begin = create_node(".");
	else
	{
		while (f->target[++i])
		{
			if (i == 0)
				begin = create_node(f->target[i]);
			else
				begin = sort_arg(begin, f->target[i]);
		}
	}
	return (begin);
}

t_node	*check_stat(t_node *begin, t_node **current, t_node **previous)
{
	struct stat	*sb;
	DIR			*dir;
	t_node		*tmp;

	dir = NULL;
	tmp = (*current)->next;
	sb = (struct stat *)ft_memalloc(sizeof(struct stat));
	if (lstat((*current)->name, sb) == -1 || ((sb->st_mode == S_IFDIR)
				&& !(dir = opendir((*current)->name))))
	{
		print_perror((*current)->name);
		if (begin == (*current))
			begin = tmp;
		if (begin != (*current))
			(*previous)->next = tmp;
		del_node((*current));
	}
	else if (sb->st_mode == S_IFDIR)
		closedir(dir);
	(*current) = tmp;
	free(sb);
	return (begin);
}

t_node	*valid_list(t_node *begin)
{
	t_node	*current;
	t_node	*previous;

	current = begin;
	previous = begin;
	while (current)
	{
		if (begin != current && previous->next != current)
			previous = previous->next;
		begin = check_stat(begin, &current, &previous);
	}
	return (begin);
}
