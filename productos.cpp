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

void productos::ingresar_producto()//ingresa o modifica productos del inventario
{
    list<string> lista;
    string id,nombre;
    int costo,unidades,unidades_totales,cantidad;
 //dado que los productos se reconoceran por su id, se pregunta, si ya existe sera modifica en cantidad, costo, nombre
    cout<<"Ingrese el ID de su producto, si este no existe sera creado: ";cin>>id;
    r=id_valores.find(id);//se verifica si ese id ya existe en el inventario
    if(r!=id_valores.end()){//si lo encontro entra aca
        l=r->second.end();//se busca el ultimo elemento de la lista, pues ahi esta el nombre
        l--;//El nombre
        cout<<"El producto que va a modificar es: "<<*l<<endl;
        l--;//El valor
        cout<<"El costo de cada paquete es(Tenga en cuenta que si este es diferente al"
              " que habia antes, este, sera modificado): ";cin>>costo;//se pregunta por el costo que tendra ahora
        l--;//Total de unidades
        unidades_totales=stoi(*l);
        l--;//Unidades por paquete
        unidades=stoi(*l);
        cout<<"Las unidades por paquete seguiran siendo las mismas."<<endl;//estan no seran modificables
        l--;//Cantidad de paquetes
        cout<<"Ingrese la cantidad a agregar: ";cin>>cantidad;
        //dado que ya habian unidades, se deben agregar a las nuevas
        unidades_totales=unidades_totales+(cantidad*unidades);
        cantidad=cantidad+stoi(*l);
        cin.ignore();
        cout<<"Ingrese el nombre con el que desea guardarlo: ";getline(cin,nombre);//se pregunta por el nombre
        costo=(costo/unidades)*unidades_totales;
        //dado la estructura, mostrada en productos.h, guardamos la informacion de esta forma
        lista.push_back(std::to_string(cantidad));
        lista.push_back(std::to_string(unidades));
        lista.push_back(std::to_string(unidades_totales));
        lista.push_back(std::to_string(costo));
        lista.push_back(nombre);
        id_valores[id]=lista;//se modifica el valor del mapa con clave id
    }
    else {//si el id no se encontro, se creara un nuevo elemento
        //se pide que ingrese los valores que debe tener el producto
        cout<<"El costo de cada paquete es: ";cin>>costo;
        cout<<"Ingrese cuantas unidades por paquete tiene el producto: ";cin>>unidades;
        cout<<"Ingrese la cantidad a agregar: ";cin>>cantidad;
        cin.ignore();
        cout<<"Ingrese el nombre con el que desea guardarlo: ";getline(cin,nombre);
        unidades_totales=unidades*cantidad;
        costo*=cantidad;
        //dado la estructura, mostrada en productos.h, guardamos la informacion de esta forma
        lista.push_back(std::to_string(cantidad));
        lista.push_back(std::to_string(unidades));
        lista.push_back(std::to_string(unidades_totales));
        lista.push_back(std::to_string(costo));
        lista.push_back(nombre);
        id_valores[id]=lista;//se modifica el valor del mapa con clave id
    }
}

void productos::visualizar_inventario()//permite ver el contenido del inventario
{
    for(r=id_valores.begin();r!=id_valores.end();r++){//va recorriendo cada elemento del mapa
        //imprime su respectivo id, y los valores que contiene cada uno
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

void productos::crear_combo()//permite crear un combo
{
    map<string,string> gasto;
    int cant;
    string nombre,ingrediente,unidades_usadas,valor;
    cin.ignore();
    cout<<"Ingrese el nombre del combo: ";getline(cin,nombre);
    cout<<"Ingrese la cantidad de ingredientes que usara: ";cin>>cant;
    for(int i=0;i<cant;i++){
        //pregunto por el id de un producto del inventario, en ejecucion este sera mostrado.
        cout<<"Ingrese el ID del ingrediente: ";cin>>ingrediente;
        //oregunta cuantas unidades va a gastar debido a que puede tener 2, por ejemplo: hamburgues doble carne.
        cout<<"Ingrese las unidad que se usaran: ";cin>>unidades_usadas;
        gasto.insert(pair<string,string>(ingrediente,unidades_usadas));//agrega a un map el id y las unidades gastadas
    }
    //el costo del combo es ingresado por el administrador
    cout<<"Ingrese el costo: ";cin>>valor;
    //al mapa del ciclo for se le agrega la informacion del costo, y nombre del combo
    gasto.insert(pair<string,string>("costo",valor));
    gasto.insert(pair<string,string>("nombre",nombre));
    //a un map, con claves el numero de combo, y valor el map gasto
    combos.insert(pair<string,map<string,string>>(std::to_string(combos.size()+1),gasto));
}

void productos::ver_combo()//nos eprmite visualisar el numero, nombre y costo del combo
{
    for(c=combos.begin();c!=combos.end();c++){//recorre combo elemento por elemento
        //imprime la informacion que debe ser conocida por el usuario
        cout<<c->first<<". "<<c->second["nombre"]<<". "<<c->second["costo"]<<endl;
    }
}

void productos::cargar_combos()//lee los combos disponibles guardados anteriormente
{
    /*
    El archivo de texto combos.txt tiene la siguiente estructura:
    "numero del combo" *"id-1" "unidades gastadas" ... "id-n" "unidades gastadas" +"costo" ."nombre"
    */
    map<string,string> gasto;
    string linea,combo,id,cantidad,costo,nombre;
    ifstream k("combos.txt");//abre el archivo combos.txt
    if(k.good()){//verifica la exitencia
        while(!k.eof()){//realiza las siguientes acciones hasta que se encuentre el fin del archivo
            getline(k,linea);//obtiene linea por linea
            combo=linea[0];//saca el numero del combo
            costo.clear();
            nombre.clear();
            for(int i=0;linea[i]!='\0';i++){
                if(linea[i-1]=='*'){//entra para obtener los prodcutos que va a utilizar
                    for(;linea[i]!='+';i++){
                        for(;linea[i]!=' ';i++)id=id+linea[i];//va obteniendo los ids de los productos necesarios
                        i++;
                        for(;linea[i]!=' ';i++)cantidad=cantidad+linea[i];//obtiene las unidades que gastara
                        gasto.insert(pair<string,string>(id,cantidad));//esto lo va agregando a un map gasto {id:costo}
                        id.clear();
                        cantidad.clear();
                    }
                }
                else if(linea[i-1]=='+'){//entra para obtener costo
                    for(;linea[i]!=' ';i++){
                        costo=costo+linea[i];//obtiene le costo
                    }
                    gasto.insert(pair<string,string>("costo",costo));//en el map gasto agrega {"costo":costo}
                }
                else if(linea[i-1]=='.'){//obtiene el nombre que se le dio al combo
                    for(;linea[i]!='\0';i++){
                        nombre=nombre+linea[i];
                    }
                    gasto.insert(pair<string,string>("nombre",nombre));//en el map gasto agrega {"nombre":nombre}
                    i--;
                }
            }
            combos.insert(pair<string,map<string,string>>(combo,gasto));//agrega al map costos {numero del combo:gasto}
            gasto.clear();//dejamos en blanco a gasto para obtener los sigueintes combos
        }
    }
    //si no es posible abrir el archivo, es porque np existe ningun combo
    else cout<<"Por el momento no hay ningun combo disponible."<<endl;
}

void productos::guardar_combos()//guarda los combos actualmente disponibles en combos.txt
{
    if(combos.size()>0){//si combos.size>0 es porque si existen combos
        ofstream k1("combos.txt");//abrimos el archivo para limpiarlo
        k1.close();
        string linea;
        //cout<<combos.size();
        for(c=combos.begin();c!=combos.end();c++){//itera en el map combos
    //vamos agregando a un string la informacion de los combos, con la estructura que debe tener el archivo combos.txt
            linea=linea+c->first+" *";//obbtiene el numero del combo
            for(a=c->second.begin();a!=c->second.find("costo");a++){
                linea=linea+a->first+" "+a->second+" ";//obtiene los productos necesarios, y las unidades necesarias
            }
            a=c->second.find("costo");
            linea=linea+"+"+a->second+" .";//agregamos al string el costo
            a++;
            linea=linea+a->second;//agregamos al string el nombre
            //abrimos el archivo, de tal forma que siempre se escriba al final de este, sin sobreescribir la informacion
            ofstream k("combos.txt", ios::app);
            k<<linea;//manda el string con toda la informacion de un combo
            k.close();
            linea="\n";
        }
    }
    else {//dado que no existen combos se elimina el archivo combos.txt
        remove("combos.txt");
    }
}

void productos::comprar_combo(string combo,string cedula)
{
    string cantidad,unidad,unidades,costo;
    int valor,Unidades,Cantidad;
    c=combos.find(combo);//el iterador se ubica en el numero del combo
    if(c!=combos.end()){//si existe, se hace lo siguiente
        while(pagar(combo,cedula)){//mientras que el pago sea insufienciete se repite la funcion pagar
            cout<<"No es suficiente dinero."<<endl;
        }
        for(a=c->second.begin();a!=c->second.find("costo");a++){//itera en los valores del combo
            r=id_valores.find(a->first);//busca el id del producto necesario para hacer el combo
            if(r!=id_valores.end()){//si existe hace lo siguiente
                //saco los valores de cada producto en variables
                l=r->second.begin();
                cantidad=*l;l++;
                unidad=*l;l++;
                unidades=*l;l++;
                costo=*l;
                //las opero, restando la cantidad de unidades que se necesita para hacer el combo
                Unidades=stoi(unidades)-stoi(a->second);
                valor=(stoi(costo)/stoi(unidades))*Unidades;
                Cantidad=Unidades/stoi(unidad);
                //los nuevos valores de estas son guardados
                *l=to_string(valor);l--;
                *l=to_string(Unidades);l--;
                l--;
                *l=to_string(Cantidad);
            }
            else cout<<"Hubo un problema comprando el combo"<<endl;
        }
    }
    else cout<<"Este combo no existe."<<endl;//dado que el numero de combo no se encontro, no realiza nada
}

void productos::eliminar_producto_vacio()//si tenemos un producto con 0 unidades totales, este sera eliminado
{
    for(r=id_valores.begin();r!=id_valores.end();r++){//con un iterador ubicamos la posicion de la clave, su id
        l=r->second.begin();//con otro iterador de lista ubicamos la tercera posicion de la lista,unid totales
        l++;l++;
        if(stoi(*l)==0) {
            id_valores.erase(r->first);//si esta es 0 sera eliminado
            if(id_valores.size()>0){//si todavia hay productos sigure verificando
                r=id_valores.begin();
            }
            else return;//si no hay productos se sale de la funcion
        }
    }
}

void productos::guardar_inventario()//GUARDA EL INVENTARIO, SI YA NO HAY UNIDADES SON ELIMINADOS
{
    string linea;
    ofstream k1("productos.txt");//abre y cierra el archivo, de tal forma que quede en blanco
    k1.close();
    //en un string guarda los valores que tiene un producto con su id
    for(r=id_valores.begin();r!=id_valores.end();r++){
        linea=linea+r->first;//primero coloca el id de este
        l=r->second.begin();
        for(l=r->second.begin();l!=r->second.end();l++){
            //va sacando la informacion restante de la lista, que esta como valor en el map id_valores
            linea=linea+" "+(*l);
        }
        ofstream k("productos.txt", ios::app);//abre el archivo y va guardando estas lineas
        k<<linea;
        k.close();
        linea="\n";
    }
}

void productos::eliminar_combo()//EN CASO DE QUE U COMBO NO ESTE DISPONIBLE, ESTE SERA ELIMINADO
{
    map<string,map<string,string>>::iterator m;
    map<string,map<string,string>>::iterator n;
    for(c=combos.begin();c!=combos.end();c++){//itera en los elemnetos de combos
        //dado que el valor de los combos es otro map, itera en este
        for(a=c->second.begin();a!=c->second.find("costo") and a!=c->second.find("nombre");a++){
            r=id_valores.find(a->first);//busca el id del primero elemento necesario para hacer el combo
            if(r!=id_valores.end()){//si lo encuentra hace lo siguiente
                l=r->second.begin();
                l++;l++;
                //verifica que sea posible comprar como minimo un combo
                if(stoi(*l)-stoi(a->second)<0){//entra aca, si no es posible
                    n=c;
                    n++;
                    //cambio de clave el map combos, de tal forma que elimine un combo que no es posible comprar
                    for(m=c;n!=combos.end();n++,m++){
                        combos[m->first]=n->second;
                    }
                    combos.erase(m->first);//elimina el ultimo elemento de map combos, pues ahora sera el penultimo
                    if(combos.size()>0){//si todavia hay combos entra aca
          //se le dan nuevos valores a c y a, de tal forma que no itere sobre un elemento de combos, que ya no existe
                        c=combos.begin();
                        a=c->second.find("costo");
                    }
                    else return;//si ya no hay combos, se sale de la funcion
                }
            }
            else{//si el producto no existe, entra aca
                m=c;
                n=c;
                n++;
                //cambio de clave el map combos, de tal forma que elimine un combo que no es posible comprar
                for(;n!=combos.end();n++,m++){
                    combos[m->first]=n->second;
                }
                combos.erase(m->first);//elimina el ultimo elemento de map combos, pues ahora sera el penultimo
                if(combos.size()>0){//si todavia hay combos entra aca
             //se le dan nuevos valores a c y a, de tal forma que no itere sobre un elemento de combos, que ya no existe
                    c=combos.begin();
                    a=c->second.find("costo");
                }
                else return;//si ya no hay combos, se sale de la funcion
            }
        }
    }
}

bool productos::pagar(string combo,string cedula){//simula el pago en una maquina dispensadora
    int din[10]={50000,20000,10000,5000,2000,1000,500,200,100,50},cant[10]={},dine=0,num;
    for(int i=0;i<=9;i++){//el usuario ingresa los billetes
        cout<<"Ingrese la cantidad de billetes de "<<din[i]<<" que desea ingresar: ";cin>>num;
        dine=dine+(din[i]*num);
    }
    c=combos.find(combo);
    a=c->second.find("costo");//obtengo el costo del combo
    dine=dine-stoi(a->second);//resto el dinero ingresado del usuario con el costo del combo
    if (dine>=0){//si el dinero si fue sufiente, hace lo siguiente
        cout<<"Sus vueltos son los siguientes."<<endl;//simula una maquina dispensadora dando vueltos
        for (int i=0;i<=9;i++){
            cant[i]=dine/din[i];
            dine=dine%din[i];
            cout<<din[i]<<": "<<cant[i]<<endl;
        }
        reporte(cedula,combo);//genera el reporte
        return 0;//retorna false si realizo el pago correctamente
    }
    else{

        return 1;//retorna true si el dinero ingresado no fue suficiente
    }
}

void productos::reporte(string cedula,string combo)//guarda la informacion de las compras realizadas
{
    //en un string guarda la informacion del reporte
    string linea;
    linea=cedula+" compro: ";//primero agrega la cedula del comprador
    c=combos.find(combo);
    a=c->second.find("nombre");
    linea=linea+a->second+" ";//agrega el combo que compro
    a=c->second.find("costo");
    linea=linea+a->second+"\n";//agrega el costo de este
    ofstream k("reporte.txt", ios::app);//abre el archivo reporte.txt, y agrega la linea al final del archivo
    k<<linea;
    k.close();
}

void productos::generar_reporte()//muestra en consola el reporte
{
    string linea;
    ifstream k("reporte.txt");
    if(k.good()){//si el archivo existe hace lo siguiente
        while(!k.eof()){
            getline(k,linea);
            cout<<linea<<endl;//imprime linea por linea el archivo de texto reporte.txt
        }
    }
}

