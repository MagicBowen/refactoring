#include "ChildrensPrice.h"

/////////////////////////////////////////////////////////////
double ChildrensPrice::getCharge(const int daysRented) const
{
	double result = 1.5;
	if(daysRented > 3)
	{
		result += (daysRented - 3) * 1.5;
	}
	return result;
}
