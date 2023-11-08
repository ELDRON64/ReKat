# ifndef NUM_UTIL
# define NUM_UTIL
// utilitys implementation
# include "common.hpp"

// true if litte eldian
bool eldian 
( ) {
	short test_eldian = 1;

	// true if little eldian ------------------------
	if ( *(char*)&test_eldian == 1 ) { return true;	}
	return false;
}

unsigned char * number::copy 
( const unsigned char* _src, num_t _n, bool is_char ) {

	if ( _n == 0 ) { return ( unsigned char* ) calloc ( 1, sizeof ( char ) ); }

	unsigned char * _rec = ( unsigned char* ) calloc ( _n, sizeof ( char ) );

	if ( eldian ( ) || is_char ) {
		for ( num_t i = 0; i < _n; i++ ) { _rec[i] = _src[i]; }
		return _rec;
	} 
	
	for ( num_t i = 0; i < _n; i++ ) { _rec[_n - i -1] = _src[i]; }
	return _rec;	
}

// resize the number
void number::resize ( num_t _n ) {
	if ( _n == 0 ) 			 { return; }
	if ( number_size == _n ) { return; }

	number_size = _n;
	number_chars = (unsigned char *) realloc ( number_chars, _n );
}


// removes end zeros -
void number::normalize 
( ) {
	num_t end_zeros = 0;

	for ( num_t i = number_size - 1; i > 0; i++ ) {
		if ( number_chars[i] == 0 ) { end_zeros ++; continue;}
		break;
	}

	resize( number_size - end_zeros );
}


number::number
( const num_t &n ) {
	number_size = sizeof( num_t );
	number_chars = copy ( (unsigned char*)&n , sizeof ( num_t ) );
}
number::number
( const unsigned char *_buf, num_t _n, bool char_mode ) {
	number_size = _n;
	number_chars = copy ( _buf, _n, char_mode );
}
number::number
( ) {
	number_size = 1;
	number_chars = (unsigned char*) calloc ( 1, sizeof ( char ) );
}
number::~number
( ) {
	free ( number_chars );
}   


// assertion
number& number::operator = 
( const number & number2 ) {
	free ( this->number_chars );
	number_chars = copy ( number2.number_chars, number2.number_size );
	number_size  = number2.number_size;
	return *this;
}


// iteration 
char number::operator[] ( num_t value ) 
{ return value > this->number_size ? 0 : this->number_chars[value]; }















std::vector < number > number::cambio_in_base 
( number base ) {
	std::vector < number > out;

	if ( base > *this ) {
		out.push_back(*this);
		return out;		
	}

	number zero;
	number one(1);
	number a = *this;

	while ( a != zero ) {
		number number3 = 0;

		if ( base > a ) {
			out.push_back(a.number_chars[0]);
			break;
		}

		number b = base;
		while ( b < a>>one ) {
			b <<= one;
		}

		while ( b != base ) {
			if ( a >= b ) {
				a -= b;
				++number3;
			}
			number3 <<= one;
			b >>= one;
		}

		while ( a >= b ) {
			if ( a == b ) {	++number3; a = number(); break; }
			a -= b;
			++number3;
		}

		if ( a == zero ) {
			out.push_back(0);
		} else {
			out.push_back(a);
		}
		a = number3;
	}

	return out;
}
void number::cambio_da_base 
( std::vector<number> numb, number base ) {
	number number3;

	number exp (1);
	for ( number n : numb ) {
		number3 += exp * n;
		exp *= base;
	}

	*this = number3;
}

std::string number::print_base_10 ( ) {

	number base(100);
	if ( base > *this ) { return std::to_string(number_chars[0]); }

	std::vector < char > out;
	number zero;
	number one(1);
	number a = *this;

	size_t current = 0;

	while ( a != 0LL ) {
		number number3 = 0;
		current++;

		// divido per 100

		if ( base > a ) {
			out.push_back(a.number_chars[0]);
			//std::cout << current << ":\t" << (int)out[current-1] << '\n';
			//std::cout << " \nend at: " << current << '\n';
			break;
		}

		number b = base;
		// trovo il massimo 1 di a
		while ( b < a>>one ) {
			b <<= one;
		}

		while ( b != base ) {
			if ( a >= b ) {
				a -= b;
				++number3;
			}
			number3 <<= one;
			b >>= one;
		}

		/*if ( a >= b ) {
			++number3;
			a-=b;
		}*/

		while ( a >= b ) {
			if ( a == b ) { //std::cout << "a = zero";
				++number3; a = number(); break; 
			}
			//std::cout << a << '\n';
			a -= b;
			++number3;
		}

		if ( a == zero ) {
			//std::cout << "a = 2zero";
			out.push_back(0);
		} else {
			//std::cout << a << '\n';
			out.push_back(a.number_chars[0]);
		}
		//std::cout << '\n' << current << ":\t" << (int)out[current-1] << '\n';

		a = number3;
	}
	//std::cout << '\n';

	// converto il vettore
	std::string out_c = "";
	size_t size = out.size();
	out_c.resize( size * 2 );

	for (size_t i = 0; i < size; i++) {
		//std::cout << i << ":\t" << (int)out [size-i-1] << '\n';
		out_c [i * 2]	  = out[ size-i-1 ] / 10 + 48;
		out_c [i * 2 + 1] = out[ size-i-1 ] % 10 + 48;
	}

	return out_c;
}

char* bit_rappresentation ( unsigned char c ) {
	char* rap = (char*) calloc (8,sizeof(char));
	//std::cout << "car ";
	for (char i = 0; i < 8; i++) {
		if ( c % 2 == 0 ) { rap[i] = '0'; }
		else { rap[i] = '1'; }

		c >>= 1;
		//std::cout <<(int) c << " ";
	}
	return rap;	
}

std::ostream& operator << (std::ostream& os, number& numb ) {
	os << "\nnumber of size: " << numb.number_size << '\n';
	os << "value of number divided in bits:  \n";
	for
	( num_t i = 0; i < numb.number_size; i++) {
		os << bit_rappresentation (  numb.number_chars[i] )<< ' ';
		os << '(' << (int) numb.number_chars[i] << ") ";
		if ( (i + 1) % 8 == 0 ) {
			os << '\n';
		}
	}

	//os << '\n' << numb.print_base_10();

	return os;
}

# endif