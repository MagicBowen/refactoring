#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <string>
#include <vector>

#include "Rental.h"

using std::string;
using std::vector;

struct Customer
{
	Customer(const string& name);
	string getName() const;
	void addRental(const Rental& rental);
	string statement() const;

private:
	typedef vector<Rental> Rentals;
	Rentals rentals;
	string name;
};

#endif
