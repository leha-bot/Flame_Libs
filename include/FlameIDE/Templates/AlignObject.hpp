#ifndef FLAMEIDE_TEMPLATES_ALIGNOBJECT_HPP
#define FLAMEIDE_TEMPLATES_ALIGNOBJECT_HPP

#include <FlameIDE/Common/Traits.hpp>
#include <FlameIDE/Common/Utils.hpp>

namespace flame_ide
{namespace templates
{

namespace align
{
using _default = IntegralConstant<SizeTraits::SsizeType, -1>;
using _1 = IntegralConstant<SizeTraits::SsizeType, 1>;
using _2 = IntegralConstant<SizeTraits::SsizeType, _1::VALUE * 2>;
using _4 = IntegralConstant<SizeTraits::SsizeType, _2::VALUE * 2>;
using _8 = IntegralConstant<SizeTraits::SsizeType, _4::VALUE * 2>;
using _16 = IntegralConstant<SizeTraits::SsizeType, _8::VALUE * 2>;
using _32 = IntegralConstant<SizeTraits::SsizeType, _16::VALUE * 2>;
using _64 = IntegralConstant<SizeTraits::SsizeType, _32::VALUE * 2>;
using _128 = IntegralConstant<SizeTraits::SsizeType, _64::VALUE * 2>;
using _256 = IntegralConstant<SizeTraits::SsizeType, _128::VALUE * 2>;
using _512 = IntegralConstant<SizeTraits::SsizeType, _256::VALUE * 2>;
using _1024 = IntegralConstant<SizeTraits::SsizeType, _512::VALUE * 2>;
} // namespace align


///
/// @brief The AlignObject struct
///
template<typename T, SizeTraits::SsizeType ALIGN>
struct AlignedObject
{
	static_assert (
			ALIGN == align::_1::VALUE || ALIGN == align::_2::VALUE
					|| ALIGN == align::_4::VALUE || ALIGN == align::_8::VALUE
					|| ALIGN == align::_16::VALUE || ALIGN == align::_32::VALUE
					|| ALIGN == align::_64::VALUE || ALIGN == align::_128::VALUE
					|| ALIGN == align::_256::VALUE || ALIGN == align::_512::VALUE
					|| ALIGN == align::_1024::VALUE
			, "Invalid ALIGN."
	);

	using Pointer = typename DefaultTraits<T>::Pointer;
	using PointerToConst = typename DefaultTraits<T>::PointerToConst;

	static constexpr auto INIT_VALUE = byte_t();
	static constexpr auto ARRAY_SIZE = size_t(sizeof(T));

	AlignedObject() noexcept;

	template<typename Arg, typename ...Args>
	AlignedObject(Arg &&arg, Args &&...args) noexcept;

	~AlignedObject() noexcept;

	///
	/// @brief getAddress
	/// @return
	///
	Pointer getAddress() noexcept;

	///
	/// @brief getAddress
	/// @return
	///
	PointerToConst getAddress() const noexcept;

	alignas(ALIGN) byte_t array[ARRAY_SIZE];
};

template<typename T>
struct AlignedObject<T, align::_default::VALUE>: public AlignedObject<T, alignof(T)>
{
	using Parent = AlignedObject<T, alignof(T)>;

	AlignedObject() noexcept = default;

	template<typename Arg, typename ...Args>
	AlignedObject(Arg &&arg, Args &&...args) noexcept;

	~AlignedObject() = default;
};
template<typename T>
using AlignObject = AlignedObject<T, align::_default::VALUE>;

}}

namespace flame_ide
{namespace templates
{

template<typename T, SizeTraits::SsizeType ALIGN>
AlignedObject<T, ALIGN>::AlignedObject() noexcept
{
	for (size_t i = 0; i < ARRAY_SIZE; ++i)
	{
		array[i] = INIT_VALUE;
	}
}

template<typename T, SizeTraits::SsizeType ALIGN>
template<typename Arg, typename ...Args>
AlignedObject<T, ALIGN>::AlignedObject(Arg &&arg, Args &&...args) noexcept :
		AlignedObject()
{
	auto pointer = getAddress();
	emplaceNew(
			pointer, flame_ide::forward<Arg>(arg), flame_ide::forward<Args>(args)...
	);
}

template<typename T, SizeTraits::SsizeType ALIGN>
AlignedObject<T, ALIGN>::~AlignedObject() noexcept
{
	// getAddress()->~T();
}

template<typename T, SizeTraits::SsizeType ALIGN>
typename AlignedObject<T, ALIGN>::Pointer
AlignedObject<T, ALIGN>::getAddress() noexcept
{
	auto address = reinterpret_cast<Types::ptrint_t>(array);
	return reinterpret_cast<typename DefaultTraits<T>::Pointer>(address);
}

template<typename T, SizeTraits::SsizeType ALIGN>
typename AlignedObject<T, ALIGN>::PointerToConst
AlignedObject<T, ALIGN>::getAddress() const noexcept
{
	auto address = reinterpret_cast<Types::ptrint_t>(array);
	return reinterpret_cast<PointerToConst>(address);
}

// Default

template<typename T>
template<typename Arg, typename ...Args>
AlignedObject<T, align::_default::VALUE>::AlignedObject(
		Arg &&arg, Args &&...args
) noexcept : Parent(flame_ide::forward<Arg>(arg), flame_ide::forward<Args>(args)...)
{}

}}

#endif // FLAMEIDE_TEMPLATES_ALIGNOBJECT_HPP
