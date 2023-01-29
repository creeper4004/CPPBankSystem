#include <boost/asio.hpp>
#include <boost/asio/completion_condition.hpp>
#include <string>
#include <iostream>

using namespace std;
using namespace boost::asio;

class Application 
{
public:
  Application(const string& address, const string& port): 
    ioservice(), socket(ioservice), endpoint(ip::address::from_string(address), stoi(port))
  {
  }

  int run() 
  {
    try 
    {
      // Connect to the server
      socket.connect(endpoint);

      // Receive the message from the server
      string message;
      boost::system::error_code error;
      boost::asio::streambuf buffer;
      size_t bytes_transferred = read(socket, buffer, boost::asio::transfer_all(), error);

      if (bytes_transferred > 0) 
        message = boost::asio::buffer_cast<const char*>(buffer.data());
      else 
        cout << "No message received" << endl;

      cout << message << endl;
    } 
    catch (const boost::system::system_error& ex) 
    {
      cout << "ERROR: " << ex.what() << endl;
      return -1;
    }
    return 0;
  }

private:
  io_service ioservice;
  ip::tcp::socket socket;
  ip::tcp::endpoint endpoint;
};

int main()
{
  Application app("127.0.0.1", "9001");
  return app.run();
}

