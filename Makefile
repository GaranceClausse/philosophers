NAME = philosophers
OBJS = $(addprefix ./srcs/, utils.o checker.o init_and_destroy.o main.o philo.o action.o \
)

CFLAGS = -Iincludes -std=c99 -Wall -Wextra -Werror
DBFLAGS = -g3

all: $(NAME)

debug: CFLAGS+=$(DBFLAGS)
debug:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $^ -o $@ -lpthread

clean: 
	$(RM) $(OBJS)
	
fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re debug