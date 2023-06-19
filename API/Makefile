CC						=	clang

NAME					=	api

SRC_DIR					=	./src
UTILS_DIR				=	${SRC_DIR}/utils
ROUTES_DIR				=	${SRC_DIR}/routes
SERVER_DIR				=	${SRC_DIR}/server
MODELS_DIR				=	${SRC_DIR}/models
LOGGER_DIR				=	${SRC_DIR}/logger
CONFIG_DIR				=	${SRC_DIR}/config
REQUEST_DIR				=	${SRC_DIR}/request
DATABASE_DIR			=	${SRC_DIR}/database
MIDDLEWARE_DIR			=	${SRC_DIR}/middlewares
CONTROLERS_DIR			=	${SRC_DIR}/controllers

MONGOOSE_DIR			=	./libs/mongoose/src

INC_DIR					=	-I./includes/ \
							-I./libs/mongoose/includes \
							-I/usr/local/include/libbson-1.0 \
							-I/usr/local/include/libmongoc-1.0 \

LIB_DIR					=	-lssl -lcrypto -lmongoc-1.0 -lbson-1.0

CFLAGS					=	-Wall -Wextra -Werror -g ${INC_DIR}

LFLAGS					=	-Wall -Wextra -Werror -g ${LIB_DIR}

SOURCES					=	${SRC_DIR}/main.c \
							${MONGOOSE_DIR}/mongoose.c \
							${ROUTES_DIR}/get_routes.c \
							${REQUEST_DIR}/get_method.c \
							${MIDDLEWARE_DIR}/auth_middleware.c \
							${MODELS_DIR}/user_model.c ${MODELS_DIR}/auth_model.c \
							${CONFIG_DIR}/load_config.c ${CONFIG_DIR}/get_instance_config.c ${CONFIG_DIR}/clear_config.c\
							${UTILS_DIR}/mensage/send_msg.c \
								${UTILS_DIR}/time/now.c \
								${UTILS_DIR}/validators/user_validators.c \
								${UTILS_DIR}/security/get_hash.c ${UTILS_DIR}/security/token.c \
								${UTILS_DIR}/request/get_body.c ${UTILS_DIR}/request/get_query_id.c \
								${UTILS_DIR}/controllers/send_result.c ${UTILS_DIR}/controllers/valid_body.c \
								${UTILS_DIR}/parse/json_to_bson.c ${UTILS_DIR}/parse/str_to_strhex.c ${UTILS_DIR}/parse/strhex_to_str.c \
							${SERVER_DIR}/connect_server.c ${SERVER_DIR}/disconnect_server.c ${SERVER_DIR}/get_instance_server.c \
							${LOGGER_DIR}/add_log.c ${LOGGER_DIR}/write_logger.c ${LOGGER_DIR}/complete_logger.c ${LOGGER_DIR}/get_instance_logger.c \
							${CONTROLERS_DIR}/user_controller.c ${CONTROLERS_DIR}/auth_controller.c ${CONTROLERS_DIR}/roll_controller.c ${CONTROLERS_DIR}/class_controller.c  ${CONTROLERS_DIR}/race_controller.c \
							${DATABASE_DIR}/database_connect.c ${DATABASE_DIR}/database_disconnect.c ${DATABASE_DIR}/get_instance_database.c ${DATABASE_DIR}/create_index.c \
								${DATABASE_DIR}/generic/db_select.c ${DATABASE_DIR}/generic/db_insert.c \


OBJS					=	${SOURCES:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	@${CC} -o ${NAME} ${OBJS} ${LFLAGS}
	@echo "\n\033[0;32mDone !"
	@echo -n "\033[0m"

%.o: %.c
	@printf "\033[0;33mGenerating server objects... %-33.33s\r" $@
	@${CC} -c $< -o $@ ${CFLAGS}

clean:
	@rm -f ${OBJS}

fclean: clean
	@rm -f ${NAME}

re: fclean	all

run:
	clear && make re && ./api

test:
	clear && make re && valgrind --leak-check=full --show-reachable=yes ./api 2> valgrind_result.txt

.PHONY: all clean fclean re test run