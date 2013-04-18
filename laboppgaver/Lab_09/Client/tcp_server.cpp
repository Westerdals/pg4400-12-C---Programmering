/**
 * @file: tcp_server.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <18.04.2013>
 *
 * @description: Contains all network functionality to represent a
 *				 server. Maintains a std::vector of tcp_connection.
 *				 One connection for each client.
 *
 *				 Enhancement suggestion: make the connection notify this
 *				 class when an error occurs, so the server can remove the
 *				 connection from the list! Custom callback function perhaps?
 */

#include "tcp_server.h"

/* Constructor, initializes a acceptor objec, listening at the given port. */
tcp_server::tcp_server(boost::asio::io_service& io_service, unsigned short& port)
	: acceptor(io_service, tcp::endpoint(tcp::v4(), port)) // No IP address specified
{
	start_accept(); // Asynchronousely start accept connections.
}

/* Asynchronousely start accept a connection. */
void tcp_server::start_accept()
{
	// Create a new tcp_connection (socket) for any new connection
	tcp_connection::tcp_ptr new_connection =
		tcp_connection::create(acceptor.get_io_service());

	// Wait for a connection to arrive.
	acceptor.async_accept(
		new_connection->getSocket(),
		boost::bind( // Callback function once a connection has been established.
			&tcp_server::handle_accept,
			this,
			new_connection,
			boost::asio::placeholders::error
		)
	);
}

/* Callback function once a connection has been established. */
void tcp_server::handle_accept(tcp_connection::tcp_ptr new_connection,
							   const boost::system::error_code& err)
{
	// Start listening to the connection if no errors occured, add it to
	// the client list.
	if (!err)
	{
		new_connection->startRead();
		clientList.push_back(new_connection);
	}
	else
	{
		new_connection->getSocket().close();
	}

	// Doesn't matter if connection fails or not, we want to support
	// more connections.
	start_accept();
}

/* Writes/transmits the given string asynchronousely to each connected client! */
void tcp_server::write(const std::string& data)
{
	// Loop through the list using iterators.
	for (auto client = clientList.begin(); client != clientList.end();)
	{
		// Sent data to the client if it is open.
		if ((*client)->getSocket().is_open())
		{
			(*client)->write(data);
			++client;
		}
		else
		{
			// We don't care for closed connections. Erase them from the list.
			// the erase function returns the next valid addressable iterator (++).
			client = clientList.erase(client);
		}
	}
}