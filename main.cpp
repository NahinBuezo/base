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

//::::::::::::IMPORTANTE::::::::::
//para compilar debe usar g++ -std=c++0x...
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
	char info[20];
	int numero;
	long long int id;
	void setnumero(int x){
		numero=x;
	}
	void setid(long long int x){
		id=x;
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
struct indice_linea{
	int rrn;
	int llave;
	void setrrn(int x){
		rrn=x;
	}
	void setllave(int x){
		llave=x;
	}
};
//*****************************************CLASE NODO PARA CLIENTE******************************************************
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
	indice_persona getIndice(long long int indice);
	nodo_cliente* buscar(long long int indice);
	friend class btree_cliente;
	friend class main;
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
	nodo_cliente* buscar(long long int indice){
		return root->buscar(indice);
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
nodo_cliente *nodo_cliente::buscar(long long int indice){
	int i=0;
	indice_persona temp=keys[i];
	while(i<n && indice > temp.id){
		temp=keys[i];
		i++;
	}
	if(temp.id==indice)
		return this;

	if(hoja==true)
		return NULL;

	return c[i]->buscar(indice);
}//fin funcion buscar
indice_persona nodo_cliente::getIndice(long long int indice){
	indice_persona correcta;
	for (int h = 0; h < size; h++)
	{
		indice_persona temp=keys[h];
		if(indice==temp.id)
			correcta=keys[h];
	}
	return correcta;
}

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

//:::::::::::::::::::::::::::::::::VAMOS CON ARBOL B PARA CIUDADES:::::::::::::::::::::::::::::::::::::::::
class nodo_ciudad{
	indice_ciudad* keys;
	int size;
	nodo_ciudad **c;
	int n;
	bool hoja;
public:
	nodo_ciudad(int size, bool hoja);
	//void insertar(indice_persona);
	void insertNonFull(indice_ciudad indice);
	void splitchild(int i, nodo_ciudad *node);
	void traverse();
	indice_ciudad getIndice(int indice);
	nodo_ciudad* buscar(int indice);
	friend class btree_ciudad;
	friend class main;
};
class btree_ciudad{
	nodo_ciudad *root;
	int minimum_degree;
public:
	btree_ciudad(int t){
		root=NULL;
		minimum_degree=t;
	}
	void traverse(){
		if(root!=NULL){
			root->traverse();
		}
	}
	nodo_ciudad* buscar(int indice){
		cout<<"Haber"<<endl;
		return root->buscar(indice);
	}
	void insertar(indice_ciudad indice);
};
//constructor de la clase nodo de ciudad
nodo_ciudad::nodo_ciudad(int t, bool leaf){
	size=t;
	hoja=leaf;
	keys=new indice_ciudad[2*size-1];
	c=new nodo_ciudad *[2*size];
	n=0;//numero de llaves
	
}//*************************FIN CONSTRUCTOR*******************************
void nodo_ciudad::traverse(){
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
nodo_ciudad *nodo_ciudad::buscar(int indice){
	int i=0;
	indice_ciudad temp=keys[i];
	while(i<n && indice > temp.id){
		temp=keys[i];
		i++;
	}
	if(temp.id==indice)
		return this;

	if(hoja==true)
		return NULL;

	return c[i]->buscar(indice);
}//fin funcion buscar
indice_ciudad nodo_ciudad::getIndice(int indice){
	indice_ciudad correcta;
	for (int h = 0; h < size; h++)
	{
		indice_ciudad temp=keys[h];
		if(indice==temp.id)
			correcta=keys[h];
	}
	return correcta;
}

void btree_ciudad::insertar(indice_ciudad indice){
	//si el arbol esta vacio
	if(root==NULL){
		root=new nodo_ciudad(minimum_degree,true);
		root->keys[0]=indice;
		root->n=1;
	}else{
		if(root->n==2*minimum_degree-1){
			nodo_ciudad *nuevo_nodo=new nodo_ciudad(minimum_degree, false);
			nuevo_nodo->c[0]=root;
			nuevo_nodo->splitchild(0, root);

			int i=0;
			indice_ciudad temp=nuevo_nodo->keys[0];
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
void nodo_ciudad::insertNonFull(indice_ciudad indice){
	int i=n-1;	//inicilizamos la posicion con uno a la derecha
	indice_ciudad temp=keys[i];
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
void nodo_ciudad::splitchild(int i, nodo_ciudad *y){
	nodo_ciudad *nuevo_nodo=new nodo_ciudad(y->size, y->hoja);
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
//::::::::::::::::::::::::::::::::::::::FIN DEL ARBOL DE CIUDADES::::::::::::::::::::::::::::::::::::::::::

//::::::::::::::::::::::::::::::::::::::::::ARBOL DE LINEA TELEFONICA::::::::::::::::::::::::::::::::::::::
class nodo_linea{
	indice_linea* keys;
	int size;
	nodo_linea **c;
	int n;
	bool hoja;
public:
	nodo_linea(int size, bool hoja);
	//void insertar(indice_persona);
	void insertNonFull(indice_linea indice);
	void splitchild(int i, nodo_linea *node);
	void traverse();
	indice_linea getIndice(int indice);
	nodo_linea* buscar(int indice);
	friend class btree_linea;
	friend class main;
};
class btree_linea{
	nodo_linea *root;
	int minimum_degree;
public:
	btree_linea(int t){
		root=NULL;
		minimum_degree=t;
	}
	void traverse(){
		if(root!=NULL){
			root->traverse();
		}
	}
	nodo_linea* buscar(int indice){
		cout<<"Haber"<<endl;
		return root->buscar(indice);
	}
	void insertar(indice_linea indice);
};
//constructor de la clase nodo de linea telefonica
nodo_linea::nodo_linea(int t, bool leaf){
	size=t;
	hoja=leaf;
	keys=new indice_linea[2*size-1];
	c=new nodo_linea *[2*size];
	n=0;//numero de llaves
	
}//*************************FIN CONSTRUCTOR*******************************
void nodo_linea::traverse(){
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
nodo_linea *nodo_linea::buscar(int indice){
	int i=0;
	indice_linea temp=keys[i];
	while(i<n && indice > temp.llave){
		temp=keys[i];
		i++;
	}
	if(temp.llave==indice)
		return this;

	if(hoja==true)
		return NULL;

	return c[i]->buscar(indice);
}//fin funcion buscar
indice_linea nodo_linea::getIndice(int indice){
	indice_linea correcta;
	for (int h = 0; h < size; h++)
	{
		indice_linea temp=keys[h];
		if(indice==temp.llave)
			correcta=keys[h];
	}
	return correcta;
}

void btree_linea::insertar(indice_linea indice){
	//si el arbol esta vacio
	if(root==NULL){
		root=new nodo_linea(minimum_degree,true);
		root->keys[0]=indice;
		root->n=1;
	}else{
		if(root->n==2*minimum_degree-1){
			nodo_linea *nuevo_nodo=new nodo_linea(minimum_degree, false);
			nuevo_nodo->c[0]=root;
			nuevo_nodo->splitchild(0, root);

			int i=0;
			indice_linea temp=nuevo_nodo->keys[0];
			if(temp.llave < indice.llave){
				i++;
			}
			nuevo_nodo->c[i]->insertNonFull(indice);
			root=nuevo_nodo;
		}else{
			root->insertNonFull(indice);
		}
	}
}//fin funcion insertar
void nodo_linea::insertNonFull(indice_linea indice){
	int i=n-1;	//inicilizamos la posicion con uno a la derecha
	indice_linea temp=keys[i];
	//se buscara la posicion para la nueva llave
	//de ser necesaario de moveran las demas llaves
	if(hoja==true){
		while(i>=0 && temp.llave > indice.llave){
			keys[i+1]=keys[i];
			i--;
		}
		keys[i+1]=indice;
		n=n+1;
	}else{
		while(i>=0 && temp.llave > indice.llave){
			i--;
		}
		if(c[i+1]->n==2*size-1){
			splitchild(i+1, c[i+1]);
			temp=keys[i+1];
			if(temp.llave < indice.llave){
				i++;
			}
		}
		c[i+1]->insertNonFull(indice);
	}

}//fin funcion insertNonFull
void nodo_linea::splitchild(int i, nodo_linea *y){
	nodo_linea *nuevo_nodo=new nodo_linea(y->size, y->hoja);
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
//:::::::::::::::::::::::::::::::::::::::::::::::FIN DE ARBOL DE LINEA TELEFONICA:::::::::::::::::::::::::

//******************************************Main demas cosas***********************************************
//Aqui estan las funciones para trabajar
string regitro_temporal;
vector<indice_persona>indice_clientes;
vector<indice_ciudad>indice_ciudades;
vector<indice_linea>indice_lineas;
btree_cliente mytree(10);
btree_ciudad tree_ciudad(5);
btree_linea tree_linea(100);
void editar_cliente();
void editar_ciudad();
void agregar_cliente();
void agregar_ciudad();
void eliminar_cliente();
void eliminar_ciudad();
void cargar_indice_cliente();
void cargar_indice_ciudad();
bool verificar_indice(long long int);
bool verificar_indice_ciudad(int);
bool verificar_indice_linea(int);
int busqueda_binaria(long long int);
int busqueda_binaria_ciudad(int);
void ordenar_indice_cliente();
void intercambiar_indice_cliente(indice_persona,indice_persona,int,int);
void ordenar_indice_ciudad();
void intercambiar_indice_ciudad(indice_ciudad,indice_ciudad,int,int);
void listar_clientes();
void listar_ciudades();
void cargar_indice_lineas();
void agregar_linea();
void editar_linea();
void eliminar_linea();
vector<string> split(string,char );
void ordenar_indice_linea();
void intercambiar_indice_linea(indice_linea,indice_linea,int,int);
int busqueda_binaria_linea(int);

//:::::::::::::::::::::::::::::::::::::MAIN:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
int main(int argc,char** argv){
	int opcion=1;
	cout<<"Se cargara el indice de clientes"<<endl;
	cargar_indice_cliente();
	cout<<"Se cargara el indice de ciudades"<<endl;
	cargar_indice_ciudad();
	cout<<"Se cargara el indice de lineas telefonicas"<<endl;
	cargar_indice_lineas();
	while(opcion>0){
		cout<<"Menu Principal\n"<<"1. Clientes\n2. Ciudades\n3. Lineas\n0. Salir"<<endl;
		cin>>opcion;
		if(opcion==1){
			int opcion_cliente=1;
			while(opcion_cliente>0){
				cout<<"Menu Cliente\n1. Agregar cliente\n2. Editar cliente\n3. Eliminar cliente\n4. Listar clientes\n5. Busqueda por arbol\n0. Salir";
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
				if(opcion_cliente==5){
					long long int id;
					try{
						cout<<"Ingrese la identidad del cliente: "<<endl;
						cin>>id;
						nodo_cliente *temporal=mytree.buscar(id);
						if(temporal==NULL){
							//cout<<"Indice no escontrado, intente de nuevo"<<endl;
						}else{
							indice_persona elegido=temporal->getIndice(id);
							cout<<"Encontrado CLAVE: "<<elegido.id<<" RRN: "<<elegido.posicion<<endl;
							int rrn=elegido.id;
							fstream leer;
							leer.open("./clientes.txt",ios::in|ios::out);
							if(leer.is_open()){
								char informacion[sizeof(registro_persona)];
								leer.seekg((sizeof(cabecera_cliente)+(sizeof(registro_persona)*(rrn-1))));
								leer.read(informacion,sizeof(registro_persona));
								cout<<informacion<<endl;
								leer.close();
							}
						}
					}catch(...){
						cout<<"SOLO INGRESE DIGITOS"<<endl;
					}
				}
			}
		}//fin opcion cliente
		if(opcion==2){
			int opcion_ciudad=1;
			try{
				while(opcion_ciudad!=0){
					cout<<"Menu de ciudades\n1. Agregar ciudad\n2. Editar ciudad\n3. Eliminar ciudad\n4. Busqueda por arbol\n0. Salir"<<endl;
					cin>>opcion_ciudad;
					if(opcion_ciudad==1){
						agregar_ciudad();
					}
					if(opcion_ciudad==2){
						editar_ciudad();
					}
					if(opcion_ciudad==3){
						eliminar_ciudad();
					}
					if(opcion_ciudad==4){
						int id;
						try{
							cout<<"Ingrese el codigo de ciudad: "<<endl;
							cin>>id;
							nodo_ciudad *temporal=tree_ciudad.buscar(id);
							if(temporal==NULL){
								cout<<"Indice no escontrado, intente de nuevo"<<endl;
							}else{
								indice_ciudad elegido=temporal->getIndice(id);
								cout<<"Encontrado CLAVE: "<<elegido.id<<" RRN: "<<elegido.posicion<<endl;
								int rrn=elegido.id;
								fstream leer;
								leer.open("./cities.txt",ios::in|ios::out);
								if(leer.is_open()){
									char informacion[sizeof(registro_ciudad)];
									leer.seekg((sizeof(cabecera_ciudad)+(sizeof(registro_ciudad)*(rrn-1))));
									leer.read(informacion,sizeof(registro_ciudad));
									cout<<informacion<<endl;
									leer.close();
								}
							}
						}catch(...){
							cout<<"SOLO INGRESE DIGITOS"<<endl;
						}
					}
				}
			}catch(...){
				cout<<"ERROR EN LA SELECCION DE MENU"<<endl;
			}
		}//fin opcion de ciudad
		if(opcion==3){
			int opcion_linea=1;
			while(opcion_linea!=0){
				cout<<"Menu De Linea Telefonica\n1. Agregar linea\n2. Editar Linea\n3. Eliminar linea\n4. Busqueda de arbol\n0. salir"<<endl;
				cin>>opcion_linea;
				if(opcion_linea==1){
					agregar_linea();
				}
				if(opcion_linea==2){
					editar_linea();
				}
				if(opcion_linea==3){
					eliminar_linea();
				}
				if(opcion_linea==4){
					int id;
					try{
						cout<<"Ingrese el numero de la linea: "<<endl;
						cin>>id;
						nodo_linea *temporal=tree_linea.buscar(id);
						if(temporal==NULL){
							//cout<<"Indice no escontrado, intente de nuevo"<<endl;
						}else{
							indice_linea elegido=temporal->getIndice(id);
							cout<<"Encontrado CLAVE: "<<elegido.llave<<" RRN: "<<elegido.rrn<<endl;
							int rrn=elegido.rrn;
							fstream leer;
							leer.open("./lineas_telefonicas.txt",ios::in|ios::out);
							if(leer.is_open()){
								char informacion[sizeof(linea_telefonica)];
								leer.seekg((sizeof(cabecera_linea)+(sizeof(linea_telefonica)*(rrn-1))));
								leer.read(informacion,sizeof(linea_telefonica));
								cout<<informacion<<endl;
								leer.close();
							}
						}
					}catch(...){
						cout<<"SOLO INGRESE DIGITOS"<<endl;
					}
				}//fin opcion de linea
			}
		}

	}
}//fin de main
//::::::::::::::::::::::::::::::::::FIN MAIN::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
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
			//cout<<t.id<<" "<<t.posicion<<endl;
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
	            tree_ciudad.insertar(temp);
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
	            if(partes.size()>1){
		            if(contador!=0){
		            	string clave=partes.at(0);
			            llave=atof(clave.c_str());
			            indice_ciudad temp;
			            temp.setid(llave);
			            temp.setpos(contador);
			            tree_ciudad.insertar(temp);
			            indice_ciudades.push_back(temp);

		        	}
	        	}
	        	contador++;
	        }
	        lectura.close();

		}
	}
	cout<<"***INDICE DE CIUDADES CARGADO CON EXITO***"<<endl;
}//fin indice de ciudades
void cargar_indice_lineas(){
	ifstream fichero("./indice_linea.txt");
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
	            indice_linea temp;
	            temp.setllave(llave);
	            temp.setrrn(posicion);
	            tree_linea.insertar(temp);
	            indice_lineas.push_back(temp);
	    }
	    fichero.close();
	}else{
		int contador=0;
		ifstream lectura("./lineas_telefonicas.txt");
		if(lectura.is_open()){
			while (! lectura.eof() ) {
		 		string frase;
	            getline (lectura,frase);
	            vector<string>partes=split(frase,',');
	            if(partes.size()>1){
		            if(contador!=0){
		            	string clave=partes.at(0);
			            llave=atoi(clave.c_str());
			            indice_linea temp;
			            temp.setllave(llave);
			            temp.setrrn(contador);
			            tree_linea.insertar(temp);
			            indice_lineas.push_back(temp);

		        	}
	        	}
	        	contador++;
	        }
	        lectura.close();

		}
	}
	cout<<"***INDICE DE LINEAS TELEFONICAS CARGADO CON EXITO***"<<endl;
}

void agregar_cliente(){
	
	try{
		string header;
		long long int id;
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
			if(!verificar_indice(id)){
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
					mytree.insertar(nuevo_indice);
					//hay que actualizar el header
					string nuevo_header="-1,Header_cliente,numero_registro,";
					nuevo_header+=static_cast<std::ostringstream*>(&(std::ostringstream() << indice_clientes.size()))->str();
					nuevo_header+=",size de registro,";
					nuevo_header+=static_cast<std::ostringstream*>(&(std::ostringstream() << sizeof(registro_persona)))->str();
					char header_nuevo[sizeof(cabecera_cliente)];
					for (int i = 0; i < sizeof(cabecera_cliente); ++i)
					{
						header_nuevo[i]=' ';
					}
					for (int i = 0; i < nuevo_header.length(); ++i)
					{
						header_nuevo[i]=nuevo_header[i];
					}
					editor.open("./clientes.txt",std::ofstream::out | std::ofstream::app);
					editor.write((char*)header_nuevo,sizeof(cabecera_cliente));
					editor.close();
					
				}else{
					int nuevo_espacio;
					char refe[sizeof(registro_persona)];
					editor.open("./clientes.txt",ios::in|ios::out);
					if(editor.is_open()){
						editor.seekg((sizeof(cabecera_cliente)+(sizeof(registro_persona)*(pos-1))));
						editor.read(refe,sizeof(registro_persona));
						char r=refe[0];
						string base(refe);
						vector<string>elementos=split(base, ',');
						string posi=elementos.at(0);
						nuevo_espacio=atoi(posi.c_str());

					}
					editor.close();
					editor.open("./clientes.txt",ios::out|ios::in);
					if(editor.is_open()){
						int length=(sizeof(cabecera_cliente)+(sizeof(registro_persona)*(pos-1)));
						editor.seekp((length-sizeof(registro_persona)));
						//editor<<endl;
						editor.write((char*)registro,sizeof(registro_persona));
					}

					editor.close();
					//hay que actualizar el header
					string nuevo_header="";
					nuevo_header+=static_cast<std::ostringstream*>(&(std::ostringstream() << nuevo_espacio))->str();
					nuevo_header+=",Header_cliente,numero_registro,";
					nuevo_header+=static_cast<std::ostringstream*>(&(std::ostringstream() << indice_clientes.size()))->str();
					nuevo_header+=",size de registro,";
					nuevo_header+=static_cast<std::ostringstream*>(&(std::ostringstream() << sizeof(registro_persona)))->str();
					char header_nuevo[sizeof(cabecera_cliente)];
					for (int i = 0; i < sizeof(cabecera_cliente); ++i)
					{
						header_nuevo[i]=' ';
					}
					for (int i = 0; i < nuevo_header.length(); ++i)
					{
						header_nuevo[i]=nuevo_header[i];
					}
					editor.open("./clientes.txt",std::ofstream::out | std::ofstream::app);
					editor.write((char*)header_nuevo,sizeof(cabecera_cliente));
					editor.close();
					indice_persona nuevo_indice;
					nuevo_indice.setid(id);
					nuevo_indice.setpos(pos);
					indice_clientes.push_back(nuevo_indice);
					mytree.insertar(nuevo_indice);
				
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
	long long int clave;
	bool correcto=true;
	string detalles="";
	long long int id;
	int pos;//posicion en el archivo 
	try{
		cout<<"Ingrese la identidad del cliente a editar: "<<endl;
		cin>>codigo;
		clave=atoll(codigo.c_str());
		cout<<clave<<endl;
		nodo_cliente *temporal=mytree.buscar(id);
		indice_persona elegido=temporal->getIndice(id);
		int rrn=elegido.id;
		pos=rrn;
		if(pos!=-1){
			string nombre;
			string apellido;
			char sexo;
			int edad;
			long long int id;
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
				if(!verificar_indice(id)){
					for (int i = 0; i < regis.length(); ++i){
						registro[i]=regis[i];
					}
					fstream editor;
					editor.open("./clientes.txt",ios::out|ios::in);
					if(editor.is_open()){
						int length=(sizeof(cabecera_cliente)+(sizeof(registro_persona)*(rrn-1)));
						editor.seekp((length-sizeof(registro_persona)));
						//editor<<endl;
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
	long long int clave;
	string cod;
	try{
		cout<<"Ingrese el ID del cliente a borrar de la base de datos (13 digitos): "<<endl;
		cin>>cod;
		clave=atoll(cod.c_str());
		nodo_cliente *temporal=mytree.buscar(clave);
		indice_persona elegido=temporal->getIndice(clave);
		int rrn=elegido.posicion;
		int pos=rrn;
		if(pos==-1){
			cout<<"---EL ID QUE UD INGRESO NO SE ENCUENTRA EN EL SISTEMA"<<endl;
		}else{
			
			int antigua_posicion;
			string info_cabecera="";
			info_cabecera+=static_cast<std::ostringstream*>(&(std::ostringstream() << rrn))->str();
			info_cabecera+=",Header_cliente,";
			info_cabecera+="registros,";
			info_cabecera+= static_cast<std::ostringstream*>(&(std::ostringstream() << (indice_clientes.size()-1)))->str();
			info_cabecera+=",";
			char nuevo_header[sizeof(cabecera_cliente)];
			cout<<"bien"<<endl;
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
			cout<<"vamos bien"<<endl;
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
bool verificar_indice(long long int llave){
	bool existe=false;
	for (int i = 0; i <indice_clientes.size(); ++i){
		indice_persona temp=indice_clientes.at(i);
		if(temp.id==llave){
			existe=true;
		}
	}
	
	return existe;
}
bool verificar_indice_ciudad(int llave){
	bool existe=false;
	for (int i = 0; i <indice_ciudades.size(); ++i){
		indice_ciudad temp=indice_ciudades.at(i);
		if(temp.id==llave){
			existe=true;
		}
	}
	return existe;
}
bool verificar_indice_linea(int llave){
	bool existe=false;
	for (int i = 0; i <indice_lineas.size(); ++i){
		indice_linea temp=indice_lineas.at(i);
		if(temp.llave==llave){
			existe=true;
		}
	}
	return existe;
}

int busqueda_binaria(long long int clave){
	int Iarriba = indice_clientes.size()-1;
  	int Iabajo = 0;
  	int Icentro;
  	int valor=-1;
  	/*for (int i = 0; i < indice_clientes.size(); ++i)
  	{
  		indice_persona temp=indice_clientes.at(i);
  		if (temp.id-clave==0){
 			valor= i;
 			cout<<valor<<endl;;
     	}
  	}*/
  	while (Iabajo <= Iarriba){
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

	}
	return valor;
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

//::::::::::::::::::::::::::FUNCIONES PARA CIUDADES:::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void agregar_ciudad(){

	try{
		string header;
		int id;
		string nombre;
		string detalles="";
		bool correcto=true;
		cout<<"Ingrese codigo de la ciudad: "<<endl;
		cin>>id;
		cout<<"Ingrese nombre de la ciudad: "<<endl;
		cin>>nombre;
		if(correcto==false){
			cout<<"---ERROR EN EL PROCESAMIENTO DE DATOS---\n"<<detalles<<endl;
			cout<<"---------------FIN REPORTE DE ERROR-----------------"<<endl;
		}else{
			
			ifstream fichero("./cities.txt");
			getline(fichero,header);
			fichero.close();
			vector<string>elementos=split(header,',');
			string numero=elementos.at(0);
			int pos=atoi(numero.c_str());
			registro_ciudad temp;
			temp.setnombre(nombre);
			temp.setcodigo(id);
			char registro[sizeof(registro_ciudad)];
			for (int i = 0; i < sizeof(registro_ciudad); ++i)
			{
				registro[i]=' ';
			}
			string regis="";
			regis+=static_cast<std::ostringstream*>(&(std::ostringstream() << temp.codigo))->str();
			regis+=",";
			regis+=temp.nombre;
			regis+=",";
			//verificamos si la identidad ingresada no esta en index
			if(!verificar_indice(id)){
				for (int i = 0; i < regis.length(); ++i)
				{
					registro[i]=regis[i];
				}
				fstream editor;
				if(pos==-1){
					cout<<"No hay espacio en el avail list"<<endl;
					editor.open("./cities.txt",std::ofstream::out | std::ofstream::app);
					editor.write((char*)registro,sizeof(registro_ciudad));
					editor.close();
					indice_ciudad nuevo_indice;
					nuevo_indice.setid(id);
					nuevo_indice.setpos(indice_ciudades.size());
					indice_ciudades.push_back(nuevo_indice);
					tree_ciudad.insertar(nuevo_indice);

					//hay que actualizar el header
					string nuevo_header="-1,Header_ciudad,numero_registro,";
					nuevo_header+=static_cast<std::ostringstream*>(&(std::ostringstream() << indice_ciudades.size()))->str();
					nuevo_header+=",size de registro,";
					nuevo_header+=static_cast<std::ostringstream*>(&(std::ostringstream() << sizeof(registro_ciudad)))->str();
					char header_nuevo[sizeof(cabecera_ciudad)];
					for (int i = 0; i < sizeof(cabecera_ciudad); ++i)
					{
						header_nuevo[i]=' ';
					}
					for (int i = 0; i < nuevo_header.length(); ++i)
					{
						header_nuevo[i]=nuevo_header[i];
					}
					editor.open("./clientes.txt",std::ofstream::out | std::ofstream::app);
					editor.write((char*)header_nuevo,sizeof(cabecera_ciudad));
					editor.close();
				}else{
					int nuevo_espacio;
					char refe[sizeof(registro_ciudad)];
					editor.open("./cities.txt",ios::in|ios::out);
					if(editor.is_open()){
						editor.seekg((sizeof(cabecera_ciudad)+(sizeof(registro_ciudad)*(pos-1))));
						editor.read(refe,sizeof(registro_ciudad));
						char r=refe[0];
						string base(refe);
						vector<string>elementos=split(base,',');
						string posi=elementos.at(0);
						nuevo_espacio=atoi(posi.c_str());

					}
					editor.close();
					editor.open("./cities.txt",ios::out|ios::in);
					if(editor.is_open()){
						int length=(sizeof(cabecera_ciudad)+(sizeof(registro_ciudad)*(pos-1)));
						editor.seekp((length-sizeof(registro_ciudad)));
						//editor<<endl;
						editor.write((char*)registro,sizeof(registro_ciudad));
					}
					editor.close();
					//hay que actualizar el header
					string nuevo_header="";
					nuevo_header+=static_cast<std::ostringstream*>(&(std::ostringstream() << nuevo_espacio))->str();
					nuevo_header+=",Header_cliente,numero_registro,";
					nuevo_header+=static_cast<std::ostringstream*>(&(std::ostringstream() << indice_ciudades.size()))->str();
					nuevo_header+=",size de registro,";
					nuevo_header+=static_cast<std::ostringstream*>(&(std::ostringstream() << sizeof(registro_ciudad)))->str();
					char header_nuevo[sizeof(cabecera_ciudad)];
					for (int i = 0; i < sizeof(cabecera_ciudad); ++i)
					{
						header_nuevo[i]=' ';
					}
					for (int i = 0; i < nuevo_header.length(); ++i)
					{
						header_nuevo[i]=nuevo_header[i];
					}
					editor.open("./clientes.txt",std::ofstream::out | std::ofstream::app);
					editor.write((char*)header_nuevo,sizeof(cabecera_ciudad));
					editor.close();
			
					indice_ciudad nuevo_indice;
					nuevo_indice.setid(id);
					nuevo_indice.setpos(pos);
					indice_ciudades.push_back(nuevo_indice);
					tree_ciudad.insertar(nuevo_indice);
				
				}
				ordenar_indice_ciudad();
				cout<<"---REGISTRO DE CIUDAD COMPLETADO CON EXITO---"<<endl;
			}else{
				cout<<"----EL ID INGRESADO YA EXISTE-----"<<endl;
			}
		}
	}catch(...){
		cout<<"---ERROR EN EL INGRESO DE DATOS---"<<endl;
	}
}
void editar_ciudad(){
	string codigo;
	int clave;
	bool correcto=true;
	string detalles="";
	try{
		cout<<"Ingrese la identidad del cliente a editar: "<<endl;
		cin>>codigo;
		clave=atoi(codigo.c_str());
		nodo_ciudad *temporal=tree_ciudad.buscar(clave);
		indice_ciudad elegido=temporal->getIndice(clave);
		int rrn=elegido.id;
		int pos=rrn;
		if(pos!=-1){
			string nombre;
			int id;
			cout<<"Ingrese codigo de la ciudad: "<<endl;
			cin>>id;
			cout<<"Ingrese nombre de la ciudad: "<<endl;
			cin>>nombre;
			if(correcto==false){
				cout<<"---ERROR DE PROCESAMIENTO DE DATOS----\n"<<detalles<<endl;
			}else{
				indice_ciudad tempo=indice_ciudades.at(pos);
				int rrn=tempo.posicion;
				char refe[sizeof(registro_ciudad)];
				//borramos el indice 
				indice_ciudades.erase(indice_ciudades.begin()+pos);
				registro_ciudad temp;
				temp.setnombre(nombre);
				temp.setcodigo(id);
				char registro[sizeof(registro_ciudad)];
				for (int i = 0; i < sizeof(registro_ciudad); ++i)
				{
					registro[i]=' ';
				}
				string regis="\n";
				regis+=static_cast<std::ostringstream*>(&(std::ostringstream() << temp.codigo))->str();
				regis+=",";
				regis+=temp.nombre;
				//regis+=",";
				if(!verificar_indice_ciudad(id)){
					for (int i = 0; i < regis.length(); ++i){
						registro[i]=regis[i];
					}
					fstream editor;
					editor.open("./cities.txt",ios::out|ios::in);
					if(editor.is_open()){
						int length=(sizeof(cabecera_ciudad)+(sizeof(registro_ciudad)*(rrn-1)));
						editor.seekp((length-sizeof(registro_ciudad)));
						//editor<<endl;
						editor.write((char*)registro,sizeof(registro_ciudad));
					}
					editor.close();
					indice_ciudad nuevo_indice;
					nuevo_indice.setid(id);
					nuevo_indice.setpos(rrn);
					indice_ciudades.push_back(nuevo_indice);
				}
			}//fin else
			cout<<"---EDITADO DE CIUDAD COMPLATADO EXITOSAMENTE---"<<endl;
			ordenar_indice_ciudad();
			
		}else{
			cout<<"***EL ID QUE UD INGRESO NO EXISTE EN EL SISTEMA***"<<endl;
		}
	}catch(...){
		cout<<"---ERROR EN EL PROCESO DE EDITADO DE CIUDAD---"<<endl;
	}
}
void eliminar_ciudad(){
	int clave;
	try{
		cout<<"Ingrese el codigo de la ciudad a borrar: "<<endl;
		cin>>clave;
		nodo_ciudad *temporal=tree_ciudad.buscar(clave);
		indice_ciudad elegido=temporal->getIndice(clave);
		int rrn=elegido.id;
		int pos=rrn;
		if(pos==-1){
			cout<<"---EL ID QUE UD INGRESO NO SE ENCUENTRA EN EL SISTEMA"<<endl;
		}else{
			indice_ciudad temp=indice_ciudades.at(pos);
			int rrn=temp.posicion;
			int antigua_posicion;
			string info_cabecera="";
			info_cabecera+=static_cast<std::ostringstream*>(&(std::ostringstream() << rrn))->str();
			info_cabecera+=",Header_ciudad,";
			info_cabecera+="registros,";
			info_cabecera+= static_cast<std::ostringstream*>(&(std::ostringstream() << (indice_ciudades.size()-1)))->str();
			info_cabecera+=",";
			char nuevo_header[sizeof(cabecera_ciudad)];
			for (int i = 0; i < sizeof(cabecera_ciudad); ++i)
			{
				 nuevo_header[i]=' ';
			}
			for (int i = 0; i < info_cabecera.length(); ++i)
			{
				nuevo_header[i]=info_cabecera[i];
			}
			//leeremos el header para extraer el numero de avail list y modificarlo
			fstream editor;
			editor.open("./cities.txt",ios::in|ios::out);
			if(editor.is_open()){
				string frase;
				getline (editor,frase);
				vector<string>elementos=split(frase,',');
				string numero=elementos.at(0);
				antigua_posicion=atoi(numero.c_str());
				editor.close();
			}
			//actualizamos el header con los nuevos datos
			editor.open("./cities.txt",ios::out|ios::in);
			if(editor.is_open()){
				editor.seekp(0,editor.beg);
				editor.write((char*)nuevo_header,sizeof(cabecera_ciudad));
				editor.close();
			}
			string eliminado="";
			eliminado+="*,";
			eliminado+=static_cast<std::ostringstream*>(&(std::ostringstream() << antigua_posicion))->str();
			eliminado+=",";
			char borrado[sizeof(registro_ciudad)];
			for (int i = 0; i < sizeof(registro_ciudad); ++i)
			{
				borrado[i]='-';
			}
			for (int i = 0; i < eliminado.length(); ++i)
			{
				borrado[i]=eliminado[i];
			}
			editor.open("./cities.txt",ios::out|ios::in);
			if(editor.is_open()){
				editor.seekp((sizeof(cabecera_ciudad)+(sizeof(registro_ciudad)*(rrn-1))));
				editor.write((char*)borrado,sizeof(registro_ciudad));
				editor.close();
			}
			indice_ciudades.erase(indice_ciudades.begin()+pos);
			ordenar_indice_ciudad();
			cout<<"-----ELIMINADO DE CIUDAD COMPLETADO-----"<<endl;

		}

	}catch(...){
		cout<<"***ERROR DE BUSQUEDA***"<<endl;
	}
}
int busqueda_binaria_ciudad(int clave){
	int Iarriba = indice_ciudades.size()-1;
  	int Iabajo = 0;
  	int Icentro;
  	int valor=-1;
  	while (Iabajo <= Iarriba){
      	Icentro = (Iarriba + Iabajo)/2;
      	indice_ciudad temp=indice_ciudades.at(Icentro);
      	if (temp.id == clave){
 			valor= Icentro;
 			
     	}else{
 			if (clave < temp.id){
   				Iarriba=Icentro-1;
 			}else{
   				Iabajo=Icentro+1;
 			}
      	}

	}
	return valor;
}
void ordenar_indice_ciudad(){
	for (int i = 0; i< indice_ciudades.size()-1 ; i++){
    	for (int j = 0; j< indice_ciudades.size()-1 ; j++){
    		indice_ciudad temp=indice_ciudades.at(j);
    		indice_ciudad temp2=indice_ciudades.at(j+1);
      		if (temp.id > temp2.id){
 				intercambiar_indice_ciudad(temp,temp2,j,(j+1));
      		}
    	}
	}
}
void intercambiar_indice_ciudad(indice_ciudad a,indice_ciudad b,int x,int y){
	indice_ciudades[x]=b;
	indice_ciudades[y]=a;
}
void agregar_linea(){
	try{
		string header;
		int id;
		int  numero;
		string detalles="";
		bool correcto=true;
		cout<<"Ingrese numero de la linea: "<<endl;
		cin>>numero;
		cout<<"Ingrese ID del cliente: "<<endl;
		cin>>id;
		if(correcto==false){
			cout<<"---ERROR EN EL PROCESAMIENTO DE DATOS---\n"<<detalles<<endl;
			cout<<"---------------FIN REPORTE DE ERROR-----------------"<<endl;
		}else{
			
			ifstream fichero("./lineas_telefonicas.txt");
			getline(fichero,header);
			fichero.close();
			vector<string>elementos=split(header,',');
			string numero=elementos.at(0);
			int num=atoi(numero.c_str());
			int pos=atoi(numero.c_str());
			linea_telefonica temp;
			temp.setnumero(num);
			temp.setid(id);
			char registro[sizeof(linea_telefonica)];
			for (int i = 0; i < sizeof(linea_telefonica); ++i)
			{
				registro[i]=' ';
			}
			string regis="";
			regis+=static_cast<std::ostringstream*>(&(std::ostringstream() << temp.numero))->str();
			regis+=",";
			regis+=static_cast<std::ostringstream*>(&(std::ostringstream() << temp.id))->str();
			regis+=",";
			//verificamos si la identidad ingresada no esta en index
			if(!verificar_indice_linea(id)){
				for (int i = 0; i < regis.length(); ++i)
				{
					registro[i]=regis[i];
				}
				fstream editor;
				if(pos==-1){
					cout<<"No hay espacio en el avail list"<<endl;
					editor.open("./lineas_telefonicas.txt",std::ofstream::out | std::ofstream::app);
					editor.write((char*)registro,sizeof(linea_telefonica));
					editor.close();
					indice_linea nuevo_indice;
					nuevo_indice.setllave(id);
					nuevo_indice.setrrn(indice_lineas.size());
					indice_lineas.push_back(nuevo_indice);
					tree_linea.insertar(nuevo_indice);
					
				}else{
					int nuevo_espacio;
					char refe[sizeof(linea_telefonica)];
					editor.open("./lineas_telefonicas.txt",ios::in|ios::out);
					if(editor.is_open()){
						editor.seekg((sizeof(cabecera_linea)+(sizeof(linea_telefonica)*(pos-1))));
						editor.read(refe,sizeof(linea_telefonica));
						char r=refe[0];
						string posi(refe);
						vector<string>elementos=split(posi,',');
						string espacio=elementos.at(0);
						nuevo_espacio=atoi(espacio.c_str());

					}
					editor.close();
					editor.open("./lineas_telefonicas.txt",ios::out|ios::in);
					if(editor.is_open()){
						int length=(sizeof(cabecera_linea)+(sizeof(linea_telefonica)*(pos-1)));
						editor.seekp((length-sizeof(linea_telefonica)));
						//editor<<endl;
						editor.write((char*)registro,sizeof(linea_telefonica));
					}
					editor.close();
					indice_linea nuevo_indice;
					nuevo_indice.setllave(id);
					nuevo_indice.setrrn(pos);
					indice_lineas.push_back(nuevo_indice);
					tree_linea.insertar(nuevo_indice);
				
				}
				ordenar_indice_linea();
				cout<<"---REGISTRO DE LINEA COMPLETADO CON EXITO---"<<endl;
			}else{
				cout<<"----EL ID INGRESADO YA EXISTE-----"<<endl;
			}
		}
	}catch(...){
		cout<<"---ERROR EN EL INGRESO DE DATOS---"<<endl;
	}

}
void editar_linea(){
	string codigo;
	int clave;
	bool correcto=true;
	string detalles="";
	try{
		cout<<"Ingrese el numero de la linea a editar: "<<endl;
		cin>>codigo;
		clave=atoi(codigo.c_str());
		nodo_linea *temporal=tree_linea.buscar(clave);
		indice_linea elegido=temporal->getIndice(clave);
		int rrn=elegido.rrn;
		int pos=rrn;
		if(pos!=-1){
			int numero;
			int id;
			cout<<"Ingrese numero de la linea: "<<endl;
			cin>>numero;
			cout<<"Ingrese Id de la linea: "<<endl;
			cin>>id;
			if(correcto==false){
				cout<<"---ERROR DE PROCESAMIENTO DE DATOS----\n"<<detalles<<endl;
			}else{
				indice_linea tempo=indice_lineas.at(pos);
				int rrn=tempo.rrn;
				char refe[sizeof(linea_telefonica)];
				//borramos el indice 
				indice_lineas.erase(indice_lineas.begin()+pos);
				linea_telefonica temp;
				temp.setnumero(numero);
				temp.setid(id);
				char registro[sizeof(linea_telefonica)];
				for (int i = 0; i < sizeof(linea_telefonica); ++i)
				{
					registro[i]=' ';
				}
				string regis="";
				regis+=static_cast<std::ostringstream*>(&(std::ostringstream() << temp.numero))->str();
				regis+=",";
				regis+=static_cast<std::ostringstream*>(&(std::ostringstream() << temp.id))->str();
				regis+=",";
				if(!verificar_indice_linea(id)){
					for (int i = 0; i < regis.length(); ++i){
						registro[i]=regis[i];
					}
					fstream editor;
					editor.open("./lineas_telefonicas.txt",ios::out|ios::in);
					if(editor.is_open()){
						int length=(sizeof(cabecera_linea)+(sizeof(linea_telefonica)*(rrn-1)));
						editor.seekp((length-sizeof(linea_telefonica)));
						//editor<<endl;
						editor.write((char*)registro,sizeof(linea_telefonica));
					}
					editor.close();
					indice_linea nuevo_indice;
					nuevo_indice.setllave(id);
					nuevo_indice.setrrn(rrn);
					indice_lineas.push_back(nuevo_indice);
				}
			}//fin else
			cout<<"---EDITADO DE LINEA COMPLATADO EXITOSAMENTE---"<<endl;
			ordenar_indice_linea();
			
		}else{
			cout<<"***EL ID QUE UD INGRESO NO EXISTE EN EL SISTEMA***"<<endl;
		}
	}catch(...){
		cout<<"---ERROR EN EL PROCESO DE EDITADO DE LINEA---"<<endl;
	}
}
void eliminar_linea(){
	int clave;
	try{
		cout<<"Ingrese el numero telefonico de la linea a borrar: "<<endl;
		cin>>clave;
		nodo_linea *temporal=tree_linea.buscar(clave);
		indice_linea elegido=temporal->getIndice(clave);
		int rrn=elegido.rrn;
		int pos=rrn;
		if(pos==-1){
			cout<<"---EL ID QUE UD INGRESO NO SE ENCUENTRA EN EL SISTEMA"<<endl;
		}else{
			indice_linea temp=indice_lineas.at(pos);
			int rrn=temp.rrn;
			int antigua_posicion;
			string info_cabecera="";
			info_cabecera+=static_cast<std::ostringstream*>(&(std::ostringstream() << rrn))->str();
			info_cabecera+=",Header_ciudad,";
			info_cabecera+="registros,";
			info_cabecera+= static_cast<std::ostringstream*>(&(std::ostringstream() << (indice_lineas.size()-1)))->str();
			info_cabecera+=",";
			char nuevo_header[sizeof(cabecera_linea)];
			for (int i = 0; i < sizeof(cabecera_linea); ++i)
			{
				 nuevo_header[i]=' ';
			}
			for (int i = 0; i < info_cabecera.length(); ++i)
			{
				nuevo_header[i]=info_cabecera[i];
			}
			//leeremos el header para extraer el numero de avail list y modificarlo
			fstream editor;
			editor.open("./lineas_telefonicas.txt",ios::in|ios::out);
			if(editor.is_open()){
				string frase;
				getline (editor,frase);
				vector<string>elementos=split(frase,',');
				string numero=elementos.at(0);
				antigua_posicion=atoi(numero.c_str());
				editor.close();
			}
			//actualizamos el header con los nuevos datos
			editor.open("./lineas_telefonicas.txt",ios::out|ios::in);
			if(editor.is_open()){
				editor.seekp(0,editor.beg);
				editor.write((char*)nuevo_header,sizeof(cabecera_linea));
				editor.close();
			}
			string eliminado="";
			eliminado+="*,";
			eliminado+=static_cast<std::ostringstream*>(&(std::ostringstream() << antigua_posicion))->str();
			eliminado+=",";
			char borrado[sizeof(linea_telefonica)];
			for (int i = 0; i < sizeof(linea_telefonica); ++i)
			{
				borrado[i]='-';
			}
			for (int i = 0; i < eliminado.length(); ++i)
			{
				borrado[i]=eliminado[i];
			}
			editor.open("./lineas_telefonicas.txt",ios::out|ios::in);
			if(editor.is_open()){
				editor.seekp((sizeof(cabecera_linea)+(sizeof(linea_telefonica)*(rrn-1))));
				editor.write((char*)borrado,sizeof(linea_telefonica));
				editor.close();
			}
			indice_lineas.erase(indice_lineas.begin()+pos);
			ordenar_indice_linea();
			cout<<"-----ELIMINADO DE LINEA COMPLETADO-----"<<endl;

		}

	}catch(...){
		cout<<"***ERROR DE BUSQUEDA***"<<endl;
	}
}
void ordenar_indice_linea(){
	for (int i = 0; i< indice_lineas.size()-1 ; i++){
    	for (int j = 0; j< indice_lineas.size()-1 ; j++){
    		indice_linea temp=indice_lineas.at(j);
    		indice_linea temp2=indice_lineas.at(j+1);
      		if (temp.llave > temp2.llave){
 				intercambiar_indice_linea(temp,temp2,j,(j+1));
      		}
    	}
	}

}
void intercambiar_indice_linea(indice_linea a,indice_linea b,int x,int y){
	indice_lineas[x]=b;
	indice_lineas[y]=a;
}
int busqueda_binaria_linea(int clave){
	int Iarriba = indice_lineas.size()-1;
  	int Iabajo = 0;
  	int Icentro;
  	int valor=-1;
  	while (Iabajo <= Iarriba){
      	Icentro = (Iarriba + Iabajo)/2;
      	indice_linea temp=indice_lineas.at(Icentro);
      	if (temp.llave == clave){
 			valor= Icentro;
 			cout<<"Valor";
     	}else{
 			if (clave < temp.llave){
   				Iarriba=Icentro-1;
 			}else{
   				Iabajo=Icentro+1;
 			}
      	}

	}
	return valor;
}

