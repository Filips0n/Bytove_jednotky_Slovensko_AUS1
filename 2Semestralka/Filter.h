#pragma once
#include "Kriterium.h"
#include "table/table.h"
#include "heap_monitor.h"
template<typename K, typename T, typename V>
class Filter {
protected:
	Kriterium<V, T>* kriterium;

public:
	Filter(Kriterium<V, T> *k);
	virtual bool splnaFilter(T *o) = 0;
	void vyfiltrujTabulku(structures::Table<K, T*>* table, structures::Table<K, T*>* table2);
};

template<typename K, typename T, typename V>
inline Filter<K, T, V>::Filter(Kriterium<V, T> *k)
{
	this->kriterium = k;
}

template<typename K, typename T, typename V>
inline void Filter<K, T, V>::vyfiltrujTabulku(structures::Table<K, T*>* table, structures::Table<K, T*>* table2)
{
	for (auto *uj : *table)
	{
		if (splnaFilter(uj->accessData()))
		{
			table2->insert(uj->getKey(), uj->accessData());
		}
	}
}

