#include "kneeboard.h"

#include <asio.hpp>
#include <algorithm>
#include <optional>

const u_short PORT = 45931;
const std::string messageIdSend = "DCS_KNBRD19283_PC";
const std::string messageIdRecv = "DCS_KNBRD19283_PH";

asio::io_context io;
std::optional<asio::ip::udp::socket> sock;
std::optional<asio::ip::udp::endpoint> app;

void _send_packet(asio::ip::udp::endpoint endpoint, std::string message) {
    if (!sock) return;

    std::array<char, 1024> buffer {};
    std::copy(message.begin(), message.end(), buffer.begin());
    sock.value().send_to(asio::buffer(buffer, message.size()), endpoint);
}

void lib_init() {
    try {
        asio::ip::udp::endpoint ep(asio::ip::udp::v4(), PORT);
        sock.emplace(io, ep);           // construct socket in-place
        sock->non_blocking(true);       // make non-blocking
    } catch (std::exception& e) {
        // DCS cannot handle exceptions across Lua boundary, so log and ignore
        // e.g., write to a file for debugging
        // std::ofstream("C:\\Temp\\dcs_socket_error.txt") << e.what();
        sock.reset();
    }
}

int lib_handshake() {
    if (!sock) return false;

    asio::ip::udp::endpoint sender;
    std::array<char, 1024> recv_buffer;
    std::error_code ec;

    std::size_t len = sock->receive_from(asio::buffer(recv_buffer), sender, 0, ec);

    if (ec == asio::error::would_block || ec == asio::error::try_again) {
        // no packet yet
        return false;
    } else if (ec) {
        // other error, maybe log it
        return false;
    }
    std::string msg(recv_buffer.data(), len);
    if (msg == messageIdRecv) {
        app.emplace(sender);
        _send_packet(sender, messageIdSend);
        return true;
    }
    return false;
}

void lib_send_packet(const char* message) {
    if (!sock || !app) return;

    _send_packet(app.value(), message);
}
