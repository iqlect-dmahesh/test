#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <arpa/inet.h>

// Custom headers
#include <util.h>

class client {
				public:
								client();
								virtual ~client();

								int    connectTo(unsigned int host, unsigned short port);

				private:
								int      _sockFd;
};

client::client()
{
				_sockFd = -1;
}

client::~client()
{
				if (_sockFd != -1) {
								close (_sockFd);
				}
}

				int
client::connectTo(
								unsigned int host,
								unsigned short port)
{
				_sockFd = socket(AF_INET, SOCK_STREAM, 0);
				if (_sockFd == -1) {
								perror ("socket(...) failed : ");
								return errno;
				}

				struct sockaddr_in serverAddr;
				serverAddr.sin_family = AF_INET;
				serverAddr.sin_port = htons(port);
				serverAddr.sin_addr.s_addr = host;
				#if 0
				if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0) {
					perror ("inet_pton(...) failed : ");
					return errno;
				}
				#endif

				if (connect(_sockFd, (struct sockaddr*)&serverAddr, sizeof(struct sockaddr_in)) == -1) {
								perror ("connect(...) failed : ");
								return errno;
				}

				static const unsigned MAX_READ_SIZE = 1023;
				char recvBuffer[MAX_READ_SIZE + 1] = {0};
				int numRead = read(_sockFd, recvBuffer, MAX_READ_SIZE);
				while (numRead) {
								std::cout << recvBuffer;
								recvBuffer[0] = '\0';
								numRead = read(_sockFd, recvBuffer, MAX_READ_SIZE);
				}
				return 0;
}

				int
main(int args, char *argv[])
{
				if (args != 2) {
								std::cout << "Usage: " << argv[0] << " <server-address>" << std::endl;
								return -1;
				}

				std::string serverAddr(argv[1]);
				struct in_addr sAddr;
				if (inet_pton(AF_INET, serverAddr.c_str(), &sAddr) < 0) {
								perror ("inet_pton(...) failed : ");
								return errno;
				}
				client cObj;
				unsigned short port = 24244;
				cObj.connectTo(sAddr.s_addr, port);
				return 0;
}


