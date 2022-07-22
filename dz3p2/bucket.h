#ifndef _bucket_h_
#define _bucket_h_

const int maxx = 100000;

#include "info.h"

struct Bucket {
	//status = -1 za deleted
	//status = 0 za empty
	//status = 1 za notEmpty
	int b, numPok;
	int k, curr, status;
	int bitovi[maxx]{};
	Info** studenti;
	Bucket(int k);
	~Bucket();
	Bucket& operator+=(const Info& i);
	bool operator-=(unsigned key);
	int operator()(unsigned key);
	bool seNalazi(unsigned key, int p);
};

#endif // !_bucket_h_
