#ifndef RENTAL_H_
#define RENTAL_H_

struct Movie;

struct Rental
{
	Rental(const Movie* movie, const int daysRented);
	int getDaysRented() const;
	const Movie& getMovie() const;

private:
	const Movie* movie;
	int daysRented;
};

#endif
