#ifndef FLAMEIDE_TEMPLATES_INTIALIZERLIST_HPP
#define FLAMEIDE_TEMPLATES_INTIALIZERLIST_HPP

#include <FlameIDE/Common/Traits.hpp>
#include <FlameIDE/Common/Utils.hpp>

namespace flame_ide
{namespace templates
{

/**
 * @brief Alternative initializer list implementation
 */
template<typename T, SizeTraits::SizeType SIZE = 64>
class InitializerList
{
public:
	using Type = typename DefaultTraits<T>::Type;
	using Pointer = typename DefaultTraits<T>::Pointer;
	using Iterator = typename DefaultTraits<T>::PointerToConst;
	using SizeType = typename SizeTraits::SizeType;

	template<typename ...Args>
	InitializerList(Args &&...args);

	~InitializerList();

	constexpr SizeType size() const noexcept;

	constexpr Iterator begin() const noexcept;

	/**
	 * @brief Return an iterator pointing to the first element of the initializer_list.
	 *
	 * @param list
	 * Initializer list.
	 */
	template<typename U, SizeTraits::SizeType SIZE1>
	typename InitializerList<U, SIZE1>::Iterator begin(
			InitializerList<U, SIZE1> list) noexcept;

	constexpr Iterator end() const noexcept;

	/**
	 * @brief Return an iterator pointing to the last element of the initializer_list.
	 *
	 * @param list
	 * Initializer list.
	 */
	template<typename U, SizeTraits::SizeType SIZE1>
	typename InitializerList<U, SIZE1>::Iterator end(
			InitializerList<U, SIZE1> list) noexcept;

private:
	template<typename ...Args>
	struct Helper;

	template<typename ArgHead, typename ...Args>
	struct Helper<ArgHead, Args ...>: public NonCreational
	{
		static inline void init(Pointer iterator, ArgHead &&argHead, Args &&...args)
		{
			using ArgHeadType = typename RemoveAllTrait<decltype(argHead)>::Type;
			static_assert(ComparingTypes<Type, ArgHeadType>::VALUE, "Include type error.");
			*iterator = forward<decltype(argHead)>(argHead);
			Helper<Args...>::init(++iterator, forward<decltype(args)>(args)...);
		}
	};

	template<typename Arg>
	struct Helper<Arg>: public NonCreational
	{
		static inline void init(Pointer iterator, Arg &&arg)
		{
			static_assert(ComparingTypes<
						typename RemovePointerTrait<Pointer>::Type
						, typename RemoveAllTrait<Arg>::Type
					>::VALUE
					, "no possible to use this ");
			*iterator = forward<decltype(arg)>(arg);
		}
	};

	SizeType listSize;

	Type list[SIZE];
};

}}

namespace flame_ide
{namespace templates
{

template<typename T, SizeTraits::SizeType SIZE>
template<typename ...Args>
InitializerList<T, SIZE>::InitializerList(Args &&...args) : listSize(sizeof...(Args))
{
	static_assert(SIZE >= sizeof...(Args), "Illegal count of arguments.");
	Helper<Args...>::init(list, forward<decltype(args)>(args)...);
}

template<typename T, SizeTraits::SizeType SIZE> constexpr
typename InitializerList<T, SIZE>::SizeType InitializerList<T, SIZE>::size() const noexcept
{
	return listSize;
}

template<typename T, SizeTraits::SizeType SIZE> constexpr
typename InitializerList<T, SIZE>::Iterator InitializerList<T, SIZE>::begin() const noexcept
{
	return list;
}

template<typename T, SizeTraits::SizeType SIZE>
template<typename U, SizeTraits::SizeType SIZE1>
typename InitializerList<U, SIZE1>::Iterator InitializerList<T, SIZE>::begin(
		InitializerList<U, SIZE1> list) noexcept
{
	return list.begin();
}

template<typename T, SizeTraits::SizeType SIZE> constexpr
typename InitializerList<T, SIZE>::Iterator InitializerList<T, SIZE>::end() const noexcept
{
	return begin() + size();
}

template<typename T, SizeTraits::SizeType SIZE>
template<typename U, SizeTraits::SizeType SIZE1>
typename InitializerList<U, SIZE1>::Iterator InitializerList<T, SIZE>::end(
		InitializerList<U, SIZE1> list) noexcept
{
	return list.end();
}

template<typename T, SizeTraits::SizeType SIZE>
InitializerList<T, SIZE>::~InitializerList()
{
	for (auto &it : *this)
		it.~T();
}

}}

#endif // FLAMEIDE_TEMPLATES_INTIALIZERLIST_HPP
