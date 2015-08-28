#ifndef TEMPLATES_ARRAY_H
#define TEMPLATES_ARRAY_H

#include "Array_Functions.h"

#include <string>

namespace flame_ide
{ namespace templates
{

template<class T>
class Array
{
protected:
	mutable bool is_initialised;
	mutable bool is_temporary;
	
	mutable T *inc_arr;
	size_t arr_size;
	size_t type_size;
	
	inline void set();
	inline void set(const size_t &length, T* arr);
	T* getPCopy() const;
	
	// static
	
public:
	Array();
	Array(const size_t &length, const T* array);
	Array(const Array<T> &array);
	Array(const size_t &arr_size);
	
	virtual ~Array();
	
	bool isInitialised() const;
	
	void pushBack(const T &data);
	void pushFront(const T &data);
	
	void insert(const size_t &index, const T &data);
	void insert(const size_t &index, const size_t &count, const T *array);
	
	void popBack();
	void popFront();
	
	void popBack(const size_t &count);
	void popFront(const size_t &count);
	
	void erase(const size_t &index); // удаляет элемент, находящийся под этим интексом
	void erase(const size_t &index, const size_t &count); // удаляет элементы после индекса
	
	void clear();
	
	void   setSize(const size_t &new_length);
	void   setCopy(const Array<T> &copying_array);
	size_t getSize() const;
	
	void setTemporary(bool is_temp = true) const;
	bool isTemporary() const;
	
	inline const T& at(const size_t &index) const;
	inline T& at(const size_t &index);
	
	inline const T& operator[](const size_t &index) const;
	inline T& operator[](const size_t &index);
	
	const Array<T> &operator=(const Array<T> &);
};

}}


using namespace flame_ide::templates;

// constructors & distructor

template<class T>
Array<T>::Array()
{
	is_temporary = false;
	set();
}
template<class T>
Array<T>::Array(const Array<T> &array)
	: Array()
{
	if(array.arr_size && array.is_initialised)
	{
		if(array.is_temporary)
		{
			this->inc_arr = array.inc_arr;
		}
		else
		{
			this->inc_arr = array.getPCopy();
		}
		this->arr_size = array.arr_size;
		this->is_initialised = true;
	}
}
template<class T>
Array<T>::Array(const size_t &array_size, const T *array)
	: Array()
{
	if(array_size)
	{
		arr_size = array_size;
		inc_arr = array_get_copy(array_size, array);
		is_initialised = true;
	}
}

template<class T>
Array<T>::Array(const size_t& array_length)
	: Array()
{
	if(array_length)
	{
		this->arr_size = array_length;
		this->is_initialised = true;
		this->inc_arr = array_get_new<T>(this->arr_size);
	}
}

template<class T>
Array<T>::~Array()
{
	if(is_initialised && !is_temporary)
	{
		array_delete<T>(inc_arr);
	}
	else
	{
		is_temporary = false;
	}
}

// private

template<class T>
void
Array<T>::set()
{
	inc_arr = nullptr;
	arr_size = 0;
	type_size = sizeof(T);
	is_initialised = false;	
}

template<class T>
T*
Array<T>::getPCopy() const
{
	return array_get_copy<T>(arr_size, inc_arr);
}

template<typename T>
void
Array<T>::set(const size_t &length, T *arr)
{
	this->inc_arr = arr;
	this->arr_size = length;
	this->is_initialised = true;
}

// public

template<class T>
bool
Array<T>::isInitialised() const
{	return is_initialised;}

template<class T>
void
Array<T>::pushBack(const T &data)
{
	size_t new_length = arr_size + 1;
	
	array_insert_element<T>(arr_size, inc_arr, arr_size, data);
	
	if(!is_initialised)
	{
		is_initialised	= true;
	}
	
	arr_size = new_length;
}

template<class T>
void
Array<T>::pushFront(const T &data)
{
	size_t new_length = arr_size + 1;
	
	array_insert_element<T>(arr_size, inc_arr, 0, data);
	
	if(!is_initialised)
	{
		is_initialised	= true;
	}
	
	arr_size = new_length;
}

template<class T>
void
Array<T>::insert(const size_t &index, const T &data)
{
	if(index > arr_size) return;
	
	size_t new_length = arr_size + 1;
	
	array_insert_element<T>(arr_size, inc_arr, index, data);
	
	if(!is_initialised)
	{
		is_initialised = true;
	}
	
	arr_size = new_length;
}

template<class T>
void
Array<T>::insert(const size_t &index, const size_t &count, const T *array)
{
	if(index > arr_size) return;
	
	size_t new_length = arr_size + count;
	
	array_insert_array<T>(arr_size, inc_arr, index, count, array);
	
	if(!is_initialised)
	{
		is_initialised = true;
	}
	
	arr_size = new_length;
}

template<class T>
void
Array<T>::popBack()
{
	if(!is_initialised) return;
	
	size_t new_length = arr_size - 1;
	T *tmp_inc_arr = inc_arr;
	
	if(new_length)
	{
		// создаем новый массив нового размера
		T *new_arr = array_get_new<T>(new_length);
		
		// копируем все данные кроме последнего
		array_copying<T>(new_length, inc_arr, 0, new_arr, 0);
		
		inc_arr = new_arr;
	}
	else
	{
		inc_arr = nullptr;
		is_initialised = false;
	}

	// удаляем старый массив
	array_delete<T>(tmp_inc_arr);
	
	arr_size = new_length;
}

template<class T>
void
Array<T>::popFront()
{
	if(!is_initialised) return;
	
	size_t new_length = arr_size - 1;
	T *tmp_inc_arr = inc_arr;
	
	if(new_length)
	{
		// создаем новый массив нового размера
		T *new_arr = array_get_new<T>(new_length);
		
		// копируем все данные кроме первого
		array_copying<T>(new_length, inc_arr, 1, new_arr, 0);
		
		inc_arr = new_arr;
	}
	else
	{
		inc_arr = nullptr;
		is_initialised = false;
	}

	// удаляем старый массив
	array_delete<T>(tmp_inc_arr);
	
	arr_size = new_length;
}

template<class T>
void
Array<T>::popBack(const size_t &count)
{
	if(!is_initialised || (count > this->arr_size)) return;
	
	size_t new_length = this->arr_size - count;
	T *tmp_inc_arr = this->inc_arr;
	
	if(new_length)
	{
		// создаем новый массив нового размера
		T *new_arr = array_get_new<T>(new_length);
		
		// копируем все данные кроме последнего
		array_copying<T>(new_length, this->inc_arr, 0, new_arr, 0);
		
		inc_arr = new_arr;
	}
	else
	{
		this->inc_arr = nullptr;
		this->is_initialised = false;
	}
	
	// удаляем старый массив
	array_delete<T>(tmp_inc_arr);
	
	this->arr_size = new_length;
}

template<class T>
void
Array<T>::popFront(const size_t &count)
{
	if(!this->is_initialised || (count > this->arr_size)) return;
	
	size_t new_length = this->arr_size - count;
	T *tmp_inc_arr = this->inc_arr;
	
	if(new_length)
	{
		// создаем новый массив нового размера
		T *new_arr = array_get_new<T>(new_length);
		
		// копируем все данные кроме первого
		array_copying<T>(new_length, this->inc_arr, count-1, new_arr, 0);
		
		inc_arr = new_arr;
	}
	else
	{
		this->inc_arr = nullptr;
		this->is_initialised = false;
	}
	
	// удаляем старый массив
	array_delete<T>(tmp_inc_arr);
	
	this->arr_size = new_length;
}

template<class T>
void
Array<T>::erase(const size_t &index)
{
	if(!this->is_initialised || (index >= this->arr_size)) return;
	
	array_erase<T>(this->arr_size, this->inc_arr, index);
	
	if(!arr_size)
	{
		is_initialised = false;
	}
}

template<class T>
void
Array<T>::erase(const size_t &index, const size_t &count)
{
	if(!this->is_initialised || ( (index + count - 1) >= this->arr_size) || !count) return;
	
	array_erase<T>(this->arr_size, this->inc_arr, index, count);
	
	if(!this->arr_size)
	{
		this->is_initialised = false;
	}
}

template<class T>
void
Array<T>::clear()
{
	if(is_initialised)
	{
		array_delete<T>(inc_arr);
		inc_arr = nullptr;
		is_initialised = false;
		arr_size = 0;
	}
}

template<class T>
void
Array<T>::setSize(const size_t &new_length)
{
	if(this->is_initialised)
	{
		array_delete<T>(this->inc_arr);
	}
	
	this->is_initialised = true;
	this->inc_arr = array_get_new<T>(new_length);
	this->arr_size = new_length;
	
}

template<class T>
void
Array<T>::setCopy(const Array<T> &copying_array)
{
	array_delete<T>(this->inc_arr);
	
	this->arr_size = copying_array.getSize();
	this->inc_arr = copying_array.getPCopy();
}

template<class T>
size_t
Array<T>::getSize() const
{
	return arr_size;
}
template<class T>
void 
Array<T>::setTemporary(bool is_temp) const
{
	this->is_temporary = is_temp;
}

template<class T>
bool
Array<T>::isTemporary() const
{
	return is_temporary;
}

// сделал "защиту от дурака", чтобы народ не выходил за границы массива
// идиотская идея, т.к. доп действие. Зато типа защищено
template<class T>
const T&
Array<T>::at(const size_t &index) const
{
	return inc_arr[index % this->arr_size];
}

template<class T>
T&
Array<T>::at(const size_t &index)
{
	return inc_arr[index % this->arr_size];
}

// "защита от дурака" х2
template<class T>
const T&
Array<T>::operator [](const size_t &index) const
{
	return this->inc_arr[index % this->arr_size];
}
template<class T>
T&
Array<T>::operator [](const size_t &index)
{
	return this->inc_arr[index % this->arr_size];
}

template<class T>
const Array<T>&
Array<T>::operator =(const Array<T> &arg)
{
	if(arg.arr_size && arg.is_initialised)
	{
		array_delete<T>(this->inc_arr);
		if(arg.is_temporary)
		{
			this->inc_arr = arg.inc_arr;
		}
		else
		{
			this->inc_arr = arg.getPCopy();
		}
		this->arr_size = arg.arr_size;
		this->is_initialised = true;
	}
	
	return *this;
}

#endif // TEMPLATES_ARRAY_H