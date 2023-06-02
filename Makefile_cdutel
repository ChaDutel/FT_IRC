#update on every project
NAME := ircserv
LST_SRC := serv

#update to match c or cpp
CC := c++
FILE_EXT := .cpp
HEADER_EXT := .hpp
CPPFLAGS := -std=c++98

#update if needed
CFLAGS = -Wall -Wextra -Werror -MD -I$(DIR_INC) #-fsanitize=address -g3
DIR_SRC := .#.
#SUB_DIR_LST := core test

#shouldn't need to update
RM := rm -rf
MD := mkdir -p

DIR_INC := include
DIR_OBJ := .object

OBJ=$(addprefix $(DIR_OBJ)/,$(addsuffix .o,$(LST_SRC)))
DEP=$(addprefix $(DIR_OBJ)/,$(addsuffix .d,$(LST_SRC)))
#SUB_DIR=$(addprefix $(DIR_OBJ)/,$(SUB_DIR_LST))

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

$(DIR_OBJ)/%.o : $(DIR_SRC)/%$(FILE_EXT) Makefile | $(DIR_OBJ) #$(SUB_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(DIR_OBJ)    :
	$(MD) $(DIR_OBJ);

$(SUB_DIR)    :
	$(MD) $@

clean :
	$(RM) $(DIR_OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re

-include $(DEP)
