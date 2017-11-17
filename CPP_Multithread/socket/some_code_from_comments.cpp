// g++ -std=c++11
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>


class SocketTcpIp {
 public:
  SocketTcpIp()
      : socket_id_(socket(AF_INET, SOCK_STREAM, 0)) {
    if (socket_id_ < 0) {
      throw std::runtime_error("Socket was not created, error number: " +
                               std::to_string(errno));
    }
  }

  SocketTcpIp(int socket_id)
      : socket_id_(socket_id) {}

  SocketTcpIp(const SocketTcpIp&) = delete;

  SocketTcpIp(SocketTcpIp&& other)
      : socket_id_(other.socket_id_) {
    other.socket_id_ = -1;
  }

  ~SocketTcpIp() {
    if (socket_id_ >= 0) {
      close(socket_id_);
    }
  }

  SocketTcpIp& operator=(const SocketTcpIp&) = delete;

  SocketTcpIp& operator=(SocketTcpIp&&) = delete;

  int Id() const noexcept {
    return socket_id_;
  }

 private:
  int socket_id_;
};


class ConnectionServer {
 public:
  static constexpr size_t kBufferSize = 256;

  ConnectionServer(uint16_t port, uint32_t address)
      : socket_(), port_(port), address_(address) {
    int set = 1;
    setsockopt(socket_.Id(), SOL_SOCKET, SO_REUSEADDR, &set, sizeof(set));

    sockaddr_in sock_addr;
    std::memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port_);
    sock_addr.sin_addr.s_addr = htonl(address);

    if (bind(socket_.Id(), (sockaddr*) &sock_addr, sizeof(sock_addr)) < 0) {
      throw std::runtime_error("Bind failed, error number: " +
                               std::to_string(errno));
    }

    if (listen(socket_.Id(), SOMAXCONN) < 0) {
      throw std::runtime_error("Listen failed, error number: " +
                               std::to_string(errno));
    }
  }

  ~ConnectionServer() {
    for (const auto& item : slave_sockets_) {
      shutdown(item.second.Id(), SHUT_RDWR);
    }
  }

  int Accept() {
    int client_id = accept(socket_.Id(), nullptr, nullptr);

    if (client_id < 0) {
      throw std::runtime_error("Accept failed, error number: " +
                               std::to_string(errno));
    }

    slave_sockets_.emplace(
        client_id, std::move(SocketTcpIp(client_id)));
    return client_id;
  }

  void Shutdown(int client_id) {
    if (shutdown(slave_sockets_[client_id].Id(), SHUT_RDWR) < 0) {
      throw std::runtime_error("Shutdown failed, error number: " +
                               std::to_string(errno));
    }

    slave_sockets_.erase(client_id);
  }

  std::string Receive(int client_id) const {
    char buffer[kBufferSize];

    ssize_t msg_size = recv(slave_sockets_.at(client_id).Id(), buffer,
                            sizeof(buffer), MSG_NOSIGNAL);

    if (msg_size < 0) {
      throw std::runtime_error("Receive failed, error number: " +
                               std::to_string(errno));
    }

    return std::string(buffer, static_cast<size_t>(msg_size));
  }

  void Send(int client_id, const std::string& message) const {
    if (send(slave_sockets_.at(client_id).Id(), message.data(),
             message.size(), MSG_NOSIGNAL) < 0) {
      throw std::runtime_error("Send failed, error number: " +
                               std::to_string(errno));
    }
  }

 private:
  SocketTcpIp socket_;
  uint16_t port_;
  uint32_t address_;
  std::map<int, SocketTcpIp> slave_sockets_;
};


int main() {
  ConnectionServer server(12345, INADDR_ANY);
  std::string msg;
  while (msg.substr(0, 4) != "exit") {
    int client_id = server.Accept();
    msg = server.Receive(client_id);
    std::cout << msg << std::flush;
    server.Send(client_id, msg);
    server.Shutdown(client_id);
  }

  return 0;
}
