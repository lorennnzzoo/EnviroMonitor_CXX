#include "Serial.h"


std::string Communicator::Serial::SendCommandAndReceiveResponse(int& timeout,const std::string& command) {
    boost::asio::io_service io_service;

    // Create a serial port object
    boost::asio::serial_port serial(io_service, Serial::Comport);

    // Set serial port parameters (e.g., 9600 baud, 8 data bits, no parity, 1 stop bit)
    serial.set_option(boost::asio::serial_port_base::baud_rate(9600));
    serial.set_option(boost::asio::serial_port_base::character_size(8));
    serial.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
    serial.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
    serial.set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));

    // Send the command to the serial port
    boost::asio::write(serial, boost::asio::buffer(command));

    // Set up a buffer for receiving data
    std::vector<char> buffer(256);  // Adjust the buffer size as needed
    std::string response;

    // Set up timeout using a simple timer
    auto start_time = std::chrono::steady_clock::now();

    try {
        // Loop to read data from the serial port until timeout
        while (true) {
            // Check if the timeout is exceeded
            auto elapsed = std::chrono::steady_clock::now() - start_time;
            if (std::chrono::duration_cast<std::chrono::seconds>(elapsed).count() > timeout) {
                throw std::runtime_error("Timeout reached while waiting for response.");
            }

            // Read available data from serial port
            size_t bytes_read = serial.read_some(boost::asio::buffer(buffer));

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
    }
    catch (const boost::system::system_error& e) {
        std::cerr << "Error reading from serial port: " << e.what() << std::endl;
        return "";
    }

    return response;
}






