#include "hashtable.h"

void HashTable::brisi()
{
	if (baket) {
		for (int i = 0; i < num; i++)
			delete baket[i];
		delete baket;
		baket = nullptr;
		obj = nullptr;
	}
}

void HashTable::kopiraj(const HashTable& ht)
{
	k = ht.k;
	p = ht.p;
	num = ht.num;
	obj = ht.obj;
	baket = new Bucket * [num];
	for (int i = 0; i < num; i++) {
		baket[i] = new Bucket(k);
		int curr = ht.baket[i]->curr;
		for (int j = 0; j < curr; j++)
			*baket[i] += *ht.baket[i]->studenti[j];
	}
}

void HashTable::premesti(HashTable& ht)
{
	k = ht.k;
	p = ht.p;
	num = ht.num;
	baket = ht.baket;
	obj = ht.obj;
	ht.baket = nullptr;
	ht.obj = nullptr;
}

HashTable::HashTable(int k, int p, AddressFunction* obj) : k(k), p(p), obj(obj)
{
	num = pow(2, p);
	baket = new Bucket * [num];
	for (int i = 0; i < num; i++)
		baket[i] = new Bucket(k);
}

HashTable::HashTable(const HashTable& ht)
{
	kopiraj(ht);
}

HashTable::HashTable(HashTable&& ht)
{
	premesti(ht);
}

HashTable::~HashTable()
{
	brisi();
}

HashTable& HashTable::operator=(const HashTable& ht)
{
	if (this != &ht) {
		brisi();
		kopiraj(ht);
	}
	return *this;
}

HashTable& HashTable::operator=(HashTable&& ht)
{
	if (this != &ht) {
		brisi();
		premesti(ht);
	}
	return *this;
}

Info* HashTable::findKey(unsigned key)
{
	Info* trazeni = nullptr;
	int i = key % num;
	int addr = (*baket[i])(key);
	if (addr != -1) 
		trazeni = baket[i]->studenti[addr];
	else if (baket[i]->curr == k) {
		int counter = 1;
		while (counter <= num) {
			i = obj->getAddress(key, i, counter, num);
			addr = (*baket[i])(key);
			if (addr != -1) {
				trazeni = baket[i]->studenti[addr];
				break;
			}
			counter++;
		}
	}
	return trazeni;
}

bool HashTable::insertKey(unsigned key, const Info& inf)
{
	if (findKey(key))
		return false;
	else {
		int i = key % num;
		int currCount = baket[i]->curr;
		if (currCount < k) {
			*baket[i] += inf;
			return true;
		}
		int counter = 1;
		while (counter <= num) {
			i = obj->getAddress(key, i, counter, num);
			currCount = baket[i]->curr;
			if (currCount < k) {
				*baket[i] += inf;
				return true;
			}
			counter++;
		}
		return false;
	}
}

bool HashTable::deleteKey(unsigned key)
{
	int counter = 0;
	bool rc;
	int i = key % num;
	while (counter < num) {
		rc = (*baket[i] -= key);
		if (rc) return true;
		i = obj->getAddress(key, i, counter, num);
		counter++;
	}
	return false;
}

void HashTable::clear()
{
	if (baket) {
		for (int i = 0; i < num; i++) {
			delete baket[i];
			baket[i] = new Bucket(k);
		}
	}
}

int HashTable::keyCount()
{
	int counter = 0;
	for (int i = 0; i < num; i++)
		counter += baket[i]->curr;
	return counter;
}

int HashTable::tableSize()
{
	return num;
}

double HashTable::fillRatio()
{
	double sum = num * k;
	int counter = keyCount();
	return counter / sum;
}

ostream& operator<<(ostream& os, const HashTable& ht)
{
	for (int i = 0; i < ht.num; i++) {
		if (ht.baket[i]->status == -1)
			os << "DELETED";
		else if (ht.baket[i]->status == 0)
			os << "EMPTY";
		else {
			int curr = ht.baket[i]->curr;
			for (int j = 0; j < curr; j++) {
				os << ht.baket[i]->studenti[j]->index;
				os << " ";
			}
		}
		os << endl;
	}
	return os;
}
