#ifndef MOVIE_H_
#define MOVIE_H_

#include <string>

using std::string;

struct Movie
{
	Movie(const string& title, const int priceCode);
	int getPriceCode() const;
	void setPriceCode(const int priceCode);
	string getTitle() const;

	static const int CHILDRENS = 2;
	static const int REGULAR   = 0;
	static const int NEW_RELEASE = 1;

private:
	string title;
	int priceCode;
};

#endif
