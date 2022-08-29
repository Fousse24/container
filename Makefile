
# Compilation
CC		= clang++
CFLAGS	=  -Werror -Wall -Wextra -Wshadow -Wconversion -Wpedantic -std=c++98 #-Werror
C_OBJ	= $(CC) $(CFLAGS) $(INC) -c $< -o $@
C_MAIN	= $(CC) $(CFLAGS) $(INC) $(OBJ) $(MAIN) -o $(NAME)

# Program
NAME	= container
DESC	= \"ft_container : a STL project\"

# Directories
D_SRC	= srcs
D_INC	= includes
D_VECT	= $(D_SRC)/Vector
D_MAP	= $(D_SRC)/Map
D_OBJ	= objs

# Includes
INC		= 


# Files
MAIN	= test.cpp

_HEAD	= $(D_INC)/iterator.hpp			\
		  $(D_INC)/iterator_traits.hpp	\
		  $(D_INC)/rb_tree.hpp			\
		  $(D_INC)/enable_if.hpp		\
		  $(D_INC)/test.hpp				\
		  \
		  $(D_VEC)/vector.hpp 			\
		  $(D_VEC)/vector_iterator.hpp	\
		  \
		  $(D_MAP)/map.hpp				\
		  $(D_MAP)/map_iterator.hpp

HEAD	= $(_HEAD)

_SRC	= test_pair.cpp
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