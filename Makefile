NAME = philo

FLAGS = -pthread -g -Wall -Wextra -Werror #-fsanitize=thread

SRC = main.c	\
	src/utils.c	\
	src/init.c	\
	src/threads.c \
	src/utils_two.c \
	src/time.c 	\
	src/death.c \
	src/sleep.c \
	src/util_three.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	cc $(FLAGS) -c $^ -o $@

$(NAME): $(OBJ) include/philo.h
	cc $(LINKFLAGS) $(OBJ) $(FLAGS) -lpthread -o $(NAME)

clean:
	rm -f $(OBJ)

fclean:
	make clean
	rm -f $(NAME)

re: fclean all