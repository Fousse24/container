
# Compilation
CC		= c++
CFLAGS	=  -Werror -Wall -Wextra -Wshadow -Wpedantic -std=c++98
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
MAIN		= $(D_TEST)/official_main.cpp
MAP_TEST	= $(D_TEST)/test_map.cpp
VECT_TEST	= $(D_TEST)/test_vector.cpp
PAIR_TEST	= $(D_TEST)/test_pair.cpp $(D_TEST)/test.cpp
RBT_TEST	= $(D_TEST)/test_rbtree.cpp

_HEAD	= $(D_INC)/iterator.hpp			\
		  $(D_INC)/iterator_traits.hpp	\
		  $(D_INC)/enable_if.hpp		\
		  $(D_INC)/test.hpp				\
		  $(D_INC)/pair.hpp				\
		  $(D_INC)/ft_lib.hpp			\
		  \
		  $(D_VECT)/vector.hpp 			\
		  $(D_VECT)/vector_iterator.hpp	\
		  \
		  $(D_MAP)/map.hpp				\
		  \
		  $(D_TREE)/rbtree.hpp			\
		  $(D_TREE)/rbtree_iterator.hpp	\
		  $(D_TREE)/rbnode.hpp			\

HEAD	= $(_HEAD)

_TEST_HEAD	= $(D_TEST)/tester.hpp			\
		  	  $(D_TEST)/tester_map.hpp		\
		  	  $(D_TEST)/tester_vector.hpp	\
		  	  $(D_TEST)/timer.hpp			\

# Recipes
all		: $(NAME)

$(NAME)	: $(HEAD) $(MAIN)
		$(C_MAIN)
		# $(shell echo "Compiling $(P_NAME) done!")
		# $(shell echo "Executable is : $(NAME)")

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
		$(eval MAIN= $(MAP_TEST))

rbt		: fclean _test _rbt $(NAME)
_rbt	: 
		$(eval MAIN= $(RBT_TEST))

vector	: fclean _test _vector $(NAME)
_vector	: 
		$(eval MAIN= $(VECT_TEST))

pair	: fclean _test _pair $(NAME)
_pair	: 
		$(eval MAIN= $(PAIR_TEST))

_test	:
		$(eval CFLAGS= -g -Wall -Wextra -Wshadow -Wconversion -Wpedantic -std=c++11)
		$(eval HEAD= -g $(HEAD) $(_TEST_HEAD))

.PHONY	: all clean fclean re test exe