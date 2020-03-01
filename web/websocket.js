//Conexion con el servidor
let socket = new WebSocket("ws://localhost:9990");
//Variable global que identifica al cliente
var g_idMensaje=0;

function dameIdMensaje()
{
    g_idMensaje++;
    return g_idMensaje;
}

//Funciones envio JSON
function pasaTarjeta(numTarjeta)
{
    var id_tarjeta=parseInt(numTarjeta);
    var id_mensaje= dameIdMensaje();
    var mensajeJson = {id:id_mensaje, tipo:"acceso",idTarjeta:id_tarjeta};
    socket.send(JSON.stringify(mensajeJson));
}
function nuevoUsuario(numTarjeta,nombre,apellidos,admin)
{
    var id_tarjeta=parseInt(numTarjeta);
    var id_mensaje= dameIdMensaje();
    var mensajeJson = {id:id_mensaje, tipo:"nuevo",idTarjeta:id_tarjeta,nombre:nombre,apellidos:apellidos,admin:admin};
    socket.send(JSON.stringify(mensajeJson));
}
function administrador(numTarjeta)
{
    var id_tarjeta=parseInt(numTarjeta);
    var id_mensaje= dameIdMensaje();
    var mensajeJson = {id:id_mensaje, tipo:"admin",idTarjeta:id_tarjeta};
    socket.send(JSON.stringify(mensajeJson));
}
function lista()
{
    var id_mensaje= dameIdMensaje();
    var mensajeJson = {id:id_mensaje, tipo:"lista"};
    socket.send(JSON.stringify(mensajeJson));
}
function listareg()
{
    var id_mensaje= dameIdMensaje();
    var mensajeJson = {id:id_mensaje, tipo:"listareg"};
    socket.send(JSON.stringify(mensajeJson));
}
function listadentro()
{
    var id_mensaje= dameIdMensaje();
    var mensajeJson = {id:id_mensaje, tipo:"listadentro"};
    socket.send(JSON.stringify(mensajeJson));
}
function reguser(numTarjeta)
{
    var id_mensaje= dameIdMensaje();
    var id_tarjeta=parseInt(numTarjeta);
    var mensajeJson = {id:id_mensaje, tipo:"reguser",idTarjeta:id_tarjeta};
    socket.send(JSON.stringify(mensajeJson));
}
//Mensaje al abrir la conexion
socket.onopen = function(e) {
  console.log("Conexion abierta");
};
//Gestion de respuestas del servidor
socket.onmessage = function (event){
    var object = JSON.parse(event.data);
    //Notificaciones
    if(object.tipoRespuesta=="notificacion"){
            //Notificacion Error (roja)
        if(object.hayError==true){
            document.getElementById("statusdiv").style.backgroundColor="rgba(200,0,0,0.7)";
        }else{//Notificacion verde
            document.getElementById("statusdiv").style.backgroundColor="rgba(0,200,0,0.7)";
        }
        //Muestra la notificacion con su mensaje para luego desaparecer tras 2 segundos
        document.getElementById("statusdiv").style.display="block";
        document.getElementById("status").innerHTML=object.mensaje;
        setTimeout(
            function()
            {
                document.getElementById("statusdiv").style.display="none";
            },2000
        )
        //Si se crea con exito un Usuario se vuelve al panel numerico
        if(object.creado==true){
            document.getElementById("anadirdiv").style.display="none";
              document.getElementById("numerico").style.display="block";
        }
    //Respuesta Administrador
    }else if (object.tipoRespuesta=="admin"){
        if(object.administrar==true){
            document.getElementById("numerico").style.display="none";
            document.getElementById("admindiv").style.display="block";
        }
    //Respuestas Listas
    }else if(object.tipoRespuesta=="lista"){
        //Lista Usuarios
        if (object.tipoLista=="todosUsuarios"){
            document.getElementById("TablaListaUsuarios").innerHTML="";
            $("#TablaListaUsuarios").append('<tr><th>NumID</th>'+
            '<th>Nombre</th>'+
            '<th>Apellidos</th>' + 
            '<th>Admin</th>');
            for (i = 0; i < object.lista.length; i++){
               
                if (object.lista[i].admin == 1){
                     var adminvalue = "Si";
                }else{
                    var adminvalue = "No";
                }
                $("#TablaListaUsuarios").append('<tr>' + 
                '<td align="center">' + object.lista[i].numid + '</td>'+
                '<td align="center">' + object.lista[i].nombre + '</td>'+
                '<td align="center">' + object.lista[i].apellidos + '</td>'+
                '<td align="center">' + adminvalue + '</td>'+'</tr>'
                );
            }
        //Lista registros
        }else if(object.tipoLista=="todosRegistros"){
            document.getElementById("TablaListaRegistros").innerHTML="";
            $("#TablaListaRegistros").append('<tr><th>ID</th>'+
            '<th>Id Usuario</th>'+
            '<th>Nombre</th>'+
            '<th>Apellidos</th>' + 
            '<th>Entrada</th>' + 
            '<th>Salida</th>');
            for (i = 0; i < object.lista.length; i++){
                $("#TablaListaRegistros").append('<tr>' + 
                '<td align="center">' + object.lista[i].id + '</td>'+
                '<td align="center">' + object.lista[i].usuarioid + '</td>'+
                '<td align="center">' + object.lista[i].nombre + '</td>'+
                '<td align="center">' + object.lista[i].apellidos + '</td>'+
                '<td align="center">' + object.lista[i].entrada + '</td>'+
                '<td align="center">' + object.lista[i].salida + '</td>'+'</tr>'
                );
            }
        //Lista Usuarios Dentro
        }else if(object.tipoLista=="usuariosDentro"){
            document.getElementById("TablaListaDentro").innerHTML="";
            $("#TablaListaDentro").append('<tr><th>ID</th>'+
            '<th>Nombre</th>'+
            '<th>Apellidos</th>'+
            '<th>Entrada</th>');
            for (i = 0; i < object.lista.length; i++){
                $("#TablaListaDentro").append('<tr>' + 
                '<td align="center">' + object.lista[i].usuarioid + '</td>'+
                '<td align="center">' + object.lista[i].nombre + '</td>'+
                '<td align="center">' + object.lista[i].apellidos + '</td>'+
                '<td align="center">' + object.lista[i].entrada + '</td>'+'</tr>'
                );
            }
        //Lista registros de un Usuario especifico
        }else if(object.tipoLista=="userIdLista"){
            document.getElementById("TablaRegistroUser").innerHTML="";
            $("#TablaRegistroUser").append('<tr><th>ID</th>'+
            '<th>Entrada</th>'+
            '<th>Salida</th>');
            for (i = 0; i < object.lista.length; i++){
                $("#TablaRegistroUser").append('<tr>' + 
                '<td align="center">' + object.lista[i].id + '</td>'+
                '<td align="center">' + object.lista[i].entrada + '</td>'+
                '<td align="center">' + object.lista[i].salida + '</td>'+'</tr>'
                );
            }
        }
    }
}
//Mensaje al cerrar la conexion
socket.onclose = function(event) {
  if (event.wasClean) {
    alert(`[close] Connection closed cleanly, code=${event.code} reason=${event.reason}`);
  } else {
    // e.g. server process killed or network down
    // event.code is usually 1006 in this case
    alert('[close] Connection died');
  }
};
//Mensaje de error
socket.onerror = function(error) {
  alert(`[error] ${error.message}`);
};
