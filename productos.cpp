#include "productos.h"


void productos::lectura()
{
    list<string> lista;
    int m=0,i,v;
    string linea,id,cantidad,unidades,unidades_totales,nombre,valor;
    ifstream k("productos.txt");
    while(!k.eof()){
        getline(k,linea);
        i=0;
        m=0;
        cantidad.clear();
        unidades.clear();
        id.clear();
        unidades_totales.clear();
        nombre.clear();
        valor.clear();
        v=1;
        while(linea[i]!='\0'){
            if(linea[i]!=' '){
                if(m==0)id=id+linea[i];
                else if(m==1)cantidad=cantidad+linea[i];
                else if(m==2)unidades=unidades+linea[i];
                else if(m==3)unidades_totales=unidades_totales+linea[i];
                else if(m==4)valor=valor+linea[i];
                else nombre=nombre+linea[i];
            }
            else{
                m++;
                if(m>4 and v!=1){
                    nombre=nombre+linea[i];
                }
                else if(m>4 and v==1){
                    v=0;
                }
            }
            i++;
        }
        lista.push_back(cantidad);
        lista.push_back(unidades);
        lista.push_back(unidades_totales);
        lista.push_back(valor);
        lista.push_back(nombre);
        //cout<<"id "<<id<<" cantidad "<<cantidad<<" unidades "<<unidades<<" unidades totales "<<unidades_totales<<endl;
        id_valores.insert(pair<string,list<string>>(id,lista));
        lista.clear();
    }
    k.close();
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
    map<string,string> gasto;
    string linea,combo,id,cantidad,costo,nombre;
    ifstream k("combos.txt");
    while(!k.eof()){
        getline(k,linea);
        combo=linea[0];
        costo.clear();
        nombre.clear();
        for(int i=0;linea[i]!='\0';i++){
            if(linea[i-1]=='*'){
                for(;linea[i]!='+';i+=4){
                    id=linea[i];
                    cantidad=linea[i+2];
                    gasto.insert(pair<string,string>(id,cantidad));
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

void productos::guardar_combos()
{
    ofstream k1("combos.txt");
    k1.close();
    string linea;
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

