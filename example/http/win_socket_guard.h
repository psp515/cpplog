//
// Created by psp515 on 21.04.2025.
//

#ifndef SOCKET_GUARD_H
#define SOCKET_GUARD_H

#include <winsock2.h>


/// A RAII-style wrapper to manage the lifetime of a Windows socket.
class WinSocketGuard
{
public:
    ///
    ///  Constructs the WinSocketGuard with a given socket.
    ///
    ///  @param socket A valid Windows socket handle.
    ///
    explicit WinSocketGuard(const SOCKET socket) : socket(socket)
    {
    }

    ///
    ///  Destructor closes the socket if it's valid.
    ///
    ~WinSocketGuard()
    {
        if (socket != INVALID_SOCKET)
        {
            closesocket(socket);
        }
    }

    ///
    /// Returns the managed socket.
    ///
    /// @return The internal SOCKET handle.
    ///
    SOCKET get() const { return socket; }

private:
    SOCKET socket;
};


#endif //SOCKET_GUARD_H
