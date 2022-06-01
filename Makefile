NAME = philosophers
OBJS = $(addprefix ./srcs/, libft.o parser.o exit.o main.o philo.o \
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