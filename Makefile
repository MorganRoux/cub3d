NAME		=	cub3d

LIBFT_DIR	=	./libs/libftprintf
MLX_DIR		=	./libs/minilibx_opengl_20191021
LIBFT		=	$(LIBFT_DIR)/libftprintf.a
MLX			=	$(MLX_DIR)/libmlx.a
LIBS		=	$(LIBFT) $(MLX)

SRCS		=	srcs/main.c \
				srcs/display/display.c \
				srcs/display/compute_fps.c \
				srcs/display/copy.c \
				srcs/hooks/hooks.c \
				srcs/hooks/move.c \
				srcs/hooks/rot.c \
				srcs/raycaster/dda.c \
				srcs/parser/cub_file.c \
				srcs/parser/loaders.c \
				srcs/parser/check_map.c \
				srcs/parser/check_others.c \
				srcs/parser/utils_parser.c \
				srcs/gnl/get_next_line.c \
				srcs/gnl/get_next_line_utils.c \
				srcs/bitmap/img_to_bmp.c \
				srcs/display/sprite.c \
				srcs/display/sort.c

SRCS_PG		=	srcs/playground/testmlx2_copy.c

OBJS		=	$(SRCS:.c=.o)
INC_PATH	=	-I./inc
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
INC_PATH	=	-I./inc
COMPILE		=	$(CC) $(FLAGS) $(INC_PATH) -L$(LIBFT_DIR) -lftprintf -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit 

%.o : %.c	
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