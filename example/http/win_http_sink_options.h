//
// Created by psp515 on 21.04.2025.
//

#ifndef WIN_HTTP_SINK_OPTIONS_H
#define WIN_HTTP_SINK_OPTIONS_H

#include <string>
#include <stdexcept>

using namespace std;


/// Configuration options for the WinHttp sink.
class WinHttpSinkOptions
{
public:
    ///
    /// Constructs WinHttpSinkOptions with the given endpoint, port, and host.
    ///
    /// @param endpoint The target endpoint for the HTTP sink (e.g., "/api/logs").
    /// @param port The port used to connect to the HTTP server.
    /// @param host The hostname or IP address of the HTTP server.
    ///
    /// @throws std::invalid_argument if any argument is empty.
    ///
    WinHttpSinkOptions(const string& endpoint, const string& port, const string& host)
        : endpoint(endpoint), port(port), host(host)
    {
        if (endpoint.empty())
            throw std::invalid_argument("Endpoint cannot be empty.");

        if (port.empty())
            throw std::invalid_argument("Port cannot be empty.");

        if (host.empty())
            throw std::invalid_argument("Host cannot be empty.");
    }

    ///
    /// Gets the configured endpoint.
    ///
    /// @return The endpoint as a string.
    ///
    const string& getEndpoint() const { return endpoint; }

    ///
    /// Gets the configured port.
    ///
    /// @return The port as a string.
    ///
    const string& getPort() const { return port; }

    ///
    /// Gets the configured host.
    ///
    /// @return The host as a string.
    ///
    const string& getHost() const { return host; }

private:
    string endpoint;
    string port;
    string host;
};


#endif //WIN_HTTP_SINK_OPTIONS_H
