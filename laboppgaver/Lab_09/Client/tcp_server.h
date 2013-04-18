#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <vector>
#include "tcp_connection.h"

class tcp_server
{
public:
	tcp_server(boost::asio::io_service&, unsigned short& port);
	void write(const std::string& data);
private:
	void start_accept();
	void handle_accept(tcp_connection::tcp_ptr, const boost::system::error_code&);

	tcp::acceptor acceptor;
	std::vector<tcp_connection::tcp_ptr> clientList;
};

#endif