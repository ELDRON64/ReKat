#include "number.hpp"

long test_max () {
	num a(123456789078934532);

	long errors = 0;
	for (size_t i = 0; i < 50; i++) {
		long n = rand ( );
		num r = n;

		bool c = a >= r;
		bool t = 123456789078934532 >= n;

		if ( c != t ) { errors++; }
	}

	return errors;
}

long test_min () {
	num a(123456789078934532);

	long errors = 0;
	for (size_t i = 0; i < 50; i++) {
		long n = rand ( );
		num r = n;

		bool c = a <= r;
		bool t = 123456789078934532 <= n;

		if ( c != t ) { errors++; }
	}

	return errors;
}

long test_sot () {
	num a(123456789078934532);

	long errors = 0;
	for (size_t i = 0; i < 50; i++) {
		long n = rand ( );
		num r = n;

		num c = a - r;
		long t = 123456789078934532 - n;
		num control = t;

		if ( c != control ) { errors++; }
	}

	return errors;
}

long test_mod () {
	num a(123456789078934532);

	long errors = 0;
	for (size_t i = 0; i < 50; i++) {
		long n = rand ( );
		num r = n;

		num c = a % r;
		long t = 123456789078934532 % n;
		num control = t;

		if ( c != control ) { errors++; }
	}

	return errors;
}

long test_div () {
	num a(123456789078934532);

	long errors = 0;
	for (size_t i = 0; i < 50; i++) {
		long n = rand ( );
		num r = n;

		num c = a / r;
		long t = 123456789078934532 / n;
		num control = t;

		if ( c != control ) { errors++; }
	}

	return errors;
}

long test_pro () {
	num a(1234);

	long errors = 0;
	for (size_t i = 0; i < 50; i++) {
		long n = rand ( );
		num r = n;

		num c = a * r;
		long t = 1234 * n;
		num control = t;

		if ( c != control ) { errors++; }
	}

	return errors;
}

int main () {
	srand ( time ( 0 ) );
	/*long errors = 0;
	long tests = 0;

	for (size_t i = 0; i < 10; i++) {
		tests += 50;
		errors += test_div();
	}

	std::cout << "div: " << errors << '\\';
	std::cout << (float)errors / tests << '\n';

	long errors10 = 0;
	long tests10 = 0;

	for (size_t i = 0; i < 10; i++) {
		tests10 += 50;
		errors10 += test_mod();
	}

	std::cout << "mod: " << errors10 << '\\';
	std::cout << (float)errors10 / tests10 << '\n';*/

	long errors1 = 0;
	long tests1 = 0;

	for (size_t i = 0; i < 10; i++) {
		tests1 += 50;
		errors1 += test_sot();
	}

	std::cout << "sot: " << errors1 << '\\';
	std::cout << (float)errors1 / tests1 << '\n';

	long errors2 = 0;
	long tests2 = 0;

	for (size_t i = 0; i < 10; i++) {
		tests2 += 50;
		errors2 += test_max();
	}

	std::cout << "max: " << errors2 << '\\';
	std::cout << (float)errors2 / tests2 << '\n';

	long errors4 = 0;
	long tests4 = 0;

	for (size_t i = 0; i < 10; i++) {
		tests4 += 50;
		errors4 += test_min();
	}

	std::cout << "min: " << errors4 << '\\';
	std::cout << (float)errors4 / tests4 << '\n';

	long errors3 = 0;
	long tests3 = 0;

	for (size_t i = 0; i < 10; i++) {
		tests3 += 50;
		errors3 += test_pro();
	}

	std::cout << "pro: " << errors3 << '\\';
	std::cout << (float)errors3 / tests3 << '\n';
}