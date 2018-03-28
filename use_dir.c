/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <skholodn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 16:53:31 by skholodn          #+#    #+#             */
/*   Updated: 2017/06/11 16:53:35 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ft_ls.h"

char	*dir_name(char *path, char *name)
{
	char	*ful_path;

	ful_path = (char *)malloc(ft_strlen(path) + ft_strlen(name) + 2);
	if (!ful_path)
		return (NULL);
	ft_bzero(ful_path, ft_strlen(path) + ft_strlen(name) + 2);
	ft_strcpy(ful_path, path);
	if (ft_strcmp(ful_path, "/") != 0)
		ft_strcat(ful_path, "/");
	ft_strcat(ful_path, name);
	return (ful_path);
}

void	find_dir(t_stack *begin, t_flag *f)
{
	while (begin)
	{
		if (begin->info->chmod[0] == 'd' && (ft_strcmp(begin->info->nm, ".")
			&& ft_strcmp(begin->info->nm, "..")))
			work_dir(begin->info->path, f, 0);
		begin = begin->next;
	}
}

void	pl_work_dir(t_stack *begin, t_flag *f)
{
	if (begin && begin->info)
	{
		print_dir(begin, f);
		if (f->dr == 2)
			find_dir(begin, f);
		free_stack(begin, f);
	}
}

void	work_dir(char *pth, t_flag *f, int one)
{
	DIR				*dir;
	struct dirent	*sd;
	t_stack			*begin;
	struct stat		*sb;
	t_name			*p;

	init_dir(&begin, &sb, &p);
	if (!one)
		ft_printf("\n%s:\n", pth);
	if ((dir = opendir(pth)) == NULL && print_perror(pth))
		return ;
	while ((sd = readdir(dir)) != NULL)
	{
		if (!f->a && (sd->d_name[0] == '.'))
			continue ;
		p->name = ft_strdup(sd->d_name);
		p->path = dir_name(pth, p->name);
		if (lstat(p->path, sb) == -1)
			print_perror(p->path);
		else
			create_file(&p, &begin, sb, f);
	}
	free_dir(dir, sd, sb, p);
	pl_work_dir(begin, f);
}

void	use_dir(t_stack *dr_list, t_flag *f)
{
	t_stack	*tmp;
	int		one;

	tmp = dr_list;
	one = 0;
	if (dr_list->next == NULL)
		one = 1;
	while (tmp)
	{
		work_dir(tmp->info->path, f, one);
		tmp = tmp->next;
	}
	free_stack(dr_list, f);
}
