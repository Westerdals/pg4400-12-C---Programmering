/**
 * @file: NetworkManager.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <17.04.2013>
 *
 * @description: A wrapper class for asynchronous network
 *				 functionality. Can be used to behave as
 *				 both a client and server.
 */

#include <thread>
#include "NetworkManager.h"

/* Constructor initialising the class with endpoint/remote host data. */
NetworkManager::NetworkManager(boost::asio::ip::address& ip, unsigned short& port)
{
	this->ip = ip;
	this->port = port;
	this->isServer = false;
}

/* Deconstructor. Stops io_service if it's running. */
NetworkManager::~NetworkManager()
{
	if (!io_service.stopped())
	{
		io_service.stop();
	}
}

/* Synchronously attempts to connect to endpoint. */
bool NetworkManager::tryConnect()
{
	if (isServer) return false; // makes no sense if already server

	// Initialize a new client object, and attempt to connect
	client = std::make_shared<tcp_client>(io_service, ip, port);

	if (client->connect())
	{
		// Success, start io_service.run() in a separate thread to prevent halt.
		// Should perhaps ideally use a thread pool as thread creation is slow.
		std::thread bt(boost::bind(&boost::asio::io_service::run, &io_service));
		bt.detach();

		return true;
	}

	// Failure, reset client obj.
	client.reset();
	return false;
}

/* Starts server on local machine, can't fail. */
void NetworkManager::startServer()
{
	if (isServer) return;

	server = std::make_shared<tcp_server>(io_service, port);
	isServer = true;
	
	// Start io_service.run() in a separate thread to prevent halt.
	// Should perhaps ideally use a thread pool as thread creation is slow.
	std::thread bt(boost::bind(&boost::asio::io_service::run, &io_service));
	bt.detach();
}

/* Wrapper function to send a data string. String MUST terminate with newline (\n)! */
void NetworkManager::sendData(const std::string& data)
{
	if (isServer && server)
	{
		server->write(data);
	}
	else if (client)
	{
		client->write(data);
	}
}