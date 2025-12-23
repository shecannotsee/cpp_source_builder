#include <asio.hpp>
#include <iostream>
#include <thread>
#include <atomic>
#include <string>

using asio::ip::tcp;

// 全局客户端 ID 计数器
std::atomic<int> client_counter{0};

void handle_client(tcp::socket socket, int client_id) {
  try {
    std::string client_name = "client-" + std::to_string(client_id);
    std::cout << client_name << " connected: " << socket.remote_endpoint() << std::endl;

    char data[1024];
    for (;;) {
      std::size_t length = socket.read_some(asio::buffer(data));
      std::string msg(data, length);
      std::cout << "[" << client_name << "] says: " << msg << std::endl;
    }
  } catch (std::exception& e) {
    std::cout << "client-" << client_id << " disconnected: " << e.what() << std::endl;
  }
}

int main() {
  try {
    asio::io_context io;

    tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 12345));
    std::cout << "Server listening on port 12345..." << std::endl;

    while (true) {
      tcp::socket socket(io);
      acceptor.accept(socket);

      int client_id = ++client_counter;  // 分配唯一 ID
      std::thread(handle_client, std::move(socket), client_id).detach();
    }

  } catch (std::exception& e) {
    std::cerr << "Server error: " << e.what() << std::endl;
  }
}
