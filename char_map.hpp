

#define ARR_SIZE 63

template<class T> 
class char_map{

public:
	class iterator{
	private:
		unsigned int index = 0;
		char_map<T>*map;
	public:
		//Constructor. Move index to the first element.
		iterator(char_map<T>*);
		//Return the data. If there is no corresponding data, it will return 0.
		T get_data();
		//Move the iterator to next element.
		//Return true if it move successfully. 
		//Otherwise, if the iterator has been at the end of the array, return false.
		bool next();
	};

	int insert( char key, T data );	
	T find( char key );	
	T remove( char key );
	unsigned int get_size();
	iterator get_iterator();

private:	
	int size = 0;
	T array[ARR_SIZE] = {0} ;
	static unsigned int key_to_ind( char key );

};


template <class T>
unsigned char_map<T>::key_to_ind( char key ){
	if( 'a' <= key && key <= 'z' ){
		return key - 'a';
	}
	if( 'A' <= key && key <= 'Z' ){
		return key - 'A' + 26;
	}
	if( '0' <= key && key <= '9' ){
		return key - '0' + 52;
	}
	if( key == '\0' ){
		return 62;
	}
}

template <class T>
int char_map<T>::insert( char key, T data ){

	unsigned int index = key_to_ind( key );
	if( array[index] == 0 ){
		array[index] = data;
		size += 1;
		return 0;
	}else{
		return -1;
	}
}

template <class T>
typename char_map<T>::iterator char_map<T>::get_iterator(){
	return iterator( this );
}

template <class T >
T char_map<T>::find( char key){	
	unsigned int index = key_to_ind( key );
	return array[index];
}

template <class T>
T char_map<T>::remove( char key ){
	unsigned int index = key_to_ind( key );
	if( array[index] != 0 ){
		T tmp = array[index];
		array[index] = 0;
		size -= 1;
		return tmp;
	}


#ifdef _DEBUG
	//	assert( size >= 0 );
#endif

}


template <class T>
unsigned int char_map<T>::get_size(){
	return size;
}

template <class T>
char_map<T>::iterator::iterator(char_map<T>* map){
	this -> map = map;
	while( map -> array[index] == 0 && index < ARR_SIZE){
		index +=1;
	}
}

template <class T>
T char_map<T>::iterator::get_data(){
	return map -> array[index];
}

template <class T>
bool char_map<T>::iterator::next(){
	if( index == ARR_SIZE -1 ){
		return false;
	}
	while( map -> array[index] == 0 ){
		if( index == ARR_SIZE - 1 ){
			return false;
		}
		index += 1;
	}
	return true;
}

