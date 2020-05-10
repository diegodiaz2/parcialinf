#include "parcial1.h"
#include "productos.h"
void aplicacion(){
    //Se crea una clase productos donde van a estar los combos y el inventario
    productos tt;
    tt.lectura();//en dado caso de que ya exista un inventario este se lee
    tt.eliminar_producto_vacio();//si se ingreso un producto donde no habian unidades sera eliminado de la base de datos
    tt.cargar_combos();//en caso de que existan combos estos seran cargados
    tt.eliminar_combo();//en caso de que un combo ya no este disponible sera eliminado
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
                while(opc2<4){
                    cout<<"1. Ingresar un producto.\n2. Crear un combo.\n3. Generar un reporte de ventas."
                          "\nDe lo contrario saldra."<<endl;cin>>opc2;
                    if(opc2==1){
                        tt.visualizar_inventario();
                        cout<<endl<<endl;
                        tt.ingresar_producto();//Ingresa o modifica un producto al inventario
                    }
                    else if(opc2==2){
                        tt.visualizar_inventario();
                        cout<<endl<<endl;
                        tt.ver_combo();
                        tt.crear_combo();
                    }
                    else if(opc2==3)tt.generar_reporte();
                }
            }
            else cout<<"La contraseña ingresada no es correcta\n"<<endl;
            cout<<"Ha salido.\n";
        break;
        case 2:
            cout<<"Ingrese su cedula: ";cin>>ced;
            tt.ver_combo();
            cout<<"Para seleccionar el combo que desea comprar ingrese el numero del combo: ";cin>>combo;
            tt.comprar_combo(combo,ced);
            cout<<"Ingrese la sala en la que se encuentra: ";cin>>ubicacion;
            cout<<"Ingrese el asiento: ";cin>>ubicacion;
        break;
        default:
            break;
    }
    tt.eliminar_producto_vacio();
    tt.eliminar_combo();
    tt.guardar_combos();
    tt.guardar_inventario();
    system ("pause");
    system("cls");
}

bool verifivar_contr(string conta){
    //verifica que la contraseña guardada en el archivo sudo.txt sea la misma a la ingresada
    string contrasena;
    char s;
    ifstream k("sudo.txt");//se extrae la contraseña del archivo sudo
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
