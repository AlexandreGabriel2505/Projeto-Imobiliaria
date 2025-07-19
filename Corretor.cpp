#include "Corretor.h"
int Corretor::nextID = 1;

Corretor::Corretor(string telefone, bool avaliador, double lat, double lng, string nome){
    this ->id = nextID++;
    this ->telefone = telefone;
    this ->avaliador = avaliador;
    this ->lat = lat;
    this ->lng = lng;
    this ->nome = nome;
}

int Corretor::getId() const {
    return id;
}

string Corretor::getTelefone() const {
    return telefone;
}

bool Corretor::getAvaliador() const {
    return avaliador;
}

double Corretor::getLat() const {
    return lat;
}
double Corretor::getLng() const {
    return lng;
}
string Corretor::getNome() const {
    return nome;
}