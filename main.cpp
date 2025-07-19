#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include "Corretor.h"
#include "Cliente.h"
#include "Imovel.h"
#include "utils.h"

// --- Protótipos das Funções ---
void ler_dados(std::vector<Corretor>&corretores, std::vector<Cliente>&clientes, std::vector<Imovel>&imoveis);
void distribuir_imoveis(std::vector<Corretor>& corretores, const std::vector<Imovel>& imoveis);
void gerar_e_imprimir_agendas(std::vector<Corretor>& corretores);

// --- Função Principal ---
int main(){
    // Prepara os vetores de armazenamento.
    std::vector<Corretor> corretores;
    std::vector<Cliente> clientes;
    std::vector<Imovel> imoveis;

    // Executa as 3 fases principais do programa.
    ler_dados(corretores,clientes,imoveis);
    distribuir_imoveis(corretores, imoveis);
    gerar_e_imprimir_agendas(corretores);
    
    return 0;
}

// Implementa a leitura dos dados de entrada.
void ler_dados(std::vector<Corretor>& corretores, std::vector<Cliente>& clientes, std::vector<Imovel>&imoveis){
    // Bloco de leitura dos Corretores
    int numCorretores;
    std::cin >> numCorretores;
    for (int i = 0; i < numCorretores; ++i) {
        // Ler os dados
        std::string telefone; int avaliador_int; double lat, lng;
        std::cin >> telefone >> avaliador_int >> lat >> lng;
        std::string nome;
        std::getline(std::cin >> std::ws, nome);
        // Conversão para bool
        bool eh_avaliador = (avaliador_int == 1);
        // Cria corretor com os dados
        Corretor c(telefone, eh_avaliador, lat, lng, nome);
        // Armazena o corretor na lista
        corretores.push_back(c);
    }
    // Bloco de leitura dos Clientes
    int numClientes;
    std::cin >> numClientes;
    for (int i = 0; i<numClientes; ++i){
        std::string telefone, nome;
        std::cin >> telefone;
        std::getline(std::cin >> std::ws, nome);
        Cliente c(telefone, nome);
        clientes.push_back(c);
    }
    // Bloco de leitura dos Imóveis
    int numImoveis;
    std::cin >> numImoveis;
    for (int i = 0; i<numImoveis; ++i){
        std::string tipo; int propId; double lat, lng, preco;
        std::cin >> tipo >> propId >> lat >> lng >> preco;
        std::string endereco;
        std::getline(std::cin >> std::ws, endereco);
        // Conversão para o enum
        TipoImovel tipo_enum;
        if (tipo == "Casa"){
            tipo_enum = CASA;
        } else if (tipo == "Apartamento"){
            tipo_enum = APARTAMENTO;
        } else {
            tipo_enum = TERRENO;
        }
        Imovel I(tipo_enum, propId, lat, lng, preco, endereco);
        imoveis.push_back(I);
    }
}
// Implementa a distribuição de imóveis (Round-Robin)
void distribuir_imoveis(std::vector<Corretor>& corretores, const std::vector<Imovel>& imoveis){
    // Filtra apenas os corretores que são avaliadores.
    std::vector<Corretor*> avaliadores;
    for(Corretor& corretor : corretores){
        // pergunta se ele é um avaliador
        if (corretor.getAvaliador() == true){
            // se sim, add na nova lista avaliadores
            avaliadores.push_back(&corretor);

        }
    }
    // Distribui os imóveis entre os avaliadores.
    if(!avaliadores.empty()){
        for(size_t i = 0; i < imoveis.size(); i++){
            // seleciona o carretor da vez com a regrado modulo
        Corretor* corretor_da_vez = avaliadores[i % avaliadores.size()];
        // add o imovel atual na lista de tarefas do corretor selecionado
        corretor_da_vez -> imoveis_atributos.push_back(imoveis[i]);
        } 
    }
}
// Implementa o agendamento (Vizinho Mais Próximo) e a impressão da saída.
void gerar_e_imprimir_agendas(std::vector<Corretor>& corretores){
    bool primeira_agenda = true;

    // Itera sobre cada corretor para gerar sua agenda individual.
    for(Corretor&corretor : corretores){
        // Pula corretores que não são avaliadores ou não têm imóveis.
        if (!corretor.getAvaliador() || corretor.imoveis_atributos.empty()){
            continue; 
        }
        // Garante a linha em branco entre as agendas.
        if (!primeira_agenda) {
            std::cout << std::endl;
        }
        primeira_agenda = false;

        // Imprime o cabeçalho da agenda do corretor.
        std::cout << "Corretor " << corretor.getId() << std::endl;
        
        // Prepara as variáveis de estado para a jornada do corretor.
        int tempo_total_minutos = 9 * 60; // começa as 9:00hs
        double local_atual_lat = corretor.getLat();
        double local_atual_lng = corretor.getLng();
        std::vector<Imovel> imoveis_nao_visitados = corretor.imoveis_atributos;

        // Loop principal: continua enquanto houver imóveis a visitar.
        while(!imoveis_nao_visitados.empty()){
            // 1. Busca pelo imóvel não visitado mais próximo.
            double menor_distancia = std::numeric_limits<double>::max();
            int indice_do_mais_proximo = -1;
            for (size_t i = 0; i < imoveis_nao_visitados.size(); i++){
                double d = haversine(local_atual_lat, local_atual_lng, imoveis_nao_visitados[i].getLat(), imoveis_nao_visitados[i].getLng());
                if(d <menor_distancia){
                    menor_distancia = d;
                    indice_do_mais_proximo = i;
                }
            }

            // 2. Calcula a agenda da visita e imprime a linha.
            int tempo_viagem = menor_distancia * 2;
            tempo_total_minutos += tempo_viagem;
            // Converte o total de minutos para o formato hora e minuto
            int hora = tempo_total_minutos/ 60;
            int minuto = tempo_total_minutos % 60;
            // Formato de saida hora e minuto
            std::cout << std::setfill('0') << std::setw(2) << hora << ":" 
            << std::setw(2) << minuto << " Imóvel " << imoveis_nao_visitados[indice_do_mais_proximo].getId() << std::endl;

            // 3. Atualiza o estado para a próxima iteração.
            tempo_total_minutos += 60;
            local_atual_lat = imoveis_nao_visitados[indice_do_mais_proximo].getLat();
            local_atual_lng = imoveis_nao_visitados[indice_do_mais_proximo].getLng();
            // Remove o imovel visitado da lista de tarefas
            imoveis_nao_visitados.erase(imoveis_nao_visitados.begin() + indice_do_mais_proximo);
        }
    }
}
