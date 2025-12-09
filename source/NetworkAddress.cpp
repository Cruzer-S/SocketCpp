#include "NetworkAddress.hpp"

#include <cstring>

int NetworkAddress::GetFamily(void) const
{
	return family_;
}

int NetworkAddress::GetType(void) const
{
	return socktype_;
}

int NetworkAddress::GetProtocol(void) const
{
	return protocol_;
}

const struct sockaddr* NetworkAddress::GetAddress(void) const
{
	return (const struct sockaddr*) &storage_;
}

socklen_t NetworkAddress::GetAddressLength(void) const
{
	return length_;
}

NetworkAddress::NetworkAddress(const struct addrinfo& ai)
{
	family_ = ai.ai_family;
	socktype_ = ai.ai_socktype;
	protocol_ = ai.ai_protocol;
	length_ = static_cast<socklen_t>(ai.ai_addrlen);

	memset(&storage_, 0x00, length_);
	memcpy(&storage_, ai.ai_addr, ai.ai_addrlen);
}