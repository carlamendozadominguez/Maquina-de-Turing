#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;


class Estado {
  
  private:

    string nombre;
    bool es_final = false;

  public:

    Estado() {}

    Estado(string n, bool f) {
        nombre = n;
        es_final = f;
    }

    string get_nombre() {
        return nombre;
    }

    bool get_es_final(){
        return es_final;
    }
};

