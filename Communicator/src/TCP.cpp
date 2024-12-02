#include "TCP.h"
#include "../../Logger/src/Log.h"

std::string* Communicator::TCP::SendCommandAndReceiveResponse(int& timeout, const std::string& command) {
    std::string* _response=nullptr;
    try {
        boost::asio::io_context io;

        // Define the server and port
        boost::asio::ip::tcp::resolver resolver(io);
        boost::asio::ip::tcp::socket socket(io);

        auto endpoints = resolver.resolve(TCP::Ip,std::to_string( TCP::Port)); // Replace with your server and port
        boost::asio::connect(socket, endpoints);

        
        std::string request = command;
        boost::asio::write(socket, boost::asio::buffer(request));

        
        char response[1024];
        size_t length = socket.read_some(boost::asio::buffer(response));        
        std::string cpyResp;
        cpyResp = std::string(response, length);
        _response = &cpyResp;
        socket.close();
    }
    catch (const std::exception& e) {        
        Log::Error("Error at TCP communication", &e);
    }

    return _response;
}