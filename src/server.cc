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
  this->socket.async_receive_from(boost::asio::buffer(this->recv_buf),
                                  this->remote_endpoint,
                                  boost::bind<void>(&Server::handle_connection, this,
                                                    boost::asio::placeholders::error,
                                                    boost::asio::placeholders::bytes_transferred));
}

void Server::handle_connection(const boost::system::error_code& error,
                               std::size_t bytes_read)
{
  std::string data;
  std::copy(this->recv_buf.begin(), this->recv_buf.begin() + bytes_read,
            std::back_inserter(data));
  
  std::cout << "Got Connection with data: " << data << std::endl;

  // continue accepting connections
  this->accept_connection();
}
