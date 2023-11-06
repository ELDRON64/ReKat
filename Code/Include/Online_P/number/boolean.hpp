# ifndef NUM_BOOL
# define NUM_BOOL
// boolean implementation
# include "common.hpp"

inline bool operator == ( const number& lhs, const number& rhs ) {
	num_t max_dim = lhs.number_size;
	if ( rhs.number_size > max_dim ) {
		max_dim = rhs.number_size;
	}
	
	for (size_t i = 0; i < max_dim; i++) {
		if ( lhs.number_chars[i] != rhs.number_chars[i]) {
			return false;
	 	}
	}

	return true;
}
inline bool operator <  ( const number& lhs, const number& rhs ) {
	num_t max_dim = lhs.number_size;
	if ( rhs.number_size > max_dim ) {
		max_dim = rhs.number_size;
	}
	// number2.resize ( max_dim );


	for ( num_t i = 1; i <= max_dim; i++) {
		if ( lhs.number_chars[max_dim - i] < rhs.number_chars[ max_dim - i]) {
			return true;
		} else if ( lhs.number_chars[max_dim - i] == rhs.number_chars[ max_dim - i]) {
			continue;
		} else {
			return false;
		}
	}

	return false;
}

inline bool operator != ( const number& lhs, const number& rhs ) { return !(lhs == rhs); }
inline bool operator >  ( const number& lhs, const number& rhs ) { return   rhs < lhs;  }
inline bool operator <= ( const number& lhs, const number& rhs ) { return !(lhs > rhs); }
inline bool operator >= ( const number& lhs, const number& rhs ) { return !(lhs < rhs); }

# endif