#include "addressfunction.h"

int QuadriaticHashing::getAddress(unsigned key, int a, int i, int num)
{
	return (int)(a + c * i * i) % num;
}
