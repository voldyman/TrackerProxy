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
#include <memory>

#include "server.h"

#define SERVER_PORT 8081

using boost::asio::ip::udp;

int main()
{
  try {
    std::shared_ptr<boost::asio::io_service> io_service;
    io_service = std::make_shared<boost::asio::io_service>();

    Server server = Server(io_service, SERVER_PORT);

    server.start();

    io_service->run();
  } catch(std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
