NAME := philosophers
SRCFILES := ./src/philosophers.c \
			./src/reading_arguments.c \
			./src/create_list.c \
			./src/manage_threads.c \
			./src/release_list.c\
			./src/check_input.c\
			./src/routines_rev.c\
			./src/subroutines.c\
			./src/get_time.c\
			./src/single_philosopher.c\
			./src/initialization.c\
			./src/guards.c\
			./src/get_values.c\
			./src/ends.c

CC = cc
CFLAGS = -Wextra -Werror -Wall -pthread
OBJS := $(SRCFILES:.c=.o) 

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(SRCFILES) $(LIBFT_EXEC) -o $(NAME) 
clean:
	rm -f $(OBJS)
fclean:	clean
	rm -f $(NAME)
	
re:		fclean all

CROSS = "\033[8m"
RED = "\033[0;1;91m"
GREEN = "\033[0;1;32m"
BLUE = "\033[0;1;34m"

.PHONY: clean fclean re