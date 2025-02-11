#ifndef FLAMEIDE_UBJSON_BASEVALUE_HPP
#define FLAMEIDE_UBJSON_BASEVALUE_HPP

#include <FlameIDE/Templates/Pointers.hpp>
#include <FlameIDE/Ubjson/Traits.hpp>

namespace flame_ide
{namespace ubjson
{

namespace base_value_utils
{

template<EnumeratedValueType UBJSON_TYPE>
struct TraitValues
{
	using Me = TraitValues<UBJSON_TYPE>;
	using Traits = ValueTraits<UBJSON_TYPE>;

	using ValueType = typename Traits::ValueType;

	EnumeratedValueType getType() const
	{
		return Traits::VALUE_TYPE;
	}

	ValueType getTypeClose() const
	{
		return Traits::VALUE_TYPE_CLOSE;
	}

	bool isDataPayload() const
	{
		return Traits::DATA_PAYLOAD;
	}
};

}

template<EnumeratedValueType UBJSON_TYPE, bool IS_ALLOCATED = FalseType::VALUE>
class BaseValue: public base_value_utils::TraitValues<UBJSON_TYPE>
{
public:
	using Me = BaseValue<UBJSON_TYPE, IS_ALLOCATED>;
	using Parent = base_value_utils::TraitValues<UBJSON_TYPE>;
	using typename Parent::ValueType;

	BaseValue() = default;
	BaseValue(const Me &) = default;
	BaseValue(Me &&) = default;

	BaseValue(const ValueType &initValue) : value(initValue)
	{}

	BaseValue(ValueType &&initValue) : value(flame_ide::move(initValue))
	{}

	~BaseValue() = default;

	Me &operator=(const Me &) = default;
	Me &operator=(Me &&) = default;

	Me &operator=(const ValueType &assigninigValue)
	{
		value = assigninigValue;
	}

	Me &operator=(ValueType &&assigninigValue)
	{
		value = flame_ide::move(assigninigValue);
	}

	operator bool()
	{
		return true;
	}

	ValueType &getValue()
	{
		return value;
	}

	const ValueType &getValue() const
	{
		return value;
	}

private:
	ValueType value;
};

template<EnumeratedValueType UBJSON_TYPE>
class BaseValue<UBJSON_TYPE, TrueType::VALUE>: public base_value_utils::TraitValues<UBJSON_TYPE>
{
public:
	using Me = BaseValue<UBJSON_TYPE, TrueType::VALUE>;
	using Parent = base_value_utils::TraitValues<UBJSON_TYPE>;
	using typename Parent::ValueType;

	BaseValue() = default;
	BaseValue(const Me &) = default;
	BaseValue(Me &&) = default;

	BaseValue(const ValueType &initValue) :
			value(templates::SharedPointer<ValueType>(initValue))
	{}

	BaseValue(ValueType &&initValue) :
			value(
					templates::SharedPointer<ValueType>(flame_ide::move(initValue))
			)
	{}

	~BaseValue() = default;

	Me &operator=(const Me &) = default;
	Me &operator=(Me &&) = default;

	Me &operator=(const ValueType &assigninigValue)
	{
		if (!value)
		{
			value = templates::SharedPointer<ValueType>(assigninigValue);
		}
		else
		{
			*value = assigninigValue;
		}
	}

	Me &operator=(ValueType &&assigninigValue)
	{
		if (!value)
		{
			value = templates::SharedPointer<ValueType>(flame_ide::move(assigninigValue));
		}
		else
		{
			*value = flame_ide::move(assigninigValue);
		}
	}

	operator bool()
	{
		return value;
	}

	ValueType &getValue()
	{
		return *value;
	}

	const ValueType &getValue() const
	{
		return *value;
	}

private:
	templates::SharedPointer<ValueType> value;
};

}}

#endif // FLAMEIDE_UBJSON_BASEVALUE_HPP
