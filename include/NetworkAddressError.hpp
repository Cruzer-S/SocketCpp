#ifndef NETWORK_ADDRESS_ERROR_HPP__
#define NETWORK_ADDRESS_ERROR_HPP__

#include "Error.hpp"

class NetworkAddressError : public Error
{
public:
	bool Ok(void) const override;
	std::string Reason(void) const override;
};

#endif