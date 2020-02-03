NAME		=	libftprintf.a

LIBFT		=	libft/libft.a

LIBFT_DIR	=	libft

SRCS		=	src/ft_printf.c \
			src/ft_printf_utils.c \
			src/ft_printf_options_others.c \
			src/ft_printf_options_diux.c \
			src/ft_printf_prints.c \
			src/ft_strjoin_ex.c
			
OBJS		=	${SRCS:.c=.o}

INC_PATH	=	-I./inc

CC		=	gcc

FLAGS		=	-Wall -Wextra -Werror

.c.o:			${SRCS} ${SRCS_BONUS}
			${CC} ${FLAGS} ${INC_PATH} -c $<  -o ${<:.c=.o}

all:			$(NAME)

$(NAME):	$(LIBFT) ${OBJS}
			ar rc ${NAME} ${OBJS}

$(LIBFT):	
			make bonus -C $(LIBFT_DIR)
			cp $(LIBFT) $(NAME)


clean:		
			make clean -C $(LIBFT_DIR)
			rm -f ${OBJS} ${OBJS_BONUS}

fclean:		clean
			make fclean -C $(LIBFT_DIR)
			rm -f ${NAME}

re:			fclean all
			
