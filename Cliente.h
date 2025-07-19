#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
using namespace std;

class Cliente {
private:
    static int nextID;
    int id;
    string nome, telefone;
public:
    Cliente(string telefone, string nome);
    int getId() const;
    string getTelefone() const;
    string getNome() const;

};

#endif 
