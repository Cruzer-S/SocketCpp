#include "Socket.hpp"

#include <cstring>

WSADATA Socket::wsaData;

Socket::Socket(const NetworkAddress& address)
    : handle_(SOCKET_INVALID_HANDLE), error_(Error(0))
{
    handle_ = socket(
        address.GetFamily(),
        address.GetType(),
        address.GetProtocol()
    );
    if (handle_ == SOCKET_INVALID_HANDLE) {
        error_ = Error(WSAGetLastError());
        return;
    }

    int rc = bind(handle_, address.GetAddress(), address.GetAddressLength());
    if (rc == SOCKET_ERROR) {
        error_ = Error(WSAGetLastError());
        closesocket(handle_);
        handle_ = SOCKET_INVALID_HANDLE;
        return;
    }

    error_ = Error(0);
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

Error Socket::GetError() const
{
    return error_;
}

Socket::NativeHandle Socket::GetNative() const
{
    return handle_;
}

Error Socket::Setup()
{
    int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (ret != 0)
        return Error(ret);

    return Error(0);
}

Error Socket::Cleanup()
{
    int ret = WSACleanup();
    if (ret != 0)
        return Error(WSAGetLastError());

    return Error(0);
}