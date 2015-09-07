#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <vector>
#include "indice_ciudad.h"
#include "indice_llamadas.h"
#include "indice_persona.h"

#include <QMainWindow>
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void ordenar_indice();
    void crear_header();
    void crear_avail_list();
    bool verificar_datos();
    bool verificar_indice();
    void agregar_ordenadamente();
    void setIndice();
    char *lee_palabra(FILE *);
private slots:
    void on_cargar_datos_al_sistema_clicked();

    void on_agregar_cliente_clicked();

    void on_competar_registro_cliente_clicked();

    void on_editar_cliente_clicked();

    void on_listar_cliente_clicked();

    void on_eliminar_cliente_clicked();


private:
    Ui::MainWindow *ui;
    vector <indice_ciudad>index_ciudad;
    vector <indice_persona>index_persona;
    vector <indice_llamadas>index_llamadas;
    vector <int>avail_cliente;
    vector <int>avail_ciudad;
    vector <int>avail_llamadas;
    string cabecera_cliente;
    string cabecera_ciudad;
    string cabecera_llamada;
   // indice_persona temp;
   // indice_ciudad tempc;
    enum columna{
        codigo,posicion
    };
};

#endif // MAINWINDOW_H
