/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_link.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <skholodn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 16:52:26 by skholodn          #+#    #+#             */
/*   Updated: 2017/06/11 16:52:30 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ft_ls.h"

int		ft_check_link(char *name)
{
	struct stat	buf;
	char		rd_link[1024];
	char		*str;
	ssize_t		nb;

	if ((nb = readlink(name, rd_link, sizeof(rd_link))) == -1)
		return (0);
	rd_link[nb] = '\0';
	if (name[0] == '/')
		str = ft_strjoin("/", rd_link);
	else
		str = rd_link;
	stat(str, &buf);
	if (name[0] == '/')
		free(str);
	if (buf.st_mode & S_IFDIR)
		return (1);
	return (0);
}

void	check_width(t_info *info)
{
	int		len;
	int		tab;

	len = (int)ft_strlen(info->name);
	tab = (len % 8) ? (len % 8) : 8;
	info->c.sum_block = (int)info->block;
	info->c.sum_node = 1;
	info->c.w_name = len + tab;
	info->c.w_uid = (int)ft_strlen(info->usr);
	info->c.w_gid = (int)ft_strlen(info->grp);
	info->c.w_link = count_nb((int)info->link);
	info->c.w_size = count_nb((int)info->size);
	info->c.w_bc = (info->chmod[0] == 'b' || info->chmod[0] == 'c') ? 8 : 0;
}

void	put_width(t_stack **fin, t_stack **begin)
{
	(*fin)->info->c.sum_block += (*begin)->info->c.sum_block;
	(*begin)->info->c.sum_block = (*fin)->info->c.sum_block;
	(*fin)->info->c.sum_node += (*begin)->info->c.sum_node;
	(*begin)->info->c.sum_node = (*fin)->info->c.sum_node;
	if ((*fin)->info->c.w_name > (*begin)->info->c.w_name)
		(*begin)->info->c.w_name = (*fin)->info->c.w_name;
	if ((*fin)->info->c.w_uid > (*begin)->info->c.w_uid)
		(*begin)->info->c.w_uid = (*fin)->info->c.w_uid;
	if ((*fin)->info->c.w_gid > (*begin)->info->c.w_gid)
		(*begin)->info->c.w_gid = (*fin)->info->c.w_gid;
	if ((*fin)->info->c.w_link > (*begin)->info->c.w_link)
		(*begin)->info->c.w_link = (*fin)->info->c.w_link;
	if ((*fin)->info->c.w_size > (*begin)->info->c.w_size)
		(*begin)->info->c.w_size = (*fin)->info->c.w_size;
	if ((*fin)->info->c.w_bc > (*begin)->info->c.w_bc)
		(*begin)->info->c.w_bc = (*fin)->info->c.w_bc;
}

char	*ft_user(struct stat *info)
{
	struct passwd	*pwd;
	char			*str;

	if ((pwd = getpwuid(info->st_uid)) != NULL)
	{
		str = ft_strdup(pwd->pw_name);
		return (str);
	}
	return (ft_itoa(info->st_uid));
}

char	*ft_group(struct stat *info)
{
	struct group	*gr;
	char			*str;

	if ((gr = getgrgid(info->st_gid)) != NULL)
	{
		str = ft_strdup(gr->gr_name);
		return (str);
	}
	return (ft_itoa(info->st_gid));
}
