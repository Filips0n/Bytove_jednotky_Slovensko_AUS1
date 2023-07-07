#define _CRT_SECURE_NO_DEPRECATE
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <cstdlib>
#include "list/array_list.h"
#include "vector/vector.h"
#include "ObecData.h"
#include "table/sorted_sequence_table.h"
#include "table/unsorted_sequence_table.h"
#include "table/sequence_table.h"
#include "Main.h"
#include "UzemnaJednotka.h"
#include "StromUzemneJednotky.h"
#include "Kriterium.h"
#include "KUJPocetObyvatelov.h"
#include "KUJCelkovaVymera.h"
#include "KUJPocetPoprodObyv.h"
#include "KUJNazov.h"
#include "KUJPocetPreprodObyv.h"
#include "KUJPocetProduktObyv.h"
#include "KUJZastavanaPlocha.h"
#include "KUJZastavanost.h"
#include "KUJTyp.h"
#include "KUJPrislusnost.h"
#include "Filter.h"
#include "FilterPodlaHodnoty.h"
#include "FilterPodlaIntervalu.h"
#include "Triedenie.h"

int main() {
	initHeapMonitor();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	SetConsoleOutputCP(1250);
	SetConsoleCP(1250);
	//tabulka dat o obciach
	structures::SortedSequenceTable<string, ObecData*>* poleObci = new structures::SortedSequenceTable<string, ObecData*>;
	ifstream infile("1 Obce SR.csv");
	string readLine;
	structures::ArrayList<string*>* zoznamUdajov = new structures::ArrayList<string*>;
	if (!infile.is_open()) { std::exit(EXIT_FAILURE); }
	getline(infile, readLine);
	//nacitavanie dat do tabulky
	while (getline(infile, readLine))
	{
		zoznamUdajov->clear();
		string value;
		stringstream line(readLine);
		while (getline(line, value, ';'))
		{
			zoznamUdajov->add(new string(value));
		}
		ObecData* obecData = new ObecData(*(zoznamUdajov->operator[](0)), stoi(*(zoznamUdajov->operator[](1))), stoi(*(zoznamUdajov->operator[](2))), stoi(*(zoznamUdajov->operator[](3))), stod(*(zoznamUdajov->operator[](4))), stod(*(zoznamUdajov->operator[](5))));
		poleObci->insert(obecData->getNazov(), obecData);
		for (auto* u : *zoznamUdajov) delete u;
	}
	infile.close();
	
	StromUzemneJednotky* stromUJ = new StromUzemneJednotky;
	ifstream infile2("2 Územné èlenenie SR.csv");
	string readLine2;
	structures::ArrayList<string*>* zoznamUdajov2 = new structures::ArrayList<string*>;
	if (!infile2.is_open()) { std::exit(EXIT_FAILURE); }
	getline(infile2, readLine2);
	//nacitavanie dat o prislusnosti
	while (getline(infile2, readLine2))
	{
		zoznamUdajov2->clear();
		string value2;
		stringstream line2(readLine2);
		while (getline(line2, value2, ';'))
		{
			zoznamUdajov2->add(new string(value2));
		}
		ObecData* data = nullptr;
		poleObci->tryFind(*(zoznamUdajov2->operator[](0)), data);
		stromUJ->vlozDoStromu(*(zoznamUdajov2->operator[](2)), *(zoznamUdajov2->operator[](1)), *(zoznamUdajov2->operator[](0)), data);
		for (auto* u : *zoznamUdajov2) delete u;
	}
	infile2.close();
	//vytvaranie kriterii, ktore sa vypisu na obrazovku
	KUJPocetObyvatelov pocObyvKUJ;
	KUJPocetPredprodObyv pocPredProdKUJ;
	KUJPocetProduktObyv pocProduktKUJ;
	KUJPocetPoprodObyv pocPoProdKUJ;
	KUJZastavanost zastavKUJ;
	KUJCelkovaVymera celkVymKUJ;
	KUJZastavanaPlocha zastPlochaKUJ;

	int numA = 0;
	do {
		system("CLS");
		cout << "Zadaj operaciu na vykonanie: " << endl;
		cout << "1 - Vypisanie informacii o uzemnych jednotkach" << endl;
		cout << "2 - Zoradenie uzemnych jednotiek" << endl;
		cout << "0 - Ukonci aplikaciu" << endl;
		cin >> numA;
		system("CLS");
		if (numA == 0) { break; }
		if (numA == 1) {
			cout << "Zadaj filtrovany typ uzemnych jednotiek: " << endl;
		}
		else if (numA == 2) {
			cout << "Zadaj typ uzemnych jednotiek na zoradenie: " << endl;
		}
		cout << "1 - Obce" << endl;
		cout << "2 - Okresy" << endl;
		cout << "3 - Kraje" << endl;
		cout << "4 - Stat" << endl;
		int cisloTypUJ;
		cin >> cisloTypUJ;
		cout << endl;

		structures::SortedSequenceTable<string, UzemnaJednotka*>* inputTab = stromUJ->getStat();
		if (cisloTypUJ == 4) { inputTab = stromUJ->getStat(); };
		if (cisloTypUJ == 3) { inputTab = stromUJ->getKraje(); };
		if (cisloTypUJ == 2) { inputTab = stromUJ->getOkresy(); };
		if (cisloTypUJ == 1) { inputTab = stromUJ->getObce(); };

		string nazovUzemnJednot2;
		if (cisloTypUJ != 4)
		{
			cout << "Chces zadat vyssiu uzemnu jednotku: " << endl;
			cout << "1 - Ano" << endl;
			cout << "2 - Nie" << endl;
			int anoNie;
			cin >> anoNie;
			cout << endl;

			if (anoNie == 1) {
				cout << "Zadaj nazov vyssieho celku: " << endl;
				cin.ignore();
				getline(cin, nazovUzemnJednot2);
				cout << endl;
			}
		}
		UzemnaJednotka* uj1 = nullptr;
		if (stromUJ->getStat()->containsKey(nazovUzemnJednot2)) { stromUJ->getStat()->tryFind(nazovUzemnJednot2, uj1);};
		if (stromUJ->getKraje()->containsKey(nazovUzemnJednot2)) { stromUJ->getKraje()->tryFind(nazovUzemnJednot2, uj1);};
		if (stromUJ->getOkresy()->containsKey(nazovUzemnJednot2)) { stromUJ->getOkresy()->tryFind(nazovUzemnJednot2, uj1);};
		if (stromUJ->getObce()->containsKey(nazovUzemnJednot2)) { stromUJ->getObce()->tryFind(nazovUzemnJednot2, uj1); };
		if (uj1 == nullptr) { stromUJ->getStat()->tryFind("Slovenská republika", uj1); };

		KUJPrislusnost* prislusnostKrit = new KUJPrislusnost(uj1);
		KUJNazov* nazovKrit = new KUJNazov();
		KUJPocetObyvatelov* pocetObyvatelovKrit = new KUJPocetObyvatelov();
		KUJZastavanost* zastavanostKrit = new KUJZastavanost();
		KUJTyp* typKrit = new KUJTyp();

		FilterPodlaHodnoty<string, UzemnaJednotka, bool>* filterPrislusnost = new FilterPodlaHodnoty<string, UzemnaJednotka, bool>(prislusnostKrit, true);
		structures::SortedSequenceTable<string, UzemnaJednotka*>* outputTab2 = new structures::SortedSequenceTable<string, UzemnaJednotka*>;
		filterPrislusnost->vyfiltrujTabulku(inputTab, outputTab2);
		structures::SortedSequenceTable<string, UzemnaJednotka*>* outputTab = new structures::SortedSequenceTable<string, UzemnaJednotka*>;
		if (numA == 1) {
			cout << "Zadaj podla coho chces filtrovat: " << endl;
			cout << "1 - Nazov" << endl;
			cout << "2 - Pocet obyvatelov" << endl;
			cout << "3 - Zastavanost" << endl;
			int num;
			cin >> num;
			cout << endl;
			if (num == 1)
			{
				cout << "Zadaj nazov uzemnej jednotky: " << endl;
				string nazov1;
				cin.ignore();
				getline(cin, nazov1);
				cout << endl;
				//Filter podla nazvu
				FilterPodlaHodnoty<string, UzemnaJednotka, string>* fph = new FilterPodlaHodnoty<string, UzemnaJednotka, string>(nazovKrit, nazov1);
				fph->vyfiltrujTabulku(outputTab2, outputTab);
				delete fph;
			}
			else if (num == 2) {
				cout << "Zadaj minimum poctu obyvatelov: " << endl;
				int min1;
				cin >> min1;
				cout << endl;
				cout << "Zadaj maximum poctu obyvatelov: " << endl;
				int max1;
				cin >> max1;
				cout << endl;
				//Filter podla poctu obyvatelov
				FilterPodlaIntervalu<string, UzemnaJednotka, int>* filterInterval = new FilterPodlaIntervalu<string, UzemnaJednotka, int>(pocetObyvatelovKrit, min1, max1);
				filterInterval->vyfiltrujTabulku(outputTab2, outputTab);
				delete filterInterval;
			}
			else if (num == 3) {
				cout << "Zadaj minimum zastavanosti: " << endl;
				double min2;
				cin >> min2;
				cout << endl;
				cout << "Zadaj maximum zastavanosti: " << endl;
				double max2;
				cin >> max2;
				cout << endl;
				//Filter podla poctu obyvatelov
				FilterPodlaIntervalu<string, UzemnaJednotka, double>* filterInterval = new FilterPodlaIntervalu<string, UzemnaJednotka, double>(zastavanostKrit, min2, max2);
				filterInterval->vyfiltrujTabulku(outputTab2, outputTab);
				delete filterInterval;
			}

			for (auto* uj : *(outputTab))
			{
				UzemnaJednotka* uzemnJedno = uj->accessData();
				cout << uzemnJedno->getVyssieUzemneJednotky() << endl;
				cout << fixed << setprecision(2) << "Pocet obyvatelov: " << pocObyvKUJ.operator()(uzemnJedno) << ", Pocet predproduktivnych obyv.: " << pocPredProdKUJ.operator()(uzemnJedno) << ", Pocet poproduktivnych obyv.: " << pocProduktKUJ.operator()(uzemnJedno)
					<< ", Pocet poproduktivnych obyv.: " << pocPoProdKUJ.operator()(uzemnJedno)  << "\nZastavanost: " << zastavKUJ.operator()(uzemnJedno) << "%, Celkova vymera: " << celkVymKUJ.operator()(uzemnJedno)
					<< "m2, Zastavana plocha: " << zastPlochaKUJ.operator()(uzemnJedno) << "m2 " << endl;
				cout << "-------------------------------------------------" << endl << endl;
			}
			cout << endl;
		}
		else if (numA == 2) {
			structures::UnsortedSequenceTable<string, UzemnaJednotka*>* unsortTable = new structures::UnsortedSequenceTable<string, UzemnaJednotka*>;
			for (auto*uj : *outputTab2) { unsortTable->insert(uj->accessData()->getNazov(), uj->accessData());}
			cout << "Zadaj podla coho chces zoradovat: " << endl;
			cout << "1 - Nazov" << endl;
			cout << "2 - Pocet obyvatelov" << endl;
			cout << "3 - Zastavanost" << endl;
			int sortNum;
			cin >> sortNum;
			cout << endl;

			cout << "Vzostupne/Zostupne: " << endl;
			cout << "1 - Vzostupne" << endl;
			cout << "2 - Zostupne" << endl;
			int ascDesc;
			cin >> ascDesc;
			cout << endl;
			bool vzostupne = true;
			if (ascDesc == 2) { vzostupne = false; };
			if (sortNum == 1)
			{
				//Triedenie podla nazvu
				Triedenie<string, UzemnaJednotka, string> triedenieNazov(unsortTable, nazovKrit, vzostupne);
				int i = 1;
				for (auto* uj : *unsortTable) {
					cout << i << ". " << uj->accessData()->getNazov() << "\n";
					i++;
				}
			} else if (sortNum == 2) {
				//Triedenie podla poctu obyvatelov
				Triedenie<string, UzemnaJednotka, int> triedeniePocetObyv(unsortTable, pocetObyvatelovKrit, vzostupne);
				int i = 1;
				for (auto* uj : *unsortTable) {
					UzemnaJednotka* uzemnJedno = uj->accessData();
					cout << i << ". " << uzemnJedno->getNazov() << " " << fixed << setprecision(2) << pocObyvKUJ.operator()(uzemnJedno) << "\n";
					i++;
				}
			} else if (sortNum == 3) {
				//Triedenie podla zastavanosti
				Triedenie<string, UzemnaJednotka, double> triedenie(unsortTable, zastavanostKrit, vzostupne);
				int i = 1;
				for (auto* uj : *unsortTable) {
					UzemnaJednotka* uzemnJedno = uj->accessData();
					cout << i << ". " << uzemnJedno->getNazov() << " " << fixed << setprecision(2) << zastavKUJ.operator()(uzemnJedno) << "%\n";
					i++;
				}
			}	
			delete unsortTable;
		}

		delete typKrit;
		delete prislusnostKrit;
		delete nazovKrit;
		delete pocetObyvatelovKrit;
		delete zastavanostKrit;
		delete filterPrislusnost;	
		delete outputTab;
		delete outputTab2;
		system("pause");

	} while (numA != 0);

	delete stromUJ;
	delete zoznamUdajov2;
	delete zoznamUdajov;
	delete poleObci;

	return 0;
}
