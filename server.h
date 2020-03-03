#ifndef SERVER_H
#define SERVER_H
#include "json.hpp"
#include <QSqlDatabase>
#include <QString>
using JSON = nlohmann::json;
/**
 * @brief Clase Server
 * Es la clase encargada de manejar el servidor
 */

class Server
{
public:
    Server();
    QSqlDatabase m_db;
    QString m_hostname;
    QString m_port;
    QString m_database;
    QString m_userName;
    QString m_password;
    QSqlDatabase conectar();
    void loadProperties();
    void readFile();
    void processLine(std::string line);
    std::map<std::string, std::string> prop;
    /**
     * @brief dameIdMensaje
     *
     * Se genera un ID de conexion que relaciona al cliente con el servidor
     * @return
     */
    int dameIdMensaje();
    /**
     * @brief iniciarServer
     *
     * Inicia el servidor
     * @return
     */
    int iniciarServer();
    /**
     * @brief acceso
     *
     * Devuelve al cliente un mensaje JSON y solicita añadir un nuevo registro cuando un usuario entra con su clave o añadirle hora de salida si el Usuario ya estaba dentro
     * @param receivedObject El JSON que recibe desde el cliente
     * @return
     */
    JSON acceso(JSON receivedObject);
    /**
     * @brief admin
     *
     * Devuelve al cliente un mensaje JSON y solicita entrar en el panel de administracion si el usuario tiene dichos privilegios
     * @param receivedObject El JSON que recibe desde el cliente
     * @return
     */
    JSON admin(JSON receivedObject);
    /**
     * @brief lista
     *
     * Devuelve al cliente un mensaje JSON con la lista de todos los usuarios
     * @param receivedObject El JSON que recibe desde el cliente
     * @return
     */
    JSON lista(JSON receivedObject);
    /**
     * @brief listareg
     *
     * Devuelve al cliente un mensaje JSON con la lista de todos los registros
     * @param receivedObject El JSON que recibe desde el cliente
     * @return
     */
    JSON listareg(JSON receivedObject);
    /**
     * @brief nuevo
     *
     * Devuelve al cliente un mensaje JSON con los datos necesarios para añadir a la base de datos un nuevo Usuario
     * @param receivedObject El JSON que recibe desde el cliente
     * @return
     */
    JSON nuevo(JSON receivedObject);
    /**
     * @brief reguser
     *
     * Devuelve al cliente un mensaje JSON con los registros de un usuario en concreto
     * @param receivedObject El JSON que recibe desde el cliente
     * @return
     */
    JSON reguser(JSON receivedObject);
    /**
     * @brief listaDentro
     *
     * Devuelve al cliente un mensaje JSON con la lista de usuarios que están dentro
     * @param receivedObject El JSON que recibe desde el cliente
     * @return
     */
    JSON listaDentro(JSON receivedObject);
    /**
     * @brief exists
     *
     * Comprueba si el JSON recibido tiene el campo especificado
     * @param json JSON a comprobar
     * @param key Nombre del campo a comprobar
     * @return
     */
    bool exists(const JSON& json, const std::string& key);

};

#endif // SERVER_H
