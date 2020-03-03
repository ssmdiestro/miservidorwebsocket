# Documentación Control de acceso


## Concepto de la aplicación
***********************************************************
La aplicación es un control de acceso que registra las horas de entrada y de salida de los usuarios.

## Funcionamiento
***********************************************************
En la página principal aparece un panel numérico junto a un botón de borrar, un botón de "Ok" y un "#" que se utiliza para entrar en el modo Administrador si el usuario tiene los privilegios. Si el Id de usuario no existe, aparece una notificación de error. Cuando se introduce un Id correcto y pulsamos "Ok" aparece una notificación dando la bienvenida al usuario o despidiendose en caso de que ya esté dentro. Si entramos en el modo Administrador aparecen las siguientes opciones de utilidad:

- Nuevo usuario

- Ver usuarios

- Ver usuarios dentro

- Ver registros

- Ver datos usuario


## Estado de la aplicación
***********************************************************
La funcionalidad principal de la aplicación funciona correctamente.
Si hubiese tenido mas tiempo hubiese querido añadir las siguientes caracteristicas:

- Mostrar las horas que el usuario ha permanecido dentro

- Mostrar el numero de resultados de devuelve la base de datos en las listas

- Mejorar la apariencia visual del cliente

- En la pestaña Datos de usuario añadir opcion de modificar y eliminar ese usuario asi como estadisticas del mismo.

- Poder cambiar el idioma en el cliente

- Obtener el numero del usuario a traves de una tarjeta NFC 

- Generacion de informes diarios/semanales/mensuales/anuales en PDF

- Hacer una gran cantidad de Tests


## Tecnología empleada
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


## Gestión de errores
***********************************************************
Durante el proceso de programación han ido surgiendo errores leves que he podido ir corrigiendo con busquedas en internet o consultando con compañeros. En la parte que mas problemas he tenido ha sido en la de certificados SSL, que he tenido que dejar sin resolver. Tuve errores de compilacion por no haber incluido las librerias a las cuales se hacia referencia dentro de la carpeta del proyecto, y lo solucioné añadiendo dichas librerias y modificando la ruta.
