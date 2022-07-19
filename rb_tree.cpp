#include "rb_tree.hpp"

rb_tree::rb_tree()
{

}

rb_tree::rb_tree( rb_tree const &obj )
{

}

rb_tree::~rb_tree()
{
}

rb_tree &	rb_tree::operator=( rb_tree const & obj )
{
	std::cout << "Copy assignment operator called" << std::endl;
	return *this;
}

void		rb_tree::setVar( type var)
{
	_var= var;
}

type		rb_tree::getVar( void ) const
{
	return _var;
}

std::ostream &	operator<<( std::ostream & o, rb_tree const & obj )
{
	return o;
}