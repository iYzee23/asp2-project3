#ifndef _bucket_h_
#define _bucket_h_

#include "info.h"

struct Bucket {
	//status = -1 za deleted
	//status = 0 za empty
	//status = 1 za notEmpty
	int k, curr, status;
	Info** studenti;
	Bucket(int k);
	~Bucket();
	Bucket& operator+=(const Info& i);
	bool operator-=(unsigned key);
	int operator()(unsigned key);
};

#endif // !_bucket_h_
