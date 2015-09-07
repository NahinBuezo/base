#include "indice_persona.h"

indice_persona::indice_persona(int id, int rrn)
{
    this->id=id;
    this->rrn=rrn;
}
int indice_persona::getID(){
    return this->id;
}
int indice_persona::getRRN(){
    return this->rrn;
}
void indice_persona::setID(int id){
    this->id=id;
}
void indice_persona::setRRN(int rrn){
    this->rrn=rrn;
}
