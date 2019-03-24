#include "Customer.h"
#include "Movie.h"
#include <sstream>

using std::stringstream;

/////////////////////////////////////////////////////////////
Customer::Customer(const string& name) : name(name)
{
}

/////////////////////////////////////////////////////////////
string Customer::getName() const
{
	return name;
}

/////////////////////////////////////////////////////////////
void Customer::addRental(const Rental& rental)
{
	rentals.push_back(rental);
}

/////////////////////////////////////////////////////////////
string Customer::statement() const
{
	double totalAmount = 0;
	int frequetRenterPointer = 0;

	stringstream ss;

	ss << "Rental Record for " << getName() << "\n";

	for(Rentals::const_iterator rental = rentals.begin(); rental != rentals.end(); ++rental)
	{
		double thisAmount = 0;

		// determine amounts for each line
		switch(rental->getMovie().getPriceCode())
		{
		case Movie::REGULAR:
			thisAmount += 2;
			if(rental->getDaysRented() > 2)
			{
				thisAmount += (rental->getDaysRented() - 2) * 1.5;
			}
			break;

		case Movie::NEW_RELEASE:
			thisAmount += rental->getDaysRented() * 3;
			break;

		case Movie::CHILDRENS:
			thisAmount += 1.5;
			if(rental->getDaysRented() > 3)
			{
				thisAmount += (rental->getDaysRented() - 3) * 1.5;
			}
			break;
		}

		// add frequent renter points
		frequetRenterPointer++;

		// add bonus for a two day new release rental
		if((rental->getMovie().getPriceCode() == Movie::NEW_RELEASE)
		  &&(rental->getDaysRented() > 1))
		{
			frequetRenterPointer++;
		}

		// show figures for this rental
		ss << "\t" << rental->getMovie().getTitle() << "\t" << thisAmount << "\n";

		totalAmount += thisAmount;
	}

	// add footer lines
	ss << "Amount ownd is " << totalAmount << "\n";
	ss << "You earned " << frequetRenterPointer << " frequent renter points";

	return ss.str();
}
