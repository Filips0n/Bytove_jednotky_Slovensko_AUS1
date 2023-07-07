#pragma once

#include "priority_queue.h"
#include "priority_queue_limited_sorted_array_list.h"
#include "heap_monitor.h"
#include "../list/linked_list.h"
#include <string>
#include <cmath>
using namespace std;
namespace structures
{
	/// <summary> Prioritny front implementovany dvojzoznamom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	/// <remarks> Implementacia efektivne vyuziva prioritny front implementovany utriednym ArrayList-om s obmedzenou kapacitou a LinkedList. </remarks>
	template<typename T>
	class PriorityQueueTwoLists : public PriorityQueue<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueTwoLists(char typeOfShortList);

		PriorityQueueTwoLists(const PriorityQueueTwoLists<T>& other);
		~PriorityQueueTwoLists();

		Structure* clone() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Prioritny front, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento prioritny front nachadza po priradeni. </returns>
		PriorityQueue<T>& operator=(const PriorityQueue<T>& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Prioritny front implementovany dvojzoznamom, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento prioritny front nachadza po priradeni. </returns>
		PriorityQueueTwoLists<T>& operator=(const PriorityQueueTwoLists<T>& other);

		/// <summary> Vrati pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </summary>
		/// <returns> Pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </returns>
		size_t size() const override;

		/// <summary> Vymaze obsah prioritneho frontu implementovaneho dvojzoznamom. </summary>
		void clear() override;

		/// <summary> Vlozi prvok s danou prioritou do prioritneho frontu implementovaneho dvojzoznamom. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(const int priority, const T& data) override;

		/// <summary> Odstrani prvok s najvacsou prioritou z prioritneho frontu implementovaneho dvojzoznamom. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>  
		T pop() override;

		/// <summary> Vrati adresou prvok s najvacsou prioritou. </summary>
		/// <returns> Adresa, na ktorej sa nachadza prvok s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>  
		T& peek() override;

		/// <summary> Vrati kopiu prvku s najvacsou prioritou. </summary>
		/// <returns> Kopia prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>  
		const T peek() const override;

		/// <summary> Vrati prioritu prvku s najvacsou prioritou. </summary>
		/// <returns> Priorita prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>  
		int peekPriority() const override;

		/// <summary>
		/// Nastavi aktualne vykonavany scenar v teste. Pre potreby vypocitania mensieho zoznamu.
		/// </summary>
		/// <param name="scenario">Cislo vykonavaneho scenaru.</param>
		void setScenario(int scenario);

		/// <summary>
		/// Vrati pouzivany typ mensieho zoznamu.
		/// </summary>
		/// <returns>Typ mensieho zoznamu.</returns>
		char getTypeOfShortList();

	private:
		/// <summary> Smernik na prioritny front ako implementovany utriednym ArrayList-om s obmedzenou kapacitou . </summary>
		/// <remarks> Z pohladu dvojzoznamu sa jedna o kratsi utriedeny zoznam. </remarks>
		PriorityQueueLimitedSortedArrayList<T>* shortList_;

		/// <summary> Smernik na dlhsi neutriedeny zoznam. </summary>
		LinkedList<PriorityQueueItem<T>*>* longList_;

		/// <summary> Typ aktualne pouzivaneho mensieho zoznamu. </summary>
		char typeOfShortList;

		/// <summary> Aktualne vykonavany scenar. </summary>
		int scenario = 0;
	protected:

		/// <summary> Vypocita velkost mensieho zoznamu. </summary>
		/// <param name="longListSize">Velkost vacsieho zoznamu.</param>
		/// <returns>Velkost mensieho zoznamu.</returns>
		virtual size_t calculateSizeOfShortList(size_t longListSize);

	};


	template<typename T>
	inline PriorityQueueTwoLists<T>::PriorityQueueTwoLists(char typeOfShortList):
		shortList_(new PriorityQueueLimitedSortedArrayList<T>()),
		longList_(new LinkedList<PriorityQueueItem<T>*>()),
		typeOfShortList(typeOfShortList),
		scenario(0)
	{
	}

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists(const PriorityQueueTwoLists<T>& other) :
		PriorityQueueTwoLists<T>(other.typeOfShortList)
	{
		*this = other;
	}

	template<typename T>
	PriorityQueueTwoLists<T>::~PriorityQueueTwoLists()
	{
		this->clear();
		delete shortList_;
		shortList_ = nullptr;
		delete longList_;
		longList_ = nullptr;
		scenario = 0;
		typeOfShortList = '\u0000';
	}

	template<typename T>
	Structure* PriorityQueueTwoLists<T>::clone() const
	{
		return new PriorityQueueTwoLists<T>(*this);
	}

	template<typename T>
	PriorityQueue<T>& PriorityQueueTwoLists<T>::operator=(const PriorityQueue<T>& other)
	{
		return *this = dynamic_cast<const PriorityQueueTwoLists<T>&>(other);
	}

	template<typename T>
	PriorityQueueTwoLists<T>& PriorityQueueTwoLists<T>::operator=(const PriorityQueueTwoLists<T>& other)
	{
		for (PriorityQueueItem<T>* item : *other.longList_)
		{
			longList_->add(new PriorityQueueItem<T>(*item));
		}
		*longList_ = *other.longList_;
		return *this;
	}

	template<typename T>
	size_t PriorityQueueTwoLists<T>::size() const
	{
		return shortList_->size() + longList_->size();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::clear()
	{
		shortList_->clear();
		for (PriorityQueueItem<T>* item : *longList_)
		{
			delete item;
		}
		longList_->clear();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::push(const int priority, const T& data)
	{
		if (longList_->size() == 0 || shortList_->minPriority() > priority)
		{
			PriorityQueueItem<T>* item = shortList_->pushAndRemove(priority, data);
			if (item != nullptr)
			{
				longList_->add(item);
			}
		}
		else
		{
			longList_->add(new PriorityQueueItem<T>(priority, data));
		}
	}

	template<typename T>
	T PriorityQueueTwoLists<T>::pop()
	{
		T data = shortList_->pop();
		if (shortList_->size() == 0 && longList_->size() > 0)
		{
			size_t capacity = calculateSizeOfShortList(longList_->size());
			if (capacity < 4) { capacity = 4; };
			shortList_->trySetCapacity(capacity);
			LinkedList<PriorityQueueItem<T>*>* helpList = new LinkedList<PriorityQueueItem<T>*>();
			while (longList_->size() > 0)
			{
				PriorityQueueItem<T>* removedItem = longList_->removeAt(0);
				PriorityQueueItem<T>* extraItem = shortList_->pushAndRemove(removedItem->getPriority(), removedItem->accessData());
				delete removedItem;
				if (extraItem != nullptr)
				{
					helpList->add(extraItem);
				}
			}
			delete longList_;
			longList_ = helpList;
		}
		return data;
	}

	template<typename T>
	T& PriorityQueueTwoLists<T>::peek()
	{
		return shortList_->peek();
	}

	template<typename T>
	const T PriorityQueueTwoLists<T>::peek() const
	{
		return shortList_->peek();
	}

	template<typename T>
	int PriorityQueueTwoLists<T>::peekPriority() const
	{
		return shortList_->peekPriority();
	}

	template<typename T>
	inline void PriorityQueueTwoLists<T>::setScenario(int scenario)
	{
		this->scenario = scenario;
	}

	template<typename T>
	inline char PriorityQueueTwoLists<T>::getTypeOfShortList()
	{
		return typeOfShortList;
	}

	template<typename T>
	inline size_t PriorityQueueTwoLists<T>::calculateSizeOfShortList(size_t longListSize)
	{
		switch (typeOfShortList)
		{
		case 'A':
			if (scenario == 0) { return static_cast <size_t>(35000 / 1000); };
			if (scenario == 1) { return static_cast <size_t>(50000 / 1000); };
			if (scenario == 2) { return static_cast <size_t>(70000 / 1000); };
			break;
		case 'B':
			return static_cast<size_t>(round(sqrt(static_cast<long double>(longListSize))));
			break;
		case 'C':
			return static_cast<size_t>(round(static_cast<long double>(longListSize)/2));
			break;
		default:
			return static_cast<size_t>(round(sqrt(static_cast<long double>(longListSize))));
		}
	}

}