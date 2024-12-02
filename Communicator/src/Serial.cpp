#include "Serial.h"
#include "../../Logger/src/Log.h"

std::string* Communicator::Serial::SendCommandAndReceiveResponse(int& timeout, const std::string& command) {
    boost::asio::io_service io_service;
    boost::asio::serial_port serial(io_service, Serial::Comport);
    std::string* response=nullptr;
    // Set serial port options
    serial.set_option(boost::asio::serial_port_base::baud_rate(Serial::BaudRate));
    serial.set_option(boost::asio::serial_port_base::character_size(Serial::DataBits));
    serial.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
    serial.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
    serial.set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));

    try {
        // Send the command
        boost::asio::write(serial, boost::asio::buffer(command));

        // Create a buffer to read the response
        std::vector<char> buffer(256);
        

        // Set up a deadline timer for the timeout
        boost::asio::deadline_timer timer(io_service);
        timer.expires_from_now(boost::posix_time::seconds(timeout));
        timer.wait(); // Wait for the timeout duration

        // Attempt to read the response
        boost::system::error_code error;
        size_t bytes_read = serial.read_some(boost::asio::buffer(buffer), error);
        std::string cpyResp;
        if (bytes_read > 0) {
            cpyResp.append(buffer.data(), bytes_read);
        }

        response = &cpyResp;

        // Handle any errors
        if (error && error != boost::asio::error::eof) {
            throw boost::system::system_error(error);
        }

       
    }
    catch (const boost::system::system_error& e) {
        // Log the error and return an empty response
        Log::Error("Error in Serial communication", &e);        
    }
    return response;
}







