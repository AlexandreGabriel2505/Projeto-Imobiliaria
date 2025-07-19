#include "Imovel.h"
int Imovel::nextId = 1;

Imovel::Imovel(TipoImovel tipo, int propId, double lat, double lng,double preco, string endereco){
    this ->id = nextId++;
    this ->tipo = tipo;
    this ->propId = propId;
    this ->lat = lat;
    this ->lng = lng;
    this ->preco = preco;
    this ->endereco = endereco;
}

int Imovel::getId() const {
    return id;
}

TipoImovel Imovel::getTipo() const {
    return tipo;
}

int Imovel::getPropId() const {
    return propId;
}

double Imovel::getLat() const {
    return lat;
}
double Imovel::getLng() const {
    return lng;
}
double Imovel::getPreco() const {
    return preco;
}
string Imovel::getEndereco() const {
    return endereco;
}