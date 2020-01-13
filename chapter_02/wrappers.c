#include <unistd.h>
#include <errno.h>
#include "wrappers.h"

int readn(int fd, void *buf, size_t count)
{
        int nleft = count, nread;
        char *ptr = buf;

        while (nleft > 0) {
                nread = read(fd, ptr, nleft);
                if (nread < 0) {
                        if (errno != EAGAIN)
                                return -1;
                        nread = 0;
                } else if (nread == 0)
                        break;

                nleft -= nread;
                ptr += nread;
        }

        return count - nleft;
}

int writen(int fd, void *buf, size_t count)
{
        int nleft = count, nwritten;
        char *ptr = buf;

        while (nleft > 0) {
                nwritten = write(fd, ptr, nleft);
                if (nwritten < 0) {
                        if (errno != EAGAIN)
                                return -1;
                        nwritten = 0;
                }

                nleft -= nwritten;
                ptr += nwritten;
        }

        return count - nleft;
}
