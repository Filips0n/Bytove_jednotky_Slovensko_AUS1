#pragma once
#include <string>
#include "table/table.h"
#include "ObecData.h"
#include "TypUzemnejJednotky.h"
#include "heap_monitor.h"

using namespace std;

class UzemnaJednotka
{
private:
	string nazov;
	TypUzemnejJednotky typ;
	UzemnaJednotka* vyssia;
	structures::Table<string, UzemnaJednotka*>* nizsie;
	ObecData* obecData;
public:
	UzemnaJednotka(string nazov, TypUzemnejJednotky typ, UzemnaJednotka* vyssia, structures::Table<string, UzemnaJednotka*>* nizsie, ObecData* obecData) {
		this->nazov = nazov;
		this->typ = typ;
		this->vyssia = vyssia;
		this->nizsie = nizsie;
		this->obecData = obecData;
	}

	string getNazov() { return nazov; };
	TypUzemnejJednotky getTyp() { return typ; };
	UzemnaJednotka* getVyssiaUzemJedn() { return vyssia; };
	structures::Table<string, UzemnaJednotka*>* getNizsieUzeJedn() { return nizsie; };
	ObecData* getObecData() { return obecData; };

	UzemnaJednotka* vlozNizsiuUzemnuJednotku(string pNazov, TypUzemnejJednotky pTyp, UzemnaJednotka* pVyssia, structures::Table<string, UzemnaJednotka*>* tabulka, ObecData* pObecData) {
		UzemnaJednotka* uj;
		if (!this->nizsie->tryFind(pNazov, uj))
		{
			uj = new UzemnaJednotka(pNazov, pTyp, pVyssia, new structures::SortedSequenceTable<string, UzemnaJednotka*>, pObecData);
			this->nizsie->insert(pNazov, uj);
			tabulka->insert(pNazov, uj);
		}
		return uj;
	};

	string getVyssieUzemneJednotky() {
		string vyssieUzemJedn = this->getNazov();
		for (UzemnaJednotka* vyssiaUJ = this->getVyssiaUzemJedn(); vyssiaUJ != nullptr; vyssiaUJ = vyssiaUJ->getVyssiaUzemJedn()) {
			vyssieUzemJedn += (this->getTyp() == TypUzemnejJednotky::STAT ? "" : " - ") + vyssiaUJ->getNazov() ;
		}
		return vyssieUzemJedn;
	};

	~UzemnaJednotka() {
		if (nizsie != nullptr)
		{
			for (auto *uj : *nizsie) {
				if (uj->accessData()->getObecData() != nullptr) {
					delete uj->accessData()->getObecData();
				}					
				delete uj->accessData();
			}
			delete nizsie;
			nizsie = nullptr;
		}
	};
};

