#ifndef MOVIE_H_
#define MOVIE_H_

#include <memory>
#include <string>

using std::auto_ptr;
using std::string;

struct Price;

struct Movie
{
	Movie(const string& title, const int priceCode);
	string getTitle() const;

	double getCharge(const int daysRented) const;
	int getFrequentRenterPointers(const int daysRented) const;

	static const int CHILDRENS = 2;
	static const int REGULAR   = 0;
	static const int NEW_RELEASE = 1;

private:
	void setPriceCode(const int priceCode);

private:
	string title;
	auto_ptr<Price> price;
};

#endif
