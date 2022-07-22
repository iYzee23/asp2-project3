#include "hashtable.h"

int HashTable::pocetnoB = -1;

void HashTable::brisi()
{
	if (baket) {
		for (int i = 0; i < num; i++)
			delete baket[i];
		delete baket; baket = nullptr;
		delete pokazivac; pokazivac = nullptr;
	}
}

void HashTable::kopiraj(const HashTable& ht)
{
	k = ht.k;
	p = ht.p;
	num = ht.num;
	b = ht.b;
	numBuk = ht.b;
	baket = new Bucket * [num];
	pokazivac = new Bucket * [num];
	for (int i = 0; i < num; i++) {
		baket[i] = new Bucket(k);
		baket[i]->b = ht.baket[i]->b;
		baket[i]->numPok = ht.baket[i]->numPok;
		baket[i]->curr = ht.baket[i]->curr;
		baket[i]->status = ht.baket[i]->status;
		for (int j = 0; j < baket[i]->b; j++)
			baket[i]->bitovi[j] = ht.baket[i]->bitovi[j];
		for (int j = 0; j < baket[i]->curr; j++)
			*baket[i] += *ht.baket[i]->studenti[j];
		pokazivac[i] = nullptr;
	}
	int curr = 0;
	for (int i = 0; i < numBuk; i++) {
		for (int j = 0; j < baket[i]->numPok; j++) {
			pokazivac[curr++] = baket[i];
		}
	}
}

void HashTable::premesti(HashTable& ht)
{
	k = ht.k;
	p = ht.p;
	num = ht.num;
	b = ht.b;
	baket = ht.baket;
	pokazivac = ht.pokazivac;
	ht.baket = nullptr;
	ht.pokazivac = nullptr;
}

HashTable::HashTable(int k, int p, int b) : k(k), p(p), b(b)
{
	pocetnoB = b;
	num = pow(2, p);
	numBuk = pow(2, b);
	baket = new Bucket * [num];
	pokazivac = new Bucket * [num];
	for (int i = 0; i < num; i++) {
		baket[i] = new Bucket(k);
		pokazivac[i] = nullptr;
	}
	for (int i = 0; i < numBuk; i++) {
		baket[i]->b = b;
		baket[i]->numPok = 1;
		unsigned bitmask = 1;
		bitmask <<= b - 1;
		int j = 0, bit;
		while (bitmask) {
			bit = (bitmask & i ? 1 : 0);
			baket[i]->bitovi[j++] = bit;
			bitmask >>= 1;
		}
		pokazivac[i] = baket[i];
	}
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
	unsigned i = (key % (int)pow(2, p));
	i >>= p - b;
	Bucket* bkt = pokazivac[i];
	if (bkt->seNalazi(key, p)) {
		int addr = (*bkt)(key);
		if (addr != -1) trazeni = bkt->studenti[addr];
	}
	return trazeni;

	/*
	Info* trazeni = nullptr;
	int numPok = pow(2, b), addr;
	for (int i = 0; i < numPok;) {
		if (pokazivac[i]->seNalazi(key, p)) {
			addr = (*pokazivac[i])(key);
			if (addr != -1)
				trazeni = pokazivac[i]->studenti[addr];
			break;
		}
		i += pokazivac[i]->numPok;
	}
	return trazeni;
	*/
}

bool HashTable::insertKey(unsigned key, const Info& inf)
{
	if (findKey(key))
		return false;
	else {
		int addr, curr;
		unsigned ind, indikator;
		for (int i = 0; i < numBuk;) {
			if (baket[i]->seNalazi(key, p)) {
				indikator = 1;
				curr = 0;
				if (baket[i]->curr < k)
					*baket[i] += inf;
				else if (baket[i]->b == p)
					return false;
				else {
					//smestanje u pomocni
					while (baket[i]->curr) {
						ind = baket[i]->studenti[0]->index;
						pomocni += *baket[i]->studenti[0];
						*baket[i] -= ind;
					}
					pomocni += inf;
					//rotacija udesno
					Bucket* pom = baket[numBuk];
					for (int j = numBuk; j > i; j--) 
						baket[j] = baket[j - 1];
					baket[i + 1] = pom; numBuk++;
					//formiranje nova dva
					baket[i]->b++;
					baket[i + 1]->b = baket[i]->b;
					for (int j = 0; j < baket[i]->b - 1; j++)
						baket[i + 1]->bitovi[j] = baket[i]->bitovi[j];
					baket[i]->bitovi[baket[i]->b - 1] = 0;
					baket[i + 1]->bitovi[baket[i + 1]->b - 1] = 1;
					while (pomocni.curr) {
						ind = pomocni.studenti[0]->index;
						if (pomocni.curr != 1) {
							if (baket[i]->seNalazi(ind, p))
								*baket[i] += *pomocni.studenti[0];
							else
								*baket[i + 1] += *pomocni.studenti[0];
						}
						else {
							if (baket[i]->seNalazi(ind, p)) {
								if (baket[i]->curr < k)
									*baket[i] += *pomocni.studenti[0];
								else
									indikator = 0;
							}
							else {
								if (baket[i + 1]->curr < k)
									*baket[i + 1] += *pomocni.studenti[0];
								else
									indikator = 0;
							}
						}
						pomocni -= ind;
					}
					//prevezivanje pokazivaca
					if (baket[i]->b > b) {
						b++;
						for (int j = 0; j < numBuk; j++)
							baket[j]->numPok *= 2;
					}
					baket[i]->numPok /= 2;
					baket[i + 1]->numPok = baket[i]->numPok;
					for (int j = 0; j < numBuk; j++)
						for (int k = 0; k < baket[j]->numPok; k++)
							pokazivac[curr++] = baket[j];
					if (!indikator) continue;
				}
				return true;
			}
			i++;
		}
	}
	return false;
}

bool HashTable::deleteKey(unsigned key)
{
	if (!findKey(key))
		return false;
	else {
		Bucket* komsa = nullptr;
		Bucket* pom = nullptr;
		int curr, numPok, indikator = 0;
		for (int i = 0; i < numBuk;) {
			if (baket[i]->seNalazi(key, p)) {
				*baket[i] -= key;
				if (!baket[i]->curr && baket[i]->b != pocetnoB) {
					komsa = findNeighbour(i, indikator);
					if (komsa) {
						numPok = pow(2, b);
						for (curr = 0; curr < numPok;) {
							if (pokazivac[curr] == baket[i])
								break;
							curr += pokazivac[curr]->numPok;
						}
						for (int j = 0; j < baket[i]->numPok; j++) {
							pokazivac[curr + j] = komsa;
							komsa->numPok++;
						}
						pom = baket[i]; numBuk--;
						for (int j = i; j < numBuk; j++)
							baket[j] = baket[j + 1];
						baket[numBuk] = pom;
						baket[numBuk]->b = -1;
						baket[numBuk]->numPok = -1;
						komsa->b--;
						if (findMaxDepth() < b) {
							b--; curr = 0;
							for (int j = 0; j < numBuk; j++) {
								baket[j]->numPok /= 2;
								for (int k = 0; k < baket[j]->numPok; k++)
									pokazivac[curr++] = baket[j];
							}
						}
					}
				}
				while (true) {
					if (indikator == -1) i--;
					if (!baket[i]->curr && baket[i]->b != pocetnoB) {
						komsa = findNeighbour(i, indikator);
						if (komsa && !komsa->curr) {
							numPok = pow(2, b);
							for (curr = 0; curr < numPok;) {
								if (pokazivac[curr] == baket[i])
									break;
								curr += pokazivac[curr]->numPok;
							}
							for (int j = 0; j < baket[i]->numPok; j++) {
								pokazivac[curr + j] = komsa;
								komsa->numPok++;
							}
							Bucket* pom = baket[i]; numBuk--;
							for (int j = i; j < numBuk; j++)
								baket[j] = baket[j + 1];
							baket[numBuk] = pom;
							baket[numBuk]->b = -1;
							baket[numBuk]->numPok = -1;
							komsa->b--;
							if (findMaxDepth() < b) {
								b--; curr = 0;
								for (int j = 0; j < numBuk; j++) {
									baket[j]->numPok /= 2;
									for (int k = 0; k < baket[j]->numPok; k++)
										pokazivac[curr++] = baket[j];
								}
							}
						}
						else break;
					}
					else break;
				}
				return true;
			}
			i++;
		}
	}
	return false;
}

void HashTable::clear()
{
	if (baket) {
		for (int i = 0; i < num; i++) {
			delete baket[i];
			baket[i] = new Bucket(k);
			pokazivac[i] = nullptr;
		}
		b = pocetnoB;
		numBuk = pow(2, b);
		for (int i = 0; i < numBuk; i++) {
			baket[i]->b = b;
			baket[i]->numPok = 1;
			unsigned bitmask = 1;
			bitmask <<= b - 1;
			int j = 0, bit;
			while (bitmask) {
				bit = (bitmask & i ? 1 : 0);
				baket[i]->bitovi[j++] = bit;
				bitmask >>= 1;
			}
			pokazivac[i] = baket[i];
		}
	}
}

int HashTable::keyCount()
{
	int counter = 0;
	int numPok = pow(2, b);
	for (int i = 0; i < numPok;) {
		counter += pokazivac[i]->curr;
		i += pokazivac[i]->numPok;
	}
	return counter;
}

int HashTable::tableSize()
{
	return numBuk;
}

double HashTable::fillRatio()
{
	double sum = numBuk * k;
	int counter = keyCount();
	return counter / sum;
}

int HashTable::findMaxDepth() const
{
	int max = -1;
	for (int i = 0; i < numBuk; i++) {
		if (baket[i]->b > max)
			max = baket[i]->b;
	}
	return max;
}

Bucket* HashTable::findNeighbour(int i, int& indikator) const
{
	Bucket* komsaLevi = (i ? baket[i - 1] : nullptr);
	Bucket* komsaDesni = (i != numBuk - 1 ? baket[i + 1] : nullptr);
	if (komsaLevi) {
		if (komsaLevi->b == baket[i]->b) {
			for (int j = 0; j < baket[i]->b - 1; j++)
				if (komsaLevi->bitovi[j] != baket[i]->bitovi[j])
					goto x;
			indikator = -1;
			return komsaLevi;
		}
	}
	x:
	if (komsaDesni) {
		if (komsaDesni->b == baket[i]->b) {
			for (int j = 0; j < baket[i]->b - 1; j++)
				if (komsaDesni->bitovi[j] != baket[i]->bitovi[j])
					goto y;
			indikator = 1;
			return komsaDesni;
		}
	}
	y:
	indikator = 0;
	return nullptr;
}

ostream& operator<<(ostream& os, const HashTable& ht)
{
	int numPok = pow(2, ht.b);
	for (int i = 0; i < numPok;) {
		int curr = ht.pokazivac[i]->curr;
		if (curr) {
			for (int j = 0; j < curr; j++) {
				os << ht.pokazivac[i]->studenti[j]->index;
				os << " ";
			}
		}
		else os << "EMPTY";
		os << endl;
		i += ht.pokazivac[i]->numPok;
	}
	return os;
}
