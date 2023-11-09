#define ONLINE_PEER
#include <ReKat.hpp>
using namespace ReKat::online;
using namespace ReKat;

int main ( int argc, char const *argv[] ) {
    if (argc == 3) {
        std::cout << "start: " << Start ( "pippo", "42068" ) << '\n';
        std::cout << "try to connect\n";
        std::cout << "new connection: " << Connect ("localhost", "localhost") << '\n';

        online::Send("1234",4,"localhost");
        char* _buf = (char*)calloc(5,sizeof(char));
        online::Recv(_buf,4,"localhost");
        std::cout << "msg recived: " << _buf << '\n';
    } else {
        std::cout << "start: " << Start ( "pippo1", "42069" ) << '\n';
        std::cout << "connection: " << New_Connection ( ) << '\n';
        std::cout << "connected to: " << Connected ( ) [0] << '\n';
        char* _buf = (char*)calloc(5,sizeof(char));
        online::Recv(_buf,4,"pippo");
        std::cout << "msg recived: " << _buf << '\n';
        online::Send("giov",4,"pippo");
    }

    std::cout << "End\n";
}
