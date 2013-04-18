/**
 * @file: tcp_client.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <18.04.2013>
 *
 * @description: Contains all network functionality to represent a
 *				 client. Maintains one tcp_connection.
 */

#include "tcp_client.h"

/* Constructor. Initializes the endpoint object and prepares a connection to the server. */
tcp_client::tcp_client(boost::asio::io_service& service, boost::asio::ip::address& ip, unsigned short& port)
	: ep(ip, port)
{
	connection = tcp_connection::create(service);
}

/* Synchronousely attempts to connect to the server. */
bool tcp_client::connect()
{
	// Synchronous functions throws exceptions on errors, unless you pass
	// it a pointer to an error_code object; example ...connect(ep, &err).
	try
	{
		// Attempt to connect, and start listening if success.
		connection->getSocket().connect(ep);
		connection->startRead();

		return true;
	}
	catch (const std::exception&)
	{
		return false; // Connection failed.
	}
}

/* Writes data asynchronousely to the socket. */
void tcp_client::write(const std::string& data)
{
	connection->write(data);
}