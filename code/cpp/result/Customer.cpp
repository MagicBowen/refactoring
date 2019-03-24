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
double Customer::getTotalCharge() const
{
	double result = 0;
	for(Rentals::const_iterator rental = rentals.begin(); rental != rentals.end(); ++rental)
	{
		result += rental->getCharge();
	}

	return result;
}

/////////////////////////////////////////////////////////////
int Customer::getTotalFrequetRenterPointer() const
{
	int result = 0;
	for(Rentals::const_iterator rental = rentals.begin(); rental != rentals.end(); ++rental)
	{
		result += rental->getFrequentRenterPointers();
	}

	return result;
}

/////////////////////////////////////////////////////////////
string Customer::statement() const
{
	stringstream ss;

	ss << "Rental Record for " << getName() << "\n";

	for(Rentals::const_iterator rental = rentals.begin(); rental != rentals.end(); ++rental)
	{
		// show figures for this rental
		ss << "\t" << rental->getMovie().getTitle() << "\t" << rental->getCharge() << "\n";
	}

	// add footer lines
	ss << "Amount ownd is " << getTotalCharge() << "\n";
	ss << "You earned " << getTotalFrequetRenterPointer() << " frequent renter points";

	return ss.str();
}
