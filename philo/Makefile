
NAME = philo
CC = cc -g
FLAGS = -Wall -Wextra -Werror

CFILES := main.c utils.c philo_life.c
OBJ_PATH := objects/
OBJS := $(CFILES:%.c=$(OBJ_PATH)%.o)

all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(OBJ_PATH)%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re