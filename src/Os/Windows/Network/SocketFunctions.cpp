#include <FlameIDE/../../src/Os/Network/SocketFunctions.hpp>

#include <FlameIDE/Common/Traits/CreationProhibitions.hpp>
#include <FlameIDE/Common/Traits/Numbers.hpp>

#include <FlameIDE/Os/Constants.hpp>

#include <Ws2tcpip.h>

class WinSockLibrary: public flame_ide::NonAssignable
{
public:
	static volatile WinSockLibrary &signeton() noexcept;

	operator bool() const volatile noexcept;

	void init() volatile noexcept;
	void destroy() volatile noexcept;

private:
	WinSockLibrary() noexcept = default;
	~WinSockLibrary() noexcept;

private:
	::WSADATA wsaData;
	flame_ide::os::Status wsaStatus = 0;
	bool inited = false;
};

//

static bool winsockInit() noexcept;

//

namespace flame_ide
{namespace os
{namespace network
{namespace socket
{
namespace // anonymous
{

::SOCKET udpСreateSocket() noexcept
{
	return ::WSASocketW(AF_INET, SOCK_DGRAM, IPPROTO_UDP, nullptr, 0, WSA_FLAG_OVERLAPPED);
}

::SOCKET tcpCreateSocket() noexcept
{
	return ::WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, WSA_FLAG_OVERLAPPED);
}

::SOCKADDR_IN ipAddressServer(Ipv4::Port port) noexcept
{
	::SOCKADDR_IN sockaddr = SOCKET_INITIALIZER.address;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = ::htons(static_cast<Types::ushort_t>(port));
	sockaddr.sin_addr.S_un.S_addr = INADDR_ANY;
	return sockaddr;
}

::SOCKADDR_IN ipAddressClient(Ipv4::Address serverAddress) noexcept
{
	::SOCKADDR_IN sockaddr = SOCKET_INITIALIZER.address;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = ::htons(static_cast<Types::ushort_t>(serverAddress.port));
	auto result = ::inet_pton(
			sockaddr.sin_family, serverAddress.ip, &sockaddr.sin_addr.S_un.S_addr
	);
	if (result != 1)
	{
		sockaddr = SOCKET_INITIALIZER.address;
	}
	return sockaddr;
}

} // namespace anonymous
}}}} // namespace flame_ide::os::network::socket

namespace flame_ide
{namespace os
{namespace network
{namespace socket
{

// UDP

Socket createUdpServer(Ipv4::Port port) noexcept
{
	Socket socket;

	if (!winsockInit())
		return socket;

	socket = Socket{ udpСreateSocket(), ipAddressServer(port) };

	const auto address = reinterpret_cast<const ::SOCKADDR *>(&socket.address);
	const auto result = ::bind(socket.descriptor, address, sizeof(socket.address));
	if (result == SOCKET_ERROR)
	{
		socket = Socket{};
	}

	return socket;
}

Socket createUdpClient(Ipv4 ipServer) noexcept
{
	Socket socket;

	if (!winsockInit())
		return socket;

	socket = Socket{ udpСreateSocket(), ipAddressClient(ipServer) };
	if (socket.descriptor == INVALID_SOCKET)
	{
		socket = Socket{};
	}
	return socket;
}

// TCP

Socket createTcpServer(Ipv4::Port port) noexcept
{
	Socket socket;

	if (!winsockInit())
		return socket;

	socket = Socket{ tcpCreateSocket(), ipAddressServer(port) };

	const auto address = reinterpret_cast<const ::SOCKADDR *>(&socket.address);
	const auto result = ::bind(socket.descriptor, address, sizeof(socket.address));
	if (result == SOCKET_ERROR)
	{
		socket = Socket{};
	}
	return socket;
}

Socket createTcpClient(Ipv4 ipServer) noexcept
{
	Socket socket;

	if (!winsockInit())
		return socket;

	socket = Socket{ tcpCreateSocket(), ipAddressClient(ipServer) };
	if (socket.descriptor == INVALID_SOCKET)
	{
		socket = os::SOCKET_INVALID;
	}
	return socket;
}

// Common

Status destroy(Socket &socket) noexcept
{
	if (::closesocket(socket.descriptor) < 0)
	{
		return -static_cast<Status>(::GetLastError());
	}
	socket.descriptor = os::SOCKET_INVALID.descriptor;

	return STATUS_SUCCESS;
}

Types::ssize_t receivingBytesNumber(const Socket &socket) noexcept
{
	u_long value = 0;
	auto result = ::ioctlsocket(socket.descriptor, FIONREAD, &value);
	if (result < 0)
	{
		return -static_cast<flame_ide::os::Status>(::GetLastError());
	}
	return static_cast<Types::ssize_t>(value);
}

Ipv4 getIpv4(const Socket &socket) noexcept
{
	auto port = ::ntohs(socket.address.sin_port);
	union
	{
		Types::uint_t value;
		Ipv4::Number address[Ipv4::COUNT_NUMBERS];
	} in;
	in.value = socket.address.sin_addr.s_addr;

	return Ipv4{ in.address, port };
}

}}}} // namespace flame_ide::os::network::socket

//

volatile WinSockLibrary &WinSockLibrary::signeton() noexcept
{
	static volatile WinSockLibrary winsock;
	return winsock;
}

WinSockLibrary::operator bool() const volatile noexcept
{
	return inited;
}

void WinSockLibrary::init() volatile noexcept
{
	if (inited)
		return;

	auto result = ::WSAStartup(MAKEWORD(2, 2), (::WSADATA *)(&wsaData));
	if (result)
	{
		wsaStatus = ::WSAGetLastError();
		return;
	}

	inited = true;
}

void WinSockLibrary::destroy() volatile noexcept
{
	if (!inited)
		return;

	wsaStatus = WSACleanup();
}

WinSockLibrary::~WinSockLibrary() noexcept
{
	destroy();
}

//

static bool winsockInit() noexcept
{
	auto &winsock = WinSockLibrary::signeton();
	winsock.init();
	return winsock.operator bool();
}