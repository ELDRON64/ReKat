#ifndef num
#define num_t unsigned long long

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

class number
{
private: 
	// copy a list of char to a new pointer --------------------------------------------------
	static unsigned char * copy ( const unsigned char* _src, num_t _n, bool is_char = false );
	
	// adgust the size of the buffer
	void normalize ( );
	
	// resize the number ----
	void resize ( num_t _n );

	// swaps a and b -------------------------
	inline void swap ( number &a, number &b );

	// printing in base 10 -------
	std::string print_base_10 ( );
	
	// cambio di base -------------------------------------------
	void cambio_da_base ( std::vector<number> num, number base );
	std::vector<number> cambio_in_base ( number base );

public:
	// number data -------------
	unsigned char *number_chars;
	num_t number_size;

	// constuctor
	 number ( const num_t &n );
	 number ( const unsigned char *_buf, num_t _n, bool char_mode = true );
	 number ( );
	~number ( );

	bool to_bool ( );

	// operations
	// --------------------------------------------

	// assertion ----------------------------------
	number& operator =  ( const number & rhs );

	// iteration
	char 	operator [] ( num_t value );

	// aritmetics ---------------------------------
	number& operator ++ ( );
	number  operator ++ (int);
	number& operator -- ( );
	number  operator -- (int);

	number& operator +=  ( const number& rhs );
	number& operator -=  ( const number& rhs );
	number& operator *=  ( const number& rhs ); 
	number& operator /=  ( const number& rhs ); 
	number& operator %=  ( const number& rhs ); 
	number& operator <<= ( const number& rhs );
	number& operator >>= ( const number& rhs );
	
	friend inline bool operator == ( const number& lhs, const number& rhs );
	friend inline bool operator != ( const number& lhs, const number& rhs );
	friend inline bool operator <  ( const number& lhs, const number& rhs );
	friend inline bool operator >  ( const number& lhs, const number& rhs );
	friend inline bool operator <= ( const number& lhs, const number& rhs );
	friend inline bool operator >= ( const number& lhs, const number& rhs );

	number operator & ( const number& rhs );

	//operator bool() const;
	
	friend std::ostream& operator << (std::ostream& os, const number& num);
};

// defined in aritmetic.cpp
// inline number operator +  ( number lhs, const number& rhs );
// inline number operator -  ( number lhs, const number& rhs );
// inline number operator *  ( number lhs, const number& rhs );
// inline number operator /  ( number lhs, const number& rhs );
// inline number operator %  ( number lhs, const number& rhs );
// inline number operator << ( number lhs, const number& rhs );
// inline number operator >> ( number lhs, const number& rhs );

// implementazione con operazioni con long

#define num number
#endif