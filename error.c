/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <skholodn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 16:51:50 by skholodn          #+#    #+#             */
/*   Updated: 2017/06/11 16:51:58 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ft_ls.h"

void	print_error(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	exit(-1);
}

int		print_perror(char *str)
{
	char	*tmp;

	tmp = ft_strjoin("ft_ls: ", str);
	perror(tmp);
	free(tmp);
	return (1);
}
