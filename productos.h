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
    void comprar_combo(string combo,string cedula);
    void eliminar_producto_vacio();
    void guardar_inventario();
    void eliminar_combo();
    bool pagar(string combo,string cedula);
    void reporte(string cedula,string combo);
    void generar_reporte();
private:
    map<string,list<string>> id_valores;
    map<string,list<string>>::iterator r;
    list<string>::iterator l;
    map<string,map<string,string>> combos;
    map<string,map<string,string>>::iterator c;
    map<string,string>::iterator a;
};
