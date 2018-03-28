/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <skholodn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 16:11:48 by skholodn          #+#    #+#             */
/*   Updated: 2017/06/11 16:54:00 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include <sys/ioctl.h>
# include <time.h>
# include <unistd.h>
# include <stdlib.h>
# include <pwd.h>
# include <grp.h>
# include <math.h>

# define DIR_C			"\033[0;34m"
# define SYM_LINK_C		"\033[0;35m"
# define SOCKET_C		"\033[0;32m"
# define PIPE_C			"\033[0;33m"
# define EXECUTABLE_C	"\033[0;31m"
# define BLOCK_SP_C		"\033[34;46m"
# define CHAR_SP_C		"\033[34;43m"
# define SETUID_C		"\033[30;41m"
# define SETGID_C		"\033[30;46m"
# define DIR_ST_C		"\033[30;42m"
# define DIR_NO_ST_C	"\033[30;43m"
# define EOC            "\033[0m"

typedef struct			s_flag
{
	int					a;
	int					dr;
	int					f;
	int					bg;
	int					dog;
	int					l1;
	int					r;
	int					t;
	int					u;
	int					stop;
	char				**target;
}						t_flag;

typedef struct			s_out
{
	int					sum_block;
	int					sum_node;
	int					w_name;
	int					w_link;
	int					w_uid;
	int					w_gid;
	int					w_size;
	int					w_bc;
}						t_out;

typedef struct			s_info
{
	char				*name;
	char				*nm;
	char				*path;
	char				ext;
	char				*chmod;
	char				*xattr;
	ssize_t				nb_xattr;
	off_t				link;
	off_t				size;
	char				*usr;
	char				*grp;
	char				*time;
	time_t				gtime;
	long				nano;
	quad_t				block;
	dev_t				rdev;
	char				*rd_link;
	t_out				c;
}						t_info;

typedef	struct			s_node
{
	char				*name;
	struct s_node		*next;
}						t_node;

typedef	struct			s_name
{
	char				*name;
	char				*path;
}						t_name;

typedef	struct			s_stack
{
	t_info				*info;
	struct s_stack		*next;
}						t_stack;

typedef struct			s_f
{
	ssize_t				col;
	ssize_t				x;
	ssize_t				y;
	ssize_t				num1;
}						t_f;

/*
** use_ls.c
*/
t_info					*create_info(t_name **p, t_info *info,
										struct stat *sb, t_flag *f);
void					create_lstat_f(t_name **p, t_stack **file,
										struct stat *sb, t_flag *f);
void					create_file(t_name **p, t_stack **file,
										struct stat *sb, t_flag *f);
void					work_file_dir(t_stack *file_list, t_stack
										*dr_list, t_flag *f);
void					apply_ls(t_node *start, t_flag *f);
/*
** use_dir.c - <OK>
*/
char					*dir_name(char *path, char *name);
void					find_dir(t_stack *begin, t_flag *f);
void					pl_work_dir(t_stack *begin, t_flag *f);
void					work_dir(char *pth, t_flag *f, int	one);
void					use_dir(t_stack *dr_list, t_flag *f);
/*
** sort_funct.c - <OK>
*/
void					ls_sort_f(t_stack **fin, t_stack **begin);
void					ls_sort_alpha(t_stack **fin, t_stack **begin);
void					ls_sort_r(t_stack **fin, t_stack **begin);
void					ls_sort_t(t_stack **fin, t_stack **begin);
void					ls_sort_rt(t_stack **fin, t_stack **begin);
/*
** print.c - <OK>
*/
void					print_xattr(t_info *file);
void					print_large(t_info *file, t_info *begin, t_flag *f);
void					print_dir_file(t_stack *file, t_info *begin, t_flag *f);
void					print_multi_col(t_stack *f, ssize_t num,
										int w_name, int g);
void					print_dir(t_stack *file, t_flag *f);
/*
** ft_ls.c - <OK>
*/
t_flag					*init_flag(void);
void					flag_replace(char find, char check, int *value);
void					flag_long(char find, char check, int *value);
void					parse_flag(char *s, t_flag	*f, int i);
/*
** free_list.c - <OK>
*/
void					free_list(t_node *list);
void					free_stack(t_stack *stack, t_flag *f);
void					free_ls(t_name **p, struct stat	**sb, t_node **start);
void					free_dir(DIR *dir, struct dirent *sd,
									struct stat *sb, t_name *p);
/*
** find_link.c - <OK>
*/
int						ft_check_link(char *name);
void					check_width(t_info *info);
char					*ft_user(struct stat *info);
char					*ft_group(struct stat *info);
void					put_width(t_stack **fin, t_stack **begin);
/*
** error.c - <OK>
*/
void					print_error(char *str);
int						print_perror(char *str);
/*
** extra_l.c - <OK>
*/
char					ls_get_acl(char *name, char *xattr, ssize_t	*nb_xattr);
char					ls_get_type(mode_t mod);
char					*ls_get_chmod(struct stat *sb, t_info *info);
void					ls_get_time(struct stat *sb, t_flag *f, t_info *info);
/*
** double_link_list.c - <OK>
*/
t_node					*create_node(char *data);
void					del_node(t_node	*node);
void					init_ls(t_stack **f, t_stack **d,
								struct stat **sb, t_name **p);
void					init_dir(t_stack **begin, struct stat **sb, t_name **p);
size_t					get_col(ssize_t num, int w_name);
/*
** create_name_validation.c - <OK>
*/
t_node					*sort_arg(t_node *begin, char *target);
t_node					*create_name(t_flag	*f, int	i);
t_node					*check_stat(t_node *begin, t_node **current,
										t_node **previous);
t_node					*valid_list(t_node	*begin);
/*
** count_nb.c - <OK>
*/
int						count_nb(int nb);
int						ft_timecmp(t_info *t1, t_info *t2);
ssize_t					ft_multicolumn(void);
void					print_file_funct(t_stack *file, t_info *begin,
											t_flag *f);
void					print_file(t_stack *file, t_flag *f);
/*
** color_my_ls.c - <OK>
*/
char					*ls_put_color(char *name, char *color);
void					find_d(t_info *info);
void					find_exe(t_info *info);
void					ls_apply_large_g(t_info *info);

#endif
