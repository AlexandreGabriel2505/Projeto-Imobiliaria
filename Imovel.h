#ifndef IMOVEL_H
#define IMOVEL_H

#include <string>
using namespace std;

enum TipoImovel {CASA, APARTAMENTO, TERRENO};

class Imovel {
    private:
     static int nextId;
     int id, propId;
     TipoImovel tipo;
     string endereco;
     double lat, lng, preco;

    public:
     Imovel(TipoImovel tipo, int propId, double lat, double lng, double preco, string endereco);
     int getId() const;
     TipoImovel getTipo() const;
     int getPropId() const;
     double getLat() const;
     double getLng() const;
     double getPreco() const;
     string getEndereco() const;
};

#endif 
