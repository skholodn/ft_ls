/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_link_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <skholodn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 16:51:36 by skholodn          #+#    #+#             */
/*   Updated: 2017/06/11 16:51:39 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ft_ls.h"

t_node	*create_node(char *data)
{
	t_node	*node;

	node = (t_node *)ft_memalloc(sizeof(t_node));
	if (!(node))
		return (NULL);
	node->name = ft_strdup(data);
	node->next = NULL;
	return (node);
}

void	del_node(t_node *node)
{
	node->next = NULL;
	free(node->name);
	free(node);
}

void	init_ls(t_stack **f, t_stack **d, struct stat **sb, t_name **p)
{
	(*f) = NULL;
	(*d) = NULL;
	(*sb) = (struct stat *)ft_memalloc(sizeof(struct stat));
	(*p) = (t_name *)ft_memalloc(sizeof(t_name));
}

void	init_dir(t_stack **begin, struct stat **sb, t_name **p)
{
	(*begin) = NULL;
	(*sb) = (struct stat *)ft_memalloc(sizeof(struct stat));
	(*p) = (t_name *)ft_memalloc(sizeof(t_name));
}

size_t	get_col(ssize_t num, int w_name)
{
	size_t	width;
	size_t	col;

	col = 0;
	if ((width = ft_multicolumn()))
	{
		while (num % (width / w_name) != 0)
			num++;
		col = num / (width / w_name);
	}
	return (col);
}
