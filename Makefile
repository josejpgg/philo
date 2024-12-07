LIBFT_NAME := libft.a
LIBFT_GH := https://github.com/josejpgg/libft_increment.git
LIBFT_PATH := ./lib/libft/
PHILO_NAME := philo
CC = cc
FLAGS = 
FLAGS = -Wall -Werror -Wextra
# FLAGS = -Wall -Werror -Wextra -fsanitize=address -g
SOURCE := main.c dinner.c getters_setters.c initialize.c message.c safe_func.c synchro_utils.c utils.c monitor.c philo_action.c
COMPILE := ${SOURCE:.c=.o}
COMPILE_BONUS := ${SOURCE_BONUS:.c=.o}

all: lib philo

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

philo: $(COMPILE)
	$(CC) $(FLAGS) $(COMPILE) $(LIBFT_NAME) -o ${PHILO_NAME}

clean:
	@rm -rf $(COMPILE)
	@make clean -C $(LIBFT_PATH)

fclean:
	@rm -rf ${PHILO_NAME}
	@make fclean -C $(LIBFT_PATH)
	@rm -rf ${LIBFT_NAME}

re: fclean clean all

lib:
	@if [ ! -f "$(LIBFT_NAME)" ]; then \
		make -C $(LIBFT_PATH); \
		mv $(LIBFT_PATH)/$(LIBFT_NAME) .; \
	fi

libft:
	@if [ ! -d "./lib" ]; then \
		mkdir -p lib; \
	fi
	@if [ -d "./lib/libft" ]; then \
		rm -rf ./lib/libft; \
	fi
	git clone $(LIBFT_GH) $(LIBFT_PATH)

test:
# time_die time_eat time_sleep
# not eat and die
	./philo 1 800 200 200
# no one die
	./philo 5 800 200 200
# stop when all has eaten 7 meals
	./philo 5 800 200 200 7
# no one die
	./philo 4 410 200 200
# one die
	./philo 4 310 200 100

leaksMac:
	export MallocStackLogging=1
	leaks --atExit --list -- ./philo 0 800 200 200

leaksCampus:
	valgrind --leak-check=yes ./client 500502 "assdadasd"

.PHONY: all clean fclean re lib
