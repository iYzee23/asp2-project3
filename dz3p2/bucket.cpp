#include "bucket.h"

Bucket::Bucket(int k) : k(k), curr(0), status(0), b(-1), numPok(-1)
{
	studenti = new Info * [k];
	for (int i = 0; i < k; i++)
		studenti[i] = nullptr;
}

Bucket::~Bucket()
{
	for (int i = 0; i < curr; i++)
		delete studenti[i];
	delete studenti;
	curr = 0;
	status = 0;
}

Bucket& Bucket::operator+=(const Info& i)
{
	studenti[curr++] = new Info(i);
	status = 1;
	return *this;
}

bool Bucket::operator-=(unsigned key)
{
	int addr = (*this)(key);
	if (addr != -1) {
		delete studenti[addr];
		for (int i = addr; i < curr - 1; i++)
			studenti[i] = studenti[i + 1];
		//studenti[curr--] = nullptr;
		studenti[--curr] = nullptr;
		if (!curr) status = -1;
		return true;
	}
	return false;
}

int Bucket::operator()(unsigned key)
{
	for (int i = 0; i < curr; i++)
		if (studenti[i]->index == key)
			return i;
	return -1;
}

bool Bucket::seNalazi(unsigned key, int p)
{
	unsigned bitmaks = 1;
	bitmaks <<= p - 1;
	for (int i = 0; i < b; i++) {
		int bit = (bitmaks & key ? 1 : 0);
		if (bitovi[i] != bit)
			return false;
		bitmaks >>= 1;
	}
	return true;
}
