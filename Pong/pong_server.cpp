#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

void runPongTcpServer()
{
    unsigned short port = 2000;

    sf::TcpListener listener;

    if (listener.listen(port) != sf::Socket::Done)
    {
        std::cout << "Error " << __LINE__ << std::endl;
        return;
    }
    std::cout << "Server is listening to port " << port << ", waiting for connections... " << std::endl;

    sf::TcpSocket sockets[2];
    std::size_t received = 0;
    sf::Packet packets[2];
    std::string buff;
    float x1 = 75, x2 = 1930, tmp_coord;

    packets[0] << x1 << x2;
    packets[1] << x2 << x1;

    if (listener.accept(sockets[0]) != sf::Socket::Done)
    {
        std::cout << "Error " << __LINE__ << std::endl;
        return;
    }
    std::cout << "Client 1 connected: " << sockets[0].getRemoteAddress() << std::endl;
    sockets[0].receive(&buff, sizeof(buff), received);
    packets[1] << buff;

    if (listener.accept(sockets[1]) != sf::Socket::Done)
    {
        std::cout << "Error " << __LINE__ << std::endl;
        return;
    }
    std::cout << "Client 2 connected: " << sockets[1].getRemoteAddress() << std::endl;
    sockets[1].receive(&buff, sizeof(buff), received);
    packets[0] << buff;

    sockets[0].send(packets[0]);
    sockets[1].send(packets[1]);

    while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
    {

        sockets[0].receive(&tmp_coord, sizeof(float), received);
        std::cout << "Client " << sockets[0].getRemoteAddress() << " sent message: " << tmp_coord << std::endl;
        sockets[1].send(&tmp_coord, sizeof(float));

        sockets[1].receive(&tmp_coord, sizeof(float), received);
        std::cout << "Client " << sockets[1].getRemoteAddress() << " sent message: " << tmp_coord << std::endl;
        sockets[0].send(&tmp_coord, sizeof(float));
    }

    std::cout << "Server stopped" << std::endl;
}

int main()
{
    runPongTcpServer();

    return 0;
}
