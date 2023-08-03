
#include "webserv.hpp"

int main(void)
{

	Webserv	Webserv;
	int		server_socket;
	int		client_socket;

	server_socket = Webserv.setupTheServer();
	fd_set	current_sockets, ready_sockets;
	FD_ZERO(&current_sockets);
	FD_SET(server_socket, &current_sockets);
	int	max_socket = server_socket;
	std::cout << "Server socket: " << server_socket << " " << max_socket << std::endl;
	while (true)
	{
		ready_sockets = current_sockets;


		if (select(max_socket + 1, &ready_sockets, NULL, NULL, NULL) < 0)
		{
			std::cerr << "select has failed!" << std::endl;
			exit(EXIT_FAILURE);
		}
		std::cout << max_socket << std::endl;
		for (int i  = 0; i <= max_socket; i++)
		{
			if (FD_ISSET(i, &ready_sockets))
			{

				if (i == server_socket)
				{
					client_socket = Webserv.acceptConnection(server_socket);
					FD_SET(client_socket, &current_sockets);
					if (client_socket > max_socket)
						max_socket = client_socket;
				}
				else
				{
					Webserv.handleRequest(i);
					Webserv.respondRequest(i);		//
					FD_CLR(i, &current_sockets);
				}
			}
		}

	}
	close(server_socket);
	close(client_socket);
	return (0);
}