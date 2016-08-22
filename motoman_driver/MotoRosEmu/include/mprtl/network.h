#ifndef FAKE_MOTOPLUS_NETWORK_H__
#define FAKE_MOTOPLUS_NETWORK_H__


#include "mptypes.h"

#include <sys/select.h> // select etc

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>


// Network API /////////////////////////////////////////////////////////////////

LONG mpSocket(LONG domain, LONG type, LONG protocol);
LONG mpListen(LONG sockfd, LONG backlog);
LONG mpAccept(LONG sockfd, struct sockaddr *addr, LONG *addrlen);
LONG mpBind(LONG sockfd, const struct sockaddr *addr, LONG addrlen);
LONG mpConnect(LONG sockfd, const struct sockaddr *addr, LONG addrlen);
LONG mpRecv(LONG sockfd, const void *buf, LONG len, LONG flags);
LONG mpRecvFrom(LONG sockfd, const void *buf, LONG len, LONG flags, struct sockaddr *src_addr, LONG *addrlen);
LONG mpSend(LONG sockfd, const void *buf, LONG len, LONG flags);
LONG mpSendTo(LONG sockfd, const void *buf, size_t len, LONG flags, const struct sockaddr *dest_addr, LONG addrlen);
LONG mpClose(LONG fd);
USHORT mpHtons(USHORT hostshort);

STATUS mpSetsockopt(int sockfd, int level, int optname, char * optval, int optlen);
int mpSelect(int width, fd_set * pReadFds, fd_set * pWriteFds, fd_set * pExceptFds, struct timeval * pTimeOut);


#endif // FAKE_MOTOPLUS_NETWORK_H__
