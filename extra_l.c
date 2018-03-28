/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <skholodn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 16:52:08 by skholodn          #+#    #+#             */
/*   Updated: 2017/06/11 16:52:12 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ft_ls.h"

char	ls_get_acl(char *name, char *xattr, ssize_t *nb_xattr)
{
	acl_t		acl;
	acl_entry_t	help;
	char		c;

	help = NULL;
	acl = acl_get_link_np(name, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &help) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	if ((*nb_xattr = listxattr(name, xattr, (size_t)*nb_xattr,
			(!*nb_xattr) ? XATTR_NOFOLLOW : XATTR_SHOWCOMPRESSION)) < 0)
		*nb_xattr = 0;
	if (*nb_xattr > 0)
		c = '@';
	else if (acl != NULL)
		c = '+';
	else
		c = ' ';
	return (c);
}

char	ls_get_type(mode_t mod)
{
	char	c;

	if (S_ISREG(mod))
		c = '-';
	else if (S_ISDIR(mod))
		c = 'd';
	else if (S_ISBLK(mod))
		c = 'b';
	else if (S_ISCHR(mod))
		c = 'c';
	else if (S_ISFIFO(mod))
		c = 'p';
	else if (S_ISLNK(mod))
		c = 'l';
	else if (S_ISSOCK(mod))
		c = 's';
	else
		c = '?';
	return (c);
}

char	*ls_get_chmod(struct stat *sb, t_info *info)
{
	char				*str;
	static const char	*rwx[] = {"---", "--x", "-w-", "-wx",
								"r--", "r-x", "rw-", "rwx"};

	str = (char *)ft_memalloc(13);
	if (!str)
		return (NULL);
	str[0] = ls_get_type(sb->st_mode);
	ft_strcpy(&str[1], rwx[(sb->st_mode >> 6) & 7]);
	ft_strcpy(&str[4], rwx[(sb->st_mode >> 3) & 7]);
	ft_strcpy(&str[7], rwx[(sb->st_mode & 7)]);
	if (sb->st_mode & S_ISUID)
		str[3] = (sb->st_mode & S_IXUSR) ? (char)'s' : (char)'S';
	if (sb->st_mode & S_ISGID)
		str[6] = (sb->st_mode & S_IXGRP) ? (char)'s' : (char)'S';
	if (sb->st_mode & S_ISVTX)
		str[9] = (sb->st_mode & S_IXOTH) ? (char)'t' : (char)'T';
	str[10] = info->ext;
	return (str);
}

void	ls_get_time(struct stat *sb, t_flag *f, t_info *info)
{
	char	*tmp_data;
	time_t	time_old;
	time_t	time_new;

	time_new = time(NULL);
	if ((info->time = (char *)ft_memalloc(13)) && f->u)
	{
		info->gtime = sb->st_atime;
		info->nano = sb->st_atimespec.tv_nsec;
		time_old = (f->l1 == 2) ? sb->st_atime : 0;
	}
	else
	{
		info->gtime = sb->st_mtime;
		info->nano = sb->st_mtimespec.tv_nsec;
		time_old = (f->l1 == 2) ? sb->st_mtime : 0;
	}
	tmp_data = ctime(&time_old);
	if (time_new - time_old < 15778476 && time_old - time_new < 30)
		ft_memmove(info->time, (tmp_data + 4), 12);
	else
	{
		ft_memmove(info->time, (tmp_data + 4), 7);
		ft_memmove(info->time + 7, (tmp_data + 19), 5);
	}
}
