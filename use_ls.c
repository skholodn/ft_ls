/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <skholodn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 16:53:42 by skholodn          #+#    #+#             */
/*   Updated: 2017/06/11 16:53:45 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ft_ls.h"

t_info	*create_info(t_name **p, t_info *info, struct stat *sb, t_flag *f)
{
	info = (t_info *)ft_memalloc(sizeof(t_info));
	info->name = ft_strdup((*p)->name);
	info->nm = ft_strdup(info->name);
	info->path = ft_strdup((*p)->path);
	if (f->dog == 1)
	{
		info->xattr = (char *)ft_memalloc(10001);
		info->nb_xattr = 10000;
	}
	info->ext = ls_get_acl(info->path, info->xattr, &info->nb_xattr);
	info->chmod = ls_get_chmod(sb, info);
	info->link = sb->st_nlink;
	info->size = sb->st_size;
	info->usr = ft_user(sb);
	info->grp = ft_group(sb);
	ls_get_time(sb, f, info);
	info->block = sb->st_blocks;
	info->rdev = sb->st_rdev;
	if (info->chmod[0] == 'l' && (info->rd_link = (char *)ft_memalloc(1025)))
		readlink(info->path, info->rd_link, 1024);
	check_width(info);
	return (info);
}

void	create_lstat_f(t_name **p, t_stack **file, struct stat *sb, t_flag *f)
{
	(*file) = (t_stack *)ft_memalloc(sizeof(t_stack));
	if (!(*file))
		return ;
	(*file)->info = create_info(p, (*file)->info, sb, f);
}

void	create_file(t_name **p, t_stack **file, struct stat *sb, t_flag *f)
{
	t_stack	*tmp;

	tmp = NULL;
	create_lstat_f(p, &tmp, sb, f);
	if (!(*file) && ((*file) = tmp))
		return ;
	if (f->f)
		ls_sort_f(&tmp, file);
	else if (f->t && f->r)
		ls_sort_rt(&tmp, file);
	else if (f->t && !f->r)
		ls_sort_t(&tmp, file);
	else if (!f->t && f->r)
		ls_sort_r(&tmp, file);
	else
		ls_sort_alpha(&tmp, file);
}

void	work_file_dir(t_stack *file_list, t_stack *dr_list, t_flag *f)
{
	if (file_list)
	{
		print_file(file_list, f);
		free_stack(file_list, f);
	}
	if (dr_list)
		use_dir(dr_list, f);
}

void	apply_ls(t_node *start, t_flag *f)
{
	t_node		*tmp;
	struct stat	*sb;
	t_stack		*file_list;
	t_stack		*dr_list;
	t_name		*p;

	tmp = start;
	init_ls(&file_list, &dr_list, &sb, &p);
	while (tmp)
	{
		if (lstat(tmp->name, sb) == -1 && print_perror(tmp->name)
			&& ((tmp = tmp->next) || !tmp))
			continue;
		p->name = ft_strdup(tmp->name);
		p->path = ft_strdup(p->name);
		if (f->dr == 1 || (!(S_ISDIR(sb->st_mode) && ((f->l1 == 2 &&
		(ft_check_link(tmp->name) == 1)) || ft_check_link(tmp->name) == 0))))
			create_file(&p, &file_list, sb, f);
		else
			create_file(&p, &dr_list, sb, f);
		tmp = tmp->next;
	}
	free_ls(&p, &sb, &start);
	work_file_dir(file_list, dr_list, f);
}
