# ifndef NUM_ARIT
# define NUM_ARIT
// arithmetic implementation
# include "common.hpp"

void number::swap 
( number &a, number &b ) {
	number c = a;
	a = b;
	b = c;
}

number& number::operator +=  ( const number& rhs ) { 
	num_t max_dim = this->number_size;
	if ( rhs.number_size > max_dim ) 
	{ max_dim = rhs.number_size; }

	int overflow = 0;
	for ( num_t i = 0; i < max_dim; i++ ) {
		unsigned char a = this->number_chars[i];
		unsigned char b = rhs.number_chars[i];

		int room = 255 - ( a + overflow );
		
		this->number_chars[i] += b + overflow; 
		if (b <= room) {
			overflow = 0;
		} else {
			overflow = 1;
		}
	}
	if ( overflow == 1 ) {
		this->resize ( this->number_size + 1 );
		this->number_chars[this->number_size - 1] = 1;
	}

	return *this; // return the result by reference
}
number& number::operator -=  ( const number& rhs ) { 
	if ( *this == rhs ) { num z; return z; }
	if ( *this < rhs )  { num z; return z; }

	num_t max_dim = number_size;
	if ( rhs.number_size > max_dim ) 
	{ max_dim = rhs.number_size; } 

	int underflow = 0;
	for ( num_t i = 0; i < max_dim; i++ ) {
		unsigned char a = this->number_chars[i];
		unsigned char b = rhs.number_chars[i];

		int room = ( a - underflow );
		
		this->number_chars[i] -= b + underflow; 
		// std::cout << number3;
		if (b <= room) { underflow = 0; } // no underflow
		else { underflow = 1; } // underflow check
	}
	if ( underflow == 1 ) {
		// std::cout << "+ + calling for resize\n";
		this->resize ( this->number_size + 1 );
		this->number_chars[this->number_size - 1] = 1;
	}

	return *this; // return the result by reference
}
number& number::operator *=  ( const number& rhs ) { 
	/* addition of rhs to *this takes place here */
	return *this; // return the result by reference
} 
number& number::operator /=  ( const number& rhs ) { 
	/* addition of rhs to *this takes place here */
	return *this; // return the result by reference
} 
number& number::operator %=  ( const number& rhs ) { 
	/* addition of rhs to *this takes place here */
	return *this; // return the result by reference
} 
number& number::operator <<= ( const number& rhs ) { 
	number i;
	do {
		// eseguo il bit shift
		unsigned char carry = 0;

		for (size_t y = 0; y < this->number_size; y++) {
			// verifico se il bit maggiore è settato
			unsigned char b = this->number_chars[y]; 
			
			this->number_chars[y] <<= 1;

			this->number_chars[y] += carry;
			
			if ( b >= 128 ) {
				carry = 1;
			} else {
				carry = 0;
			}
		}
		if ( carry == 1 ) {
			this->resize ( this->number_size + 1 );
			this->number_chars[this->number_size - 1] = 1;
		}
		
		++i;
	} while ( i < rhs );

	this->normalize();
	return *this; // return the result by reference
}
number& number::operator >>= ( const number& rhs ) { 
	/* addition of rhs to *this takes place here */
	return *this; // return the result by reference
}

/*
number& number::operator + 
( const number & number2 ) {
	number n2 = number2;

	num_t max_dim = number_size;
	if ( number2.number_size > max_dim ) {
		max_dim = number2.number_size;
		this->resize(max_dim);
	} else { n2.resize(max_dim); }

	number number3 = *this;

	int overflow = 0;
	for ( num_t i = 0; i < max_dim; i++ ) {
		unsigned char a = number3.number_chars[i];
		unsigned char b = number2.number_chars[i];

		int room = 255 - ( a + overflow );
		
		number3.number_chars[i] += b + overflow; 
		if (b <= room) {
			overflow = 0;
		} else {
			overflow = 1;
		}
	}
	if ( overflow == 1 ) {
		number3.resize ( number3.number_size + 1 );
		number3.number_chars[number3.number_size - 1] = 1;
	}

	return number3;	
}
number& number::operator - 
( const number & number2 ) {
	if ( *this == number2 ) { num z; return z; }
	if ( *this < number2 )  { num z; return z; }
	num_t original_1 = this->number_size;
	num_t original_2 = number2.number_size;

	num_t max_dim = number_size;
	if ( number2.number_size > max_dim ) {
		max_dim = number2.number_size;
		this->resize(max_dim);
	} // else { number2.resize(max_dim); }

	number number3 = *new number;
	number3.number_size = this->number_size;
	number3.number_chars = copy ( this->number_chars, this->number_size );

	int underflow = 0;
	for ( num_t i = 0; i < max_dim; i++ ) {
		unsigned char a = number3.number_chars[i];
		unsigned char b = number2.number_chars[i];

		int room = ( a - underflow );
		// std::cout << "i: " << i << " a: " << (int)a << " b: " << (int)b << '\n'; 
		// std::cout << "under " << underflow << '\n';
		// std::cout << "room " << (int)room << '\n';
		
		number3.number_chars[i] -= b + underflow; 
		// std::cout << number3;
		// std::cout << "n3["<<i<<"] " << (int) number3.number_chars[i] << '\n';
		if (b <= room) {
			// no underflow
			underflow = 0;
		} else {
			// underflow check
			// std::cout << "+ underflow find\n";
			underflow = 1;
		}
	}
	if ( underflow == 1 ) {
		// std::cout << "+ + calling for resize\n";
		number3.resize ( number3.number_size + 1 );
		number3.number_chars[number3.number_size - 1] = 1;
	}


	this->resize ( original_1 );

	return number3;	
}
number& number::operator * 
( const number & number2 ) {
	number number3 = *new number;

	number a = *this;
	number b = number2;
	number zero;
	number one (1);

	if ( b > a ) { swap(a, b); }
		
	while 
	( b != zero ) {
		if (b.number_chars[0] & 0x1 ) { number3 += a; }
		a += a;
		b >>= one;
	}

	return number3;
}
number& number::operator / 
( const number & number2 ) {
	if ( *this == number2 ) { return *new number(1);}

	if ( *this > number2 ) {
		return *new number();
	}
	number number3 = *new number;

	number a = *this;
	number b = number2;
	b.normalize();
	std::cout << a << b;


	// trovo il massimo 1 di a
	while ( b <= a ) {
		std::cout << "\na";
		b <<= 1;
	}

	std::cout << a << b << "\nstamp\n";

	while ( b != number2 ) {
		//std::cout << "b\n";
		if ( a >= b ) {
			a -= b;
			++number3;
		}
		number3 <<= 1;
		b >>= 1;
	}

	while ( a >= b ) {
		if ( a == b ) { return ++number3; }
		a -= b;
		++number3;
	}

	return number3;
}
number& number::operator % 
( const number & number2 ) {

	if ( *this == number2 ) { return *new number(1);}

	if ( *this > number2 ) {
		return *new number();
	}

	number a = *this;
	number b = number2;

	number shift(0);
	// trovo il massimo 1 di a
	while ( b < a ) {
		++shift;
		b <<= 1;
	}

	while ( b != number2 ) {
		if ( a > b ) {
			a -= b;
		}
		b >>= 1;
	}
	while ( a >= b ) {
		if ( a == b ) { return *new number(); }
		a -= b;
	}

	return a;
}

number& number::operator << 
( const number & number2 ) {
	// moltiplica per 2 ^ number2

	number number3 = *new number;
	number3.number_size = this->number_size;
	number3.number_chars = copy ( this->number_chars, this->number_size );

	number i = 1;
	do {
		// eseguo il bit shift
		unsigned char carry = 0;

		for (size_t i = 0; i < number3.number_size; i++) {
			// verifico se il bit maggiore è settato
			unsigned char b = number3.number_chars[i]; 
			
			number3.number_chars[i] <<= 1;

			number3.number_chars[i] += carry;
			
			if ( b >= 128 ) {
				carry = 1;
			} else {
				carry = 0;
			}
		}
		if ( carry == 1 ) {
			number3.resize ( number3.number_size + 1 );
			number3.number_chars[number3.number_size - 1] = 1;
		}
		
		++i;
	} while ( i < number2 );

	number3.normalize();
	return number3;
	
}
number& number::operator >> 
( const number & number2 ) {
	// divide per 2 ^ number2

	number number3 = *new number;
	number3.number_size = this->number_size;
	number3.number_chars = copy ( this->number_chars, this->number_size );

	number i = 1;
	do {
		// eseguo il bit shift 
		unsigned char carry = 0;

		for 
		(size_t i = number3.number_size; i > 0; i--) {
			unsigned char b = number3.number_chars[i - 1]; 
			
			number3.number_chars[i-1] >>= 1;

			number3.number_chars[i-1] += carry;
			if ( b & 0x1 ) {
				carry = 128;
			} else {
				carry = 0;
			}
		}
		++i;
	} while ( i < number2 );
	number3.normalize();

	return number3;
}
*/




// prefix increment
number& number::operator++ ( ) {
    // actual increment takes place here
    return *this; // return new value by reference
}
// prefix decrement
number& number::operator-- ( ) {
    // actual decrement takes place here
    return *this; // return new value by reference
}



// -----------------------------------------------------------
// derivati --------------------------------------------------
inline number  operator +  ( number lhs, const number& rhs ) {
	lhs += rhs; // reuse compound assignment
	return lhs; // return the result by value (uses move constructor)
}
inline number  operator -  ( number lhs, const number& rhs ) {
	lhs -= rhs; // reuse compound assignment
	return lhs; // return the result by value (uses move constructor)
}
inline number  operator *  ( number lhs, const number& rhs ) {
	lhs *= rhs; // reuse compound assignment
	return lhs; // return the result by value (uses move constructor)
}
inline number  operator /  ( number lhs, const number& rhs ) {
	lhs /= rhs; // reuse compound assignment
	return lhs; // return the result by value (uses move constructor)
}
inline number  operator %  ( number lhs, const number& rhs ) {
	lhs %= rhs; // reuse compound assignment
	return lhs; // return the result by value (uses move constructor)
}
inline number  operator << ( number lhs, const number& rhs ) {
	lhs <<= rhs; // reuse compound assignment
	return lhs; // return the result by value (uses move constructor)
}
inline number  operator >> ( number lhs, const number& rhs ) {
	lhs >>= rhs; // reuse compound assignment
	return lhs; // return the result by value (uses move constructor)
} 
number number::operator ++ ( int )
{
	number old = *this; // copy old value
    operator++();  // prefix increment
    return old;    // return old value
} 
number number::operator -- ( int )
{
	number old = *this; // copy old value
    operator--();  // prefix decrement
    return old;    // return old value
}
// -----------------------------------------------------------
// -----------------------------------------------------------

# endif