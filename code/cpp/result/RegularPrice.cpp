#include "RegularPrice.h"

/////////////////////////////////////////////////////////////
double RegularPrice::getCharge(const int daysRented) const
{
	double result = 2;
	if(daysRented > 2)
	{
		result += (daysRented - 2) * 1.5;
	}
	return result;
}
