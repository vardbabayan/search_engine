//simple tcp socket server example with boost asio
//sudo apt install libboost-dev
//g++ -lpthread -lboost_system server.cpp -o server

#include <iostream>
#include <boost/asio.hpp>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

//using namespace boost::asio
//using ip::tcp

std::string host = "tcp://127.0.0.1:3306";
std::string name = "user";
std::string passwd = "password";
std::string dbname = "db_crawler";

void search(const std::string& text)
{
    std::vector<std::pair<std::string, std::string> > results;

    sql::Driver *driver;
    sql::Connection *connection;

    driver = get_driver_instance();
    connection = driver->connect("tcp://127.0.0.1:3306", name, passwd);
    connection->setSchema(dbname);

    auto pstmt = connection->prepareStatement("SELECT * from Documents WHERE MATCH(description, text) AGAINST ((?) in NATURAL LANGUAGE MODE)");
    std::string textSearch = "'%" + text + "%'";
    pstmt->setString(1, textSearch);

    auto result = pstmt->executeQuery();

    for(unsigned i = 0; i < 10; ++i)
    {
        if(!result->next())
        {
            break;
        }

        std::string url = result->getString("url").asStdString();
        std::string title = result->getString("description").asStdString();
        
        std::cout << url << " " << title << "\n";
        results.push_back(std::make_pair(url, title));
    }

    driver->threadEnd();
    connection->close();

    delete connection;
}

int main(int argc, char* argv[]) 
{
    auto const address = boost::asio::ip::make_address("127.0.0.1");
	const int port = 8080;

	boost::asio::io_service io_service;

	// listen for new connection
	boost::system::error_code ec;
	
    boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(address, port)); 
	
    // socket creation
    boost::asio::ip::tcp::socket socket(io_service); 	
	
    // waiting for connection
    acceptor.accept(socket);
    
    while(true) 
    {
        // read operation
        boost::asio::streambuf buf;
        boost::asio::read_until(socket, buf, "\n",ec);
        
        if(ec)
        {
            std::cout << ec.message() << std::endl; 
            return 1;
        }

        std::string data = boost::asio::buffer_cast<const char*>(buf.data());
        
        std::cout << "received data: " << data << std::endl;

        search(data);
        
        //write operation
        boost::asio::write(socket, boost::asio::buffer("response from server\n"), ec);
        if(ec)
        {
            std::cout << ec.message() << std::endl; 
            return 1;
        }
    }
    
	return 0;
}