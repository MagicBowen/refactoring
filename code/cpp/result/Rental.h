#ifndef RENTAL_H_
#define RENTAL_H_

struct Movie;

struct Rental
{
	Rental(const Movie* movie, const int daysRented);
	const Movie& getMovie() const;

	double getCharge() const;
	int getFrequentRenterPointers() const;

private:
	const Movie* movie;
	int daysRented;
};

#endif
