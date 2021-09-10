NAME			=	fractol

SRCS_DIR		=	./srcs/

OBJS_DIR		=	./objs/

HEADERS_DIR		=	./includes/

LIBFT_DIR		=	./libft/

SRCS			=	$(SRCS_DIR)	




HEADERS			=	$(wildcard $(HEADERS_DIR)*.h)

OBJS			=	$(addprefix $(OBJS_DIR), $(notdir $(SRCS:.c=.o)))

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror

LDFLAGS			=	-L$(LIBMLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -framework OpenGL -framework Appkit -O3

RM				=	rm -f

LIBFT			=	$(addprefix $(LIBFT_DIR), libft.a)

LIBMLX			=	$(addprefix $(LIBMLX_DIR), libmlx.a)

LIBFT_DIR		=	./libft/

LIBMLX_DIR		=	./mlx/

all:	$(LIBFT) $(LIBMLX) $(NAME)
$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c $(HEADERS) $(LIBFT) $(LIBMLX) | $(OBJS_DIR)
	$(CC) $(CFLAGS) -O3 -I$(HEADERS_DIR) -Imlx -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(LIBMLX):
	make -C $(LIBMLX_DIR)

$(NAME): $(OBJS) $(LIBFT) $(LIBMLX)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

clean:
		$(RM) -r $(OBJS_DIR)
		make clean -C $(LIBFT_DIR) fclean

fclean: clean
		$(RM) $(NAME)
		make clean -C $(LIBFT_DIR) fclean

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

re:	fclean $(OBJS_DIR) all

.PHONY:	all clean fclean re
