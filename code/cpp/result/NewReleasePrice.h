#ifndef NEWRELEASEPRICE_H_
#define NEWRELEASEPRICE_H_

#include "Price.h"

struct NewReleasePrice : Price
{
	virtual double getCharge(const int daysRented) const;
	virtual int getFrequentRenterPointers(const int daysRented) const;
};

#endif
