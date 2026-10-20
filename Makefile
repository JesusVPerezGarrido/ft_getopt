NAME	:=	getopt.a

CPP		:= cc
CFLAGS	:= -Wall -Werror -Wextra --std=c89

INCS	:= -Iinc
HDRS	:=	$(addprefix inc/, \
				ft_getopt.h )

FILES	:=	ft_getopt.c
SRCS	:=	$(addprefix src/, $(FILES))
OBJS	:=	$(addprefix	obj/, $(FILES:.c=.o))
TEST_BIN	:=test_getopt

all: ${NAME}

test: $(TEST_BIN)
	./$(TEST_BIN)
	@rm -f $(TEST_BIN)

$(TEST_BIN): tests/main.c $(SRCS) $(HDRS)
	@echo "Compiling: tests/main.c"
	@$(CPP) $(CFLAGS) $(INCS) tests/main.c $(SRCS) -o $@

obj:
	@mkdir -p obj

${NAME}: ${OBJS}
	@echo "Creating: $(NAME)"
	@ar rcs ${NAME} ${OBJS}

obj/%.o: src/%.c $(HDRS) | obj
	@echo "Compiling: $(notdir $<)"
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	@echo "Removing: $(NAME:.a=) object files"
	@rm -rf obj

fclean: clean
	@echo "Removing: $(NAME)"
	@rm -f ${NAME}

re: fclean all

.PHONY: all test clean fclean re bonus obj
