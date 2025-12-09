#include "NetworkAddressError.hpp"

#if defined(_WIN32)
#include <WS2tcpip.h>
#else
#include <netdb.h>
#endif

bool NetworkAddressError::Ok(void) const
{
    return code_ == 0;
}

std::string NetworkAddressError::Reason(void) const
{
#if defined(_WIN32)
    return std::string(gai_strerrorA(code_));
#else
    return std::string(gai_strerror(code_));
#endif
}   // ignore exception; if std::string cause exception, you are **fucked** up.