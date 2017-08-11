/*
 * file:       Utils.hpp
 *
 * created:    17.07.2017
 * author:     kachsheev
 */
#ifndef UTILS_HPP
#define UTILS_HPP

#include <Templates/Traits.hpp>

namespace flame_ide
{namespace templates
{

/**
 * @brief Get info about T is a primitive type or not.
 */
template<typename T>
inline constexpr bool isPrimitiveType() noexcept;

/**
 * @brief Comparing types.
 * @tparam First param.
 * @tparam Second param.
 */
template<typename T, typename U>
inline constexpr bool isSameTypes() noexcept;

/**
 * @brief std::move alternative.
 */
template<typename T> constexpr inline
typename RemoveReference<T>::Type&& move(T &&reference) noexcept;

/**
 * @brief std::forward alternative.
 */
template<class T> constexpr inline
T&& forward(T &&reference) noexcept;

/**
 * @brief Copying range.
 */
template<typename IteratorInput, typename IteratorOutput>
void copy(IteratorInput start, IteratorInput end
		, IteratorOutput out);

/**
 * @brief Getting size of range.
 */
template<typename Iterator, typename SizeTraits = flame_ide::templates::SizeTraits>
typename SizeTraits::SizeType countIterations(Iterator start, Iterator end);

/**
 * @brief Adapter for palcement new operator.
 *
 * Call custom constructors.
 */
template<typename T, typename ...Args> inline
typename DefaultTraits<T>::Pointer
placementNew(typename DefaultTraits<T>::Pointer pointer, Args &&...args) noexcept;

/**
 * @brief Comparing ranges.
 */
template<typename Iterator1 , typename Iterator2>
bool isEqual(Iterator1 start1, Iterator1 end1,
		Iterator2 start2, Iterator2 end2);

}}

template<typename T>
inline void *operator new(flame_ide::templates::SizeTraits::SizeType
		, T *pointer) noexcept
{
	return pointer;
}

template<typename T>
inline void *operator new[](flame_ide::templates::SizeTraits::SizeType
		, T * pointer) noexcept
{
	return pointer;
}

template<typename T>
inline void operator delete(void *, T *) noexcept
{}

template<typename T>
inline void operator delete[](void *, T *) noexcept
{}

namespace flame_ide
{namespace templates
{

template<typename T> inline constexpr
bool isPrimitiveType() noexcept
{
	using IsChar = ComparingTypes<T, Types::char_t>;
	using IsUchar = ComparingTypes<T, Types::uchar_t>;

	using IsShort = ComparingTypes<T, Types::short_t>;
	using IsUshort = ComparingTypes<T, Types::ushort_t>;

	using IsInt =ComparingTypes<T, Types::int_t>;
	using IsUint = ComparingTypes<T, Types::uint_t>;

	using IsLong = ComparingTypes<T, Types::long_t>;
	using IsUlong = ComparingTypes<T, Types::ulong_t>;

	using IsLlong = ComparingTypes<T, Types::llong_t>;
	using IsUllong = ComparingTypes<T, Types::ullong_t>;

	using IsFloat = ComparingTypes<T, Types::float_t>;

	using IsDouble = ComparingTypes<T, Types::double_t>;
	using IsLdouble = ComparingTypes<T, Types::ldouble_t>;

	return (IsChar::VALUE || IsUchar::VALUE
			|| IsShort::VALUE || IsUshort::VALUE
			|| IsInt::VALUE || IsUint::VALUE
			|| IsLong::VALUE || IsUlong::VALUE
			|| IsLlong::VALUE || IsUllong::VALUE
			|| IsFloat::VALUE
			|| IsDouble::VALUE || IsLdouble::VALUE);
}

template<typename T, typename U> inline constexpr
bool isSameTypes() noexcept
{
	return ComparingTypes<T, U>::VALUE;
}

template<typename T> constexpr inline
typename RemoveReference<T>::Type &&move(T &&reference) noexcept
{
	return static_cast<typename RemoveReference<T>::Type &&>(reference);
}

template<class T> constexpr inline
T&& forward(T &&reference) noexcept
{
	return static_cast<T &&>(reference);
}

template<typename IteratorInput, typename IteratorOutput>
void copy(IteratorInput start, IteratorInput end
		, IteratorOutput out)
{
	static_assert(!isSameTypes<decltype(*start), decltype(*out)>(), "Types is not equal");

	for(auto iterator = start; iterator != end; ++iterator, ++out)
		*out = *iterator;
}

template<typename Iterator, typename SizeTraits>
typename SizeTraits::SizeType countIterations(Iterator start, Iterator end)
{
	Types::ulong_t count = 0;
	for(auto iterator = start; iterator != end; ++iterator, ++count)
	{}
	return count;
}

template<typename T, typename ...Args> inline
typename DefaultTraits<T>::Pointer
placementNew(typename DefaultTraits<T>::Pointer pointer, Args &&...args) noexcept
{
	return new (pointer) typename DefaultTraits<T>::Type(forward(args)...);
}

template<typename Iterator1, typename Iterator2>
bool isEqual(Iterator1 start1, Iterator1 end1
		, Iterator2 start2, Iterator2 end2)
{
	static_assert(!isSameTypes<decltype(*start1), decltype(*start2)>(), "Types is not equal");

	bool equal = true;
	auto iterator1 = start1;
	auto iterator2 = start2;

	for(; iterator1 != end1 && iterator2 != end2 && equal; ++iterator1, ++iterator2)
		equal = (equal && *iterator1 == *iterator2);

	if(iterator1 == end1)
		if(iterator2 == end2)
			return equal;
		else
			return false;
	else
		return false;

	return equal;
}

}}

#endif // UTILS_HPP