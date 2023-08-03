#ifndef	WEBSERV_HPP
# define	WEBSERV_HPP

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <unistd.h>

#include <cerrno>
#include <cstdlib>

#include <string.h>
#include <poll.h>
#include <sys/select.h>

#include <iostream>


class	Webserv
{
	private:
		int			__socketfd;
		sockaddr_in	__sockaddr;
		int			__sockaddr_len;
		int			__accepted_socket_fd;   // new socket
	public:
	//	Cannonical
		Webserv(void);
		Webserv(const Webserv& other);
		Webserv&	operator=(const Webserv& other);
		~Webserv();

		int		getSocketFd(void);
		int		setupTheServer(void);
		int 	acceptConnection(int socketfd);
		void	handleRequest(int socketfd);
		void	respondRequest(int socketfd);  //

	//Exceptions 	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	class	FailedAtAcceptingConnection: public std::exception
	{
	public:
		virtual const char	*what() const throw();			
	};

	class	FailedAtListening: public std::exception
	{
	public:
		virtual const char	*what() const throw();			
	};

	class	FailedToCreateASocket: public std::exception
	{
	public:
		virtual const char	*what() const throw();			
	};

	class	BindingToTheSocketFailed: public std::exception
	{
	public:
		virtual const char	*what() const throw();			
	};
};

//Colors	===========================
# define	BLANK "\033[0m"
# define	RED	"\033[0;31m"
# define	GREEN "\033[0;32m"
# define	YELL "\033[0;33m"
# define	CYAN "\033[0;36m"

#endif