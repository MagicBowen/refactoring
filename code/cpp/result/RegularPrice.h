#ifndef REGULARPRICE_H_
#define REGULARPRICE_H_

#include "Price.h"

struct RegularPrice : Price
{
	virtual double getCharge(const int daysRented) const;
};

#endif
