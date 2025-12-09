#include "Socket.hpp"

#include <cstring>

WSADATA Socket::wsaData;

Socket::Socket(const NetworkAddress& address)
    : handle_(SOCKET_INVALID_HANDLE), error_(SocketError(0))
{
    handle_ = socket(
        address.GetFamily(),
        address.GetType(),
        address.GetProtocol()
    );
    if (handle_ == SOCKET_INVALID_HANDLE) {
        error_ = SocketError(WSAGetLastError());
        return;
    }

    int rc = bind(handle_, address.GetAddress(), address.GetAddressLength());
    if (rc == SOCKET_ERROR) {
        error_ = SocketError(WSAGetLastError());
        closesocket(handle_);
        handle_ = SOCKET_INVALID_HANDLE;
        return;
    }

    error_ = SocketError(0);
}

Socket::~Socket(void)
{
    if (IsValid())
        closesocket(handle_);
}

bool Socket::IsValid() const
{
    return handle_ != SOCKET_INVALID_HANDLE;
}

SocketError Socket::GetError() const
{
    return error_;
}

Socket::NativeHandle Socket::GetNative() const
{
    return handle_;
}

SocketError Socket::Setup()
{
    int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (ret != 0)
        return SocketError(ret);

    return SocketError(0);
}

SocketError Socket::Cleanup()
{
    int ret = WSACleanup();
    if (ret != 0)
        return SocketError(WSAGetLastError());

    return SocketError(0);
}