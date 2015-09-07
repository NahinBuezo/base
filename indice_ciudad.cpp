#include "indice_ciudad.h"

indice_ciudad::indice_ciudad(int codigo, int posicion)
{
    this->codigo=codigo;
    this->posicion=posicion;
}
int indice_ciudad::getCodigo(){
    return this->codigo;
}
int indice_ciudad::getPosicion(){
    return this->posicion;
}
void indice_ciudad::setCodigo(int codigo){
    this->codigo=codigo;
}
void indice_ciudad::setPosicion(int posicion){
    this->posicion=posicion;
}
