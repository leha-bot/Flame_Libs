#ifndef ANALYSERS_UBJSON_SIMPLETYPEVALUES_HPP
#define ANALYSERS_UBJSON_SIMPLETYPEVALUES_HPP

namespace flame_ide
{namespace ubjson
{

struct NullValue
{};

struct Noop
{};

struct True
{
	constexpr operator bool()
	{
		return true;
	}
};

struct False
{
	constexpr operator bool()
	{
		return false;
	}
};

}}

#endif // SIMPLETYPEVALUES_HPP