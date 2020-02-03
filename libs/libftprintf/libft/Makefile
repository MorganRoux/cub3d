NAME		=	libft.a

SRCS		=	ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memccpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strlen.c \
			ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isprint.c \
			ft_isascii.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_strdup.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strcmp.c \
			ft_strncmp.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strnstr.c \
			ft_atoi.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_uitoa_base.c \
			ft_ultoa_base.c \
			ft_strmapi.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_calloc.c

SRCS_BONUS	=	ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstmap_bonus.c 
			
OBJS		=	${SRCS:.c=.o}

OBJS_BONUS	=	${SRCS_BONUS:.c=.o}

INC_PATH	=	-I./inc

CC		=	gcc

FLAGS		=	-Wall -Wextra -Werror

$(NAME):		${OBJS}
			ar rc ${NAME} ${OBJS}

.c.o:			${SRCS} ${SRCS_BONUS}
			${CC} ${FLAGS} ${INC_PATH} -c $<  -o ${<:.c=.o}

all:			$(NAME)

bonus:			${OBJS} ${OBJS_BONUS}
			ar rc ${NAME} ${OBJS} ${OBJS_BONUS}

clean:		
			rm -f ${OBJS} ${OBJS_BONUS}

fclean:			clean
			rm -f ${NAME}

re:			fclean bonus
			
test:		all
			./test.sh | cat -e
