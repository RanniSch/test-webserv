#include	"webserv.hpp"

Webserv::Webserv(void)
{

}

Webserv::~Webserv(void)
{
	close(__accepted_socket_fd);
	close(__socketfd);
}

int	Webserv::setupTheServer()
{
	std::cout << GREEN << "###	Server is being created!	===========" << std::endl;
	__socketfd = socket(AF_INET, SOCK_STREAM, 0); // __socketfd -> is a socket descriptor, an integer (like a file-handle)

	if (__socketfd == -1)
		throw	FailedToCreateASocket();
	std::cout << GREEN "[SUCCESS]: " BLANK << "Socket fd: " << __socketfd << std::endl;

	memset(&__sockaddr, 0, sizeof(__sockaddr)); // This has to be replaced by our own libft memset function.
	__sockaddr.sin_family = AF_INET;
	__sockaddr.sin_port = htons(8000);
	__sockaddr.sin_addr.s_addr = INADDR_ANY;
	if (bind(__socketfd, (struct sockaddr*)&__sockaddr, sizeof(__sockaddr)) < 0)
		throw	BindingToTheSocketFailed();
	std::cout << GREEN "[SUCCESS]: " BLANK << "Binding worked!" << std::endl;
	if (listen(__socketfd, 10) < 0)
		throw	FailedAtListening();
	std::cout << GREEN "[SUCCESS]: " BLANK << "At listening!" << std::endl;
	return (__socketfd);
}

int	Webserv::acceptConnection(int socketfd)
{
	__sockaddr_len = sizeof(sockaddr);
	__accepted_socket_fd =  accept(socketfd, (struct sockaddr*)&__sockaddr, (socklen_t*)&__sockaddr_len);
	if (__accepted_socket_fd < 0)
		throw FailedAtAcceptingConnection();
	return (__accepted_socket_fd);
}

int		Webserv::getSocketFd(void)
{
	return (__socketfd);
}

void	Webserv::handleRequest(int accepted_socketfd)
{
	int bytesReceived;
	char	buffer[100] = {0};

	std::string	httpRequest;
	while (1)
	{
		bytesReceived = read(accepted_socketfd, buffer, 99);
		buffer[bytesReceived] = '\0';
    	httpRequest += buffer;
		//std::cout << GREEN << buffer << BLANK << std::endl;
		if (httpRequest.find("\r\n\r\n") != std::string::npos)
           break;
	}
	std::cout << "Hello new connection: " << accepted_socketfd << std::endl;
	std::cout << httpRequest << std::endl;
	int rc = send(accepted_socketfd, httpRequest.c_str(), httpRequest.size(), 0);
	std::cout << "======================================" << std::endl;
}

void	Webserv::respondRequest(int	accepted_socketfd)
{
	void hello (char* str);
	hello((char *)"<html><body><h1>Hello World!</h1></body></html>");
	write(accepted_socketfd, hello, strlen(hello));
	close(accepted_socketfd);
}

const char	*Webserv::FailedAtAcceptingConnection::what() const throw()
{
	return ("ERROR: Failed at accepting connection");
}

const char	*Webserv::FailedAtListening::what() const throw()
{
	return ("ERROR: Failed at listening for the socket");
}

const char	*Webserv::FailedToCreateASocket::what() const throw()
{
	return ("ERROR: Failed to create a socket");
}

const char	*Webserv::BindingToTheSocketFailed::what() const throw()
{
	return ("ERROR: Binding to the socket has failed");
}

