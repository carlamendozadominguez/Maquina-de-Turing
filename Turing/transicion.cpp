#include "estado.cpp"
#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

class Transicion {
  private:
    Estado estado_origen;
    Estado estado_siguiente;

    vector<char> sustitucion;
    vector<char> movimiento;
    vector<char>leido;

  public:

    Transicion();

    Transicion(Estado e1, Estado e2, vector<char> l, vector<char> p,vector<char> m) {
        estado_origen = e1;
        estado_siguiente = e2;

        leido = l;
        sustitucion = p;
        movimiento = m;
    }

    Estado get_estado_origen(){
        return estado_origen;
    }

    Estado get_estado_siguiente(){
        return estado_siguiente;
    }

    char get_leido_pos(int i) {
        return leido[i];
    }
    char get_sustitucion_pos(int i) {
        return sustitucion[i];
    }

    char get_movimiento_pos(int i) {
        return movimiento[i];
    }


    void print() {
        cout << get_estado_origen().get_nombre() << " (" ;

        for(unsigned int i = 0; i < leido.size(); i++) {
            if(i == leido.size()-1)
                cout << leido[i] << ")";
            else
                cout << leido[i] <<",";
        }

        cout<< "= " << get_estado_siguiente().get_nombre() <<"(";

        for(unsigned int i = 0; i < sustitucion.size(); i++) {
            if(i == sustitucion.size()-1)
                cout << sustitucion[i] <<")";
            else
                cout << sustitucion[i] << ",";
        }

        cout<<",(";


        for(unsigned int i = 0; i < movimiento.size(); i++) {
            if(i == movimiento.size()-1)
                cout << movimiento[i] << ")";
            else
                cout << movimiento[i] << ",";
        }
        cout<<endl;
    }
};
