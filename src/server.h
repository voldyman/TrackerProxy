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

#ifndef SERVER_H
#define SERVER_H

#include <memory>

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::udp;

class Server {
  private:
    std::shared_ptr<boost::asio::io_service> io_service;
    udp::socket socket;
    unsigned short port;

  public:
    Server(std::shared_ptr<boost::asio::io_service> service,
           unsigned short port);
    void start();

  private:
    void accept_connection();
    void handle_connection(const boost::system::error_code&, std::size_t,
                           boost::array<char, 1024>, udp::endpoint);

};

#endif
