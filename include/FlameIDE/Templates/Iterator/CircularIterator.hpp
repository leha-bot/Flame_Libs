#ifndef FLAMEIDE_TEMPLATES_ITERATOR_CIRCULARITERATOR_HPP
#define FLAMEIDE_TEMPLATES_ITERATOR_CIRCULARITERATOR_HPP

#include <FlameIDE/Templates/Iterator/IteratorTraits.hpp>
#include <FlameIDE/Templates/Iterator/Iterator.hpp>

#include <FlameIDE/Templates/Range.hpp>

#include <FlameIDE/Templates/Iterator/Operators.hpp>

namespace flame_ide
{namespace templates
{

template<
	typename IteratorType
	, IteratorCategory ITERATOR_CATEGORY =
			iterator_utils::GetIteratorInfo<IteratorType>::CATEGORY
	, typename Traits = typename iterator_utils::IteratorTraits<IteratorType>
	, typename MetaType = void
>
class CircularIterator;

}}

namespace flame_ide
{namespace templates
{

template<
	typename IteratorType
	, typename Traits
	, typename MetaType
>
class CircularIterator<IteratorType, IteratorCategory::FORWARD, Traits, MetaType>:
		public Iterator<
			IteratorType, IteratorCategory::FORWARD, Traits, MetaType
		>
{
public:
	using Parent = Iterator<
		IteratorType, IteratorCategory::FORWARD, Traits, MetaType
	>;
	using Me = CircularIterator<
		IteratorType, IteratorCategory::FORWARD, Traits, MetaType
	>;
	using Range = templates::Range<IteratorType>;

	CircularIterator() = default;
	CircularIterator(const Me &) = default;
	CircularIterator(IteratorType iterator, Range containerActualRange)
			: Parent(iterator)
			, range(containerActualRange)
	{}
	~CircularIterator() = default;
	Me& operator=(const Me &) = default;

	FLAMEIDE_ITERATOR_OPERATOR_INC_POSTFIX

	Me &operator++()
	{}

private:
	mutable Range range;
};

template<
	typename IteratorType
	, typename Traits
	, typename MetaType
>
class CircularIterator<IteratorType, IteratorCategory::BIDIRECTIONAL, Traits, MetaType>:
		public Iterator<
			IteratorType, IteratorCategory::BIDIRECTIONAL, Traits, MetaType
		>
{
	using Parent = Iterator<
		IteratorType, IteratorCategory::BIDIRECTIONAL, Traits, MetaType
	>;
	using Me = CircularIterator<
		IteratorType, IteratorCategory::BIDIRECTIONAL, Traits, MetaType
	>;
	using Range = templates::Range<IteratorType>;

	CircularIterator() = default;
	CircularIterator(const Me &) = default;
	CircularIterator(IteratorType iterator, Range containerActualRange)
			: Parent(iterator)
			, range(containerActualRange)
	{}
	~CircularIterator() = default;
	Me& operator=(const Me &) = default;

	FLAMEIDE_ITERATOR_OPERATOR_INC_POSTFIX
	FLAMEIDE_ITERATOR_OPERATOR_DEC_POSTFIX

	Me &operator++()
	{}

	Me &operator--()
	{}

private:
	mutable Range range;
};

template<
	typename IteratorType
	, typename Traits
	, typename MetaType
>
class CircularIterator<IteratorType, IteratorCategory::RANDOM_ACCESS, Traits, MetaType>:
		public Iterator<
			IteratorType, IteratorCategory::RANDOM_ACCESS, Traits, MetaType
		>
{
	using Parent = Iterator<
		IteratorType, IteratorCategory::RANDOM_ACCESS, Traits, MetaType
	>;
	using Me = CircularIterator<
		IteratorType, IteratorCategory::RANDOM_ACCESS, Traits, MetaType
	>;
	using Range = templates::Range<IteratorType>;

	CircularIterator() = default;
	CircularIterator(const Me &) = default;
	CircularIterator(IteratorType iterator, Range containerActualRange)
			: Parent(iterator)
			, range(containerActualRange)
	{}
	~CircularIterator() = default;
	Me& operator=(const Me &) = default;

	FLAMEIDE_ITERATOR_OPERATOR_INC_POSTFIX
	FLAMEIDE_ITERATOR_OPERATOR_DEC_POSTFIX

	FLAMEIDE_ITERATOR_OPERATOR_PLUS
	FLAMEIDE_ITERATOR_OPERATOR_MINUS

	Me &operator++()
	{}

	Me &operator--()
	{}

	template<typename IntType>
	Me &operator+=(IntType value)
	{}

	template<typename IntType>
	Me &operator-=(IntType value)
	{}

private:
	mutable Range range;
};

}}

#include <FlameIDE/Templates/Iterator/UndefOperators.hpp>

#endif // FLAMEIDE_TEMPLATES_ITERATOR_CIRCULARITERATOR_HPP