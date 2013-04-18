/**
 * @file: tcp_connection.h
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <18.04.2013>
 *
 * @description: A class for maintaining a connection to a remote host using a
 *				 Boost.Asio socket object. Contains functions for read/write.
 *
 *				 Inspired and partly fetched from the official Boost.Asio tutorials:
 *				 http://www.boost.org/doc/libs/1_53_0/doc/html/boost_asio/tutorial.html
 */

#ifndef TCP_CONNECTION
#define TCP_CONNECTION

// Boost.Asio requires this for Windows
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define _WIN32_WINNT 0x0501
#endif

#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
//#include <functional> - std::bind() alternative to boost::bind()
#include <boost/enable_shared_from_this.hpp>

using boost::asio::ip::tcp; // Let's make life a bit easier.

// Class inherits from enable_shared_from_this, which makes it easy to create
// a shared_ptr of the object.
class tcp_connection
	: public boost::enable_shared_from_this<tcp_connection>
{
public:
	// Make life easier by typedef-ing our own shared_ptr type.
	typedef boost::shared_ptr<tcp_connection> tcp_ptr;
	static const int bufferSize = 512; // Size of read buffer (input)

	/* Function to create a new tcp_connection object. This should be the
	   only way, as connection must be dynamically allocated in order to stay
	   alive through the asynchronous calls.*/
	static tcp_ptr create(boost::asio::io_service& io_service)
	{
		return tcp_ptr(new tcp_connection(io_service));
	}

	/* Returns the socket object. */
	tcp::socket& getSocket();

	/* Transmits (writes) data to the socket. */
	void write(const std::string& data);

	/* Reads asynchronousely from the socket. */
	void startRead();
private:
	/* Unavailable constructor; initializes the socket object. */
	tcp_connection(boost::asio::io_service&);

	/* Callback function for completed write operation. Treats errors only,
       no need to verify success - TCP guarantees it! */
	void handle_write(const boost::system::error_code&, size_t bytes_transferred);

	/* Callback function that determines when we have reached the end of the incoming
	   message (newline). NB: 0 = done reading | 1 = there's more to read. */
	size_t on_read(const boost::system::error_code&, size_t bytes_read);

	/* Callback function being called once read is complete; on_read returns "positive" (0) */
	void read_complete(const boost::system::error_code&, size_t bytes_read);

	tcp::socket socket; // The actual socket object
	char readBuffer[bufferSize]; // Buffer to store read data
	std::string writeBuffer; // Buffer to store data to write (string)
};

#endif