#include "JSON.h"

using namespace flame_ide::JSON;

Single::Single()
	: JSON::Data(0, 0, 1)
{}

Single::Single(const Data* data)
	: Single()
{
	if(data->getType() == SINGLE)
	{ Single(*((Single*)data)); }
}

Single::Single(const Single& single)
	: Single()
{ this->str_data = single.str_data; }

Single::Single(const std::string& value)
	: Single()
{ this->str_data = value; }


Single::~Single() {}

const Single &
Single::operator =(const JSON::Single &single)
{
	this->str_data = single.str_data;
	return *this;
}

Data*
Single::getCopy() const
{
	return nullptr;
}

std::string
Single::getAsString() const
{ return this->str_data; }

void
Single::setAsString(const std::string &json_single)
{ str_data = json_single; }
