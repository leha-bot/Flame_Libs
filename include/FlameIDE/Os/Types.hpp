#ifndef FLAMEIDE_OS_TYPES_HPP
#define FLAMEIDE_OS_TYPES_HPP

#include <FlameIDE/Os/Posix/Types.hpp>
#include <FlameIDE/Os/Windows/Types.hpp>

namespace flame_ide
{namespace os
{

/// @brief
using FileDescriptor = FLAMEIDE_OS_NAMESPACE::OsFileDescriptor;

/// @brief
using Status = FLAMEIDE_OS_NAMESPACE::OsStatus;

/// @brief
using SocketAddressIn = FLAMEIDE_OS_NAMESPACE::OsSocketAddressIn;

/// @brief
using SocketDescriptor = FLAMEIDE_OS_NAMESPACE::OsSocketDescriptor;

/// @brief
using Socket = FLAMEIDE_OS_NAMESPACE::OsSocket;

/// @brief
using SocketReceive = FLAMEIDE_OS_NAMESPACE::OsSocketReceive;

/// @brief
using ThreadContext = FLAMEIDE_OS_NAMESPACE::OsThreadContext;

/// @brief
using ThreadTaskTrait = FLAMEIDE_OS_NAMESPACE::OsThreadTaskTrait;

/// @brief
using MutexContext = FLAMEIDE_OS_NAMESPACE::OsMutexContext;

/// @brief
using SpinContext = FLAMEIDE_OS_NAMESPACE::OsSpinlockContext;

/// @brief
using SemaphoreContext = FLAMEIDE_OS_NAMESPACE::OsSemaphoreContext;

/// @brief
using SemaphoreValue = FLAMEIDE_OS_NAMESPACE::OsSemaphoreValue;

/// @brief Library handler
using LibraryHandle = FLAMEIDE_OS_NAMESPACE::OsLibraryHandle;

/// @brief The ActionType enum
enum class ActionType
{
	READER
	, WRITER
	, BIDIRECTIONAL
};

/// @brief The ActionMethod enum
enum class ActionMethod
{
	SYNCHRONOUS
	, ASYNCHRONOUS
};

/// @brief The StreamType enum
enum class StreamType
{
	MEMORY
	, PIPE
	, NAMED_PIPE
	, FILE
	, SOCKET
};

}} // namespace flame_ide::os

inline
FLAMEIDE_OS_NAMESPACE::OsSocket::OsSocket(const OsSocketReceive &socket) noexcept
{
	operator=(socket);
}

inline FLAMEIDE_OS_NAMESPACE::OsSocket &
FLAMEIDE_OS_NAMESPACE::OsSocket::operator=(const OsSocketReceive &socketReceive) noexcept
{
	address = socketReceive.address;
	descriptor = *socketReceive.descriptor;
	return *this;
}

inline
FLAMEIDE_OS_NAMESPACE::OsSocketReceive::OsSocketReceive(const OsSocket &socket) noexcept
{
	operator=(socket);
}

inline FLAMEIDE_OS_NAMESPACE::OsSocketReceive &
FLAMEIDE_OS_NAMESPACE::OsSocketReceive::operator=(const OsSocket &socket) noexcept
{
	address = socket.address;
	descriptor = &socket.descriptor;
	return *this;
}

#undef FLAMEIDE_OS_NAMESPACE

#endif // FLAMEIDE_OS_TYPES_HPP
