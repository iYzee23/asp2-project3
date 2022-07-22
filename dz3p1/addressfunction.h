#ifndef _addressfunction_h_
#define _addressfunction_h_

class AddressFunction {
public:
	virtual int getAddress(unsigned key, int a, int i, int num) = 0;
};

class QuadriaticHashing : public AddressFunction {
private:
	double c;
public:
	QuadriaticHashing(double c) : c(c) {}
	int getAddress(unsigned key, int a, int i, int num) override;
};

#endif // !_addressfunction_h_