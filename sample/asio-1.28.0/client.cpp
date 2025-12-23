#include <asio.hpp>
#include <iostream>
#include <thread>

using asio::ip::tcp;

int main() {
  try {
    asio::io_context io;
    tcp::socket socket(io);
    socket.connect(tcp::endpoint(asio::ip::address::from_string("127.0.0.1"), 12345));
    std::cout << "Connected to server!" << std::endl;

    std::string message;
    while (std::getline(std::cin, message)) {
      if (message == "exit") break;
      asio::write(socket, asio::buffer(message));
    }

  } catch (std::exception& e) {
    std::cerr << "Client error: " << e.what() << std::endl;
  }
}
