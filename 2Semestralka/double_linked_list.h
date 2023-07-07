#pragma once

#include "structure_iterator.h"
#include "list/list.h"
#include "ds_routines.h"
#include "heap_monitor.h"
#include <iostream>
using namespace std;
namespace structures
{

	/// <summary> Prvok obojstranne zretazeneho cyklickeho zoznamu. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
	template<typename T>
	class DoubleLinkedListItem : public DataItem<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "data"> Data, ktore uchovava. </param>
		DoubleLinkedListItem(T data);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prvok obojstranne zretazeneho cyklickeho zoznamu, z ktoreho sa prevezmu vlastnosti.. </param>
		DoubleLinkedListItem(const DoubleLinkedListItem<T>& other);

		/// <summary> Destruktor. </summary>
		~DoubleLinkedListItem();

		/// <summary> Getter nasledujuceho prvku zretazeneho zoznamu. </summary>
		/// <returns> Nasledujuci prvok zretazeneho zoznamu. </returns>
		DoubleLinkedListItem<T>* getNext();
		/// <summary>
		/// Getter predchadajuceho prvku zretazeneho zoznamu.
		/// </summary>
		/// <returns>Predchadzajuci prvok zretazeneho zoznamu.</returns>
		DoubleLinkedListItem<T>* getPrevious();

		/// <summary> Setter nasledujuceho prvku zretazeneho zoznamu. </summary>
		/// <param name´= "next"> Novy nasledujuci prvok zretazeneho zoznamu. </param>
		void setNext(DoubleLinkedListItem<T>* next);
		/// <summary> Setter predchadzajuceho prvku zretazeneho zoznamu. </summary>
		/// <param name´= "next"> Novy predchadzajuci prvok zretazeneho zoznamu. </param>
		void setPrevious(DoubleLinkedListItem<T>* previous);
	private:
		/// <summary> Nasledujuci prvok zretazeneho zoznamu. </summary>
		DoubleLinkedListItem<T>* next_;
		/// <summary> Predchadzajuci prvok zretazeneho zoznamu. </summary>
		DoubleLinkedListItem<T>* previous_;
	};

	/// <summary> Obojstranne zretazeny cyklicky zoznam. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
	template<typename T>
	class DoubleLinkedList : public List<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		DoubleLinkedList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Obojstranne zretazeny cyklicky zoznam, z ktoreho sa prevezmu vlastnosti. </param>
		DoubleLinkedList(const DoubleLinkedList<T>& other);

		/// <summary> Destruktor. </summary>
		~DoubleLinkedList();

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat zoznamu. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const override;

		/// <summary> Vrati pocet prvkov v zozname. </summary>
		/// <returns> Pocet prvkov v zozname. </returns>
		size_t size() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zoznam, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		List<T>& operator=(const List<T>& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zoznam, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		DoubleLinkedList<T>& operator=(const DoubleLinkedList<T>& other);

		/// <summary> Vrati adresou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Adresa prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		T& operator[](const int index) override;

		/// <summary> Vrati hodnotou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Hodnota prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		const T operator[](const int index) const override;

		/// <summary> Prida prvok do zoznamu. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		void add(const T& data) override;

		/// <summary> Vlozi prvok do zoznamu na dany index. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		/// <param name = "index"> Index prvku. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		/// <remarks> Ak je ako index zadana hodnota poctu prvkov (teda prvy neplatny index), metoda insert sa sprava ako metoda add. </remarks>
		void insert(const T& data, const int index) override;

		/// <summary> Odstrani prvy vyskyt prvku zo zoznamu. </summary>
		/// <param name = "data"> Odstranovany prvok. </param>
		/// <returns> true, ak sa podarilo prvok zo zoznamu odobrat, false inak. </returns>
		bool tryRemove(const T& data) override;

		/// <summary> Odstrani zo zoznamu prvok na danom indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		T removeAt(const int index) override;

		/// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
		/// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
		/// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
		int getIndexOf(const T& data) override;

		/// <summary> Vymaze zoznam. </summary>
		void clear() override;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getBeginIterator() const override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getEndIterator() const override;
	private:
		/// <summary> Pocet prvkov v zozname. </summary>
		size_t size_;
		/// <summary> Prvy prvok zoznamu. </summary>
		DoubleLinkedListItem<T>* first_;
	private:
		/// <summary> Vrati prvok zoznamu na danom indexe. </summary>
		/// <param name = "index"> Pozadovany index. </summary>
		/// <returns> Prvok zoznamu na danom indexe. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		DoubleLinkedListItem<T>* getItemAtIndex(int index) const;
	private:
		/// <summary> Iterator pre Obojstranne zretazeny cyklicky zoznam. </summary>
		class DoubleCycleLinkedLinkedListIterator : public Iterator<T>
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "position"> Pozicia v zretazenom zozname, na ktorej zacina. </param>
			DoubleCycleLinkedLinkedListIterator(DoubleLinkedListItem<T>* position);

			/// <summary> Destruktor. </summary>
			~DoubleCycleLinkedLinkedListIterator();

			/// <summary> Operator priradenia. Priradi do seba hodnotu druheho iteratora. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> Vrati seba po priradeni. </returns>
			Iterator<T>& operator= (const Iterator<T>& other) override;

			/// <summary> Porovna sa s druhym iteratorom na nerovnost. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> True, ak sa iteratory nerovnaju, false inak. </returns>
			bool operator!=(const Iterator<T>& other) override;

			/// <summary> Vrati data, na ktore aktualne ukazuje iterator. </summary>
			/// <returns> Data, na ktore aktualne ukazuje iterator. </returns>
			const T operator*() override;

			/// <summary> Posunie iterator na dalsi prvok v strukture. </summary>
			/// <returns> Iterator na dalsi prvok v strukture. </returns>
			/// <remarks> Zvycajne vrati seba. Ak vrati iny iterator, povodny bude automaticky zruseny. </remarks>
			Iterator<T>& operator++() override;
		private:
			/// <summary> Aktualna pozicia v zozname. </summary>
			DoubleLinkedListItem<T>* position_;
		};
	};

	template<typename T>
	inline DoubleLinkedListItem<T>::DoubleLinkedListItem(T data) :
		DataItem<T>(data),
		next_(nullptr),
		previous_(nullptr)
	{
	}

	template<typename T>
	inline DoubleLinkedListItem<T>::DoubleLinkedListItem(const DoubleLinkedListItem<T>& other) :
		DataItem<T>(other),
		next_(other.next_),
		previous_(other.previous_)
	{
	}

	template<typename T>
	inline DoubleLinkedListItem<T>::~DoubleLinkedListItem()
	{
		next_ = nullptr;
		previous_ = nullptr;
	}

	template<typename T>
	inline DoubleLinkedListItem<T>* DoubleLinkedListItem<T>::getNext()
	{
		return next_;
	}

	template<typename T>
	inline DoubleLinkedListItem<T>* DoubleLinkedListItem<T>::getPrevious()
	{
		return previous_;
	}

	template<typename T>
	inline void DoubleLinkedListItem<T>::setNext(DoubleLinkedListItem<T>* next)
	{
		next_ = next;
	}

	template<typename T>
	inline void DoubleLinkedListItem<T>::setPrevious(DoubleLinkedListItem<T>* previous)
	{
		previous_ = previous;
	}

	template<typename T>
	inline DoubleLinkedList<T>::DoubleLinkedList() :
		List<T>(),
		size_(0),
		first_(nullptr)
	{
	}

	template<typename T>
	inline DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList<T>& other) :
		DoubleLinkedList()
	{
		*this = other;
	}

	template<typename T>
	inline DoubleLinkedList<T>::~DoubleLinkedList()
	{
		clear();
	}

	template<typename T>
	inline Structure* DoubleLinkedList<T>::clone() const
	{
		return new DoubleLinkedList<T>(*this);
	}

	template<typename T>
	inline size_t DoubleLinkedList<T>::size() const
	{
		return size_;
	}

	template<typename T>
	inline List<T>& DoubleLinkedList<T>::operator=(const List<T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const DoubleLinkedList<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(const DoubleLinkedList<T>& other)
	{
		if (true)
		{
			clear();
			for (T data : other)
			{
				add(data);
			}
		}
		return *this;
	}



	template<typename T>
	inline T& DoubleLinkedList<T>::operator[](const int index)
	{
		DoubleLinkedListItem<T>* item = getItemAtIndex(index);
		return item->accessData();
	}

	template<typename T>
	inline const T DoubleLinkedList<T>::operator[](const int index) const
	{
		DoubleLinkedListItem<T>* item = getItemAtIndex(index);
		return item->accessData();
	}

	template<typename T>
	inline void DoubleLinkedList<T>::add(const T& data)
	{
		DoubleLinkedListItem<T>* newItem = new DoubleLinkedListItem<T>(data);
		if (size_ == 0)
		{
			first_ = newItem;
			first_->setNext(first_);
			first_->setPrevious(first_);
		}
		else
		{
			first_->getPrevious()->setNext(newItem);
			newItem->setPrevious(first_->getPrevious());
			newItem->setNext(first_);
			first_->setPrevious(newItem);
		}

		size_++;
	}

	template<typename T>
	inline void DoubleLinkedList<T>::insert(const T& data, const int index)
	{
		if (index == static_cast<int>(size_))
		{
			add(data);
		}
		else
		{
			DSRoutines::rangeCheck(index, size_);
			DoubleLinkedListItem<T>* newItem = new DoubleLinkedListItem<T>(data);
			if (index == 0)
			{
				newItem->setNext(first_);
				newItem->setPrevious(first_->getPrevious());
				newItem->getPrevious()->setNext(newItem);
				first_->setPrevious(newItem);
				first_ = newItem;
			}
			else
			{

				DoubleLinkedListItem<T>* prevItem = getItemAtIndex(index - 1);
				newItem->setNext(prevItem->getNext());
				newItem->setPrevious(prevItem);
				prevItem->setNext(newItem);
				prevItem = newItem->getNext();
				prevItem->setPrevious(newItem);
			}
			size_++;
		}
	}

	template<typename T>
	inline bool DoubleLinkedList<T>::tryRemove(const T& data)
	{
		int index = getIndexOf(data);
		if (index == -1)
		{
			return false;
		}
		else
		{
			removeAt(index);
			return true;
		}
	}

	template<typename T>
	inline T DoubleLinkedList<T>::removeAt(const int index)
	{
		DSRoutines::rangeCheck(index, size_);
		DoubleLinkedListItem<T>* delItem;
		if (size_ == 1)
		{
			delItem = first_;
			first_ = nullptr;
		}
		else
		{
			if (index == 0)
			{
				first_->getNext()->setPrevious(first_->getPrevious());
				first_->getPrevious()->setNext(first_->getNext());
				delItem = first_;
				first_ = delItem->getNext();
			}
			else if (size() - 1 == index)
			{
				delItem = first_->getPrevious();
				delItem->getPrevious()->setNext(first_);
				first_->setPrevious(delItem->getPrevious());

			}
			else
			{
				DoubleLinkedListItem<T>* prevItem = getItemAtIndex(index - 1);
				delItem = prevItem->getNext();
				prevItem->setNext(delItem->getNext());
				delItem->getNext()->setPrevious(delItem->getPrevious());
			}
		}
		T result = delItem->accessData();
		delete delItem;
		size_--;
		return result;
	}

	template<typename T>
	inline int DoubleLinkedList<T>::getIndexOf(const T& data)
	{
		DoubleLinkedListItem<T>* item = first_;
		int index = 0;
		if (size_ == 0) { return -1; };
		while (first_->getPrevious() != item)
		{
			if (item->accessData() == data)
			{
				return index;
			}
			index++;
			item = item->getNext();
		}

		return -1;
	}

	template<typename T>
	inline void DoubleLinkedList<T>::clear()
	{
		if (size_ != 0)
		{
			DoubleLinkedListItem<T>* delItem = first_;
			delItem->getPrevious()->setNext(nullptr);
			DoubleLinkedListItem<T>* nextItem;

			while (delItem != nullptr)
			{
				nextItem = delItem->getNext();
				delItem->setNext(nullptr);
				delItem->setPrevious(nullptr);
				delete delItem;
				delItem = nextItem;
			}

			size_ = 0;
			first_ = nullptr;
		}
	}

	template<typename T>
	inline Iterator<T>* DoubleLinkedList<T>::getBeginIterator() const
	{
		return new DoubleCycleLinkedLinkedListIterator(first_);
	}

	template<typename T>
	inline Iterator<T>* DoubleLinkedList<T>::getEndIterator() const
	{
		return new DoubleCycleLinkedLinkedListIterator(nullptr);
	}

	template<typename T>
	inline DoubleLinkedListItem<T>* DoubleLinkedList<T>::getItemAtIndex(int index) const
	{
		DSRoutines::rangeCheck(index, size_);
		DoubleLinkedListItem<T>* result = first_;
		if (index < static_cast<int>(size_) / 2)
		{
			for (int i = 0; i < index; i++)
			{
				result = result->getNext();
			}
		}
		else
		{
			for (size_t i = 0; i < size_ - 1 - index; i++)
			{
				result = result->getPrevious();
			}
		}
		return result;
	}

	template<typename T>
	inline DoubleLinkedList<T>::DoubleCycleLinkedLinkedListIterator::DoubleCycleLinkedLinkedListIterator(DoubleLinkedListItem<T>* position) :
		position_(position)
	{
	}

	template<typename T>
	inline DoubleLinkedList<T>::DoubleCycleLinkedLinkedListIterator::~DoubleCycleLinkedLinkedListIterator()
	{
		position_ = nullptr;
	}

	template<typename T>
	inline Iterator<T>& DoubleLinkedList<T>::DoubleCycleLinkedLinkedListIterator::operator=(const Iterator<T>& other)
	{
		position_ = dynamic_cast<const DoubleCycleLinkedLinkedListIterator&>(other).position_;
		return *this;
	}

	template<typename T>
	inline bool DoubleLinkedList<T>::DoubleCycleLinkedLinkedListIterator::operator!=(const Iterator<T>& other)
	{
		return position_ != dynamic_cast<const DoubleCycleLinkedLinkedListIterator&>(other).position_;
	}

	template<typename T>
	inline const T DoubleLinkedList<T>::DoubleCycleLinkedLinkedListIterator::operator*()
	{		return position_->accessData();
	}

	template<typename T>
	inline Iterator<T>& DoubleLinkedList<T>::DoubleCycleLinkedLinkedListIterator::operator++()
	{
		position_ = position_->getNext();
		return *this;
	}
}