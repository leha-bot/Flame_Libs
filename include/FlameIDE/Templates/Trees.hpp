#ifndef FLAMEIDE_TEMPLATES_TREES_HPP
#define FLAMEIDE_TEMPLATES_TREES_HPP

#include <FlameIDE/Common/Traits.hpp>
#include <FlameIDE/Common/Utils.hpp>
#include <FlameIDE/Templates/Allocator.hpp>
#include <FlameIDE/Templates/Iterator.hpp>

namespace flame_ide
{namespace templates
{

namespace tree_utils
{

// Nodes

template<typename T, typename Traits = ContainerTraits<T>>
struct Node
{
	using Me = Node<T, Traits>;

	using Type = typename Traits::Type;
	using Reference = typename Traits::Reference;
	using ConstReference = typename Traits::ConstReference;
	using MoveReference = typename Traits::MoveReference;

	Node() = default;
	Node(Me &&node);
	Node(const Me &node);

	Me *left;
	Me *right;
	Me *previous;
	Type object;
};

template<typename T, typename Options, typename Traits = ContainerTraits<T>>
struct CustomNode: public Node<T, Traits>
{
	using Me = CustomNode<T, Traits, Options>;
	using Parent = Node<T, Traits>;

	using typename Parent::Type;
	using typename Parent::Reference;
	using typename Parent::ConstReference;
	using typename Parent::MoveReference;

	CustomNode() = default;

	using Parent::left;
	using Parent::right;
	using Parent::previous;
	Options options;
	using Parent::object;
};

template<typename Node>
struct ThreadingOption
{
	Node *next;
	Node *previous;
};

struct RbOptions
{
};

template<typename T, typename Traits>
using RbNode = CustomNode<T, RbOptions, Traits>;

// Iterator

template<typename T, typename Options, typename Traits>
class TreeIterator: public iterator_utils::BaseIterator<CustomNode<T, Options, Traits> *
		, IteratorCategory::BIDIRECTIONAL, IteratorAccess::NON_CONSTANT, Traits>
{
public:
	using Me = flame_ide::templates::tree_utils::TreeIterator<T, Options, Traits>;
	using Parent = iterator_utils::BaseIterator<
		CustomNode<T, Options, Traits> *
		, IteratorCategory::BIDIRECTIONAL
		, IteratorAccess::NON_CONSTANT
		, Traits
	>;
	using Node = flame_ide::templates::tree_utils::CustomNode<T, Options, Traits>;

	using typename Parent::Type;

	using typename Parent::Reference;
	using typename Parent::ConstReference;
	using typename Parent::MoveReference;

	using typename Parent::Pointer;
	using typename Parent::PointerToConst;

private:
	Node *current;
	Node *next;
	Node *previous;
};

/*
 * Обход дерева на псевдокоде:
 * left()
 * right()
 * current.
*/
}

template<
	typename T
	, typename Traits = ContainerTraits<T>
	, typename Allocator = allocator::ObjectAllocator<tree_utils::Node<T, Traits>>
>
class Tree
{
public:
	using Type = typename Traits::Type;
	using Pointer = typename Traits::Pointer;
	using PointerToConst = typename Traits::PointerToConst;
	using Reference = typename Traits::Reference;
	using ConstReference = typename Traits::ConstReference;
	using MoveReference = typename Traits::MoveReference;
	using SizeType = typename Traits::SizeType;
	using SsizeType = typename Traits::SsizeType;

};

}}

#endif // FLAMEIDE_TEMPLATES_TREES_HPP
