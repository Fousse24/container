
# Compilation
CC		= c++
CFLAGS	=  -Werror -Wall -Wextra -Wshadow -Wconversion -Wpedantic -std=c++11 #-Werror
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
D_TREE	= $(D_SRC)/Tree
D_TEST	= $(D_SRC)/Tester
D_OBJ	= objs

# Includes
INC		= -I$(D_INC) -I$(D_VECT) -I$(D_MAP) -I$(D_TREE)


# Files
MAIN	= test_map.cpp
MAP_M	= $(D_TEST)/test_map.cpp

_HEAD	= $(D_INC)/iterator.hpp			\
		  $(D_INC)/iterator_traits.hpp	\
		  $(D_INC)/enable_if.hpp		\
		  $(D_INC)/test.hpp				\
		  \
		  $(D_VECT)/vector.hpp 			\
		  $(D_VECT)/vector_iterator.hpp	\
		  \
		  $(D_MAP)/map.hpp				\
		  \
		  $(D_TREE)/rbtree.hpp			\
		  $(D_TREE)/rbtree_iterator.hpp	\
		  $(D_TREE)/rbnode.hpp	\
		  \
		#   $(D_TEST)/test_map.cpp		\



HEAD	= $(_HEAD)

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

map		: fclean _test _map $(NAME)

_map	: 
		$(eval MAIN= $(MAP_M))

_test	:
		$(eval CFLAGS= -g -Wall -Wextra -Wshadow -Wconversion -Wpedantic -std=c++11)

.PHONY	: all clean fclean re test exe