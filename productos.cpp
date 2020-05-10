#include "productos.h"


void productos::lectura()//se lee el inventario
//a tomar en cuenta de que si no tenemos ningun  producto el archivo no debe existir
{
    list<string> lista;//en esta lista iran: cantidad de paquetes, unidad por pquete, unidades totales, costo, nombre
    int m=0,i,v;
    string linea,id,cantidad,unidades,unidades_totales,nombre,valor;
    ifstream k("productos.txt");//se abre el archiivo productos para cargar la informacion
    if(k.good()){//se verifica de que el archvio si exista
        while(!k.eof()){//todo dentro del while se realiza hasta encontrar el final del archivo
            getline(k,linea);//se obtiene una linea, donde se encuentra toda la informacion de un producto
            i=0;
            m=0;
            cantidad.clear();
            unidades.clear();
            id.clear();
            unidades_totales.clear();
            nombre.clear();
            valor.clear();
            v=1;
            while(linea[i]!='\0'){//se realiza hasta encontrar el final del string
                //se procede a sacar la informacion del archivo, esta se encuentra ordenada asi:
                //"id" "cantidad de paquetes" "unidades por paquete" "unidades totales" "costo" "nombre del producto"/n
                if(linea[i]!=' '){//se ignoran los espacios
                    //hay un contador m, que va aunmentando a medida que encontramos un espacio
                    //dado que si se encuentra un espacio pasamos a una informacion distinta
                    if(m==0)id=id+linea[i];//obtiene el id;
                    else if(m==1)cantidad=cantidad+linea[i];//obtiene la cantidad de paquetes
                    else if(m==2)unidades=unidades+linea[i];//obtiene las unidades por paquete
                    else if(m==3)unidades_totales=unidades_totales+linea[i];//obtiene las unidades totales
                    else if(m==4)valor=valor+linea[i];//obtiene el valor
                    else nombre=nombre+linea[i];//obtiene el nombre del producto
                }
                else{
                    m++;
                    if(m>4 and v!=1){//si ya estamos encontrando el nombre los espacios son tomados en cuenta
                        nombre=nombre+linea[i];
                    }
                    else if(m>4 and v==1){//mientras que estemos hayando algun dato distinto al nombre v permanece en 1
                        v=0;
                    }
                }
                i++;
            }
            lista.push_back(cantidad);//como primera posicion tenemos la cantidad
            lista.push_back(unidades);//segunda: las unidades por paquete
            lista.push_back(unidades_totales);//tercera: unidades totales
            lista.push_back(valor);//cuarta: valor
            lista.push_back(nombre);//quinta: nombre
            //se agregan los valores a un mapa de la siguiente forma:
            //{id:[cantidad,unidades por paquete,unidades totales,valor,nombre]}
            id_valores.insert(pair<string,list<string>>(id,lista));
            lista.clear();//se limpia la lista para obtener las productos
        }
        k.close();
    }
    //se muestra en dado caso de que el archivo no exista, y por ende no hayan productos
    else cout<<"No hay ningun producto en el inventario."<<endl;
}

void productos::ingresar_producto()
{
    list<string> lista;
    string id,nombre;
    int costo,unidades,unidades_totales,cantidad;
    cout<<"Ingrese el ID de su producto, si este no existe sera creado: ";cin>>id;
    r=id_valores.find(id);
    if(r!=id_valores.end()){
        l=r->second.end();
        l--;//El nombre
        cout<<"El producto que va a modificar es: "<<*l<<endl;
        l--;//El valor
        cout<<"El costo de cada paquete es(Tenga en cuenta que si este es diferente al"
              " que habia antes, este, sera modificado): ";cin>>costo;
        //costo=costo+stoi(*l);
        l--;//Total de unidades
        unidades_totales=stoi(*l);
        l--;//Unidades por paquete
        unidades=stoi(*l);
        cout<<"Las unidades por paquete seguiran siendo las mismas."<<endl;
        l--;//Cantidad de paquetes
        cout<<"Ingrese la cantidad a agregar: ";cin>>cantidad;
        unidades_totales=unidades_totales+(cantidad*unidades);
        cantidad=cantidad+stoi(*l);
      //cout<<"Ingrese cuantas unidades por paquete tiene el producto: ";cin>>unidades;
        cin.ignore();
        cout<<"Ingrese el nombre con el que desea guardarlo: ";getline(cin,nombre);
        costo=(costo/unidades)*unidades_totales;
        lista.push_back(std::to_string(cantidad));
        lista.push_back(std::to_string(unidades));
        lista.push_back(std::to_string(unidades_totales));
        lista.push_back(std::to_string(costo));
        lista.push_back(nombre);
        id_valores[id]=lista;
    }
    else {
        cout<<"El costo de cada paquete es: ";cin>>costo;
        cout<<"Ingrese cuantas unidades por paquete tiene el producto: ";cin>>unidades;
        cout<<"Ingrese la cantidad a agregar: ";cin>>cantidad;
        cin.ignore();
        cout<<"Ingrese el nombre con el que desea guardarlo: ";getline(cin,nombre);
        unidades_totales=unidades*cantidad;
        costo*=cantidad;
        lista.push_back(std::to_string(cantidad));
        lista.push_back(std::to_string(unidades));
        lista.push_back(std::to_string(unidades_totales));
        lista.push_back(std::to_string(costo));
        lista.push_back(nombre);
        id_valores[id]=lista;
    }
}

void productos::visualizar_inventario()
{
    for(r=id_valores.begin();r!=id_valores.end();r++){
        cout<<"ID: "<<r->first<<". ";
        l=r->second.begin();
        cout<<"Cantidad: "<<*l;
        l++;
        cout<<". Unidad de paquete: "<<*l;
        l++;
        cout<<". Unidades totales: "<<*l;
        l++;
        cout<<". Costo: "<<*l;
        l++;
        cout<<". Nombre: "<<*l<<"."<<endl;
    }
}

void productos::crear_combo()
{
    map<string,string> gasto;
    int cant;
    string nombre,ingrediente,unidades_usadas,valor;
    cin.ignore();
    cout<<"Ingrese el nombre del combo: ";getline(cin,nombre);
    cout<<"Ingrese la cantidad de ingredientes que usara: ";cin>>cant;
    for(int i=0;i<cant;i++){
        cout<<"Ingrese el ID del ingrediente: ";cin>>ingrediente;
        cout<<"Ingrese las unidad que se usaran: ";cin>>unidades_usadas;
        gasto.insert(pair<string,string>(ingrediente,unidades_usadas));
    }
    cout<<"Ingrese el costo: ";cin>>valor;
    gasto.insert(pair<string,string>("costo",valor));
    gasto.insert(pair<string,string>("nombre",nombre));
    combos.insert(pair<string,map<string,string>>(std::to_string(combos.size()+1),gasto));
}

void productos::ver_combo()
{
    for(c=combos.begin();c!=combos.end();c++){
        cout<<c->first<<". "<<c->second["nombre"]<<". "<<c->second["costo"]<<endl;
    }
}

void productos::cargar_combos()
{
    bool ban=1;
    map<string,string> gasto;
    string linea,combo,id,cantidad,costo,nombre;
    ifstream k("combos.txt");
    if(k.good()){
        while(!k.eof()){
            getline(k,linea);
            combo=linea[0];
            costo.clear();
            nombre.clear();
            for(int i=0;linea[i]!='\0';i++){
                if(linea[i-1]=='*'){
                    for(;linea[i]!='+';i++){
                        for(;linea[i]!=' ';i++)id=id+linea[i];
                        i++;
                        for(;linea[i]!=' ';i++)cantidad=cantidad+linea[i];
                        gasto.insert(pair<string,string>(id,cantidad));
                        id.clear();
                        cantidad.clear();
                    }
                }
                else if(linea[i-1]=='+'){
                    for(;linea[i]!=' ';i++){
                        costo=costo+linea[i];
                    }
                    gasto.insert(pair<string,string>("costo",costo));
                }
                else if(linea[i-1]=='.'){
                    for(;linea[i]!='\0';i++){
                        nombre=nombre+linea[i];
                    }
                    gasto.insert(pair<string,string>("nombre",nombre));
                    i--;
                }
            }
            combos.insert(pair<string,map<string,string>>(combo,gasto));
            gasto.clear();
        }
    }
    else cout<<"Por el momento no hay ningun combo disponible."<<endl;
}

void productos::guardar_combos()
{
    if(combos.size()>0){
        ofstream k1("combos.txt");
        k1.close();
        string linea;
        cout<<combos.size();
        if(combos.size()>0){
            for(c=combos.begin();c!=combos.end();c++){
                linea=linea+c->first+" *";
                for(a=c->second.begin();a!=c->second.find("costo");a++){
                    linea=linea+a->first+" "+a->second+" ";
                }
                a=c->second.find("costo");
                linea=linea+"+"+a->second+" .";
                a++;
                linea=linea+a->second;
                ofstream k("combos.txt", ios::app);
                k<<linea;
                k.close();
                linea="\n";
            }
        }
    }
    else {
        remove("combos.txt");
    }
}

void productos::comprar_combo(string combo,string cedula)
{
    string cantidad,unidad,unidades,costo;
    int valor,Unidades,Cantidad;
    c=combos.find(combo);
    if(c!=combos.end()){
        while(pagar(combo,cedula)){
            cout<<"No es suficiente dinero."<<endl;
        }
        for(a=c->second.begin();a!=c->second.find("costo");a++){
            r=id_valores.find(a->first);
            if(r!=id_valores.end()){
                l=r->second.begin();
                cantidad=*l;l++;
                unidad=*l;l++;
                unidades=*l;l++;
                costo=*l;
                Unidades=stoi(unidades)-stoi(a->second);
                valor=(stoi(costo)/stoi(unidades))*Unidades;
                Cantidad=Unidades/stoi(unidad);
                *l=to_string(valor);l--;
                *l=to_string(Unidades);l--;
                l--;
                *l=to_string(Cantidad);
            }
            else cout<<"Hubo un problema comprando el combo"<<endl;
        }
    }
    else cout<<"Este combo no existe."<<endl;
}

void productos::eliminar_producto_vacio()//si tenemos un producto con 0 unidades totales, este sera eliminado
{
    for(r=id_valores.begin();r!=id_valores.end();r++){//con un iterador ubicamos la posicion de la clave, su id
        l=r->second.begin();//con otro iterador de lista ubicamos la tercera posicion de la lista,unid totales
        l++;l++;
        if(stoi(*l)==0) {
            id_valores.erase(r->first);//si esta es 0 sera eliminado
            r=id_valores.begin();
        }
    }
}

void productos::guardar_inventario()
{
    string linea;
    ofstream k1("productos.txt");
    k1.close();
    for(r=id_valores.begin();r!=id_valores.end();r++){
        linea=linea+r->first;
        l=r->second.begin();
        for(l=r->second.begin();l!=r->second.end();l++){
            linea=linea+" "+(*l);
        }
        ofstream k("productos.txt", ios::app);
        k<<linea;
        k.close();
        linea="\n";
    }
}

void productos::eliminar_combo()
{
    map<string,map<string,string>>::iterator m;
    map<string,map<string,string>>::iterator n;
    for(c=combos.begin();c!=combos.end();c++){
        for(a=c->second.begin();a!=c->second.find("costo") and a!=c->second.find("nombre");a++){
            r=id_valores.find(a->first);
            if(r!=id_valores.end()){
                l=r->second.begin();
                l++;l++;
                if(stoi(*l)-stoi(a->second)<0){
                    n=c;
                    n++;
                    for(m=c;n!=combos.end();n++,m++){
                        combos[m->first]=n->second;
                    }
                    combos.erase(m->first);
                    if(combos.size()>0){
                        c=combos.begin();
                        a=c->second.find("costo");
                    }
                    else return;
                }
            }
            else{
                m=c;
                n=c;
                n++;
                for(;n!=combos.end();n++,m++){
                    combos[m->first]=n->second;
                }
                combos.erase(m->first);
                if(combos.size()>0){
                    c=combos.begin();
                    a=c->second.find("costo");
                }
                else return;
            }
        }
    }
}

bool productos::pagar(string combo,string cedula){
    int din[10]={50000,20000,10000,5000,2000,1000,500,200,100,50},cant[10]={},dine=0,num;
    for(int i=0;i<=9;i++){
        cout<<"Ingrese la cantidad de billetes de "<<din[i]<<" que desea ingresar: ";cin>>num;
        dine=dine+(din[i]*num);
    }
    c=combos.find(combo);
    a=c->second.find("costo");
    dine=dine-stoi(a->second);
    if (dine>=0){
        cout<<"Sus vueltos son los siguientes."<<endl;
        for (int i=0;i<=9;i++){
            cant[i]=dine/din[i];
            dine=dine%din[i];
            cout<<din[i]<<": "<<cant[i]<<endl;
        }
        reporte(cedula,combo);
        return 0;
    }
    else{

        return 1;
    }
}

void productos::reporte(string cedula,string combo)
{
    string linea;
    linea=cedula+" compro: ";
    c=combos.find(combo);
    a=c->second.find("nombre");
    linea=linea+a->second+" ";
    a=c->second.find("costo");
    linea=linea+a->second+"\n";
    ofstream k("reporte.txt", ios::app);
    k<<linea;
    k.close();
}

void productos::generar_reporte()
{
    string linea;
    ifstream k("reporte.txt");
    while(!k.eof()){
        getline(k,linea);
        cout<<linea<<endl;
    }
}

