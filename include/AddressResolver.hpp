#ifndef ADDRESS_RESOLVER_HPP
#define ADDRESS_RESOLVER_HPP

#include <tuple>
#include <vector>

#if defined(_WIN32)
#include <WS2tcpip.h>
#else
#include <netdb.h>
#endif

#include "NetworkAddress.hpp"
#include "NetworkAddressError.hpp"

class AddressResolver
{
private:
    using Result = std::tuple<Error, std::vector<NetworkAddress>>;

public:
    struct Hints {
        int family = AF_UNSPEC;
        int socktype = 0;
        int protocol = 0;
        int flags = AI_ADDRCONFIG;

        Hints(int family = AF_INET, int socktype = SOCK_STREAM,
              int protocol = IPPROTO_TCP, int flags = AI_ADDRCONFIG)
        {
        }
    };

public:
    static Result Resolve(const char* host, const char* service, const Hints &);
    static Result ResolvePassive(const char* service, const Hints &);

private:
    static Result ResolveImpl(const char* host, const char* service, const Hints &);
};

#endif