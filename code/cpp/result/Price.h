#ifndef PRICE_H_
#define PRICE_H_

struct Price
{
	virtual double getCharge(const int daysRented) const = 0;

	virtual int getFrequentRenterPointers(const int daysRented) const
	{
		return 1;
	}

	virtual ~Price() {}
};

#endif
