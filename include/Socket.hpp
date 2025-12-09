#ifndef SOCKET_HPP__
#define SOCKET_HPP__

#if defined(_WIN32)
#include <WinSock2.h>
#include <WS2tcpip.h>

using socket_native_t = SOCKET;
const socket_native_t SOCKET_INVALID_HANDLE = INVALID_SOCKET;
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

using socket_native_t = int;
const socket_native_t SOCKET_INVALID_HANDLE = -1;
#endif

#include "NetworkAddress.hpp"
#include "SocketError.hpp"

class Socket
{
private:
    using NativeHandle = socket_native_t;
    static const NativeHandle InvalidHandle = SOCKET_INVALID_HANDLE;

private:
#if defined(_WIN32)
    static WSADATA wsaData;
#endif
public:
    static SocketError Setup(void);
    static SocketError Cleanup(void);

public:
    Socket(const NetworkAddress&);
    ~Socket(void);

public:
    bool IsValid(void) const;
    SocketError GetError(void) const;
    NativeHandle GetNative(void) const;

private:
    SocketError error_;
    NativeHandle handle_;
};

#endif