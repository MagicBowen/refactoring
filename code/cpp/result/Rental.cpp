#include "Rental.h"

#include "Movie.h"

////////////////////////////////////////////////////////////
Rental::Rental(const Movie* movie, const int daysRented)
	: movie(movie), daysRented(daysRented)
{
}

////////////////////////////////////////////////////////////
const Movie& Rental::getMovie() const
{
	return *movie;
}

////////////////////////////////////////////////////////////
double Rental::getCharge() const
{
	return movie->getCharge(daysRented);
}

////////////////////////////////////////////////////////////
int Rental::getFrequentRenterPointers() const
{
	return movie->getFrequentRenterPointers(daysRented);
}
