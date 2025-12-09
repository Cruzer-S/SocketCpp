#include "AddressResolver.hpp"

#include <cstring>

using Result = std::tuple<SocketError, std::vector<NetworkAddress>>;

Result AddressResolver::ResolveImpl(const char* host, const char* service, const Hints& hints)
{
    struct addrinfo ai = { };

    memset(&ai, 0x00, sizeof(struct addrinfo));
    ai.ai_family = hints.family;
    ai.ai_socktype = hints.socktype;
    ai.ai_protocol = hints.protocol;

    ai.ai_flags = hints.flags;

    struct addrinfo* ai_ret = nullptr;
    int rc = getaddrinfo(host, service, &ai, &ai_ret);
    std::vector<NetworkAddress> out;
    if (rc != 0)
        return { NetworkAddressError::NetworkAddressError(rc), std::move(out) };

    for (struct addrinfo* ai = ai_ret; ai; ai = ai->ai_next)
        out.push_back(NetworkAddress(*ai));

    freeaddrinfo(ai_ret);

    return { NetworkAddressError::NetworkAddressError(0), std::move(out) };
}

Result AddressResolver::Resolve(const char* host, const char* service, const Hints& hints)
{
    return ResolveImpl(host, service, hints);
}

Result AddressResolver::ResolvePassive(const char* service, const Hints& hintsIn)
{
    Hints h = hintsIn;

    h.flags |= AI_PASSIVE;

    return ResolveImpl(nullptr, service, h);
}