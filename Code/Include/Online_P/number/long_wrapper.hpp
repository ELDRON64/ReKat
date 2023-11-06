# ifndef NUM_WRAPPER
# define NUM_WRAPPER
// wrapper implementation
# include "number.hpp"

number& number::operator = 
( const long long &number2 ) {
	number_size = sizeof(long);
	number_chars = copy ( (unsigned char*)&number2, sizeof(long) );
	return *this;
}

// aritmetics
number& number::operator + 
( const long long &number2 ) {
	num n2(number2);
	return *this + n2;
}
number& number::operator - 
( const long long &number2 ) {
	num n2(number2);
	return *this - n2;
}

number& number::operator * 
( const long long &number2 ) {
	num n2(number2);
	return *this * n2;
}
number& number::operator / 
( const long long &number2 ) {
	num n2(number2);
	return *this / n2;
}
number& number::operator % 
( const long long &number2 ) {
	num n2(number2);
	return *this % n2;
}
number& number::operator << 
( const long long &number2 ) {
	num n2(number2);
	return *this << n2;
}
number& number::operator >> 
( const long long &number2 ) {
	num n2(number2);
	return *this >> n2;
}

// mist operators
void number::operator += 
( const long long &number2 ) {
	number number3 = *this + number2;
	*this = number3;
}
void number::operator -= 
( const long long &number2 ) {
	number number3 = *this - number2;
	*this = number3;
}
void number::operator *= 
( const long long &number2 ) {
	number number3 = *this * number2;
	*this = number3;
}
void number::operator /= 
( const long long &number2 ) {
	number number3 = *this / number2;
	*this = number3;
}
void number::operator <<= 
( const long long &number2 ) {
	number number3 = *this << number2;
	*this = number3;
}
void number::operator >>= 
( const long long &number2 ) {
	number number3 = *this >> number2;
	*this = number3;
}

// booleans
bool number::operator != 
( const long long &number2 ) {
	number number3(number2);
	return number3 != *this;
}
bool number::operator == 
( const long long &number2 ) {
	number number3(number2);
	return number3 == *this;
}
bool number::operator >  
( const long long &number2 ) {
	number number3(number2);
	return *this > number3;
}
bool number::operator <  
( const long long &number2 ) {
	number number3(number2);
	return *this < number3;
}
bool number::operator >= 
( const long long &number2 ) {
	number number3(number2);
	return *this >= number3;
}
bool number::operator <= 
( const long long &number2 ) {
	number number3(number2);
	return *this <= number3;
}

# endif