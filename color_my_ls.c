/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_my_ls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <skholodn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 16:50:58 by skholodn          #+#    #+#             */
/*   Updated: 2017/06/11 16:51:02 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ft_ls.h"

char	*ls_put_color(char *name, char *color)
{
	size_t	namelen;
	size_t	colorlen;
	char	*str;
	char	*tmp;

	tmp = name;
	namelen = ft_strlen(tmp);
	colorlen = ft_strlen(color);
	str = (char *)ft_memalloc(colorlen + namelen + 6);
	ft_memcpy(str, color, colorlen);
	ft_memcpy(str + colorlen, tmp, namelen);
	ft_memcpy(str + colorlen + namelen, EOC, 5);
	free(tmp);
	return (str);
}

void	find_d(t_info *info)
{
	char	*ch;

	ch = info->chmod;
	if (ch[2] == 'w' && ch[5] == 'w' && ch[8] == 'w')
	{
		if (ch[9] == 't' || ch[9] == 'T')
			info->name = ls_put_color(info->name, DIR_ST_C);
		else
			info->name = ls_put_color(info->name, DIR_NO_ST_C);
	}
	else
		info->name = ls_put_color(info->name, DIR_C);
}

void	find_exe(t_info *info)
{
	char	*ch;

	ch = info->chmod;
	if (ch[3] == 'x' || ch[3] == 's' || ch[6] == 'x'
		|| ch[6] == 's' || ch[9] == 'x')
	{
		if (ch[3] == 's' || ch[3] == 'S')
			info->name = ls_put_color(info->name, SETUID_C);
		else if (ch[6] == 's' || ch[6] == 'S')
			info->name = ls_put_color(info->name, SETGID_C);
		else
			info->name = ls_put_color(info->name, EXECUTABLE_C);
	}
}

void	ls_apply_large_g(t_info *info)
{
	if (info->chmod[0] == 'l')
		info->name = ls_put_color(info->name, SYM_LINK_C);
	else if (info->chmod[0] == 's')
		info->name = ls_put_color(info->name, SOCKET_C);
	else if (info->chmod[0] == 'p')
		info->name = ls_put_color(info->name, PIPE_C);
	else if (info->chmod[0] == 'b')
		info->name = ls_put_color(info->name, BLOCK_SP_C);
	else if (info->chmod[0] == 'c')
		info->name = ls_put_color(info->name, CHAR_SP_C);
	else if (info->chmod[0] == 'd')
		find_d(info);
	else if (info->chmod[0] == '-')
		find_exe(info);
}
