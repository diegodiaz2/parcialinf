#include "parcial1.h"
#include "usuario.h"
void aplicacion(){
    //Se crea una clase productos donde van a estar los combos y el inventario
    productos tt;
    usuario usuarios;
    usuarios.leer_usuarios();
//    tt.lectura();//en dado caso de que ya exista un inventario este se lee
//    tt.eliminar_producto_vacio();//si se ingreso un producto donde no habian unidades sera eliminado de la base de datos
//    tt.cargar_combos();//en caso de que existan combos estos seran cargados
//    tt.eliminar_combo();//en caso de que un combo ya no este disponible sera eliminado
    int opc1,opc2=0;
    string conta,ced,combo,ubicacion;
    cout<<"1. Ingresar como administrador.\n2. Ingresar como usuario.\n";cin>>opc1;
    cin.ignore();
    switch (opc1) {//Se decide si ingresar como administrador o usuario comprador
        case 1://Ingresa como administrador
            cout<<"Ingrese la contraseña: ";
            std::getline(std::cin,conta);//conta es la contraseña del administrador
                                        //Esta debe estar guardada en un archivo llamdo sudo.txt
            //cout<<"Contraseña:"<<conta<<endl;
            if(verifivar_contr(conta)){//se procede a verificar que la contraseña sea igual a la guardada
                tt.lectura();//en dado caso de que ya exista un inventario este se lee
                tt.eliminar_producto_vacio();//si se ingreso un producto donde no habian unidades sera eliminado de la base de datos
                tt.cargar_combos();//en caso de que existan combos estos seran cargados
                tt.eliminar_combo();//en caso de que un combo ya no este disponible sera eliminado
                while(opc2<5){
                    cout<<"1. Ingresar un producto.\n2. Crear un combo.\n3. Generar un reporte de ventas."
                          "\n4. Registrar un usuario."
                          "\nDe lo contrario saldra."<<endl;cin>>opc2;
                    if(opc2==1){
                        //cuando entra a ingresar un producto, deja ver los productos que actualmente existen
                        tt.visualizar_inventario();
                        cout<<endl<<endl;
                        tt.ingresar_producto();//Ingresa o modifica un producto al inventario
                    }
                    else if(opc2==2){
                        //cuando entra a ingresar un producto, deja ver los productos que actualmente existen
                        tt.visualizar_inventario();
                        cout<<endl<<endl;
                        //permite ver los combos que hay disponibles por el momento
                        tt.ver_combo();
                        //permite crear un combo
                        tt.crear_combo();
                    }
                    else if(opc2==3)tt.generar_reporte();//visualiza las ventas realizadas
                    else if(opc2==4)usuarios.anadir_usuario();//añade un nuevo usuario
                }
                tt.eliminar_producto_vacio();//antes de guardar en el archivo, elimina productos sin unidades
                tt.eliminar_combo();//elimina los combos que ya no estan disponibles
                tt.guardar_combos();//guarda los combos
                tt.guardar_inventario();//guarda el inventario
            }
            //si la contraseña no fue la misma a la que hay en sudo, no permite entrar
            else cout<<"La contraseña ingresada no es correcta\n"<<endl;
            cout<<"Ha salido.\n";
        break;
        case 2:
            usuarios.ingresar();//permite ingresar como usuario, y realiza todo el proceso de compra
        break;
        default:
            break;
    }
    usuarios.guardar_usuarios();//guarda los nuevos usuarios
    system ("pause");
    system("cls");
}

bool verifivar_contr(string conta){
    //verifica que la contraseña guardada en el archivo sudo.txt sea la misma a la ingresada
    string contrasena;
    char s;
    ifstream k("../Parcial1/sudo.txt");//se extrae la contraseña del archivo sudo
    k.get(s);
    while(!k.eof()){
        contrasena.push_back(s);
        k.get(s);
    }
    k.close();
    //si la contraseña es igual a lo guardado en el archivo de texto, se permite realizar funciones de administrador
    if(conta==contrasena)return 1;
    //de lo contrario se le informa que no es correcta su contraseña, y se devuelve al menu principal
    else return 0;
}
