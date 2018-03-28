/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <skholodn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 16:52:37 by skholodn          #+#    #+#             */
/*   Updated: 2017/06/11 16:52:41 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ft_ls.h"

void	free_list(t_node *list)
{
	t_node *tmp;

	tmp = list;
	while (list)
	{
		free(list->name);
		list = list->next;
		free(tmp);
		tmp = list;
	}
}

void	free_stack(t_stack *stack, t_flag *f)
{
	t_stack *tmp;
	t_stack *prev;

	tmp = stack;
	prev = stack;
	while (tmp)
	{
		free(tmp->info->name);
		free(tmp->info->nm);
		free(tmp->info->path);
		if (tmp->info->chmod[0] == 'l')
			free(tmp->info->rd_link);
		free(tmp->info->chmod);
		(f->dog) ? free(tmp->info->xattr) : 0;
		free(tmp->info->usr);
		free(tmp->info->grp);
		free(tmp->info->time);
		free(tmp->info);
		tmp->info = NULL;
		tmp = tmp->next;
		prev->next = NULL;
		free(prev);
		prev = tmp;
	}
}

void	free_ls(t_name **p, struct stat	**sb, t_node **start)
{
	free((*p));
	free((*sb));
	free_list((*start));
}

void	free_dir(DIR *dir, struct dirent *sd, struct stat *sb, t_name *p)
{
	free(sb);
	free(p);
	free(sd);
	closedir(dir);
}
