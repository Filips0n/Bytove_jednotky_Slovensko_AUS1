#pragma once

#include "table/unsorted_sequence_table.h"
#include "Kriterium.h"
#include "heap_monitor.h"
#include <iostream>
template <typename K, typename T, typename V>
class Triedenie
{
private:
	structures::UnsortedSequenceTable<K, T*>* table_;
	Kriterium<V, T>* kriterium;
	bool vzostupne;
public:
	Triedenie(structures::UnsortedSequenceTable<K, T*>* t, Kriterium<V, T>* k, bool vzostupne);
	void sort(T* UJmin, T* UJmax, int pMin, int pMax);
};

template<typename K, typename T, typename V>
inline Triedenie<K, T, V>::Triedenie(structures::UnsortedSequenceTable<K, T*>* t, Kriterium<V, T>* k, bool vzostupne)
{
	this->table_ = t;
	this->kriterium = k;
	this->vzostupne = vzostupne;
	if (this->table_->size() > 1)
	{
		sort(this->table_->operator[]((this->table_->getItemAtIndex(0)).getKey()), this->table_->operator[]((this->table_->getItemAtIndex(table_->size() - 1)).getKey()), 0, (table_->size() - 1));
	}
}

template<typename K, typename T, typename V>
inline void Triedenie<K, T, V>::sort(T* UJmin, T* UJmax, int pMin, int pMax)
{
	V pivot = kriterium->operator()(this->table_->operator[]((this->table_->getItemAtIndex((pMin + pMax) / 2)).getKey()));
	T* left = UJmin;
	T* right = UJmax;
	int indexMin = pMin;
	int indexMax = pMax;
	do {
		while (vzostupne ? kriterium->operator()(left) < pivot : kriterium->operator()(left) > pivot)
		{
			indexMin++;
			left = this->table_->operator[]((this->table_->getItemAtIndex(indexMin)).getKey());
		}
		while (vzostupne ? kriterium->operator()(right) > pivot : kriterium->operator()(right) < pivot)
		{
			indexMax--;
			right = this->table_->operator[]((this->table_->getItemAtIndex(indexMax)).getKey());
		}

		if (indexMin <= indexMax)
		{
			this->table_->swap(indexMin, indexMax);
			indexMin++;
			left = this->table_->operator[]((this->table_->getItemAtIndex(indexMin)).getKey());
			indexMax--;
			if (indexMax < 0) { indexMax = 0; }
			right = this->table_->operator[]((this->table_->getItemAtIndex(indexMax)).getKey());
		}
	} while (indexMin <= indexMax);

	if (pMin < indexMax)
	{
		sort(this->table_->operator[]((this->table_->getItemAtIndex(pMin)).getKey()), right, pMin, indexMax);
	}

	if (indexMin < pMax)
	{
		sort(left, this->table_->operator[]((this->table_->getItemAtIndex(pMax)).getKey()), indexMin, pMax);
	}
}

