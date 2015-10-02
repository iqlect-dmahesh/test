#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <arpa/inet.h>

// Custom headers
#include <util.h>

class server {
				public:
								server(unsigned host, unsigned port);
								virtual ~server();

								int    start();
								bool   isActive() const {
												return (_sockFd != -1);
								};

				private:
								void   invalidate();

								int             _sockFd;
								unsigned int    _host;
								unsigned short  _port;
};

server::server(
								unsigned host,
								unsigned port) :
				_host(host), _port(port)
{
				FFL;
}

server::~server()
{
				invalidate();
				FFL;
}

				void
server::invalidate()
{
				if (isActive()) {
								close (_sockFd);
				}
				_sockFd = -1;
}

				int
server::start()
{
				_sockFd = socket(AF_INET, SOCK_STREAM, 0);
				if (_sockFd == -1) {
								perror ("socket(...) failed : ");
								return errno;
				}

				struct sockaddr_in serverAddr;
				memset(&serverAddr, 0, sizeof(struct sockaddr_in));
				serverAddr.sin_family = AF_INET;
				serverAddr.sin_addr.s_addr = htonl(_host);
				serverAddr.sin_port = htons(_port);

				if ((bind(_sockFd, (struct sockaddr*) &serverAddr, sizeof(struct sockaddr_in))) == -1) {
								perror ("bind(...) failed : ");
								return errno;
				}

				if ((listen(_sockFd, 1024)) == -1) {
								perror ("listen(...) failed : ");
								return errno;
				}

				for (;;) {
								int connFd = accept(_sockFd, (struct sockaddr*)NULL, (socklen_t *)NULL);
								if (connFd == -1) {
												std::cerr << "Failed to accept connection" << std::endl;
												continue;
								}

								time_t ticks = time(NULL);
								std::string time(ctime(&ticks));
								write(connFd, time.c_str(), time.length());
								close (connFd);
				}
}

				int
main ()
{
				server sObj(INADDR_ANY, 24244);
				sObj.start();
				return 0;
}



