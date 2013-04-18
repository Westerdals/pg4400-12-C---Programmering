/**
 * @file: tcp_connection.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <18.04.2013>
 *
 * @description: A class for maintaining a connection to a remote host using a
 *				 Boost.Asio socket object. Contains functions for read/write.
 *
 *				 Inspired and partly fetched from the official Boost.Asio tutorials:
 *				 http://www.boost.org/doc/libs/1_53_0/doc/html/boost_asio/tutorial.html
 */

#include <iostream>
#include "tcp_connection.h"

/* Constructor; initializes the socket object. */
tcp_connection::tcp_connection(boost::asio::io_service& io_service)
	: socket(io_service)
{
}

/* Returns the socket object. */
tcp::socket& tcp_connection::getSocket()
{
	return socket;
}

/* Transmits (writes) data to the socket. */
void tcp_connection::write(const std::string& data)
{
	// Add a newline as the remote host expects the data stream to end with it.
	writeBuffer = data + '\n';

	// Write the data asynchronousely to the socket
	boost::asio::async_write(
		socket,
		boost::asio::buffer(writeBuffer), // Make the buffer applicable for boost.asio
		boost::bind( // callback function (functor)
			&tcp_connection::handle_write,
			this->shared_from_this(), // pointer to this object
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred
		)
	);
}

/* Callback function for completed write operation. Treats errors only,
   no need to verify success - TCP guarantees it! */
void tcp_connection::handle_write(const boost::system::error_code& err, size_t bytes_transferred)
{
	if (err)
	{
		std::cout << "Failed to send message!" << std::endl;
		
		// Check the type of error
		if (err.value() == boost::asio::error::connection_reset)
		{
			std::cout << "Connection to remote host was lost." << std::endl;
		}
		else
		{
			std::cout << "#" << err.value() << ": " << err.message() << std::endl;
		}

		socket.close();
	}
}

/* Reads asynchronousely from the socket.  */
void tcp_connection::startRead()
{
	async_read(
		socket,
		boost::asio::buffer(readBuffer), // Make the buffer applicable for boost.asio
		// This function (functor) determines when we have reached the end of the
		// incoming message (newline).
		boost::bind(
			&tcp_connection::on_read,
			this->shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred
		),
		// This callback function is called once read is complete; the previous
		// binded function returns "positive" (0).
		boost::bind(
			&tcp_connection::read_complete,
			this->shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred
		)
	);
}

/* Callback function that determines when we have reached the end of the incoming message (newline). 
   NB: 0 = done reading | 1 = there's more to read. */
size_t tcp_connection::on_read(const boost::system::error_code& err, size_t bytes_read)
{
	if (err) return 0; // we're done if an error has occured

	// Look for a newline in the readbuffer
	char* newlinePos = std::find(readBuffer, readBuffer + bytes_read, '\n');
	bool found = newlinePos < (readBuffer + bytes_read); // Did we find one?

	if (found)
	{
		*newlinePos = '\0';
		return 0;
	}

	return 1;
}

/* Callback function being called once read is complete; on_read returns "positive" (0) */
void tcp_connection::read_complete(const boost::system::error_code& err, size_t bytes_read)
{
	// Check for errors
	if (err)
	{
		std::cout << "Failed to read data." << std::endl;
		
		// Check the error type
		if (err.value() == boost::asio::error::connection_reset)
		{
			std::cout << "Connection to remote host was lost." << std::endl;
		}
		else
		{
			std::cout << "#" << err.value() << ": " << err.message() << std::endl;
		}

		socket.close();
	}
	else
	{
		// Output the recieved message
		std::cout << readBuffer << std::endl;

		// Clear the readBuffer, set it to zero.
		for (char* it = readBuffer; it != readBuffer + bufferSize; ++it)
		{
			*it = 0;
		}

		startRead(); // Start listening for new incoming data immediately!
	}
}