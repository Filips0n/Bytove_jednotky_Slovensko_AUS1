#pragma once
#include "UzemnaJednotka.h"
#include "table/sorted_sequence_table.h"

class StromUzemneJednotky
{
private:
	UzemnaJednotka* koren = nullptr;
	structures::SortedSequenceTable<string, UzemnaJednotka*>* stat = new structures::SortedSequenceTable<string, UzemnaJednotka*>;
	structures::SortedSequenceTable<string, UzemnaJednotka*>* kraje = new structures::SortedSequenceTable<string, UzemnaJednotka*>;
	structures::SortedSequenceTable<string, UzemnaJednotka*>* okresy = new structures::SortedSequenceTable<string, UzemnaJednotka*>;
	structures::SortedSequenceTable<string, UzemnaJednotka*>* obce = new structures::SortedSequenceTable<string, UzemnaJednotka*>;
public:
	StromUzemneJednotky() {
		koren = new UzemnaJednotka("Slovenská republika", TypUzemnejJednotky::STAT, nullptr, new structures::SortedSequenceTable<string, UzemnaJednotka*>, nullptr);
		this->stat->insert(koren->getNazov(), koren);
	};

	~StromUzemneJednotky();

	structures::SortedSequenceTable<string, UzemnaJednotka*>* getStat() { return this->stat; };
	structures::SortedSequenceTable<string, UzemnaJednotka*>* getKraje() { return this->kraje; };
	structures::SortedSequenceTable<string, UzemnaJednotka*>* getOkresy() { return this->okresy; };
	structures::SortedSequenceTable<string, UzemnaJednotka*>* getObce() { return this->obce; };

	void vlozDoStromu(string kraj, string okres, string obec, ObecData* data) {
		UzemnaJednotka* tableNode = this->koren->vlozNizsiuUzemnuJednotku(kraj, TypUzemnejJednotky::KRAJ, this->koren, kraje, nullptr);
		tableNode = tableNode->vlozNizsiuUzemnuJednotku(okres, TypUzemnejJednotky::OKRES, tableNode, okresy, nullptr);
		tableNode->vlozNizsiuUzemnuJednotku(obec, TypUzemnejJednotky::OBEC, tableNode, obce, data);
	}
};

StromUzemneJednotky::~StromUzemneJednotky()
{
	delete koren;
	koren = nullptr;
	delete stat;
	stat = nullptr;
	delete kraje;
	kraje = nullptr;
	delete okresy;
	okresy = nullptr;
	delete obce;
	obce = nullptr;
}