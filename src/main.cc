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
