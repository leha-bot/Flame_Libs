#ifndef JSON_H
#define JSON_H

#include <string>

#include "../Templates/Array.h"

namespace flame_ide
{namespace JSON
{

typedef enum
{
	PAIR = 0,
	SINGLE = 1,
	ARRAY = 10,
	OBJECT = 100
} Type;

class Data;
class DataContainer;

class Single;

class Object;
class Array;

struct Pair;

class Data
{
	bool is_single;
	bool is_array;
	bool is_object;
	
	bool is_container;
	
	unsigned int type;
protected:
	mutable unsigned long level; // глубина записи
public:
	Data();
	Data(bool is_object_type
		 ,bool is_array_type
		 ,bool is_single_type);
	
	virtual ~Data();
	
	bool isObject() const;
	bool isArray() const;
	bool isSingle() const;
	bool isPair() const;
	
	bool isContainer() const;
	
	unsigned int getType() const;
	
	virtual Data* getCopy() const = 0;
		
	virtual std::string getAsString() const = 0;
	virtual void        setAsString(const std::string&) = 0;
};

class DataContainer
		: public Data
{
#ifdef FUTURE
protected:
	virtual void pushBack_Single(const Single* single) = 0;
	virtual void pushBack_Pair(const Pair* pair) = 0;
	virtual void pushBack_Array(const Array* array) = 0;
	virtual void pushBack_Object(const Object* object) = 0;
#endif
	
public:
	DataContainer(const bool& is_object_type
				  ,const bool& is_array_type);
	
	virtual void pushBack(Data *data) = 0;
	virtual void pushFront(Data *data) = 0;
	
	virtual void insert(const size_t &index, Data *data) = 0;
	virtual void insert(const size_t &index, const size_t &count, Data **data) = 0;
	
	virtual void popBack() = 0;
	virtual void popFront() = 0;
	
	virtual void erase(const size_t &index) = 0;
	virtual void erase(const size_t &index, const size_t &count) = 0;
	
	~DataContainer();
};

class Pair
		: public Data
{
public:
	std::string key;
	Data* data;
	
	Pair();
	Pair(const Pair &pair);
	
	~Pair();
	
	Data* getCopy() const;
	
	std::string getAsString() const;
	void        setAsString(const std::string& json_pair);
	
	const Pair& operator=(const Pair& pair);
};

class Single
		: public Data
{
	std::string str_data;
	
public:
	Single();
	Single(const Data *data);
	Single(const Single &single);
	Single(const std::string& value);
	
	~Single();
	
	const Single & operator=(const Single& single);
	
#ifdef FUTURE
	// future
	int           getInt();
	unsigned int  getUInt();
	
	long          getLong();
	unsigned long getULong();
	
	float         getFloat();
	double        getDouble();
	
	bool          getBool();
	
	bool          isNull();
#endif
	
	Data* getCopy() const;
	
	std::string getAsString() const;
	void        setAsString(const std::string& single);
	
};

class Object
		: public DataContainer
{
	templates::Array<Pair> arr;
public:
	Object();
	Object(const Data *data);
	Object(const Object &object);
	Object(const templates::Array<Pair> &template_array);
	Object(const size_t& size);
	
	~Object();
	
#ifdef FUTURE // пока думаю, как с этим быть
	Data* operator [](const std::string &str_index) const;
	Data* operator [](const char *c_str_index) const;
#endif
	Data* operator [](const size_t &index);
	
	const Object & operator=(const Object& object);
	
	void   setSize(const size_t &new_size);
	size_t getSize();
	
	void pushBack(Data *data);
	void pushFront(Data *data);
	
	void insert(const size_t &index, Data *data);
	void insert(const size_t &index, const size_t &count, Data **data);
	
	void popBack();
	void popFront();
	
	void erase(const size_t &index);
	void erase(const size_t &index, const size_t &count);
	
	Data* getCopy() const;
	
	std::string getAsString() const;
	void        setAsString(const std::string &json_object);
};

class Array
		: public DataContainer
{
	templates::Array<Data*> arr;
	
public:
	Array();
	Array(const Data *data);
	Array(const Array &array);
	Array(const size_t& size);
	
	~Array();
	
	Data* operator[](const size_t &index);
	
	void   setSize(const size_t &new_size);
	size_t getSize();
	
	void pushBack(Data *data);
	void pushFront(Data *data);
	
	void insert(const size_t &index, Data *data);
	void insert(const size_t &index, const size_t &count, Data **data);
	
	void popBack();
	void popFront();
	
	void erase(const size_t &index);
	void erase(const size_t &index, const size_t &count);
	
	Data* getCopy() const;
	
	std::string getAsString() const;
	void        setAsString(const std::string &json_array);
};

}}

#endif // JSON_H
