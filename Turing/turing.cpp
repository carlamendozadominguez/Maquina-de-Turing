
#include "cinta.cpp"
#include "transicion.cpp"
#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

class Turing {
  private:
    vector<Estado> estados;
    vector<Transicion> transiciones;
    int n_tran;
    int n_cintas;
    vector<Cinta> cintas;

    Estado estado_actual;

  public:

    Turing(vector<Estado> e, vector<Transicion> t, vector<Cinta> c ) {
        estados = e;
        estado_actual = e[0]; //Deberia ponerse el estado inicial segun el archivo (modificar constructor)
        transiciones = t;
        cintas = c;
    }

    void set_ncinta(int x) {
        n_cintas=x;
    }

    bool ejecutar() {

        bool existe_transicion = true;
        vector<char> elem;

        while(existe_transicion) {

            while(!elem.empty()) {
                elem.pop_back();
            }

            for(int i=0; i<n_cintas; i++)
                elem.push_back(cintas[i].get_cinta_pos(cintas[i].get_cabezal()));
            //Buscamos la proxima transicion con ese simbolo o conjuntos de simbolos.
            existe_transicion = proximaTransicion(elem);

        }

        //Si el estado a donde se llega es final entonces finalizamos
        if(transiciones[n_tran].get_estado_siguiente().get_es_final())
            return true;

        if(!existe_transicion) {
            return false;
        }
    }

    bool proximaTransicion(vector<char> ele) {
        bool aux=false;

        for(unsigned int i = 0; i < transiciones.size(); i++) {
            //Como puede haber mas de una cinta, comparamos los simbolos de ambas cintas.
            if(transiciones[i].get_estado_origen().get_nombre() == estado_actual.get_nombre())
                for(unsigned int j = 0; j < n_cintas; j++) {
                    if(transiciones[i].get_leido_pos(j) == ele[j]) {
                        aux=true;
                    }

                    else {
                        aux = false;
                        j = n_cintas;
                    }
                }

            if(aux == true) {
                cout << "  Estado actual: " << estado_actual.get_nombre();
                cout << "  Leido:" ;

                for(int j = 0; j < ele.size(); j++) {
                    cout << ele[j] <<" ";
                }

                cout << "  --> Transicion: ";
                transiciones[i].print();

                for(unsigned int j=0; j < n_cintas; j++) {

                    cintas[j].set_cinta_pos(cintas[j].get_cabezal(),transiciones[i].get_sustitucion_pos(j));

                    //Segun el movimiento movemos el cabezal a derecha(+1), izquiera(-1) o misma posicion
                    if(transiciones[i].get_movimiento_pos(j) == 'R') {
                        cintas[j].set_cabezal(cintas[j].get_cabezal()+1);
                    }

                    else if(transiciones[i].get_movimiento_pos(j) == 'L') { //mirar si se esta en el borde
                        cintas[j].set_cabezal(cintas[j].get_cabezal()-1);
                    }

                    else if(transiciones[i].get_movimiento_pos(j) == 'S') { //mirar si se esta en el borde
                        cintas[j].set_cabezal(cintas[j].get_cabezal());
                    }

                    //Aqui hacemos la cinta infinita
                    if(cintas[j].get_cabezal() == 0) {
                        cintas[j].insert_blanco();
                        cintas[j].set_cabezal(1);
                    } else if(cintas[j].get_cabezal() == cintas[j].cinta_size()) {

                        cintas[j].push_blanco();
                        cintas[j].set_cabezal(cintas[j].cinta_size()-1);

                    }

                }

                //Ahora el estado actual sera segun la transicion que hayamos elegido
                estado_actual = transiciones[i].get_estado_siguiente();
                n_tran = i;

                return true;
            }
        }

        return false;
    }

    void verTransiociones() {
        for(unsigned int i = 0; i < transiciones.size(); i++) {
            transiciones[i].print();
        }
    }

    void verCinta() {

        cout<<endl<<"CINTA: ";
        for(unsigned int j = 0; j < n_cintas; j++) {
            for(int k = 0; k < cintas[j].cinta_size(); k++) {
                cout << "|" << cintas[j].get_cinta_pos(k) << "";
            }
            cout << "|" << endl << "       ";
        }
        cout << endl;
    }
};
