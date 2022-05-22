NAME = philosophers
OBJS = $(addprefix srcs/, libft.o main.o\
)

CFLAGS = -Iincludes -Wall -Wextra -Werror
DBFLAGS = -g3

all: $(NAME)

debug: CFLAGS+=$(DBFLAGS)
debug:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $^ -o $@ 

clean: 
	$(RM) $(OBJS)
	
fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re debug