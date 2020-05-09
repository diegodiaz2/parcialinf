#include "parcial1.h"
#include "productos.h"
void aplicacion(){
    productos tt;
    tt.lectura();
    tt.eliminar_producto_vacio();
    tt.cargar_combos();
    tt.eliminar_combo();
    int opc1,opc2=0;
    string conta,ced,combo;
    cout<<"1. Ingresar como administrador.\n2. Ingresar como usuario.\n";cin>>opc1;
    cin.ignore();
    switch (opc1) {
        case 1://Ingresa como administrador
            cout<<"Ingrese la contraseña: ";
            std::getline(std::cin,conta);//conta es la contraseña del administrador
                                        //Esta debe estar guardada en un archivo llamdo sudo.txt
            //cout<<"Contraseña:"<<conta<<endl;
            if(verifivar_contr(conta)){
                while(opc2<4){
                    tt.visualizar_inventario();
                    cout<<"1. Ingresar un producto.\n2. Crear un combo.\n3. Generar un reporte de ventas."
                          "\nDe lo contrario saldra."<<endl;cin>>opc2;
                    if(opc2==1)tt.ingresar_producto();//Ingresa o modifica un producto al inventario
                    else if(opc2==2){
                        tt.crear_combo();
                        tt.ver_combo();
                    }
                    else if(opc2==3)tt.ingresar_producto();
                }
            }
            else cout<<"La contraseña ingresada no es correcta\n"<<endl;
            tt.guardar_combos();
            cout<<"Ha salido.\n";
        break;
        case 2:
            cout<<"Ingrese su cedula: ";cin>>ced;
            tt.ver_combo();
            cout<<"Para seleccionar el combo que desea comprar ingrese el numero del combo: ";cin>>combo;
            tt.comprar_combo(combo);


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

bool verifivar_contr(string conta){//verifica que la contraseña guardada en el archivo sudo.txt sea la misma a la ingresada
    string contrasena;
    char s;
    ifstream k("sudo.txt");
    k.get(s);
    while(!k.eof()){
        contrasena.push_back(s);
        k.get(s);
    }
    k.close();
    //cout<<contrasena;
    if(conta==contrasena)return 1;
    else return 0;
}
