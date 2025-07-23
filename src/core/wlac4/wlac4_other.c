//
// file:			wlac4_empty.cpp
// path:			src/core/wlac4/wlac4_empty.cpp
// created on:		2022 Sep 12
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <ldap.h>
#include <cinternal/disable_compiler_warnings.h>
#include <string.h>
#include <io.h>
#include <cinternal/undisable_compiler_warnings.h>


WLAC4_BEGIN_C

static int ioctl_private(int a_d, int a_request, va_list* a_arg_list_p) CPPUTILS_NOEXCEPT;

static inline int IsDescriptorASocketInline(int a_d) CPPUTILS_NOEXCEPT {
    // Declarations
    fd_set rfds;
    int maxsd;
    int nSelectReturn;
    struct timeval	aTimeout;
    int nIsSocket;

    // First is to check descriptor
    if (a_d < 0)return 0;

    aTimeout.tv_sec = 0;
    aTimeout.tv_usec = 0;

    FD_ZERO(&rfds);
    FD_SET((unsigned int)a_d, &rfds);
    maxsd = (int)(a_d + 1);
    nSelectReturn = select(maxsd, &rfds, &rfds, &rfds, &aTimeout);
    if (nSelectReturn == SOCKET_ERROR)
    {
        nSelectReturn = WSAGetLastError();
        if (nSelectReturn == WSANOTINITIALISED)
        {
            return WSANOTINITIALISED;
        }
    }
    nIsSocket = (nSelectReturn >= 0) ? 1 : 0;
    return nIsSocket;

}


WLAC4_WLAC4_EXPORT int strncasecmp(const char* a_s1, const char* a_s2, size_t a_n)
{
    size_t i = 0;
    int nC1, nC2;

    for (; i < a_n && a_s1[i] != 0 && a_s2[i] != 0; ++i)
    {
        nC1 = _toupper(a_s1[i]);
        nC2 = _toupper(a_s2[i]);
        if (nC2 != nC1) { return nC2 - nC1; }
    }

    return a_n ? ((int)(a_s2[i] - a_s1[i])) : 0;
}


WLAC4_WLAC4_EXPORT int strcasecmp(const char* a_s1, const char* a_s2)
{
    size_t unLen1 = strlen(a_s1);
    size_t unLen2 = strlen(a_s2);

    unLen1 = (unLen2 < unLen1) ? unLen2 : unLen1;
    return strncasecmp(a_s1, a_s2, unLen1);
}


WLAC4_WLAC4_EXPORT int ldap_initialize(LDAP** a_ldp, const char* a_uri)
{
    //WINLDAPAPI LDAP * LDAPAPI ldap_initA( _In_ const PSTR HostName, ULONG PortNumber );
    size_t unHostNameLen;
    int nPort;
    char* pcHostName;
    char* pcPort, * pcTerm;

    //func_ldyp_init = (LDAP(LDAPAPI*)(PCHAR, ULONG))GetProcAddress(s_ldap_lib_handle, "ldap_initA");

    pcPort = strstr(a_uri, "://");

    if (pcPort) { // Linux style
        nPort = strtol(a_uri, &pcTerm, 10);
        if (pcTerm == a_uri) {  // Port should be default
            nPort = LDAP_PORT;
        }
        pcHostName = pcPort + strlen("://");
    }
    else {  // windows style
        pcPort = strchr(a_uri, ':');
        if (pcPort) {
            nPort = strtol(pcPort, &pcTerm, 10);
            if (pcTerm == pcPort) {  // Port should be default
                nPort = LDAP_PORT;
            }
            unHostNameLen = (size_t)(pcPort - a_uri);
            pcHostName = (char*)_alloca(unHostNameLen + 1);
            memcpy(pcHostName, a_uri, unHostNameLen);
            pcHostName[unHostNameLen] = '\0';
        }
        else {
            pcHostName = (char*)a_uri;
            nPort = LDAP_PORT;
        }
    }  // else{  // windows style

    *a_ldp = ldap_initA(pcHostName, (ULONG)nPort);
    return 0;
}


WLAC4_WLAC4_EXPORT
int
gethostbyname_r(const char* name, struct hostent* ret, char* buf,
    unsigned int buflen, struct hostent** result, int* h_errnop)
{
    static HANDLE s_hMutex = CPPUTILS_STATIC_CAST(HANDLE, 0);
    int                     hsave;
    struct hostent* ph;

    WaitForSingleObject(s_hMutex, INFINITE); /* begin critical area */
    hsave = h_errno;

#pragma warning (push)
#pragma warning (disable:4996)
    ph = gethostbyname(name);
    //getaddrinfo()

    *h_errnop = h_errno; /* copy h_errno to *h_herrnop */

    if (ph == NULL) *result = NULL;
    else {

        char** p;
        char** q;
        char* pbuf;
        int     nbytes = 0;
        int     naddr = 0;
        int     naliases = 0;

        /* determine if we have enough space in buf */

        /* count how many addresses */

        for (p = ph->h_addr_list; *p != 0; p++) {

            nbytes += ph->h_length; /* addresses */
            nbytes += sizeof(*p);  /* pointers */
            naddr++;
        }
        nbytes += sizeof(*p); /* one more for the terminating NULL */

        /* count how many aliases, and total length of strings */

        for (p = ph->h_aliases; *p != 0; p++) {

            nbytes += (int)(strlen(*p) + 1); /* aliases */
            nbytes += sizeof(*p);       /* pointers */
            naliases++;
        }
        nbytes += sizeof(*p); /* one more for the terminating NULL */

        /* here nbytes is the number of bytes required in buffer */
        /* as a terminator must be there, the minimum value is ph->h_length */

        if ((unsigned int)nbytes > buflen) {

            *result = NULL;
            //pthread_mutex_unlock(&__mutex); /* end critical area */
            ReleaseMutex(s_hMutex);
            return ERANGE; /* not enough space in buf!! */
        }

        /* There is enough space. Now we need to do a deep copy! */

        /* Allocation in buffer:
        from [0] to [(naddr - 1) * sizeof (*p)]:
        pointers to addresses
        at [naddr * sizeof (*p)]:
        NULL
        from [(naddr+1) * sizeof(*p)] to [(naddr+naliases) * sizeof(*p)] :
        pointers to aliases
        at [(naddr+naliases+1) * sizeof(*p)]:
        NULL
        then naddr addresses (fixed length), and naliases aliases (asciiz).
        */

        *ret = *ph;   /* copy whole structure (not its address!) */

        /* copy addresses */

        q = (char**)buf; /* pointer to pointers area (type: char **) */
        ret->h_addr_list = q; /* update pointer to address list */
        pbuf = buf + ((naddr + naliases + 2) * sizeof(*p)); /* skip that area */

        for (p = ph->h_addr_list; *p != 0; p++) {

            memcpy(pbuf, *p, ph->h_length); /* copy address bytes */
            *q++ = pbuf;                     /* the pointer is the one inside buf... */
            pbuf += ph->h_length;            /* advance pbuf */
        }
        *q++ = NULL; /* address list terminator */

        /* copy aliases */

        ret->h_aliases = q; /* update pointer to aliases list */
        for (p = ph->h_aliases; *p != 0; p++) {

            strcpy(pbuf, *p);   /* copy alias strings */
            *q++ = pbuf;         /* the pointer is the one inside buf... */
            pbuf += strlen(*p); /* advance pbuf */
            *pbuf++ = 0;         /* string terminator */
        }
        *q++ = NULL; /* terminator */

        strcpy(pbuf, ph->h_name);  /* copy alias strings */
        ret->h_name = pbuf;
        pbuf += strlen(ph->h_name); /* advance pbuf */
        *pbuf++ = 0;                /* string terminator */

        *result = ret;  /* and let *result point to structure */

    }
    //h_errno = hsave;  /* restore h_errno */
    WSASetLastError(hsave);

    //pthread_mutex_unlock(&__mutex); /* end critical area */
    ReleaseMutex(s_hMutex);
#pragma warning (pop)
    return *result == CPPUTILS_NULL ? -1 : 0;
}


WLAC4_WLAC4_EXPORT int ioctl(int a_d, int a_request, ...)
{
    // Declarations
    int nReturn;
    va_list args;

    va_start(args, a_request);
    nReturn = ioctl_private(a_d, a_request, &args);
    va_end(args);
    return nReturn;
}



static int ioctl_private(int a_d, int a_request, va_list* a_arg_list_p) CPPUTILS_NOEXCEPT
{
    // Declarations
    // INTERFACE_INFO*	pIfaceInfo;
    // struct ifconf* pIfConf;
    // struct ifreq *ifr;
    // DWORD dwOutBufSize;
    // DWORD dwOutBufSizeReturned;
    // int nNumberOfInterfaces0;
    // int nNumberOfInterfaces;
    // int i;

    void* pLstArg;  // Last Argument
    int nIsSocket;
    int nReturn = 0;
    DWORD dwReturned;
    unsigned long ulnNonBlocking;
    int* pnNonBlocking;

    // First is to check descriptor
    if (a_d < 0)return a_d;
    nIsSocket = IsDescriptorASocketInline(a_d);

    if (nIsSocket == 1)
    {
        switch (a_request)
        {
            //case SIOCGIFCONF:
            //	pIfConf = va_arg(*a_arg_list_p, struct ifconf*);
            //
            //	dwOutBufSize = 64 * sizeof(INTERFACE_INFO);
            //	pLstArg = pIfaceInfo = (INTERFACE_INFO*)_alloca(dwOutBufSize);
            //	nReturn = (int)WSAIoctl((SOCKET)a_d, SIO_GET_INTERFACE_LIST, NULL, 0,
            //		pLstArg, dwOutBufSize, &dwOutBufSizeReturned, 0, NULL);
            //	if (nReturn == SOCKET_ERROR)
            //	{
            //		nReturn = WSAGetLastError();
            //		nReturn = nReturn > 0 ? -nReturn : nReturn;
            //		//va_end(args);
            //		break;
            //	}
            //	nNumberOfInterfaces0 = pIfConf->ifc_len / sizeof(struct ifreq);
            //	nNumberOfInterfaces = dwOutBufSizeReturned / sizeof(INTERFACE_INFO);
            //	if (nNumberOfInterfaces > nNumberOfInterfaces0){ nNumberOfInterfaces = nNumberOfInterfaces0; }
            //	pIfConf->ifc_len = nNumberOfInterfaces*sizeof(struct ifreq);
            //
            //	ifr = pIfConf->ifc_req;
            //	for (i = 0; i < nNumberOfInterfaces; ++i, ++ifr, ++pIfaceInfo)
            //	{
            //		memset(ifr, 0, sizeof(struct ifreq));
            //
            //		ifr->ifr_flags = (short int)pIfaceInfo->iiFlags;
            //		//ifr->ifr_ifru.ifru_addr = pIfaceInfo->iiAddress.Address;
            //		//ifr->ifr_ifru.ifru_dstaddr = pIfaceInfo->iiAddress.Address;
            //
            //		// Get the name of interface
            //		//ifr->ifr_ifrn.ifrn_name[IFNAMSIZ - 1] = (unsigned char)pIfaceInfo->iiFlags;
            //
            //		if (pIfaceInfo->iiFlags&IFF_UP)
            //		{
            //			ifr->ifr_ifru.ifru_addr = pIfaceInfo->iiAddress.Address;
            //		}
            //		else if (pIfaceInfo->iiFlags&IFF_BROADCAST){ ifr->ifr_ifru.ifru_broadaddr = pIfaceInfo->iiBroadcastAddress.Address; }
            //		else if (pIfaceInfo->iiFlags&IFF_LOOPBACK){ ifr->ifr_ifru.ifru_dstaddr = pIfaceInfo->iiAddress.Address; }
            //		else if (pIfaceInfo->iiFlags&IFF_POINTTOPOINT){ ifr->ifr_ifru.ifru_hwaddr = pIfaceInfo->iiNetmask.Address; }
            //		else if (pIfaceInfo->iiFlags&IFF_MULTICAST){ ifr->ifr_ifru.ifru_netmask = pIfaceInfo->iiNetmask.Address; }
            //	}
            //	break;
            //case SIOCGIFFLAGS:
            //	ifr = va_arg(*a_arg_list_p, struct ifreq*);
            //	//pIfaceInfo = (INTERFACE_INFO*)((void*)ifr->winInfo2);
            //	//ifr->ifr_flags = (short int)pIfaceInfo->iiFlags;
            //	break;
        case FIONBIO:  // pnNonBlocking
            pnNonBlocking = va_arg(*a_arg_list_p, int*);
            ulnNonBlocking = *pnNonBlocking;
            nReturn = ioctlsocket((SOCKET)a_d, FIONBIO, &ulnNonBlocking);
            break;
        default:
            pLstArg = va_arg(*a_arg_list_p, void*);
            nReturn = ioctlsocket((SOCKET)a_d, (long)a_request, pLstArg);
            break;
        }
    }
    else if (nIsSocket == 0)
    {
        switch (a_request)
        {
        case 0:
            break;
        default:
            pLstArg = va_arg(*a_arg_list_p, void*);
            nReturn = (int)DeviceIoControl((HANDLE)_get_osfhandle(a_d), a_request, pLstArg, 0, pLstArg, 0, &dwReturned, NULL);
            break;
        }
    }

    return nReturn;
}


WLAC4_END_C
