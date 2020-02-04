NAME		=	cub3d

LIBFT_DIR	=	./libs/libftprintf
MLX_DIR		=	./libs/minilibx_opengl_20191021
LIBFT		=	$(LIBFT_DIR)/libftprintf.a
MLX			=	$(MLX_DIR)/libmlx.a
LIBS		=	$(LIBFT) $(MLX)

SRCS		=	srcs/main.c

SRCS_PG		=	srcs/playground/testmlx2.c

OBJS		=	$(SRCS:.c=.o)
INC_PATH	=	-I./inc
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
INC_PATH	=	-I./inc
COMPILE		=	$(CC) $(FLAGS) $(INC_PATH) -L$(LIBFT_DIR) -lftprintf -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit 

%.o : %.c	$(SRCS)
			$(CC) $(FLAGS) $(INC_PATH) -c $<  -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(LIBS) ${OBJS}
			$(COMPILE) $(OBJS) -o $(NAME)
$(LIBFT):	
			make -C $(LIBFT_DIR)
$(MLX):			
			make -C $(MLX_DIR)

clean:		
			make clean -C $(LIBFT_DIR)
			make clean -C $(MLX_DIR)
			rm -f ${OBJS}

fclean:		
			make fclean -C $(LIBFT_DIR)
			make fclean -C $(MLX_DIR)
			rm -f ${OBJS}
			rm -f ${NAME}

re:			fclean all

playground:	$(LIBS) $(SRCS_PG)
			$(COMPILE) $(SRCS_PG) -o srcs/playground/cub3d_pg.out
			./srcs/playground/cub3d_pg.out

.PHONY:		clean fclean all re 