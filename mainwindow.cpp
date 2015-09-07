#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "indice_persona.h"
#include "indice_llamadas.h"
#include "indice_ciudad.h"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <QMessageBox>
#include <QtGui>
#include <QtCore>
#include <stdlib.h>
#include <stdio.h>
#include <QTableWidgetItem>


using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->index_persona;
    this->index_ciudad;
    this->index_llamadas;
    
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::crear_header(){
    //creando cabecera de clientes
    this->cabecera_cliente="-HEADER\n";
    this->cabecera_cliente+="-Numero de registros: ";
    this->cabecera_cliente+=index_persona.size();
    this->cabecera_cliente+="\n-Size por registro: ";
    this->cabecera_cliente+="54 Bytes";
    //creando cabecera de ciudades
    this->cabecera_ciudad="-HEADER\n";
    this->cabecera_ciudad+="-Numero de registros: ";
    this->cabecera_ciudad+=index_ciudad.size();
    this->cabecera_ciudad+="\n-Size por registro: 51 Bytes";
    //creando cabecera de registro de llamadas
    this->cabecera_cliente="-HEADER\n";
    this->cabecera_cliente+="-Numero de registros: ";
    this->cabecera_cliente+=index_llamadas.size();
    this->cabecera_cliente+="\n-Size por registro: 37 Bytes";
    
    
}
void MainWindow::crear_avail_list(){
    //creando avai list de clientes
    
    ifstream leer2("custom.bin",ios::binary);
    leer2.seekg (0, leer2.end);
    int length = leer2.tellg();
    leer2.seekg (0, leer2.beg);
    string frase2;
    int contador=0;
    while (leer2.is_open()) {
        leer2.read((char*)&frase2,sizeof(string));
        if(frase2.find("-")==-1||frase2.find("-")==NULL){
            if(frase2.find("*")!=-1||frase2.find("*")!=NULL){
                this->avail_cliente.push_back(contador);
            }
        }
        frase2="";
        contador++;
        if(leer2.eof())
            leer2.close();
    }
    contador=0;
    
    //-----------------------------------------------------------------------------
    //ahora crearemos el avail list de ciudades
    ifstream leer_ciudad("ciudad.bin",ios::binary);
    leer_ciudad.seekg (0, leer_ciudad.end);
    length = leer_ciudad.tellg();
    leer_ciudad.seekg (0, leer_ciudad.beg);
    string frase;
    
    while (leer_ciudad.is_open()) {
        leer_ciudad.read((char*)&frase,sizeof(string));
        if(frase.find("-")==-1||frase.find("-")==NULL){
            if(frase.find("*")!=-1||frase.find("*")!=NULL){
                this->avail_ciudad.push_back(contador);
            }
        }
        frase="";
        contador++;
        if(leer_ciudad.eof())
            leer_ciudad.close();
    }
    contador=0;
    frase="";
    //--------------------------------------------------------------------------------------
    //ahora crearemos el avail list del registro de llamadas
    ifstream leer_llamada("datollamadas.bin",ios::binary);
    leer_llamada.seekg (0, leer_llamada.end);
    length = leer_llamada.tellg();
    leer_llamada.seekg (0, leer_llamada.beg);
    
    while (leer_llamada.is_open()) {
        leer_llamada.read((char*)&frase,sizeof(string));
        if(frase.find("-")==-1||frase.find("-")==NULL){
            if(frase.find("*")!=-1||frase.find("*")!=NULL){
                this->avail_llamadas.push_back(contador);
            }
        }
        frase="";
        contador++;
        if(leer_llamada.eof())
            leer_llamada.close();
    }
    contador=0;
    
    
    
    
}
void MainWindow::ordenar_indice(){
    
}

void MainWindow::on_cargar_datos_al_sistema_clicked()
{
    //procederemos a cargar los indices de ciudades, clientes y registro de llamadas
    //se verifica si dichos indices existen sino se crean
    cout<<"Empecemos"<<endl;
    ifstream leer_cliente("indice_persona.txt",ios::in);
    if(leer_cliente.is_open()){
        leer_cliente.seekg (0, leer_cliente.end);
        int length = leer_cliente.tellg();
        leer_cliente.seekg (0, leer_cliente.beg);
        string frase2;
        while (leer_cliente.is_open()) {
            
            leer_cliente.read((char*)&frase2,sizeof(string));
            string id_referencia,pos;
            id_referencia=frase2.substr(0,15);
            pos=frase2.substr(15,(frase2.length()-16));
            int id=atoi(id_referencia.c_str());
            int rn=atoi(pos.c_str());
            indice_persona temp(id,rn);
            index_persona.push_back(temp);
            frase2="";
            if(leer_cliente.eof())
                leer_cliente.close();
        }
        cout<<"Indice de persona cargado"<<endl;
        //si el archivo no existe pues no es abierto asi que se debe crear con el siguiente codigo
    }else{
        try{
            string frase2;
            int contador=0;
            string mega="";
            cout<<"NO existe indice... a crearlo"<<endl;
            ifstream leer2("./personas.txt");
            if(leer2.is_open()){
                cout<<"Aqui vamos"<<endl;
                while(!leer2.eof()){
                    cout<<"leyendo"<<endl;
                    // leer2.seekg (0, leer2.end);
                    //int length = leer2.tellg();
                    // leer2.seekg (0, leer2.beg);
                    // leer2.read((char*)&frase2, sizeof (string));
                    leer2>>frase2;
                    cout<<"cogimos linea"<<endl;
                    string lin=frase2;
                    cout<<"pasamos el elemento";
                    cout<<lin<<endl;
                    if(frase2[0]!='-'&&frase2[0]!='*'){
                        for(int i=0; i<15; i++){
                            mega+=frase2[i];
                        }
                        int codex=atoi(mega.c_str());
                        indice_persona sub(codex,contador);
                        index_persona.push_back(sub);
                        cout<<"agregamos un indice"<<endl;
                    }
                    contador++;
                    mega="";
                    frase2="";
                    
                }
                leer2.close();
            }
            cout<<"Indice de persona creado"<<endl;
        }catch(...){
            QMessageBox::information(this,"Informe","Ha ocurrido un error");
        }
    }
    
    //ahora cargaremos el indice de ciudades para trabajar...
    //--------------------------------------------------------------------------------------------------------------------
    /*ifstream leer_ciudad("indice_ciudad.txt",ios::in);
    if(leer_ciudad.is_open()){
        leer_ciudad.seekg (0, leer_ciudad.end);
        int length = leer_ciudad.tellg();
        leer_ciudad.seekg (0, leer_ciudad.beg);
        string frase3;
        while (leer_ciudad.is_open()) {
        
            leer_ciudad.read((char*)&frase3,sizeof(string));
            string id_referencia,pos;
            id_referencia=frase3.substr(0,2);
            pos=frase3.substr(3,(frase3.length()-3));
            int id=atoi(id_referencia.c_str());
            int rn=atoi(pos.c_str());
            indice_ciudad temp(id,rn);
            index_ciudad.push_back(temp);
            frase3="";
            if(leer_ciudad.eof())
                leer_ciudad.close();
        }
        cout<<"Indice de ciudad cargado"<<endl;
        //si el archivo no existe pues no es abierto asi que se debe crear con el siguiente codigo
    }else{
        cout<<"No existe indice de ciudad, se procede acrearlo..."<<endl;
        ifstream leer2("ciudad.txt",ios::in);
        leer2.seekg (0, leer2.end);
        int length = leer2.tellg();
        leer2.seekg (0, leer2.beg);
        string frase2;
        int contador=0;
        while (leer2.is_open()) {
            leer2.read((char*)&frase2,15);
            if(frase2.find("-")==-1||frase2.find("-")==NULL){
                int clave=atoi(frase2.c_str());
                indice_ciudad temp(clave,contador);
                index_ciudad.push_back(temp);
            }
            frase2="";
            contador++;
            if(leer2.eof())
                leer2.close();
        }
        cout<<"Indice de ciudad creado"<<endl;
    }
    cout<<"Termino"<<endl;
    
    //ahora cargaremos el indice de registro de llamadas para trabajar...
    //........................................................................
    //cargamos los indices d eclientes a la tabla de indices de clientes
    cout<<index_persona.size();
    */
    for(int i=0; i<index_persona.size();i++){
        
        indice_persona temp=index_persona.at(i);
        cout<<temp.getID()<<endl;
        ui->tabla_indices_clientes->insertRow(ui->tabla_indices_clientes->rowCount());
        ui->tabla_indices_clientes->setItem(ui->tabla_indices_clientes->rowCount()-1,1,new QTableWidgetItem(temp.getID()));
        ui->tabla_indices_clientes->setItem(ui->tabla_indices_clientes->rowCount()-1,2,new QTableWidgetItem(temp.getRRN()));
    }
    
}

void MainWindow::on_agregar_cliente_clicked()
{
    
}
bool MainWindow::verificar_datos(){
    bool correcto=false;
    int edad;
    int identidad;
    try{
        
        string ed=ui->edad_cliente->text().toStdString();
        edad=atoi(ed.c_str());
        string iden=ui->id_cliente->text().toStdString();
        identidad=atoi(iden.c_str());
        if(ui->nombre_cliente->text().contains("1")||ui->nombre_cliente->text().contains("2")||ui->nombre_cliente->text().contains("3")
                ||ui->nombre_cliente->text().contains("4")||ui->nombre_cliente->text().contains("5")||ui->nombre_cliente->text().contains("6")
                ||ui->nombre_cliente->text().contains("7")||ui->nombre_cliente->text().contains("8")||ui->nombre_cliente->text().contains("9")
                ||ui->nombre_cliente->text().contains("0")){
            QMessageBox::information(this,"Error","El nombre y apellido no debe tener digitos");
        }else{
            if(ui->apellido_cliente->text().contains("1")||ui->apellido_cliente->text().contains("2")||ui->apellido_cliente->text().contains("3")
                    ||ui->apellido_cliente->text().contains("4")||ui->apellido_cliente->text().contains("5")||ui->apellido_cliente->text().contains("6")
                    ||ui->apellido_cliente->text().contains("7")||ui->apellido_cliente->text().contains("8")||ui->apellido_cliente->text().contains("9")
                    ||ui->apellido_cliente->text().contains("0")){
                QMessageBox::information(this,"Error","El nombre y apellido no debe contener numeros");
            }else{
                correcto=true;
            }
        }
    }catch(...){
        QMessageBox::information(this,"Error","Solo debe ingresar numeros en la edad e identidad");
        correcto=false;
    }
    return correcto;
}
bool MainWindow::verificar_indice(){
    bool existe=false;
    string numeros=ui->id_cliente->text().toStdString();
    int clave=atoi(numeros.c_str());
    for(int i=0; i<index_persona.size(); i++){
        
        indice_persona temp=index_persona.at(i);
        
        if(temp.getID()==clave){
            existe=true;
        }
    }
    return existe;
}

void MainWindow::on_competar_registro_cliente_clicked()
{
    string registro;
    string var=ui->tipo_operacion->text().toStdString();
    int tipo=atoi(var.c_str());
    if(ui->nombre_cliente->text().isEmpty()||ui->apellido_cliente->text().isEmpty()||ui->id_cliente->text().isEmpty()|| ui->edad_cliente->text().isEmpty()){
        QMessageBox::information(this,"Error","Debe llenar todos los campos");
    }else{
        if(ui->id_cliente->text().length()!=15){
            QMessageBox::information(this,"Error","El ID debe tener 15 digitos");
        }else{
            if(ui->edad_cliente->text().length()>3){
                QMessageBox::information(this,"Error","La edad no debe ser mayor de 3 digitos");
            }else{
                if(verificar_datos()){
                    int edad;
                    int identidad;
                    
                    string ed=ui->edad_cliente->text().toStdString();
                    edad=atoi(ed.c_str());
                    string iden=ui->id_cliente->text().toStdString();
                    identidad=atoi(iden.c_str());
                    registro="";
                    registro+=iden;
                    registro+=",";
                    registro+=ui->nombre_cliente->text().toStdString();
                    registro+=",";
                    registro+=ui->apellido_cliente->text().toStdString();
                    registro+=",";
                    registro+=ui->sexo_cliente->currentText().toStdString();
                    registro+=",";
                    registro+=ed;
                    if(verificar_indice()==false){
                        indice_persona temp2(identidad,index_persona.size());
                        if(tipo==1){
                            int contador=0;
                            int size=0;
                            this->index_persona.push_back(temp2);
                            if(this->avail_cliente.empty()){
                                
                                string linea;
                                ifstream leer("./personas.txt");
                                if(leer.is_open()){
                                    while(!leer.eof()){
                                        getline(leer,linea);
                                        size+=linea.length();
                                        linea="";
                                        
                                    }
                                    leer.close();
                                }
                                
                            }
                            ofstream escribir("./personas.txt");
                            escribir.seekp(size);
                            escribir<<endl;
                            escribir<<registro;
                            escribir.close();
                            ui->nombre_cliente->setText("");
                            ui->apellido_cliente->setText("");
                            ui->edad_cliente->setText("");
                            ui->id_cliente->setText("");
                            ui->tipo_operacion->setText("1");
                            ui->clave_label->setText("");
                            ui->sexo_label->setText("");
                            QMessageBox::information(this,"Informe","Archivo agregado con exito");
                        }
                        if(tipo==2){
                            string base=ui->clave_label->text().toStdString();
                            int idd=atoi(base.c_str());
                            for(int i=0; i<this->index_persona.size(); i++){
                                indice_persona temp3=this->index_persona.at(i);
                                if(temp3.getID()==idd){
                                    this->index_persona.erase(this->index_persona.begin()+i);
                                }
                            }
                            int size=0;
                            int contador=0;
                            string pos_rrn=ui->number_rrn->text().toStdString();
                            int localizacion=atoi(pos_rrn.c_str());
                            string texto;
                            this->index_persona.push_back(temp2);
                            ifstream leer("./personas.txt");
                            if(leer.is_open()){
                                while(!leer.eof()){
                                    getline(leer,texto);
                                    if(contador<localizacion){
                                        size+=texto.length();
                                    }
                                    contador++;
                                    texto="";
                                    
                                }
                                leer.close();
                            }
                            ofstream escribir("./personas.txt");
                            escribir.seekp(size);
                            escribir<<registro;
                            escribir.close();
                            ui->nombre_cliente->setText("");
                            ui->apellido_cliente->setText("");
                            ui->edad_cliente->setText("");
                            ui->id_cliente->setText("");
                            ui->tipo_operacion->setText("1");
                            ui->clave_label->setText("");
                            ui->sexo_label->setText("");
                            QMessageBox::information(this,"Informe","Archivo modificado con exito");
                            
                        }
                        
                        //ahora procedemos a escribir el nuevo elemento en el archivo
                        // ofstream escritor("./")
                        
                    }
                }else{
                    QMessageBox::information(this,"Error","Dartos erroneos verifica lo siguiente:\n-Digitos solamente en ID y edad\n-15 digitos de de ID\n-1 a 3 digitos en edad\n-nada de numeros en nombre y apellido");
                }
                
                
            }
        }
    }
}

void MainWindow::on_editar_cliente_clicked()
{
    vector<string>elementos;
    string registro;
    string linea;
    int pos=ui->tabla_indices_clientes->currentRow();
    indice_persona temp=index_persona.at(pos);
    int line=temp.getRRN();
    ifstream leer("personas.txt");
    int contador=0;
    if(leer.is_open()){
        while(!leer.eof()){
            getline(leer,linea);
            if(contador==line){
                registro=linea;
            }
            contador++;
            linea="";
        }
    }
    string pedazo="";
    for(int i=0; i<registro.length(); i++){
        if(registro[i]!=','){
            pedazo+=registro[i];
        }else{
            elementos.push_back(pedazo);
            pedazo="";
        }
    }
    string cid=elementos.at(0);
    string cname=elementos.at(1);
    string clast=elementos.at(2);
    string csex=elementos.at(3);
    string cedad=elementos.at(4);
    ui->id_cliente->setText(cid.data());
    ui->nombre_cliente->setText(cname.data());
    ui->apellido_cliente->setText(clast.data());
    ui->edad_cliente->setText(cedad.data());
    ui->tipo_operacion->setText("2");
    ui->number_rrn->setText(""+line);
    ui->sexo_label->setText(csex.data());
    ui->clave_label->setText(cid.data());
    
}
char* MainWindow::lee_palabra(FILE *fichero){
    
    char buffer[15]; /* Cada palabra, de 30 caracteres como máximo */
    
    fgets(buffer,16,fichero); /* Se lee la palabra mediante fgets, se guarda en buffer, 30 caracteres como máximo, del tipo FILE* fichero */
    
    return buffer; /* Devuelve la cadena de caracteres que corresponde a la palabra+caracter de fin de linea */
}

void MainWindow::on_listar_cliente_clicked()
{
    string linea;
    ifstream leer("./personas.txt");
    if(leer.is_open()){
        while(!leer.eof()){
            getline (leer,linea);
            cout << linea << endl;
            
        }
        leer.close();
        QMessageBox::information(this,"Lista de clientes",linea.data());
    }
}

void MainWindow::on_eliminar_cliente_clicked()
{
    if(ui->tabla_indices_clientes->currentRow()<0&&ui->tabla_indices_clientes->currentRow()>(ui->tabla_indices_clientes->rowCount()-1)){
        QMessageBox::information(this,"Advertencia","Debe seleccionar una fila");
    }else{
        QTableWidgetItem* numero_referencia=ui->tabla_indices_clientes->item(ui->tabla_indices_clientes->currentRow(),0);
        string num=numero_referencia->text().toStdString();
        int pos=atoi(num.c_str());
        int contador=0;
        string line;
        string line2;
        int pos2=ui->tabla_indices_clientes->currentRow();
        index_persona.erase(index_persona.begin()+pos2);
        this->avail_cliente.push_back(pos);
        ifstream leer("./personas.txt");
        if(leer.is_open()){
            while(!leer.eof()){
                getline(leer,line);
                if(contador==pos){
                    line2="*";
                    line2+=line;
                }else{
                    line="";
                    contador++;
                }
            }
            leer.close();
        }
        ofstream escribir("./personas.txt");
        //int length=escribir.tellp();
        escribir.seekp((pos-1)*103);
        escribir<<line2;
        QMessageBox::information(this,"Informacion","Registro borrado con exito");
        escribir.close();
        
    }
}
