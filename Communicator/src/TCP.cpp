#include "TCP.h"


std::string  Communicator::TCP::SendCommandAndReceiveResponse(int& timeout, const std::string& command) {
    boost::asio::io_service io_service;

    // Create a TCP socket object
    boost::asio::ip::tcp::socket socket(io_service);
    // Create the endpoint (address and port)
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(Communicator::TCP::Ip), Communicator::TCP::Port);
    std::string response;
    try {
        // Connect the socket to the remote endpoint
        socket.connect(endpoint);

        // Send the command to the server
        boost::asio::write(socket, boost::asio::buffer(command));

        // Set up a buffer for receiving data
        std::vector<char> buffer(256);  // Adjust the buffer size as needed


        // Set up timeout using a simple timer
        auto start_time = std::chrono::steady_clock::now();

        // Loop to read data from the socket until timeout
        while (true) {
            // Check if the timeout is exceeded
            auto elapsed = std::chrono::steady_clock::now() - start_time;
            if (std::chrono::duration_cast<std::chrono::seconds>(elapsed).count() > timeout) {
                throw std::runtime_error("Timeout reached while waiting for response.");
            }

            // Read available data from the socket
            size_t bytes_read = socket.read_some(boost::asio::buffer(buffer));

            if (bytes_read > 0) {
                response.append(buffer.data(), bytes_read);
            }

            // Optionally, break if you receive a specific terminator (e.g., newline)
            // if (bytes_read > 0 && buffer[bytes_read - 1] == '\n') {
            //     break;
            // }

            // Sleep for a short period to avoid busy waiting
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        socket.close();  // Close the socket after communication
    }
    catch (const boost::system::system_error& e) {
        std::cerr << "Error in TCP communication: " << e.what() << std::endl;
        return "";
    }

    return response;
}