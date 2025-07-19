#include "Cliente.h"
int Cliente::nextID = 1;

Cliente::Cliente(string telefone, string nome){
    this ->id = nextID++;
    this ->telefone = telefone;
    this ->nome = nome;
}
int Cliente::getId() const {
    return id;
}

string Cliente::getTelefone() const {
    return telefone;
}
string Cliente::getNome() const {
    return nome;
}