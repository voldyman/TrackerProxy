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

#include <iostream>

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>

#define SERVER_PORT 8081

using boost::asio::ip::udp;

int main()
{
  try {
    boost::asio::io_service io_service;
    udp::socket socket(io_service, udp::endpoint(udp::v4(), SERVER_PORT));


    boost::array<char, 1024> recv_buf;
    udp::endpoint remote_endpoint;
    boost::system::error_code error;

    socket.async_receive_from(boost::asio::buffer(recv_buf), remote_endpoint,
                              boost::bind<void>([](const boost::system::error_code& error, std::size_t b) {
                                  std::cout <<"recv "<<std::endl;

                                },
                                boost::asio::placeholders::error,
                                boost::asio::placeholders::bytes_transferred));
    io_service.run();
  } catch(std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
