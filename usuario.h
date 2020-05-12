#include "productos.h"
//fstream k("../Parcial/archivos/usuarios.txt")

//estructura de usuarios= map<int,string>
//{cedula1:contraseña,cedula2:contraseña,...,cedulan:contraseña}

class usuario
{
public:
    void leer_usuarios();
    void anadir_usuario();
    void ingresar();
    void guardar_usuarios();
private:
    map<int,string> usuarios;
    map<int,string>::iterator r;
};
