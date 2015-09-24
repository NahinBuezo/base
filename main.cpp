#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>  
#include <stdlib.h> 
#include <cstdlib> 
#include <sstream>
#include <cmath>
#include <ctgmath>


using namespace std;

vector<string> split(string, char );
struct registro_persona{
	char nombre[50];
	char apellido[50];
	int edad;
	char sexo;
	long long int id_cliente;
	void setnombre(string name){
		for (int i = 0; i < 50; ++i)
		{
			nombre[i]='\0';
		}
		for (int i = 0; i < name.length(); ++i)
		{
			nombre[i]=name[i];
		//	cout<<nombre[i];
		}
		//cout<<endl;
		
	}
	void setapellido(string ape){
		for (int i = 0; i < 50; ++i)
		{
			apellido[i]='\0';
		}
		for (int i = 0; i < ape.length(); ++i)
		{
			apellido[i]=ape[i];
			//cout<<apellido[i];

		}
		//cout<<apellido<<endl;
		
	}
	void setide(long long int x){
		id_cliente=x;
		//cout<<id_cliente<<endl;		
	}
	void setedad(int x){
		edad=x;
	}

	void setsexo(char x){
		sexo=x;
	}
	

};
struct registro_ciudad{
	char nombre[50];
	int codigo;
	void setnombre(string name){
		for (int i = 0; i < name.length(); ++i)
		{
			nombre[i]=name[i];
		}
	}
	void setcodigo(int x){
		codigo=x;
	}
};
struct linea_telefonica{
	int numero;
	int id_cliente;
	void setnumero(int x){
		numero=x;
	}
	void setid(int x){
		id_cliente=x;
	}
};
struct cabecera_cliente{
	char info[200];

	
	void setinfo(string x){
		for (int i = 0; i < 200; i++){
			info[i]=' ';
		}
		for (int i = 0; i < x.length(); i++)
		{
			info[i]=x[i];
		}
	}


};
struct cabecera_ciudad{
	char info[200];
	void setinfo(string x){
		for (int i = 0; i < 200; ++i)
		{
			info[i]=' ';
		}
		for (int i = 0; i < x.length(); ++i)
		{
			info[i]=x[i];
		}
	}


};
struct cabecera_linea{
	char info[200];
	void setinfo(string x){
		for (int i = 0; i < x.length(); ++i)
		{
			info[i]=x[i];
		}
	}


};
struct indice_persona{
	long long int id;
	int posicion;
	void setid(long long int x){
		id=x;
	}
	void setpos(int x){
		posicion=x;
	}
};
struct indice_ciudad{
	int id;
	int posicion;
	void setid(int x){
		id=x;
	}
	void setpos(int x){
		posicion=x;
	}
};
//*****************************************CLASE NODO******************************************************
class nodo_cliente{
	indice_persona* keys;
	int size;
	nodo_cliente **c;
	int n;
	bool hoja;
public:
	nodo_cliente(int size, bool hoja);
	//void insertar(indice_persona);
	void insertNonFull(indice_persona indice);
	void splitchild(int i, nodo_cliente *node);
	void traverse();
	nodo_cliente *buscar(indice_persona indice);
	friend class btree_cliente;
};
//******************************************FIN CLASE NODO*************************************************
//******************************************ARBOL B DE CLIENTES********************************************
class btree_cliente{
	nodo_cliente *root;
	int minimum_degree;
public:
	btree_cliente(int t){
		root=NULL;
		minimum_degree=t;
	}
	void traverse(){
		if(root!=NULL){
			root->traverse();
		}
	}
	nodo_cliente *buscar(indice_persona indice){
		return(root==NULL)? NULL : root->buscar(indice);
	}
	void insertar(indice_persona indice);
};
//******************************************FIN DE ARBOL DE CLIENTES****************************************
//constructor de la clase nodo de cliente
nodo_cliente::nodo_cliente(int t, bool leaf){
	size=t;
	hoja=leaf;
	keys=new indice_persona[2*size-1];
	c=new nodo_cliente *[2*size];
	n=0;//numero de llaves
	
}//*************************FIN CONSTRUCTOR*******************************

void nodo_cliente::traverse(){
	int i;
	for (i = 0; i < n; i++){
		if(hoja==false){
			c[i]->traverse();
			//cout<<" "<<keys[i]<<endl;
		}
	}
	if(hoja==false){
		c[i]->traverse();
	}
}//fin de traverse
nodo_cliente *nodo_cliente::buscar(indice_persona indice){
	int i=0;
	indice_persona temp=keys[i];
	while(i<n && indice.id > temp.id){
		temp=keys[i];
		i++;
	}
	if(temp.id==indice.id)
		return this;

	if(hoja==true)
		return NULL;

	return c[i]->buscar(indice);
}//fin funcion buscar

void btree_cliente::insertar(indice_persona indice){
	//si el arbol esta vacio
	if(root==NULL){
		root=new nodo_cliente(minimum_degree,true);
		root->keys[0]=indice;
		root->n=1;
	}else{
		if(root->n==2*minimum_degree-1){
			nodo_cliente *nuevo_nodo=new nodo_cliente(minimum_degree, false);
			nuevo_nodo->c[0]=root;
			nuevo_nodo->splitchild(0, root);

			int i=0;
			indice_persona temp=nuevo_nodo->keys[0];
			if(temp.id < indice.id){
				i++;
			}
			nuevo_nodo->c[i]->insertNonFull(indice);
			root=nuevo_nodo;
		}else{
			root->insertNonFull(indice);
		}
	}
}//fin funcion insertar
void nodo_cliente::insertNonFull(indice_persona indice){
	int i=n-1;	//inicilizamos la posicion con uno a la derecha
	indice_persona temp=keys[i];
	//se buscara la posicion para la nueva llave
	//de ser necesaario de moveran las demas llaves
	if(hoja==true){
		while(i>=0 && temp.id > indice.id){
			keys[i+1]=keys[i];
			i--;
		}
		keys[i+1]=indice;
		n=n+1;
	}else{
		while(i>=0 && temp.id > indice.id){
			i--;
		}
		if(c[i+1]->n==2*size-1){
			splitchild(i+1, c[i+1]);
			temp=keys[i+1];
			if(temp.id < indice.id){
				i++;
			}
		}
		c[i+1]->insertNonFull(indice);
	}

}//fin funcion insertNonFull

void nodo_cliente::splitchild(int i, nodo_cliente *y){
	nodo_cliente *nuevo_nodo=new nodo_cliente(y->size, y->hoja);
	nuevo_nodo->n=size-1;

	//se copia la ultima llave de y en nuevo_nodo
	for (int j = 0; j < size-1; j++){
		nuevo_nodo->keys[j]=y->keys[j+size];
	}
	if(y->hoja==false){
		for (int j = 0; j < size; j++){
			nuevo_nodo->c[j]=y->c[j+size];
		}
	}
	//reducimos el numero de llaves en y
	y->n=size-1;

	//este nodo tendra nuevos hijo asi que tenemos que crear nuevo espacio
	for (int j = n; j>= i+1; j--){
		c[j+1]=c[j];		
	}
	//ahora enlazamos el nuevo hijo con este nodo
	c[i+1]=nuevo_nodo;
	//se movera una llave de este nodo asi que tenemos que mover una posicion a las demas llaves
	for (int j = n-1; j>=i; j--){
		keys[j+1]=keys[j];
	}
	//copiamos la llave en enmedio de y a este nodo
	keys[i]=y->keys[size-1];
	//aumentamos el numero de llaves de este nodo
	n=n+1;
}//fin de metodo splitchild

//******************************************Main demas cosas***********************************************
//Aqui estan las funciones para trabajar
string regitro_temporal;
vector<indice_persona>indice_clientes;
vector<indice_ciudad>indice_ciudades;
btree_cliente mytree(10);
void editar_cliente();
void editar_ciudad();
void agregar_cliente();
void agregar_ciudad();
void eliminar_cliente();
void eliminar_ciudad();
void cargar_indice_cliente();
void cargar_indice_ciudad();
bool verificar_indice(long double,int);
int busqueda_binaria(long double);
void ordenar_indice_cliente();
void intercambiar_indice_cliente(indice_persona,indice_persona,int,int);
void ordenar_indice_ciudad();
void intercambiar_indice_ciudad();
void listar_clientes();
vector<string> split(string,char );
int main(int argc,char** argv){
	int opcion=1;
	cout<<"Se cargara el indice de clientes"<<endl;
	cargar_indice_cliente();
	cout<<"Se cargo el indice de clientes"<<endl;
	while(opcion>0){
		cout<<"Menu Principal\n"<<"1. Clientes\n2. Ciudades\n3. Lineas\n0. Salir"<<endl;
		cin>>opcion;
		if(opcion==1){
			int opcion_cliente=1;
			while(opcion_cliente>0){
				cout<<"Menu Cliente\n1. Agregar cliente\n2. Editar cliente\n3. Eliminar cliente\n4. Listar clientes\n0. Salir";
				cout<<endl;
				cin>>opcion_cliente;
				if(opcion_cliente==1){
					agregar_cliente();
				}
				if(opcion_cliente==2){
					editar_cliente();
				}
				if(opcion_cliente==3){
					eliminar_cliente();
				}
				if(opcion_cliente==4){
					listar_clientes();
				}
			}
		}

	}
}//fin de main
void cargar_indice_cliente(){
	ifstream fichero("./indice_cliente.txt");
	long long int llave;
	int posicion;
	vector<string>elementos;
	if(fichero.is_open()){
		 while (! fichero.eof() ) {
		 		string frase;
	            getline (fichero,frase);
	            vector<string>partes=split(frase,',');
	            string clave=partes.at(0);
	            llave=atoll(clave.c_str());
	            string pos=partes.at(1);
	            posicion=atoi(pos.c_str());
	            indice_persona temp;
	            temp.setid(llave);
	            temp.setpos(posicion);
	            indice_clientes.push_back(temp);
	        }
	        fichero.close();

	  	
	}else{
		int contador=0;
		ifstream lectura("./clientes.txt");
		if(lectura.is_open()){
			while (! lectura.eof() ) {
		 		string frase;
	            getline (lectura,frase);
	            vector<string>partes=split(frase,',');
	            if(partes.size()>1){
		            if(contador!=0){
		            	string clave=partes.at(0);
			            llave=atof(clave.c_str());
			            indice_persona temp;
			            temp.setid(llave);
			            temp.setpos(contador);
			            indice_clientes.push_back(temp);

		        	}
	        	}
	        	contador++;
	        }
	        lectura.close();

		}
		ordenar_indice_cliente();
		for (int i = 0; i < indice_clientes.size(); ++i)
		{
			indice_persona t=indice_clientes.at(i);
			cout<<t.id<<" "<<t.posicion<<endl;
		}

	}
	for (int i = 0; i < indice_clientes.size(); ++i){
		indice_persona t=indice_clientes.at(i);
		mytree.insertar(t);
	}

	cout<<"***INDICE DE CLIENTES CARGADO CON EXITO***"<<endl;
}
void cargar_indice_ciudad(){
	ifstream fichero("./indice_ciudad.txt");
	int llave;
	int posicion;
	vector<string>elementos;
	if(fichero.is_open()){
		 while (! fichero.eof() ) {
		 		string frase;
	            getline (fichero,frase);
	            vector<string>partes=split(frase,',');
	            string clave=partes.at(0);
	            llave=atoi(clave.c_str());
	            string pos=partes.at(1);
	            posicion=atoi(pos.c_str());
	            indice_ciudad temp;
	            temp.setid(llave);
	            temp.setpos(posicion);
	            indice_ciudades.push_back(temp);
	        }
	        fichero.close();

	  	
	}else{
		int contador=0;
		ifstream lectura("./cities.txt");
		if(lectura.is_open()){
			while (! lectura.eof() ) {
		 		string frase;
	            getline (lectura,frase);
	            vector<string>partes=split(frase,',');
	            if(contador!=0){
	            	string clave=partes.at(0);
		            llave=atoi(clave.c_str());
		            indice_ciudad temp;
		            temp.setid(llave);
		            temp.setpos(contador);
		            indice_ciudades.push_back(temp);
	        	}
	        	contador++;
	        }
	        lectura.close();

		}
	}
	cout<<"***INDICE DE CIUDADES CARGADO CON EXITO***"<<endl;
}//fin indice de ciudades

void agregar_cliente(){
	
	try{
		string header;
		long double id;
		string nombre;
		string apellido;
		string detalles="";
		bool correcto=true;
		char sexo;
		int edad;
		cout<<"Ingrese identidad del cliente: "<<endl;
		cin>>id;
		cout<<"Ingrese nombre del cliente: "<<endl;
		cin>>nombre;
		cout<<"Ingrese apellido del cliente: "<<endl;
		cin>>apellido;
		cout<<"Ingrese sexo del cliente (M/F): "<<endl;
		cin>>sexo;
		cout<<"Ingrese edad del cliente (solo digitos): "<<endl;
		cin>>edad;
		if(sexo!='m'&&sexo!='M'&&sexo!='f'&&sexo!='F'){
			detalles+="Solo puede ingresar la letra M o F en sexo del cliente\n";
			correcto=false;
		}
		if(edad>100){
			detalles+="La edad no puede exceder los 100\n";
			correcto=false;
		}
		if(correcto==false){
			cout<<"---ERROR EN EL PROCESAMIENTO DE DATOS---\n"<<detalles<<endl;
			cout<<"---------------FIN REPORTE DE ERROR-----------------"<<endl;
		}else{
			
			ifstream fichero("./clientes.txt");
			getline(fichero,header);
			fichero.close();
			vector<string>elementos=split(header,',');
			string numero=elementos.at(0);
			int pos=atoi(numero.c_str());
			registro_persona temp;
			temp.setnombre(nombre);
			temp.setapellido(apellido);
			temp.setide(id);
			temp.setsexo(sexo);
			temp.setedad(edad);
			char registro[sizeof(registro_persona)];
			for (int i = 0; i < sizeof(registro_persona); ++i)
			{
				registro[i]=' ';
			}
			string regis="";
			regis+=static_cast<std::ostringstream*>(&(std::ostringstream() << temp.id_cliente))->str();
			regis+=",";
			regis+=temp.nombre;
			regis+=",";
			regis+=temp.apellido;
			regis+=",";
			regis+=static_cast<std::ostringstream*>(&(std::ostringstream() << temp.sexo))->str();
			regis+=",";
			regis+=static_cast<std::ostringstream*>(&(std::ostringstream() << temp.edad))->str();
			//verificamos si la identidad ingresada no esta en index
			if(!verificar_indice(id,1)){
				for (int i = 0; i < regis.length(); ++i)
				{
					registro[i]=regis[i];
				}
				fstream editor;
				if(pos==-1){
					cout<<"No hay espacio en el avail list"<<endl;
					editor.open("./clientes.txt",std::ofstream::out | std::ofstream::app);
					editor.write((char*)registro,sizeof(registro_persona));
					editor.close();
					indice_persona nuevo_indice;
					nuevo_indice.setid(id);
					nuevo_indice.setpos(indice_clientes.size());
					indice_clientes.push_back(nuevo_indice);
					
				}else{
					int nuevo_espacio;
					char refe[sizeof(registro_persona)];
					editor.open("./clientes.txt",ios::in|ios::out);
					if(editor.is_open()){
						editor.seekg((sizeof(cabecera_cliente)+(sizeof(registro_persona)*(pos-1))));
						editor.read(refe,sizeof(registro_persona));
						char r=refe[0];
						string posi="";
						posi+=r;
						nuevo_espacio=atoi(posi.c_str());

					}
					editor.close();
					editor.open("./clientes.txt",ios::out|ios::in);
					if(editor.is_open()){
						editor.seekp((sizeof(cabecera_cliente)+(sizeof(registro_persona)*(pos-1))));
						editor.write((char*)registro,sizeof(registro_persona));
					}
					editor.close();
					indice_persona nuevo_indice;
					nuevo_indice.setid(id);
					nuevo_indice.setpos(pos);
					indice_clientes.push_back(nuevo_indice);
				
				}
				ordenar_indice_cliente();
				cout<<"---REGISTRO DE CLIENTE COMPLETADO CON EXITO---"<<endl;
			}else{
				cout<<"----EL ID INGRESADO YA EXISTE-----"<<endl;
			}
		}
	}catch(...){
		cout<<"---ERROR EN EL INGRESO DE DATOS---"<<endl;
	}
}
void editar_cliente(){
	string codigo;
	long double clave;
	bool correcto=true;
	string detalles="";
	try{
		cout<<"Ingrese la identidad del cliente a editar: "<<endl;
		cin>>codigo;
		clave=atof(codigo.c_str());
		cout<<clave<<endl;
		int pos=busqueda_binaria(clave);
		cout<<"Resultado de busqueda_binaria "<<pos<<endl;
		if(pos!=-1){
			string nombre;
			string apellido;
			char sexo;
			int edad;
			long double id;
			cout<<"Ingrese id del cliente: "<<endl;
			cin>>id;
			cout<<"Ingrese nombre del cliente: "<<endl;
			cin>>nombre;
			cout<<"Ingrese apellido del cliente: "<<endl;
			cin>>apellido;
			cout<<"Ingrese sexo del cliente (M/F): "<<endl;
			cin>>sexo;
			cout<<"Ingrese edad del cliente: "<<endl;
			cin>>edad;
			if(sexo!='m'&&sexo!='M'&&sexo!='f'&&sexo!='F'){
				detalles+="Solo puede ingresar la letra M o F en sexo del cliente\n";
				correcto=false;
			}
			if(edad>100){
				detalles+="La edad no puede exceder los 100\n";
				correcto=false;
			}
			if(correcto==false){
				cout<<"---ERROR DE PROCESAMIENTO DE DATOS----\n"<<detalles<<endl;
			}else{
				indice_persona tempo=indice_clientes.at(pos);
				int rrn=tempo.posicion;
				char refe[sizeof(registro_persona)];
				//borramos el indice 
				indice_clientes.erase(indice_clientes.begin()+pos);
				registro_persona temp;
				temp.setnombre(nombre);
				temp.setapellido(apellido);
				temp.setide(id);
				temp.setsexo(sexo);
				temp.setedad(edad);
				char registro[sizeof(registro_persona)];
				for (int i = 0; i < sizeof(registro_persona); ++i)
				{
					registro[i]=' ';
				}
				string regis="";
				regis+=static_cast<std::ostringstream*>(&(std::ostringstream() << temp.id_cliente))->str();
				regis+=",";
				regis+=temp.nombre;
				regis+=",";
				regis+=temp.apellido;
				regis+=",";
				regis+=static_cast<std::ostringstream*>(&(std::ostringstream() << temp.sexo))->str();
				regis+=",";
				regis+=static_cast<std::ostringstream*>(&(std::ostringstream() << temp.edad))->str();
				if(!verificar_indice(id,1)){
					for (int i = 0; i < regis.length(); ++i){
						registro[i]=regis[i];
					}
					fstream editor;
					editor.open("./clientes.txt",ios::out|ios::in);
					if(editor.is_open()){
						editor.seekp((sizeof(cabecera_cliente)+(sizeof(registro_persona)*(rrn-1))));
						editor.write((char*)registro,sizeof(registro_persona));
					}
					editor.close();
					indice_persona nuevo_indice;
					nuevo_indice.setid(id);
					nuevo_indice.setpos(rrn);
					indice_clientes.push_back(nuevo_indice);
				}
			}//fin else
			cout<<"---EDITADO DE CLIENTE COMPLATADO EXITOSAMENTE---"<<endl;
			ordenar_indice_cliente();
			
		}else{
			cout<<"***EL ID QUE UD INGRESO NO EXISTE EN EL SISTEMA***"<<endl;
		}
	}catch(...){
		cout<<"---ERROR EN EL PROCESO DE EDITADO DE CLIENTE---"<<endl;
	}
}
void eliminar_cliente(){
	long double clave;
	try{
		cout<<"Ingrese el ID del cliente a borrar de la base de datos (13 digitos): "<<endl;
		cin>>clave;
		int pos=busqueda_binaria(clave);
		if(pos==-1){
			cout<<"---EL ID QUE UD INGRESO NO SE ENCUENTRA EN EL SISTEMA"<<endl;
		}else{
			indice_persona temp=indice_clientes.at(pos);
			int rrn=temp.posicion;
			int antigua_posicion;
			string info_cabecera="";
			info_cabecera+=static_cast<std::ostringstream*>(&(std::ostringstream() << rrn))->str();
			info_cabecera+=",Header_cliente,";
			info_cabecera+="registros,";
			info_cabecera+= static_cast<std::ostringstream*>(&(std::ostringstream() << (indice_clientes.size()-1)))->str();
			info_cabecera+=",";
			char nuevo_header[sizeof(cabecera_cliente)];
			for (int i = 0; i < sizeof(cabecera_cliente); ++i)
			{
				 nuevo_header[i]=' ';
			}
			for (int i = 0; i < info_cabecera.length(); ++i)
			{
				nuevo_header[i]=info_cabecera[i];
			}
			//leeremos el header para extraer el numero de avail list y modificarlo
			fstream editor;
			editor.open("./clientes.txt",ios::in|ios::out);
			if(editor.is_open()){
				string frase;
				getline (editor,frase);
				vector<string>elementos=split(frase,',');
				string numero=elementos.at(0);
				antigua_posicion=atoi(numero.c_str());
				editor.close();
			}
			//actualizamos el header con los nuevos datos
			editor.open("./clientes.txt",ios::out|ios::in);
			if(editor.is_open()){
				editor.seekp(0,editor.beg);
				editor.write((char*)nuevo_header,sizeof(cabecera_cliente));
				editor.close();
			}
			string eliminado="";
			eliminado+="*,";
			eliminado+=static_cast<std::ostringstream*>(&(std::ostringstream() << antigua_posicion))->str();
			eliminado+=",";
			char borrado[sizeof(registro_persona)];
			for (int i = 0; i < sizeof(registro_persona); ++i)
			{
				borrado[i]='-';
			}
			for (int i = 0; i < eliminado.length(); ++i)
			{
				borrado[i]=eliminado[i];
			}
			editor.open("./clientes.txt",ios::out|ios::in);
			if(editor.is_open()){
				editor.seekp((sizeof(cabecera_cliente)+(sizeof(registro_persona)*(rrn-1))));
				editor.write((char*)borrado,sizeof(registro_persona));
				editor.close();
			}
			indice_clientes.erase(indice_clientes.begin()+pos);
			ordenar_indice_cliente();
			cout<<"-----ELIMINADO DE CLIENTE COMPLETADO-----"<<endl;

		}

	}catch(...){
		cout<<"***ERROR DE BUSQUEDA***"<<endl;
	}

}//fin eliminado de cliente
bool verificar_indice(long double llave,int tipo){
	bool existe=false;
	if(tipo==1){
		for (int i = 0; i <indice_clientes.size(); ++i)
		{
			indice_persona temp=indice_clientes.at(i);
			if(temp.id==llave){
				existe=true;
			}
		}
	}
	if(tipo==2){
		for (int i = 0; i <indice_ciudades.size(); ++i){
			indice_ciudad temp=indice_ciudades.at(i);
			if(temp.id==llave){
				existe=true;
			}
		}
	}
	return existe;
}

int busqueda_binaria(long double clave){
	int Iarriba = indice_clientes.size()-1;
  	int Iabajo = 0;
  	int Icentro;
  	int valor=-1;
  	for (int i = 0; i < indice_clientes.size(); ++i)
  	{
  		indice_persona temp=indice_clientes.at(i);
  		if (temp.id-clave==0){
 			valor= i;
 			cout<<valor<<endl;;
     	}
  	}
  	/*while (Iabajo <= Iarriba){
      	Icentro = (Iarriba + Iabajo)/2;
      	indice_persona temp=indice_clientes.at(Icentro);
      	if (temp.id == clave){
 			valor= Icentro;
 			cout<<"Valor";
     	}else{
 			if (clave < temp.id){
   				Iarriba=Icentro-1;
 			}else{
   				Iabajo=Icentro+1;
 			}
      	}
	}*/
  	return valor;;
}
void listar_clientes(){
	ifstream leer("./clientes.txt");
	string registro;
	cout<<"-----------------REGISTRO DE CLIENTES-------------------------"<<endl;
	if(leer.is_open()){
		while (! leer.eof() ) {
	        getline (leer,registro);
	        cout<<registro<<endl;
	    }
	    leer.close();

	}
	cout<<"----------------FIN REGISTROS DE CLIENTES--------------------------"<<endl;
}

void ordenar_indice_cliente(){
	for (int i = 0; i< indice_clientes.size()-1 ; i++){
    	for (int j = 0; j< indice_clientes.size()-1 ; j++){
    		indice_persona temp=indice_clientes.at(j);
    		indice_persona temp2=indice_clientes.at(j+1);
      		if (temp.id > temp2.id){
 				intercambiar_indice_cliente(temp,temp2,j,(j+1));
      		}
    	}
	}
}
void intercambiar_indice_cliente(indice_persona a,indice_persona b,int x,int y){
	indice_clientes[x]=b;
	indice_clientes[y]=a;
}


vector<string> split(string str, char delimiter) {
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;
  
  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }
  
  return internal;
}
