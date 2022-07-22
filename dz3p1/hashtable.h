#ifndef _hashtable_h_
#define _hashtable_h_

#include "bucket.h"
#include "addressfunction.h"

class HashTable {
private:
	void brisi();
	void kopiraj(const HashTable& ht);
	void premesti(HashTable& ht);

	int k, p, num;
	Bucket** baket = nullptr;
	AddressFunction* obj = nullptr;
public:
	HashTable(int k, int p, AddressFunction* obj);
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
};

#endif // !_hashtable_h_
