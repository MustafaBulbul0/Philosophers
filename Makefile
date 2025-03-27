NAME = philo
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf
CC = cc

SRC = philo.c \
	utils/utils_one.c \
	utils/utils_two.c \
	utils/philosopher_life_cycle.c \
	utils/free.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
