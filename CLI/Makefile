CC						=	clang

NAME					=	cli

SRC_DIR					=	./src
IO_DIR					=	${SRC_DIR}/io
CONFIG_DIR				=	${SRC_DIR}/config
DISPLAY_DIR				=	${SRC_DIR}/display
REQUEST_DIR				=	${SRC_DIR}/request

INC_DIR					=	-I./includes/

CFLAGS					=	-Wall -Wextra -Werror -g ${INC_DIR}

LFLAGS					=	-Wall -Wextra -Werror -g

SOURCES					=	\
							./src/main.c \
							${IO_DIR}/read_log.c \
							${CONFIG_DIR}/load_config.c ${CONFIG_DIR}/show_malformated_msg.c \
							${DISPLAY_DIR}/display_list.c ${DISPLAY_DIR}/display_log.c ${DISPLAY_DIR}/display_table.c ${DISPLAY_DIR}/set_color.c \
								${DISPLAY_DIR}/list/clear_list.c ${DISPLAY_DIR}/list/init_list.c \
								${DISPLAY_DIR}/table/clear_table.c ${DISPLAY_DIR}/table/init_table.c \
							${REQUEST_DIR}/add_request.c ${REQUEST_DIR}/clear_request.c ${REQUEST_DIR}/create_request.c ${REQUEST_DIR}/get_request.c ${REQUEST_DIR}/load_requests.c \

OBJS					=	$(SOURCES:.c=.o)

all: $(NAME)

$(NAME): ${OBJS}
	@$(CC) -o $(NAME) $(OBJS) $(LFLAGS)
	@echo "\n\033[0;32mDone !"
	@echo -n "\033[0m"

%.o: %.c
	@printf "\033[0;33mGenerating CLI objects... %-33.33s\r" $@
	@$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean	all

run:
	clear && make re && ./cli

test:
	clear && make re && valgrind --leak-check=full --show-reachable=yes ./cli -a

.PHONY: all clean fclean re test