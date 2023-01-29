#include <iostream>
#include <string>
#include <boost/asio.hpp>

#include "../common/ClientInfo.hpp"

using namespace std;
using namespace boost::asio;

class Database
{
public:
  virtual void connect() = 0;
  virtual void query(const string&) = 0;
private:
};


class Bank : Database
{
public:
  Bank(const string& address, const string& port): 
    acceptor(service, ip::tcp::endpoint(ip::address::from_string(address),
    stoi(port)))
  {
  }
  void connect() override 
  {
    // connect to database implementation
  }

  void query(const string& query) override 
  {
    // perform database query implementation
  }

  void start_server()
  {
    for (;;)
    {
      ip::tcp::socket client_socket(service);

      acceptor.accept(client_socket);

      string request = read_request(client_socket);
      string response = process_request(request);

      write_response(client_socket, response);
    }
  }


private:
  // Create an io_service object
  io_service service;
  // Create an acceptor object
  ip::tcp::acceptor acceptor;

  //ip::tcp::socket client_socket(io_service);
  
  string read_request(ip::tcp::socket& socket) 
  {
    // read request from socket
    return "";
  }

  string process_request(const string& request) 
  {
    // process request and return response
    string message = "Welcome To The BankSystem";
    return message;
  }

  void write_response(ip::tcp::socket& socket, const string& response) 
  {
    // Send a message to the client
    boost::asio::write(socket, boost::asio::buffer(response));
    // write response to socket
  }
};



int main(int argc, char* argv[]) 
{
    Bank bank("127.0.0.1", "9001");
    bank.connect();
    bank.start_server();

    return 0;
}

