#ifndef INDICE_PERSONA_H
#define INDICE_PERSONA_H

class indice_persona
{
    int id;
    int rrn;
public:
    indice_persona(int,int);
    int getID();
    int getRRN();
    void setID(int);
    void setRRN(int);

};

#endif // INDICE_PERSONA_H
