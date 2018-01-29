#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "turing.cpp"

using namespace std;

//Comprobamos que el simbolo este en el alfabeto
bool comprobar(char simbolo,vector<string> alfabet,int n_transicion) {
    string sim(1,simbolo);

    if(find(alfabet.begin(),alfabet.end(),sim) == alfabet.end()) {
        cout << endl << "MODIFIQUE EL FICHERO:";
        cout << "Error en la transicion " << n_transicion << endl;
        return false;
    }

    return true;
}

//Separamos un string que tiene varias palabras
vector<string> separar_string(string v) {

    vector<string> vector;
    string item;
    char delim = ' ';
    stringstream aux(v);

    while (getline(aux, item, delim)) {
        vector.push_back(item);
    }

    return vector;
}

int main() {

    char fichero_t[50];
    cout << "Introduce un fichero: ";
    cin >> fichero_t;
    cout << "\x1B[2J\x1B[H";

    string dummy=" ";
    char delim = ' ',aux;
    string est_actual,estado_next,item;
    vector<char> simbolo,simbolo_sustitucion,movimientos;
    int pos,pos2,n_transicion = 0,n_cintas = 0;
    string ite,s;
    vector<Estado> estado;
    vector<Transicion> t;
    vector<Cinta> ci;

    ifstream fich;
    fich.open(fichero_t);

    if(fich.is_open()) {

        getline(fich,dummy);

        //Si encontramos un comentario ignoramos esa linea
        while(dummy[0] == '#') {
            getline(fich,dummy);
        }

        //Separamos nuestro dummy en palabras individuales
        vector<string> estados = separar_string(dummy);

        string alfabeto;
        getline(fich,alfabeto);
        vector<string> alfabet = separar_string(alfabeto);

        string alfabeto_cinta;
        getline(fich,alfabeto_cinta);
        vector<string> alfabet_cinta= separar_string(alfabeto_cinta);

        string estado_inicial;
        getline(fich,estado_inicial);

        string blanco;
        getline(fich,blanco);

        //puede haber mas de un estado de aceptacion por eso los guardamos todos
        string estado_final;
        getline(fich,estado_final);
        vector<string> estado_aceptacion = separar_string(estado_final);

        //Creamos nuestros objetos estados y comprobamos si se trata de un estado de aceptacion
        for(unsigned int i = 0; i < estados.size(); i++) {
            for(unsigned int j = 0; j < estado_aceptacion.size(); j++)
                if(estados[i] == estado_aceptacion[j]) {
                    estado.push_back(Estado(estados[i],1));

                } else {
                    estado.push_back(Estado(estados[i],0));
                }
        }

        while(!fich.eof()) {
            //En cada nueva transicion pongo las variables como nuevas
            est_actual = " ";

            while(!simbolo.empty()) {
                simbolo.pop_back();
                simbolo_sustitucion.pop_back();
                movimientos.pop_back();
            }

            n_transicion ++ ;

            fich >> est_actual;

            if(est_actual != " ") {
                //Como no sabemos cual es el numero de estados cogeremos simbolos hasta que se llegue al estado siguiente
                n_cintas = 0;
                fich >> s;
                int i = 1;
                while(i != 0) {
                    if(find(estados.begin(),estados.end(),s) == estados.end()) {
                        aux = s[0];
                        simbolo.push_back(aux);
                        fich >> s;
                        n_cintas++;
                    } else {
                        estado_next = s;
                        i = 0;
                    }
                }

                for(int i = 0; i < n_cintas; i++) {
                    fich >> aux;
                    simbolo_sustitucion.push_back(aux);
                }

                for(unsigned int i = 0; i < n_cintas; i++) {
                    fich >> aux;
                    movimientos.push_back(aux);
                }

                for(unsigned int i = 0; i < estados.size(); i++) {
                    if(estado_next == estado[i].get_nombre())
                        pos2 = i;

                    if(est_actual == estado[i].get_nombre())
                        pos = i;
                }

                t.push_back(Transicion(estado[pos],estado[pos2],simbolo,simbolo_sustitucion,movimientos));
            }
        }

        fich.close();

        string cadena = " ";
        vector<char> c;

        //Si se escribe q se sale del programa
        while(cadena != "q") {

            cout << "Introduce la cadena que deseas evaluar: ";
            cin >>  cadena;

            if(cadena != "q") {
                while(!c.empty()) {
                    c.pop_back();
                }

                for(unsigned int i = 0; i < cadena.size(); i++)
                    c.push_back(cadena[i]);

                while(!ci.empty()) {
                    ci.pop_back();
                }

                //Meto la cadena en la primera cinta
                ci.push_back(Cinta(c,blanco[0]));

                //Y creo tantas cintas como se hayan especificado
                for(unsigned int i = 1; i < n_cintas; i++) {
                    ci.push_back(Cinta(blanco[0]));
                }

                Turing turing(estado,t,ci);

                cout << "\nTRANSICIONES:" << endl;
                turing.verTransiociones();
                cout << "\n\n";
                turing.set_ncinta(n_cintas);
                turing.verCinta();

                //Esta es la funcion interesante
                bool acepta = turing.ejecutar();
                turing.verCinta();

                cout << "\nSe acepta: " << boolalpha << acepta<< endl<< endl;
            }
        }
    }

    else
        cout  << "Error de apertura" << endl;

}