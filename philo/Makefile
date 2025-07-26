NAME = philo
CFLAG = -Wall -Wextra -Werror -fsanitize=thread
RM = rm -rf
CC = cc

SRC = main.c \
	./utils/utils_one.c ./utils/utils_two.c ./utils/free.c \
	./philosophers/philosophers_life_cycle.c \
	./philosophers/ft_initialize.c ./philosophers/creat_thread.c

OBJDIR = OBJ
OBJ = $(patsubst %.c, $(OBJDIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAG) $(OBJ) -o $(NAME)

$(OBJDIR)/%.o: %.c philo.h | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAG) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re