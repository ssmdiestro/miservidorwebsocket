#ifndef SERVER_H
#define SERVER_H
#include "json.hpp"
using JSON = nlohmann::json;
class Server
{
public:
    Server();
    int iniciarServer();
    JSON registro(JSON receivedObject);
    JSON acceso(JSON receivedObject);
    JSON admin(JSON receivedObject);
    JSON lista(JSON receivedObject);
    JSON listareg(JSON receivedObject);
    JSON nuevo(JSON receivedObject);
    int dameIdMensaje();
    bool exists(const JSON& json, const std::string& key);

};

#endif // SERVER_H
