/**
 * @file: NetworkManager.h
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <17.04.2013>
 *
 * @description: A wrapper class for asynchronous network
 *				 functionality. Can be used to behave as
 *				 both a client and server.
 */

#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "tcp_client.h"
#include "tcp_server.h"

class NetworkManager
{
public:
	/* Constructor initialising the class with endpoint/remote host data. */
	NetworkManager(boost::asio::ip::address&, unsigned short&);

	/* Deconstructor. Stops io_service if it's running. */
	~NetworkManager();

	/* Synchronously attempts to connect to endpoint. */
	bool tryConnect();

	/* Starts server on local machine, can't fail. */
	void startServer();

	/* Wrapper function to send a data string. String MUST terminate with newline (\n)! */
	void sendData(const std::string& data);
private:
	boost::asio::io_service io_service; // Boost.Asio's "global" yet incredible important io object
	boost::asio::ip::address ip;
	unsigned short port;
	bool isServer;

	std::shared_ptr<tcp_client> client;
	std::shared_ptr<tcp_server> server;
};

#endif