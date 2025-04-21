//
// Created by psp515 on 19.04.2025.
//


#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <stdexcept>
#include <cpplog/sink.h>
#include <cpplog/extensions/formatter.h>
#include "win_http_sink.h"

#include <iostream>

#include "win_socket_guard.h"
#include "win_http_sink_options.h"

using namespace std;
using namespace cpplog;
using namespace cpplog::common;
using namespace cpplog::extensions;

WinHttpSink::WinHttpSink(const LogLevel level, const WinHttpSinkOptions& options) : Sink(level), options(options)
{
    if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
        throw std::runtime_error("Failed to initialize WinHttp sink.");
    }
}

void WinHttpSink::log(const LogEventOptions &options, const LogEvent &event)
{
    struct addrinfo hints = {}, *result;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(this->options.getHost().c_str(), this->options.getPort().c_str(), &hints, &result) != 0) {
        throw std::runtime_error("getaddrinfo failed.");
    }

    const SOCKET rawSock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (rawSock == INVALID_SOCKET) {
        freeaddrinfo(result);
        throw std::runtime_error("Socket creation failed.");
    }

    const WinSocketGuard sock(rawSock);

    if (connect(sock.get(), result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR) {
        freeaddrinfo(result);
        throw std::runtime_error("Connection failed.");
    }

    freeaddrinfo(result);

    const auto request = this->getRequest(options, event);

    send(sock.get(), request.c_str(), (int)request.size(), 0);

    array<char, 4096> buffer{};
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(sock.get(), &readfds);

    const timeval timeout {
        .tv_sec = 5,
        .tv_usec = 0
    };

    const int selectResult = select(0, &readfds, nullptr, nullptr, &timeout);

    if ( selectResult > 0) {
        int bytesReceived;
        do {
            bytesReceived = recv(sock.get(), buffer.data(), (buffer.size() - 1), 0);
            if (bytesReceived > 0) {
                buffer[bytesReceived] = '\0';
            }
        } while (bytesReceived > 0);
    }
}

string WinHttpSink::getRequest(const LogEventOptions &options, const LogEvent &event) const
{
    const auto formatter = Formatter(options);

    const auto content = formatter.format(event);
    const auto content_type = options.logAsJson() ? "application/json" : "application/text";

    const auto request = "POST " + this->options.getEndpoint() + " HTTP/1.1\r\n"
                      "Host: " +  this->options.getHost() + "\r\n"
                      "Content-Type: " + content_type + "\r\n"
                      "Content-Length: " + std::to_string(content.size()) + "\r\n"
                      "Connection: close\r\n\r\n"
                      + content;

    return request;
}

WinHttpSink::~WinHttpSink()
{
    WSACleanup();
}