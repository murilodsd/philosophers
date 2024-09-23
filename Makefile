CC=cc
CCFLAGS=-Wall -Wextra -Werror -g
#MANDATORY
NAME=
SRC_PATH=src/
SRCS_NAMES=
OBJ_PATH=build/
OBJS_NAMES=$(SRCS_NAMES:.c=.o)
OBJS=$(addprefix $(OBJ_PATH), $(OBJS_NAMES))
#BONUS
NAME_BONUS=$(addsuffix _bonus, $(NAME))
SRC_PATH_BONUS=src_bonus/
SRCS_NAMES_BONUS=
SRCS_BONUS=$(addprefix $(SRC_PATH_BONUS), $(SRCS_NAMES_BONUS))
OBJ_PATH_BONUS=build_bonus/
OBJS_NAMES_BONUS=$(SRCS_NAMES_BONUS:.c=.o)
OBJS_BONUS=$(addprefix $(OBJ_PATH_BONUS), $(OBJS_NAMES_BONUS))
#GENERAL
LIB_STATIC_NAME = libft.a
LIB_PATH=lib/
LIBS_FLAGS=-l$(patsubst lib%.a, %, $(LIB_STATIC_NAME)) -L$(LIB_PATH)
LIB_STATIC= $(addprefix $(LIB_PATH) , $(INCLUDE_PATH))
INCLUDE_PATH=./include/ ./lib/*/include/
INCLUDE_FLAG=$(addprefix -I , $(INCLUDE_PATH))
RM=rm -f

all: libs $(NAME)

$(NAME): $(OBJS) $(LIB_STATIC)
	$(CC) $(CCFLAGS) $(OBJS) $(INCLUDE_FLAG) $(LIBS_FLAGS) -o $(NAME)

libs:
	make all -C lib/libft

bonus: libs $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIB_STATIC)
	$(CC) $(CCFLAGS) $(OBJS_BONUS) $(INCLUDE_FLAG) $(LIBS_FLAGS) -o $(NAME_BONUS)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(CCFLAGS) -c $< -o $@ $(INCLUDE_FLAG)

$(OBJ_PATH_BONUS)%.o: $(SRC_PATH_BONUS)%.c
	mkdir -p $(OBJ_PATH_BONUS)
	$(CC) $(CCFLAGS) -c $< -o $@ $(INCLUDE_FLAG)

clean:
	make clean -C lib/libft
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	make fclean -C lib/libft
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all bonus

norm:
	norminette -R CheckDefine $(INCLUDE_PATH)*.h
	norminette -R CheckForbiddenSourceHeader $(SRC_PATH)*.c

.PHONY=all bonus clean fclean re norm libs
