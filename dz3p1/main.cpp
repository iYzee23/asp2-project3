#include "hashtable.h"
#include <fstream>
#include <sstream>

unsigned index;
string imePrez;
string sifra;
double c;
AddressFunction* obj = nullptr;
HashTable* tabela = nullptr;
int k, p, izbor;
ifstream dat;
string imeDat;
string red;
string pom;

void meni() {
	cout << "1 - Kreiraj tabelu" << endl;
	cout << "2 - Obrisi tabelu" << endl;
	cout << "3 - Dodaj studenta" << endl;
	cout << "4 - Obrisi studenta" << endl;
	cout << "5 - Pronadji studenta" << endl;
	cout << "6 - Isprazni tabelu" << endl;
	cout << "7 - Broj studenata u tabeli" << endl;
	cout << "8 - Velicina tabele" << endl;
	cout << "9 - Ispisi tabelu" << endl;
	cout << "10 - Popunjenost tabele" << endl;
	cout << "11 - Dodaj ispit za studenta" << endl;
	cout << "12 - Obrisi ispit za studenta" << endl;
	cout << "13 - Zavrsi program" << endl;
	cout << "Izbor? "; cin >> izbor;
}

int main() {

	while (true) {
		meni();
		switch (izbor) {
			case 1:
				if (!tabela) {
					cout << "C? "; cin >> c;
					obj = new QuadriaticHashing(c);
					cout << "K? "; cin >> k;
					cout << "P? "; cin >> p;
					tabela = new HashTable(k, p, obj);
					cout << "Uspesno ste kreirali tabelu";
					cout << endl << endl;
				}
				else {
					cout << "Tabela vec postoji";
					cout << endl << endl;
				}
				break;
			case 2: 
				if (tabela) {
					delete obj; obj = nullptr;
					delete tabela; tabela = nullptr;
					cout << "Uspesno ste obrisali tabelu";
					cout << endl << endl;
				}
				else {
					cout << "Tabela ne postoji";
					cout << endl << endl;
				}
				break;
			case 3: 
				if (tabela) {
					cout << "Datoteka (0-ne, 1-da)? "; cin >> izbor;
					if (izbor) {
						cout << "Ime datoteke? "; cin >> imeDat;
						dat.open(imeDat);
						if (!dat.is_open()) {
							cout << "Doslo je do greske pri otvaranju";
							cout << endl << endl;
						}
						else {
							getline(dat, red);
							while (getline(dat, red)) {
								stringstream ss(red);
								getline(ss, imePrez, ',');
								index = stoi(imePrez);
								getline(ss, imePrez, ',');
								Info stud(index, imePrez);
								while (getline(ss, sifra, ' '))
									stud += sifra;
								tabela->insertKey(index, stud);
							}
							cout << "Uspesno ste dodali studente";
							cout << endl << endl;
							dat.close();
						}
					}
					else {
						cout << "Index? "; cin >> index; getchar();
						cout << "Ime i prezime? "; getline(cin, imePrez);
						Info stud(index, imePrez);
						cout << "Predmeti (-1 za kraj)? ";
						while (true) {
							cin >> sifra;
							if (sifra == "-1") break;
							stud += sifra;
						}
						if (tabela->insertKey(index, stud)) {
							cout << "Uspesno ste uneli studenta";
							cout << endl << endl;
						}
						else {
							cout << "Student nije uspesno dodat";
							cout << endl << endl;
						}
					}
				}
				else {
					cout << "Prvo morate kreirati tabelu";
					cout << endl << endl;
				}
				break;
			case 4:
				if (tabela) {
					cout << "Index? "; cin >> index;
					if (tabela->deleteKey(index)) {
						cout << "Uspesno ste obrisali studenta";
						cout << endl << endl;
					}
					else {
						cout << "Dati student ne postoji";
						cout << endl << endl;
					}
				}
				else {
					cout << "Prvo morate kreirati tabelu";
					cout << endl << endl;
				}
				break;
			case 5: 
				if (tabela) {
					cout << "Index? "; cin >> index;
					Info* studz = tabela->findKey(index);
					if (!studz) {
						cout << "Dati student ne postoji";
						cout << endl << endl;
					}
					else {
						cout << "Index: " << studz->index << endl;
						cout << "Ime i prezime: " << studz->imePrezime << endl;
						cout << "Prijavljeni ispiti: ";
						Elem* tek = studz->prvi;
						while (tek) {
							cout << tek->sifraPred << " ";
							tek = tek->next;
						}
						cout << endl;
						cout << "Ispit (0-obrisi, 1-dodaj)? "; cin >> izbor;
						if (izbor == 1) {
							cout << "Predmet? "; cin >> sifra;
							if (*studz += sifra) cout << "Uspesno ste dodali ispit";
							else cout << "Dati ispit vec postoji";
							cout << endl;
						}
						else if (izbor == 0) {
							cout << "Predmet? "; cin >> sifra;
							if (*studz -= sifra) cout << "Uspesno ste izbrisali ispit";
							else cout << "Dati ispit ne postoji";
							cout << endl;
						}

						cout << endl;
					}
				}
				else {
					cout << "Prvo morate kreirati tabelu";
					cout << endl << endl;
				}
				break;
			case 6: 
				if (tabela) {
					tabela->clear();
					cout << "Uspesno ste ispraznili tabelu";
					cout << endl << endl;
				}
				else {
					cout << "Prvo morate kreirati tabelu";
					cout << endl << endl;
				}
				break;
			case 7: 
				if (tabela) {
					cout << tabela->keyCount();
					cout << endl << endl;
				}
				else {
					cout << "Prvo morate kreirati tabelu";
					cout << endl << endl;
				}
				break;
			case 8: 
				if (tabela) {
					cout << tabela->tableSize();
					cout << endl << endl;
				}
				else {
					cout << "Prvo morate kreirati tabelu";
					cout << endl << endl;
				}
				break;
			case 9: 
				if (tabela) {
					cout << *tabela;
					cout << endl;
				}
				else {
					cout << "Prvo morate kreirati tabelu";
					cout << endl << endl;
				}
				break;
			case 10: 
				if (tabela) {
					cout << tabela->fillRatio();
					cout << endl << endl;
				}
				else {
					cout << "Prvo morate kreirati tabelu";
					cout << endl << endl;
				}
				break;
			case 11: 
				if (tabela) {
					cout << "Index? "; cin >> index;
					Info* studz = tabela->findKey(index);
					if (!studz) {
						cout << "Dati student ne postoji";
						cout << endl << endl;
					}
					else {
						cout << "Predmet? "; cin >> sifra;
						if (*studz += sifra) {
							cout << "Uspesno ste dodali ispit";
							cout << endl << endl;
						}
						else {
							cout << "Dati ispit vec postoji";
							cout << endl << endl;
						}
					}
				}
				else {
					cout << "Prvo morate kreirati tabelu";
					cout << endl << endl;
				}
				break;
			case 12: 
				if (tabela) {
					cout << "Index? "; cin >> index;
					Info* studz = tabela->findKey(index);
					if (!studz) {
						cout << "Dati student ne postoji";
						cout << endl << endl;
					}
					else {
						cout << "Predmet? "; cin >> sifra;
						if (*studz -= sifra) {
							cout << "Uspesno ste izbrisali ispit";
							cout << endl << endl;
						}
						else {
							cout << "Dati ispit ne postoji";
							cout << endl << endl;
						}
					}
				}
				else {
					cout << "Prvo morate kreirati tabelu";
					cout << endl << endl;
				}
				break;
			case 13: 
				if (tabela) {
					delete obj; obj = nullptr;
					delete tabela; tabela = nullptr;
				}
				cout << "Zelimo Vam lep ostatak dana! :)";
				cout << endl;
				return 0;
				break;
			default: 
				cout << "Los izbor. Pokusajte ponovo";
				cout << endl << endl;
				break;
		}
	}
}