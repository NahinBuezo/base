#ifndef INDICE_CIUDAD_H
#define INDICE_CIUDAD_H

class indice_ciudad
{
    int codigo;
    int posicion;
public:
    indice_ciudad(int,int);
    int getCodigo();
    int getPosicion();
    void setCodigo(int);
    void setPosicion(int);
};

#endif // INDICE_CIUDAD_H
