
# Compilation
CC		= clang++
CFLAGS	=  -Werror -Wall -Wextra -Wshadow -Wconversion -Wpedantic -std=c++98
C_OBJ	= $(CC) $(CFLAGS) $(INC) -c $< -o $@
C_MAIN	= $(CC) $(CFLAGS) $(INC) $(OBJ) $(MAIN) -o $(NAME)

# Program
NAME	= container
DESC	= \"ft_container : a STL project\"

# Directories
D_SRC	= src
D_INC	= include
D_OBJ	= objs


# Files
MAIN	= test.cpp

_HEAD	= Vector.hpp
HEAD	= $(patsubst %.hpp, $(D_INC)/%.hpp, $(_HEAD))

_SRC	= 	
SRC		= $(patsubst %.cpp, $(D_SRC)/%.cpp, $(_SRC))

_OBJ	= $(_SRC:.cpp=.o)
OBJ		= $(patsubst %.o, $(D_OBJ)/%.o, $(_OBJ))

$(D_OBJ)/%.o : %.cpp
		$(C_OBJ)

# Recipes
all		: $(NAME)

$(NAME)	: $(HEAD) $(SRC) $(D_OBJ) $(OBJ) $(MAIN)
		$(C_MAIN)
		# $(shell echo "Compiling $(P_NAME) done!")
		# $(shell echo "Executable is : $(NAME)")

$(D_OBJ)	:
		@ mkdir $(D_OBJ)

clean	: 
		@ rm -rf $(D_OBJ)
		# $(shell echo "Cleaning done!")

fclean	: clean
		@ rm -f $(NAME)

re		: fclean all

exe		: test
		# $(shell ./$(NAME))

test	: _test $(NAME)

_test	:
		$(eval CFLAGS= -Wall -Wextra -Wshadow -Wconversion -Wpedantic -std=c++98)

.PHONY	: all clean fclean re test exe