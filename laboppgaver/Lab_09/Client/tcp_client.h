/**
 * @file: tcp_client.h
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <18.04.2013>
 *
 * @description: Contains all network functionality to represent a
 *				 client. Maintains one tcp_connection.
 */

#ifndef TCP_CLIENT
#define TCP_CLIENT

#include "tcp_connection.h"

class tcp_client
{
public:
	/* Constructor. Initializes the endpoint object and prepares a connection to the server. */
	tcp_client(boost::asio::io_service& service, boost::asio::ip::address& ip, unsigned short& port);

	/* Synchronousely attempts to connect to the server. */
	bool connect();

	/* Writes data asynchronousely to the socket. */
	void write(const std::string& data);
private:
	tcp_connection::tcp_ptr connection; // Connection to the server
	boost::asio::ip::tcp::endpoint ep; // Endpoint data
};

#endif TCP_CLIENT