#include "parcial1.h"
class productos
{
public:
    void lectura();
    void ingresar_producto();
    void visualizar_inventario();
    void crear_combo();
    void ver_combo();
    void cargar_combos();
    void guardar_combos();
private:
    map<string,list<string>> id_valores;
    map<string,list<string>>::iterator r;
    list<string>::iterator l;
    map<string,map<string,string>> combos;
    map<string,map<string,string>>::iterator c;
    map<string,string>::iterator a;
};
