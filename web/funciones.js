
function init(){
    //Declaracion de variables
    var numero= document.getElementById("numero");
    var uno= document.getElementById('uno');
    var dos= document.getElementById("dos");
    var tres= document.getElementById("tres");
    var cuatro= document.getElementById("cuatro");
    var cinco= document.getElementById("cinco");
    var seis= document.getElementById("seis");
    var siete= document.getElementById("siete");
    var ocho= document.getElementById("ocho");
    var nueve= document.getElementById("nueve");
    var cero= document.getElementById("cero");
    var ok= document.getElementById("ok");
    var admin= document.getElementById("admin");
    var borrar= document.getElementById("borrar");
    var atras= document.getElementById("atras");
    var anadir= document.getElementById("anadir");
    var nuevo= document.getElementById("nuevo");
    var listarUsuarios= document.getElementById("listarUsuarios");
    var listarRegistros= document.getElementById("listarRegistros");
    var listarDentro= document.getElementById("listarDentro");
    var datosUsuario= document.getElementById("datosUsuario");
    var buscar= document.getElementById("buscar");
    var max= 7;
    // Funcionamiento de botones numericos
    uno.onclick=function(e){
        if(numero.textContent.length<max){
            numero.textContent = numero.textContent+"1";
        }
    }
    dos.onclick=function(e){
        if(numero.textContent.length<max){
            numero.textContent = numero.textContent+"2";
        }
    }
    tres.onclick=function(e){
        if(numero.textContent.length<max){
            numero.textContent = numero.textContent+"3";
        }
    }
    cuatro.onclick=function(e){
        if(numero.textContent.length<max){
            numero.textContent = numero.textContent+"4";
        }
    }
    cinco.onclick=function(e){
       if(numero.textContent.length<max){
            numero.textContent = numero.textContent+"5";
        }
    }
    seis.onclick=function(e){
        if(numero.textContent.length<max){
            numero.textContent = numero.textContent+"6";
        }
    }
    siete.onclick=function(e){
        if(numero.textContent.length<max){
            numero.textContent = numero.textContent+"7";
        }
    }
    ocho.onclick=function(e){
        if(numero.textContent.length<max){
            numero.textContent = numero.textContent+"8";
        }
    }
    nueve.onclick=function(e){
        if(numero.textContent.length<max){
            numero.textContent = numero.textContent+"9";
        }
    }
    cero.onclick=function(e){
        if(numero.textContent.length<max){
            numero.textContent = numero.textContent+"0";
        }
    }
   borrar.onclick=function(e){
        if(numero.textContent.length>0){
            numero.textContent = numero.textContent.slice(0, -1);
        }
    }
    ok.onclick=function(e){
        if(numero.textContent.length>0){
            pasaTarjeta(numero.textContent)
            numero.textContent="";
        }
    }
    admin.onclick=function(e){
        if(numero.textContent.length>0){
            administrador(numero.textContent)
            numero.textContent="";
        }
    }
    
    //Funciones Administrador
    //Abrir formulario de añadir nuevo Usuario
    anadir.onclick=function(e){
        document.getElementById("admindiv").style.display="none";
        document.getElementById("anadirdiv").style.display="block";
    }
    //Nuevo usuario
    nuevo.onclick=function(e){
        var numTarjeta=document.getElementById("numnuevo").value;
        var nombre=document.getElementById("nombre").value;
        var apellidos=document.getElementById("apellidos").value;7
        //Muestra notificacion de error si el numero es 0 o mayor que el maximo
        if (numTarjeta.length>max || numTarjeta.length ==0 )
        {
            document.getElementById("statusdiv").style.display="block";
            document.getElementById("statusdiv").style.backgroundColor="rgba(200,0,0,0.7)";
            document.getElementById("status").innerHTML="El numero de tarjeta debe tener entre 1 y 7 caracteres";
            setTimeout(function(){
                document.getElementById("statusdiv").style.display="none";
            },2000)
        }else
        {   //Muestra notificacion de error si el campo de nombre o apellido está vacio
            if (nombre.length==0 || apellidos.length==0)
            {
                document.getElementById("statusdiv").style.display="block";
                document.getElementById("statusdiv").style.backgroundColor="rgba(200,0,0,0.7)";
                document.getElementById("status").innerHTML="No puedes dejar Nombre y/o Apellidos vacios";
                setTimeout(function(){
                    document.getElementById("statusdiv").style.display="none";
                },2000)
            }else{
                if(document.getElementById("chkbox_admin").checked == true)
                {
                    var admin = 1;
                }else{
                    var admin = 0;
                }
                document.getElementById("numnuevo").value="";
                document.getElementById("nombre").value="";
                document.getElementById("apellidos").value="";
                document.getElementById("chkbox_admin").checked = false;
                nuevoUsuario(numTarjeta,nombre,apellidos,admin);
            }
        }
       
    }
    //Lista Usuarios
    listarUsuarios.onclick=function(e){
        document.getElementById("admindiv").style.display="none";
        document.getElementById("listauserdiv").style.display="block";
        lista();
    }
    //Lista Registros
    listarRegistros.onclick=function(e){
        document.getElementById("admindiv").style.display="none";
        document.getElementById("listaregdiv").style.display="block";
        listareg();
    }
    //Lista Usuarios Dentro
    listarDentro.onclick=function(e){
        document.getElementById("admindiv").style.display="none";
        document.getElementById("listadentrodiv").style.display="block";
        listadentro();
    }
    //Abrir Formulario de seleccion de Usuario
    datosUsuario.onclick=function(e){
        document.getElementById("admindiv").style.display="none";
        document.getElementById("datosusuariodiv").style.display="block";
    }
    //Buscar un usuario y mostrar sus datos
    buscar.onclick=function(e){
        var numTarjeta=document.getElementById("datosId").value;
        if(document.getElementById("datosId").value.length>0){
            reguser(numTarjeta);
            document.getElementById("datosId").value="";
        }
    }
    //Volver al panel numerico
    atras.onclick=function(e){
        document.getElementById("admindiv").style.display="none";
        document.getElementById("numerico").style.display="block";
        
    }
    //Boton volver al menu de Administracion
    function adminback()
    {
        document.getElementById("admindiv").style.display="block";
        document.getElementById("anadirdiv").style.display="none";
        document.getElementById("listauserdiv").style.display="none";
        document.getElementById("listaregdiv").style.display="none";
        document.getElementById("listadentrodiv").style.display="none";
        document.getElementById("datosusuariodiv").style.display="none";
        document.getElementById("TablaRegistroUser").innerHTML="";
    }
    
}
