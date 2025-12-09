#ifndef NETWORK_ADDRESS__
#define NETWORK_ADDRESS__

#if defined(_WIN32)
#include <WinSock2.h>
#include <WS2tcpip.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#endif

class NetworkAddress
{
private:
	struct sockaddr_storage storage_;
	socklen_t length_;
	int family_;
	int socktype_;
	int protocol_;

public:
	NetworkAddress(const struct addrinfo&);

	int GetFamily(void) const;
	int GetType(void) const;
	int GetProtocol(void) const;

	const struct sockaddr* GetAddress(void) const;
	socklen_t GetAddressLength(void) const;
};

#endif