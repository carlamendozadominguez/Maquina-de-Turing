
#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

class Cinta {

  private:
    vector<char> cinta;
    int cabezal;
    char blanco;

  public:

    Cinta(char b):cinta(2,b) {
        cabezal = 1;
        blanco = b;
    }

    Cinta(vector<char>c,char b) {
        c.insert(c.begin(),1,b);
        c.push_back(b);
        cinta = c;
        cabezal = 1;
        blanco = b;

    }

    int get_cabezal() {
        return(cabezal);
    }
    void set_cabezal(int cabezal_) {
        cabezal = cabezal_;
    }
    vector<char> get_cintas() {
        return cinta;
    }

    void set_cintas(vector<char> c) {
        cinta = c;
    }
    int cinta_size() {
        return cinta.size();
    }

    char get_cinta_pos(int i) {
        return cinta[i];
    }

    void set_cinta_pos(int i,char c) {
        cinta[i] = c;
    }

    void insert_blanco() {
        cinta.insert(cinta.begin(),1,blanco);
    }

    void push_blanco() {
        cinta.push_back(blanco);
    }

};
