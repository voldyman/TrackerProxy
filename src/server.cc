/*
  The MIT License (MIT)

  Copyright (c) 2014 Akshay Shekher

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.

*/

#include "server.h"

Server::Server(std::shared_ptr<boost::asio::io_service> service,
               unsigned short port) :
  socket(*service, udp::endpoint(udp::v4(), port))
{
  this->io_service = service;
  this->port = port;

}

void Server::start()
{
  accept_connection();
}

void Server::accept_connection()
{
  boost::array<char, 1024> reciv_buf;
  udp::endpoint endpoint;

  auto callback = boost::bind<void>(&Server::handle_connection, this,
                                    boost::asio::placeholders::error,
                                    boost::asio::placeholders::bytes_transferred,
                                    reciv_buf, endpoint);
  
  this->socket.async_receive_from(boost::asio::buffer(reciv_buf),
                                  endpoint, callback);
}

void Server::handle_connection(const boost::system::error_code& error,
                               std::size_t bytes_read, boost::array<char, 1024> recv_buf,
                               udp::endpoint endpoint)
{
  // continue accepting connections
  this->accept_connection();
    
  std::vector<char> data(std::begin(recv_buf), std::begin(recv_buf) + bytes_read);

  std::cout << "Got Connection with data: " << data[0] << " " << data.size() << std::endl;

  udp::resolver resolver(*this->io_service);
  udp::resolver::query query("tracker.istole.it", "80");

  udp::endpoint server_endpoint;

  try {
    server_endpoint = *resolver.resolve(query);
  } catch(boost::system::system_error& error) {
    std::cout<< error.what() << std::endl;
    return;
  }

  std::cout << "Sending data" << std::endl;
  std::shared_ptr<udp::socket> server_socket = std::make_shared<udp::socket>(udp::socket(*this->io_service));
  server_socket->open(udp::v4());
  server_socket->send_to(boost::asio::buffer(data), server_endpoint);
  std::cout << "Sent, waiting " << std::endl;
  boost::array<char, 128> server_recv_buf;
  udp::endpoint sender_endpoint;
  size_t len = server_socket->receive_from(
    boost::asio::buffer(server_recv_buf), sender_endpoint);

  std::cout << "Length received: " << len << std::endl;

}
