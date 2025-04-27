NAME = philo
CFLAG = -Wall -Wextra -Werror
RM = rm -rf
CC = cc
SRC = main.c \
	./utils/utils_one.c \
	./utils/utils_two.c \
	./utils/utils_three.c \
	./utils/philosophers_life_cycle.c \
	./utils/free.c


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAG) $(OBJ) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAG) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
