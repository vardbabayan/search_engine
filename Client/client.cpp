#include <iostream>
#include <boost/asio.hpp>

//using namespace boost::asio;
//using ip::tcp;

int main(int argc, char* argv[]) 
{
	auto const address = boost::asio::ip::make_address("127.0.0.1");
	const int port = 8080;

	boost::asio::io_service io_service;

	// socket creation
	boost::asio::ip::tcp::socket socket(io_service);
	
    // connection
	boost::system::error_code ec;
 	socket.connect(boost::asio::ip::tcp::endpoint(address, port), ec);
	
    if(ec)
    {
        std::cout << ec.message() << std::endl; 
        return 1;
    }

	while(true)
	{
		std::string message;
		std::getline(std::cin, message);
		
		message = message + '\n';

		// request/message from client
		// const string msg = "Hello from Client!\n";
		boost::system::error_code error;
		boost::asio::write(socket, boost::asio::buffer(message), error);
		
		if(error)
		{
			std::cout << "send failed: " << error.message() << std::endl;
		}
		
		// getting response from server
		boost::asio::streambuf receive_buffer;
		boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);
		
		if(error && error != boost::asio::error::eof) 
		{
			std::cout << "receive failed: " << error.message() << std::endl;
		}
		else 
		{
			const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
			std::cout << data << std::endl;
		}

		std::cout << "again\n";
	}
	
    return 0;
}