#include "NewReleasePrice.h"

/////////////////////////////////////////////////////////////
double NewReleasePrice::getCharge(const int daysRented) const
{
	return daysRented * 3;
}

/////////////////////////////////////////////////////////////
int NewReleasePrice::getFrequentRenterPointers(const int daysRented) const
{
	return (daysRented > 1) ? 2 : 1;
}
