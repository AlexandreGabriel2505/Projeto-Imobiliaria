#ifndef CORRETOR_H
#define CORRETOR_H

#include <string>
#include <vector>
#include "Imovel.h"
using namespace std;

class Corretor{
    private:
      static int nextID;
      int id;
      string nome, telefone;
      bool avaliador;
      double lat, lng;
     
    public:
      // Guardar os imoveis que este corretor especifico deve avaliar
      vector<Imovel> imoveis_atributos;
      
      Corretor(string telefone, bool avaliador, double lat,double lng, string nome);
      int getId() const;
      string getTelefone() const;
      bool getAvaliador() const;
      double getLat() const;
      double getLng() const;
      string getNome() const;

};

#endif  
