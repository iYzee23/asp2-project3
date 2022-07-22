#ifndef _info_h_
#define _info_h_

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <cstdlib>

using namespace std;

struct Elem {
	string sifraPred;
	Elem* next = nullptr;
	Elem(const string& sifra) : sifraPred(sifra) {}
};

struct Info {
	unsigned index;
	string imePrezime;
	Elem* prvi = nullptr;
	Elem* posl = nullptr;
	Info(unsigned ind, string imePr) : index(ind), imePrezime(imePr) {}
	Info(const Info& i);
	~Info();
	bool operator+=(string sifraPred);
	bool operator-=(string sifraPred);
	bool operator()(string sifraPred);
};

#endif // !_info_h_
