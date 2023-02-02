

template<class C>
class Tester
{
private:
	C _container;
public:
	Tester() : _container(C()) {};
	Tester( C container ) : _container(container) {};
	~Tester() {};
	Tester( const & tester ) { *this = tester };

	

}