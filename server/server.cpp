#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include <ctime>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

std::string get_current_time() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    return std::ctime(&now_time);
}

std::string read_file(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("Could not open file: " + path);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void handle_request(http::request<http::string_body>& req, http::response<http::string_body>& res) {
    res.version(req.version());

    if (req.target() == "/") {
        res.result(http::status::ok);
        res.set(http::field::content_type, "text/html");
        res.body() = read_file("/app/frontend/index.html"); 
    }
    else if (req.target() == "/time") {
        res.result(http::status::ok);
        res.set(http::field::content_type, "text/plain");
        res.body() = get_current_time(); 
    }
    else {
        res.result(http::status::not_found);
        res.set(http::field::content_type, "text/plain");
        res.body() = "Not Found";
    }

    res.prepare_payload();
}

int main() {
    try {
        auto const address = net::ip::make_address("0.0.0.0");
        auto const port = static_cast<unsigned short>(8082);

        net::io_context ioc{1};

        tcp::acceptor acceptor{ioc, {address, port}};
        std::cout << "Server is running on http://localhost:" << port << std::endl;

        while (true) {
            tcp::socket socket{ioc};
            acceptor.accept(socket);

            beast::flat_buffer buffer;
            http::request<http::string_body> req;
            http::read(socket, buffer, req);

            http::response<http::string_body> res;
            handle_request(req, res);

            http::write(socket, res);
            socket.shutdown(tcp::socket::shutdown_send);
        }
    } catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}