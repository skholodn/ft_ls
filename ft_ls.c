/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <skholodn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 16:52:52 by skholodn          #+#    #+#             */
/*   Updated: 2017/06/11 16:52:55 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ft_ls.h"

t_flag	*init_flag(void)
{
	t_flag	*f;

	f = (t_flag *)ft_memalloc(sizeof(t_flag));
	if (!f)
		return (0);
	f->stop = 1;
	return (f);
}

void	flag_replace(char find, char check, int *value)
{
	if (find == check || *value)
		*value = 1;
	else
		*value = 2;
}

void	flag_long(char find, char check, int *value)
{
	if (find == check)
		*value = 1;
	else
		*value = 2;
}

void	parse_flag(char *s, t_flag *f, int i)
{
	while (s && s[++i])
	{
		if (s[i] == 'a')
			f->a = 1;
		else if (s[i] == 'd' || s[i] == 'R')
			flag_replace(s[i], 'd', &f->dr);
		else if (s[i] == 'f')
			f->f = 1;
		else if (s[i] == 'G')
			f->bg = 1;
		else if (s[i] == 'l' || s[i] == '1')
			flag_long(s[i], '1', &f->l1);
		else if (s[i] == 'r')
			f->r = 1;
		else if (s[i] == 't')
			f->t = 1;
		else if (s[i] == 'u')
			f->u = 1;
		else if (s[i] == '@')
			f->dog = 1;
		else
			print_error("usage: ft_ls [-adfGlrRtu1@] [directory ...]");
	}
}

int		main(int ac, char **av)
{
	int		i;
	t_flag	*f;
	t_node	*begin;

	if (ac < 1)
		print_error("usage: ft_ls [-adfGlrRtu1@] [directory ...]");
	i = 0;
	f = init_flag();
	while (++i < ac)
	{
		if (av[i][0] == '-' && av[i][1] == '-')
			f->stop = 0;
		else if (av[i][0] == '-' && f->stop)
			parse_flag(av[i], f, 0);
		else
		{
			f->target = av + i;
			break ;
		}
	}
	begin = create_name(f, -1);
	begin = valid_list(begin);
	apply_ls(begin, f);
	return (0);
}
