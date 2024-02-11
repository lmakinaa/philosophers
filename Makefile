CC=cc
CFLAGS=-Werror -Wextra -Wall
GC_DIR=./allocation_manager
GC_O=$(GC_DIR)/allocation_manager.o
GC_H=$(GC_DIR)/allocation_manager.h
PHILO_O=main.o args_parse.o gathering_around_table.o utils.o dinning.o preparing_table.o
HEADER_H=philo.h
NAME=philo

all: $(NAME)

$(NAME): $(PHILO_O) $(GC_O)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(HEADER_H)
	$(CC) $(CFLAGS) -c $< -o $@

$(GC_DIR)/%.o: $(GC_DIR)/%.c $(GC_H)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(PHILO_O) $(GC_O)

fclean: clean
	rm -f $(NAME)

.PHONY: clean fclean
