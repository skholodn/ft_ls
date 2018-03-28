NAME = ft_ls

CFLAGS = -Wall -Wextra -Werror

INCLUDE = include/

SRCS = color_my_ls.c \
	   count_nb.c \
	   create_name_validation.c \
	   double_link_list.c \
	   error.c \
	   extra_l.c \
	   find_link.c \
	   free_list.c \
	   ft_ls.c \
	   print.c \
	   sort_funct.c \
	   use_dir.c \
	   use_ls.c

OBJ = $(SRCS: .c=.o)

LIBFT = libft/libft.a

PRINTF = ft_printf/libftprintf.a

all: $(NAME)

$(NAME) : $(OBJ) $(LIBFT) $(PRINTF)
			gcc $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(PRINTF)

%.o: %.c $(INCLUDES)
	gcc $(CFLAGS) -c -o $@ $<

$(LIBFT):
	make -C ./libft/

$(PRINTF):
	make -C ./ft_printf/

clean:
	rm -f *.o
	make clean -C libft/
	make clean -C ft_printf/

fclean: clean
	rm -f $(NAME)

re: clean all

