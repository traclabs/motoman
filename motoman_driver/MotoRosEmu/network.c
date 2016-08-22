
#include <mprtl/network.h>

#include <unistd.h>



// Network API /////////////////////////////////////////////////////////////////


LONG mpSocket(LONG domain, LONG type, LONG protocol)
{
  return socket(domain, type, protocol);
}


LONG mpListen(LONG sockfd, LONG backlog)
{
  return listen(sockfd, backlog);
}


LONG mpAccept(LONG sockfd, struct sockaddr *addr, LONG *addrlen)
{
  return accept(sockfd, addr, (size_t*)addrlen);
}


LONG mpBind(LONG sockfd, const struct sockaddr *addr, LONG addrlen)
{
  return bind(sockfd, addr, addrlen);
}


LONG mpConnect(LONG sockfd, const struct sockaddr *addr, LONG addrlen)
{
  return connect(sockfd, addr, addrlen);
}


LONG mpRecv(LONG sockfd, const void *buf, LONG len, LONG flags)
{
  return recv(sockfd, (void*)buf, len, flags);
}


LONG mpRecvFrom(LONG sockfd, const void *buf, LONG len, LONG flags, struct sockaddr *src_addr, LONG *addrlen)
{
  return recvfrom(sockfd, (void*)buf, len, flags, src_addr, (size_t*)addrlen);
}


LONG mpSend(LONG sockfd, const void *buf, LONG len, LONG flags)
{
  return send(sockfd, (void*)buf, len, flags);
}


LONG mpSendTo(LONG sockfd, const void *buf, size_t len, LONG flags, const struct sockaddr *dest_addr, LONG addrlen)
{
  return sendto(sockfd, (void*)buf, len, flags, dest_addr, addrlen);
}


LONG mpClose(LONG fd)
{
  return close(fd);
}


STATUS mpSetsockopt(int sockfd, int level, int optname, char * optval, int optlen)
{
  return setsockopt(sockfd, level, optname, optval, optlen);
}


int mpSelect(int width, fd_set * pReadFds, fd_set * pWriteFds, fd_set * pExceptFds, struct timeval * pTimeOut)
{
  return select(width, pReadFds, pWriteFds, pExceptFds, pTimeOut);
}


USHORT mpHtons(USHORT hostshort)
{
  return htons(hostshort);
}
