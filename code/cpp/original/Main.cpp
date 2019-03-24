#include <iostream>
#include <memory>
#include "Customer.h"
#include "Movie.h"
#include "Rental.h"

using namespace std;

#define ASSERT_EQ(expect, result)    	\
	if(expect == result)  				\
	{									\
		cout << "PASS" << endl;			\
	}									\
	else								\
	{									\
		cout << "FAILED! " << endl;		\
		cout << "EXPECT: " << endl;		\
		cout << expect << endl;			\
		cout << "RESULT: " << endl;		\
		cout << result << endl;			\
	}

int main()
{
	auto_ptr<Movie> m1(new Movie("Family", Movie::CHILDRENS));
	auto_ptr<Movie> m2(new Movie("The Star on the Earth", Movie::NEW_RELEASE));
	auto_ptr<Movie> m3(new Movie("THe American Leader", Movie::REGULAR));

	Customer customer("Brain");
	customer.addRental(Rental(m1.get(), 3));
	customer.addRental(Rental(m2.get(), 4));
	customer.addRental(Rental(m3.get(), 5));

	string expect = "";
	expect += "Rental Record for Brain\n";
	expect += "\tFamily\t1.5\n";
	expect += "\tThe Star on the Earth\t12\n";
	expect += "\tTHe American Leader\t6.5\n";
	expect += "Amount ownd is 20\n";
	expect += "You earned 4 frequent renter points";

	ASSERT_EQ(expect, customer.statement());

	return 0;
}
