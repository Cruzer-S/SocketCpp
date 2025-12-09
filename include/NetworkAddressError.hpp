#ifndef NETWORK_ADDRESS_ERROR_HPP__
#define NETWORK_ADDRESS_ERROR_HPP__

#include "SocketError.hpp"

class NetworkAddressError : public SocketError
{
public:
	NetworkAddressError(int code);

	bool Ok(void) const override;
	std::string Reason(void) const override;
};

#endif