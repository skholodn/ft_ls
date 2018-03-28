/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_nb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <skholodn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 16:51:12 by skholodn          #+#    #+#             */
/*   Updated: 2017/06/11 16:51:14 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ft_ls.h"

int		count_nb(int nb)
{
	int		count;

	count = 1;
	if (nb < 0)
		count++;
	while (nb > 9 || nb < -9)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

int		ft_timecmp(t_info *t1, t_info *t2)
{
	if (t1->gtime > t2->gtime)
		return (-1);
	else if (t1->gtime < t2->gtime)
		return (1);
	else
	{
		if (t1->nano > t2->nano)
			return (-1);
		else if (t1->nano < t2->nano)
			return (1);
		else
			return (ft_strcmp(t1->name, t2->name));
	}
}

ssize_t	ft_multicolumn(void)
{
	struct winsize	win;
	char			*p;
	int				width;

	width = 0;
	if (isatty(STDOUT_FILENO))
	{
		width = 80;
		if ((p = getenv("COLUMNS")) != NULL && *p != '\0')
			width = ft_atoi(p);
		else if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &win) != -1 &&
				win.ws_col > 0)
			width = win.ws_col;
	}
	return (width);
}

void	print_file_funct(t_stack *file, t_info *begin, t_flag *f)
{
	if (f->bg == 1)
		ls_apply_large_g(file->info);
	if (f->l1 == 2)
		print_large(file->info, begin, f);
}

void	print_file(t_stack *file, t_flag *f)
{
	t_stack	*begin;

	begin = file;
	while (file)
	{
		print_file_funct(file, begin->info, f);
		file = file->next;
	}
}
