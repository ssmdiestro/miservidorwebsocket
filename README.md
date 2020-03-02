# Documentacion Control de acceso


## Concepto de la aplicacion
***********************************************************
La aplicacion es un control de acceso que registra las horas de entrada y de salida de los usuarios.

## Funcionamiento
***********************************************************
En la pagina principal aparece un panel numérico junto a un boton de borrar, un boton de "Ok" y un "#" que se utiliza para entrar en el modo Administrador si el usuario tiene los privilegios. Si el Id de usuario no existe, aparece una notificacion de error. Cuando se introduce un Id correcto y pulsamos "Ok" aparece una notificacion dando la bienvenida al usuario o despidiendose en caso de que ya esté dentro. Si entramos en el modo Administrador aparecen las siguientes opciones de utilidad:

- Nuevo usuario

- Ver usuarios

- Ver usuarios dentro

- Ver registros

- Ver datos usuario


## Estado de la aplicacion
***********************************************************
La funcionalidad principal de la aplicacion funciona correctamente aunque es posible que haya varios errores porque no he tenido tiempo a realizar tests y corregir fallos.
Si hubiese tenido mas tiempo hubiese querido añadir las siguientes caracteristicas:

- Mostrar las horas que el usuario ha permanecido dentro

- Mostrar el numero de resultados de devuelve la base de datos en las listas

- Mejorar la apariencia visual del cliente

- Obtener los parametros de configuracion de la base de datos desde un archivo externo

- En la pestaña Datos de usuario añadir opcion de modificar y eliminar ese usuario asi como estadisticas del mismo.

- Poder cambiar el idioma en el cliente

- Obtener el numero del usuario a traves de una tarjeta NFC 

- Generacion de informes diarios/semanales/mensuales/anuales en PDF

- Hacer una gran cantidad de Tests


## Tecnologia empleada
***********************************************************
**Servidor:**

- C++

- QT Creator

- Websocket

- JSON

**Cliente:**

- Apache2

- HTML

- CSS

- JavaScript

- JQuery

- JSON

**Base de Datos:**

- Postgres


**Control de versiones:**

- Git


## Gestion de errores
***********************************************************
Durante el proceso de programación han ido surgiendo errores leves que he podido ir corrigiendo con busquedas en internet o consultando con compañeros. En la parte que mas problemas he tenido ha sido en la de certificados SSL, que por falta de tiempo he tenido que dejar sin resolver. Junto a otros fallos que desconozco porque no tuve tiempo a realizar tests.
