#ifndef _SQUID_EUI_EUI64_H
#define _SQUID_EUI_EUI64_H

#if USE_SQUID_EUI

namespace Ip
{
class Address;
}

#if HAVE_CSTRING
#include <cstring>
#endif
#if HAVE_SYS_EUI64_H
#include <sys/eui64.h>
#endif

/* memcpy and friends */
#if HAVE_STRING_H
#include <string.h>
#endif

namespace Eui
{

/* EUI-64 is 8 bytes. */
#if defined(EUI64_LEN)
#define SZ_EUI64_BUF EUI64_LEN
#else
#define SZ_EUI64_BUF 8
#endif

class Eui64
{

public:
    Eui64() { clear(); };
    Eui64(const Eui64 &t) { memcpy(this, &t, sizeof(Eui64)); };
    ~Eui64() {};

    const unsigned char *get(void);

    bool set(const char *src, const int len) {
        if (len > SZ_EUI64_BUF) return false;
        if (len < SZ_EUI64_BUF) clear();
        memcpy(eui, src, len);
        return true;
    };

    void clear() { memset(eui, 0, SZ_EUI64_BUF); };

    /**
     * Decode an ascii representation of an EUI-64 address.
     *
     * \param asc   ASCII representation of an EUI-64 address
     * \param eth   Binary representation of the EUI_64 address
     * \retval false        Conversion to binary failed. Invalid address
     * \retval true         Conversion completed successfully
     */
    bool decode(const char *asc);

    /**
     * Encode an ascii representation (asc) of an EUI-64 address.
     *
     * \param buf   Buffer to receive ASCII representation of an EUI-64 address
     * \param len   Length of the buffer space available. Must be >= SZ_EUI64_BUF bytes or the encode will fail.
     * \param eui   Binary representation of the EUI-64 address
     * \retval false        Conversion to ASCII failed.
     * \retval true         Conversion completed successfully.
     */
    bool encode(char *buf, const int len);

    // lookup an EUI-64 address via IPv6 SLAAC or NDP
    bool lookup(const Ip::Address &c);

    // lookup an EUI-64 address via IPv6 NDP
    bool lookupNdp(const Ip::Address &c);

    // lookup an EUI-64 address via decoding the IPv6 address SLAAC data
    bool lookupSlaac(const Ip::Address &c);

private:
    unsigned char eui[SZ_EUI64_BUF];
};

} // namespace Eui

#endif /* USE_SQUID_EUI */
#endif /* _SQUID_EUI_EUI64_H */
