#include "usuario.h"

void usuario::leer_usuarios()//permite leer los usuarios ya registrados antes
{
    string contrasena,cedula;
    ifstream k("../Parcial1/usuarios.txt");
    if(k.good()){//verifica que el archivo exista
        while(!k.eof()){
            k>>cedula;
            k>>contrasena;
            //en el map usuarios, añade como clave la cedula, y como valor la contraseña
            usuarios.insert(pair<int,string>(stoi(cedula),contrasena));
        }
    }
    else cout<<"ERROR LEYENDO LOS USUARIOS."<<endl;
}

void usuario::anadir_usuario()//permite registar un nuevo usuario
{
    int cedula;
    string contrasena;
    cout<<"Ingrese la cedula: ";cin>>cedula;
    cout<<"Ingrese la contrasena: ";cin>>contrasena;
    r=usuarios.find(cedula);//busca la cedula que quieren registrar
    if(r!=usuarios.end()){//si la encuentra en el map usuarios es porque ya existe un usuario con esta cedula
        cout<<"Ya hay un usuario con esta cedula."<<endl;
    }
    else {//de lo contrasrio lo añade
        usuarios.insert(pair<int,string>(cedula,contrasena));
    }
}

void usuario::ingresar()
{
    productos tt;
    tt.lectura();//en dado caso de que ya exista un inventario este se lee
    tt.eliminar_producto_vacio();//si se ingreso un producto donde no habian unidades sera eliminado de la base de datos
    tt.cargar_combos();//en caso de que existan combos estos seran cargados
    tt.eliminar_combo();//en caso de que un combo ya no este disponible sera eliminado
    int cedula;
    string contrasena,combo,ubicacion;
    cout<<"Ingrese su cedula: ";cin>>cedula;
    cout<<"Ingrese la contraseña: ";cin>>contrasena;
    r=usuarios.find(cedula);//busca la cedula con la quieren ingresar
    if(r!=usuarios.end()){//si la encuentra verifica la contraseña
        if(r->second==contrasena){//si la contraseña es correcta permite ingresar como usuario
            tt.ver_combo();//deja ver los combos para que el usuario elija alguno
            cout<<"Para seleccionar el combo que desea comprar ingrese el numero del combo: ";cin>>combo;
            tt.comprar_combo(combo,to_string(r->first));//realiza el procedimeinto de compra
            cout<<"Ingrese la sala en la que se encuentra: ";cin>>ubicacion;//pide la sala
            cout<<"Ingrese el asiento: ";cin>>ubicacion;//pide el asiento
        }
        else cout<<"Contrasena incorrecta."<<endl;
    }
    else cout<<"No existen usuarios con esta cedula."<<endl;//en dado caso de que esa contraseña no exista no ingresa
    tt.eliminar_producto_vacio();
    tt.eliminar_combo();
    tt.guardar_combos();
    tt.guardar_inventario();
}

void usuario::guardar_usuarios()//guarda en el txt los usuarios que han sido registrados
{
    ofstream k("../Parcial1/usuarios.txt");
    k.close();
    string total="";
    for(r=usuarios.begin();r!=usuarios.end();r++){
        total=total+to_string(r->first)+" "+r->second;//en un string añade la informacion "\ncedula contraseña"
        ofstream k("../Parcial1/usuarios.txt",ios::app);
        k<<total;
        k.close();
        total="\n";
    }
}

