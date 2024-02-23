CC=cc
CFLAGS=-Werror -Wextra -Wall
PHILO_O=main.o args_parse.o utils.o dinning.o more_utils.o
HEADER_H=philo.h
NAME=philo

all: $(NAME)

$(NAME): $(PHILO_O)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(HEADER_H)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(PHILO_O)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean
