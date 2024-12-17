#include "TCP.h"
#include "../../Logger/src/Log.h"

std::string* Communicator::TCP::SendCommandAndReceiveResponse(int& timeout, const std::string& command) {
    std::string* _response=nullptr;
    try {

        // Create an ASIO I/O context
        asio::io_context io_context;

        // Resolve the server address and port
        asio::ip::tcp::resolver resolver(io_context);
        asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(TCP::Ip,std::to_string(TCP::Port));

        // Create and connect the socket
        asio::ip::tcp::socket socket(io_context);
        asio::connect(socket, endpoints);

        // Send the command
        asio::write(socket, asio::buffer(command));

        // Receive the response
        char response[1024] = { 0 }; // Buffer for the response
        size_t length = socket.read_some(asio::buffer(response));
        std::string cpyResponse= std::string(response, length);
        _response = &cpyResponse;
        socket.close();
    }
    catch (const std::exception& e) {
        Log::Error("Error at TCP communication", &e);
    }
    return _response;
}