#ifndef _hashtable_h_
#define _hashtable_h_

#include "bucket.h"

class HashTable {
private:
	void brisi();
	void kopiraj(const HashTable& ht);
	void premesti(HashTable& ht);

	static int pocetnoB;
	int k, p, num, b, numBuk;
	Bucket** baket = nullptr;
	Bucket** pokazivac = nullptr;
	Bucket pomocni = Bucket(k + 1);
public:
	HashTable(int k, int p, int b);
	HashTable(const HashTable& ht);
	HashTable(HashTable&& ht);
	~HashTable();
	HashTable& operator=(const HashTable& ht);
	HashTable& operator=(HashTable&& ht);

	Info* findKey(unsigned key);
	bool insertKey(unsigned key, const Info& inf);
	bool deleteKey(unsigned key);
	void clear();
	int keyCount();
	int tableSize();
	friend ostream& operator<<(ostream& os, const HashTable& ht);
	double fillRatio();
	int findMaxDepth() const;
	Bucket* findNeighbour(int i, int& indikator) const;
};

#endif // !_hashtable_h_
