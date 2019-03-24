#ifndef CHILDRENSPRICE_H_
#define CHILDRENSPRICE_H_

#include "Price.h"

struct ChildrensPrice : Price
{
	virtual double getCharge(const int daysRented) const;
};

#endif
