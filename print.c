/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <skholodn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 16:53:06 by skholodn          #+#    #+#             */
/*   Updated: 2017/06/11 16:53:08 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ft_ls.h"

void	print_xattr(t_info *file)
{
	ssize_t	ns;
	ssize_t	val;
	char	*value;

	ns = 0;
	value = (char *)ft_memalloc(10);
	while (ns < file->nb_xattr)
	{
		if (-1 == (val = getxattr(file->path,
			&file->xattr[ns], value, 9, 0, 0)))
			val = 32;
		ft_printf("\t%s\t   %i\n", &file->xattr[ns], val);
		ns += ft_strlen(&file->xattr[ns]) + 1;
	}
	free(value);
}

void	print_large(t_info *file, t_info *begin, t_flag *f)
{
	if (file->chmod[0] == 'l')
		ft_printf("%s %*d %-*s  %-*s %-*s%*d %s %s -> %s\n", file->chmod,
		begin->c.w_link, file->link, begin->c.w_uid, file->usr, begin->c.w_gid,
		file->grp, begin->c.w_bc, " ", begin->c.w_size, file->size,
		file->time, file->name, file->rd_link);
	else if (file->chmod[0] == 'c' || file->chmod[0] == 'b')
		ft_printf("%s %*d %-*s  %-*s %*d,%*d %s %s\n", file->chmod,
		begin->c.w_link, file->link, begin->c.w_uid, file->usr,
		begin->c.w_gid, file->grp, 4, major(file->rdev), 4,
		minor(file->rdev), file->time, file->name);
	else
		ft_printf("%s %*d %-*s  %-*s %*s%*d %s %s\n", file->chmod,
		begin->c.w_link, file->link, begin->c.w_uid, file->usr, begin->c.w_gid,
		file->grp, begin->c.w_bc, " ", begin->c.w_size, file->size, file->time,
		file->name);
	if (f->dog && file->nb_xattr)
		print_xattr(file);
}

void	print_dir_file(t_stack *file, t_info *begin, t_flag *f)
{
	if (f->bg == 1)
		ls_apply_large_g(file->info);
	if (f->l1 == 2)
		print_large(file->info, begin, f);
	else if (f->l1 == 1)
		ft_printf("%s\n", file->info->name);
}

void	print_multi_col(t_stack *f, ssize_t num, int w_name, int g)
{
	t_f		c;
	char	*arr[num];
	size_t	nm[num];

	c.x = 0;
	c.col = get_col(num, w_name);
	c.num1 = num;
	while (f)
	{
		(g == 1) ? ls_apply_large_g(f->info) : 0;
		arr[c.x] = f->info->name;
		nm[c.x++] = ft_strlen(f->info->nm);
		f = f->next;
	}
	c.x = 0;
	c.y = -1;
	while (++c.y != c.num1)
	{
		ft_printf("%-s%*s", arr[c.x], w_name - (int)nm[c.x], " ");
		c.x = c.x + c.col;
		if (c.x > c.num1 - 1 && ft_printf("\n"))
			c.x = c.x % c.col + 1;
	}
}

void	print_dir(t_stack *file, t_flag *f)
{
	t_stack	*begin;

	begin = file;
	if (!(f->l1))
	{
		print_multi_col(file, file->info->c.sum_node,
			file->info->c.w_name, f->bg);
		return ;
	}
	if (f->l1 == 2)
		ft_printf("total %d\n", file->info->c.sum_block);
	while (file)
	{
		print_dir_file(file, begin->info, f);
		file = file->next;
	}
}
