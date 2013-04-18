#include <iostream>
#include "tcp_connection.h"
//#include <functional> - std::bind()

tcp_connection::tcp_connection(boost::asio::io_service& io_service)
	: socket(io_service)
{
}

tcp::socket& tcp_connection::getSocket()
{
	return socket;
}

void tcp_connection::write(const std::string& data)
{
	writeBuffer = data + '\n';

	boost::asio::async_write(
		socket,
		boost::asio::buffer(writeBuffer),
		boost::bind(
			&tcp_connection::handle_write,
			this->shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred
		)
	);
}

void tcp_connection::handle_write(const boost::system::error_code& err, size_t bytes_transferred)
{
	/*if (err)
	{
		std::cout << "Failed to send message!" << std::endl;
	}*/
}

void tcp_connection::startRead()
{
	async_read(
		socket,
		boost::asio::buffer(readBuffer),
		boost::bind(
			&tcp_connection::on_read,
			this->shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred
		),
		boost::bind(
			&tcp_connection::read_complete,
			this->shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred
		)
	);
}

size_t tcp_connection::on_read(const boost::system::error_code& err, size_t bytes_read)
{
	if (err) return 0;

	char* newlinePos = std::find(readBuffer, readBuffer + bytes_read, '\n');
	bool found = newlinePos < readBuffer + bytes_read;

	if (found)
	{
		*newlinePos = '\0';
		return 0;
	}

	return 1;
}

void tcp_connection::read_complete(const boost::system::error_code& err, size_t bytes_read)
{
	if (err)
	{
		std::cout << "Failed to read!" << std::endl;
	}
	else
	{
		std::cout << readBuffer << std::endl;

		for (char* it = readBuffer; it != readBuffer + bufferSize; ++it)
		{
			*it = 0;
		}

		startRead();
	}
}