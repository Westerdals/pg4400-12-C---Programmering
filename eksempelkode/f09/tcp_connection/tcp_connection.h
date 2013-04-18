#ifndef TCP_CONNECTION
#define TCP_CONNECTION

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define _WIN32_WINNT 0x0501
#endif

#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

using boost::asio::ip::tcp;

class tcp_connection
	: public boost::enable_shared_from_this<tcp_connection>
{
public:
	typedef boost::shared_ptr<tcp_connection> tcp_ptr;
	static const int bufferSize = 512;

	static tcp_ptr create(boost::asio::io_service& io_service)
	{
		return tcp_ptr(new tcp_connection(io_service));
	}

	tcp::socket& getSocket();

	void write(const std::string& data);
	void startRead();
private:
	tcp_connection(boost::asio::io_service&);
	void handle_write(const boost::system::error_code&, size_t bytes_transferred);
	size_t on_read(const boost::system::error_code&, size_t bytes_read);
	void read_complete(const boost::system::error_code&, size_t bytes_read);

	tcp::socket socket;
	char readBuffer[bufferSize];
	std::string writeBuffer;
};

#endif