template <class T>
class link_list{
public:

	struct node{
		node*next;
		T data;
	};
	node* head;
	node* end;

	void append( const link_list<T>& );	
	void insert( T );
	link_list();
};

#include "link_list.cpp"
