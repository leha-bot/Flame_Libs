#include <FlameIDE/Streams/RamStream.hpp>

namespace flame_ide
{namespace streams
{

RamStream::RamStream() = default;
RamStream::~RamStream() = default;

SizeTraits::SsizeType RamStream::write(Parent::InputByteRange range)
{
	auto currentSize = buffer.size();
	for (auto i : range)
	{
		buffer.pushBack(i);
	}
	auto newSize = buffer.size();
	return static_cast<SizeTraits::SsizeType>(newSize - currentSize);
}

SizeTraits::SsizeType RamStream::write(Parent::InputCircularByteRange range)
{
	auto currentSize = buffer.size();
	for (auto i : range)
	{
		buffer.pushBack(i);
	}
	auto newSize = buffer.size();
	return static_cast<SizeTraits::SsizeType>(newSize - currentSize);
}

SizeTraits::SsizeType RamStream::read(Parent::OutputByteRange range)
{
	auto currentSize = buffer.size();
	for (auto &i : range)
	{
		if (buffer.size())
		{
			i = *buffer.begin();
			buffer.erase(buffer.begin());
		}
		else
		{
			break;
		}
	}
	auto newSize = buffer.size();
	return static_cast<SizeTraits::SsizeType>(currentSize - newSize);
}

SizeTraits::SsizeType RamStream::read(Parent::OutputCircularByteRange range)
{
	auto currentSize = buffer.size();
	for (auto &i : range)
	{
		if (buffer.size())
		{
			i = *buffer.begin();
			buffer.erase(buffer.begin());
		}
		else
		{
			break;
		}
	}
	auto newSize = buffer.size();
	return static_cast<SizeTraits::SsizeType>(currentSize - newSize);
}

}}
