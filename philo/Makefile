SRC = 	main.c \
		check.c \
		init.c \
		utils.c \
		utils2.c \

NAME = philo
OBJ = ${SRC:.c=.o}
CC = gcc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror

.c.o:
		$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

all: ${NAME}

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
		${RM} ${OBJ}

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re