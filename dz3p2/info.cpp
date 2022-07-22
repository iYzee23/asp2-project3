#include "info.h"

Info::Info(const Info& i)
{
	index = i.index;
	imePrezime = i.imePrezime;
	Elem* tek = i.prvi;
	while (tek) {
		*this += tek->sifraPred;
		tek = tek->next;
	}
}

Info::~Info()
{
	Elem* tek = prvi;
	while (tek) {
		Elem* stari = tek;
		tek = tek->next;
		delete stari;
	}
	prvi = nullptr;
	posl = nullptr;
}

bool Info::operator+=(string sifraPred)
{
	if ((*this)(sifraPred)) 
		return false;
	Elem* novi = new Elem(sifraPred);
	if (!prvi) prvi = novi;
	else posl->next = novi;
	posl = novi;
	return true;
}

bool Info::operator-=(string sifraPred)
{
	Elem* prev = nullptr;
	Elem* tek = prvi;
	while (tek) {
		if (tek->sifraPred == sifraPred) {
			if (!prev) {
				prvi = prvi->next;
				tek->next = nullptr;
				delete tek;
			}
			else if (tek == posl) {
				posl = prev;
				posl->next = nullptr;
				delete tek;
			}
			else {
				prev->next = tek->next;
				tek->next = nullptr;
				delete tek;
			}
			return true;
		}
		prev = tek;
		tek = tek->next;
	}
	return false;
}

bool Info::operator()(string sifraPred)
{
	Elem* tek = prvi;
	while (tek) {
		if (tek->sifraPred == sifraPred)
			return true;
		tek = tek->next;
	}
	return false;
}
