#include "Movie.h"
#include "ChildrensPrice.h"
#include "NewReleasePrice.h"
#include "RegularPrice.h"
#include <exception>

////////////////////////////////////////////////////////////
Movie::Movie(const string& title, const int priceCode) : title(title)
{
	setPriceCode(priceCode);
}

////////////////////////////////////////////////////////////
void Movie::setPriceCode(const int priceCode)
{
	switch(priceCode)
	{
	case REGULAR:
		price.reset(new RegularPrice());
		break;
	case CHILDRENS:
		price.reset(new ChildrensPrice());
		break;
	case NEW_RELEASE:
		price.reset(new NewReleasePrice());
		break;
	default:
		throw std::exception();
	}
}

////////////////////////////////////////////////////////////
string Movie::getTitle() const
{
	return title;
}

////////////////////////////////////////////////////////////
int Movie::getFrequentRenterPointers(const int daysRented) const
{
	return price->getFrequentRenterPointers(daysRented);
}

////////////////////////////////////////////////////////////
double Movie::getCharge(const int daysRented) const
{
	return price->getCharge(daysRented);
}
