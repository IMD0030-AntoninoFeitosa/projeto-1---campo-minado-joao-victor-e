#include <iostream>
#include <chrono> // for std::chrono functions
#include <array>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
//#include "Game.h"

template<int LINHAS,int COLUNAS>
using Map =  std::array<std::array<int,COLUNAS>,LINHAS>;
std::vector<std::vector<int>> mapa;
const std::string CONFIG_FILE = "config.cfg";
enum class Difficulty { beginner, intermediary, advanced };

void show_usage(void);
void exibir_comandos(void);
void jogada (void);
void marcar (void);
void tempo (void);
void create_map(void);
void start_game();

Map<10,10> map1;
Map<15,15> map2;
Map<15,30> map3;

int lose = 0;
void show_usage(void){
  std::cout << "Usage: game [option]" << std::endl;
  std::cout << "Option:" << std::endl;
  std::cout << " -h or --help                  Display this information." << std::endl;
  std::cout << " -d or --difficulty <option>   Change the game difficulty for <option>" << std::endl;
  std::cout << "                               -b or --beginner" << std::endl;
  std::cout << "                               -i or --intermediary" << std::endl;
  std::cout << "                               -a or --advanced" << std::endl;
  std::cout << "                               -r or --records" << std::endl;
}


template<int LINHAS,int COLUNAS>
void exibir_mapa(Map <LINHAS,COLUNAS> & mapa){
  for(int y=0;y<LINHAS;y++){
    for(int x=0;x<COLUNAS;x++){
      std::cout << "+ ";
    }
    std::cout <<" "<<std::endl;
  }
  exibir_comandos();
}

void gerar_mapa(std::vector<std::vector<int>> & vet, int linhas, int colunas){
  for(int y=0;y<linhas;y++){
    // vetor que representa uma linha
    std::vector<int> linha;
    for(int x=0;x<colunas;x++){
      linha.push_back(y);
    }
    vet.push_back(linha);
  }
}

void start_game(Difficulty level){
  switch(level){
    //O mapa gerado não é o mesmo exibido;
    //Bolar algum jeito de exibir o mesmo mapa. Como?
    case (Difficulty::beginner):
      gerar_mapa(mapa, 10,10);
      exibir_mapa<10,10>(map1);
      break;
    case Difficulty::intermediary:
      gerar_mapa(mapa, 15,15);
      exibir_mapa<15,15>(map2);
      break;
    case Difficulty::advanced:
      gerar_mapa(mapa, 15, 30);
      exibir_mapa<15,30>(map3);
      break;
  }
  
}

void exibir_comandos(void){
  std::cout<<"Entre com o comando desejado"<<std::endl<<std::endl;
  std::cout<<"R: Revelar posição"<<std::endl;
  std::cout<<"M: Marcar Bombas"<<std::endl;
  std::cout<<"T: Verificar Tempo"<<std::endl;
  jogada();
}
void revelar(std::vector<std::vector<int>> mapa,int x,int y){
  
}
void jogada(void){
  std::string comando;
  int linha, coluna;
  while (lose==0){
  std::cin>>comando;
    if(comando == "R" ){
      std::cout<<"Informe a linha e coluna respectivamente: ";
      std::cin>>linha>>coluna;
      if(valida_posicao(linha,coluna)){
        if(nao_revelada(linha,coluna)){
          if(mapa[linha][coluna]._eh_vazia()){
            revelar(mapa, linha-1, coluna-1);      
            revelar(mapa, linha  , coluna-1);      
            revelar(mapa, linha+1, coluna-1);
            
            revelar(mapa, linha  , coluna+1);       
            revelar(mapa, linha  , coluna-1); 
            
            revelar(mapa, linha-1, coluna+1); 
            revelar(mapa, linha  , coluna+1); 
            revelar(mapa, linha+1, coluna+1); 
            
            mapa[linha][coluna].mostrar(linha,coluna);    
            } 
          else if(mapa[linha][coluna]._eh_numero()){
            mapa[linha][coluna].mostrar(linha,coluna);
          }  
        }
      }
      exibir_comandos();
    }
    else if(comando =="M"){
      std::cout<<"Informe a linha e coluna respectivamente: ";
      std::cin>>linha>>coluna;
      marcar();    
      exibir_comandos();
    }
    else if(comando=="T"){
      tempo();
      exibir_comandos();
    }
    else{
      std::cout<<"Comando inexistente! ";
      exibir_comandos();
    }
  }
  
}

  
void marcar(void){

  
}
void tempo(void){
  
    std::cout<<"Meu Deus deu Certo!";
  
}


void store_difficulty(const std::string config_file, Difficulty level){
  std::ofstream file;
  file.open (config_file.c_str(), std::ifstream::out);
  if(file.is_open()){
    switch(level){
      case Difficulty::beginner: file << 'b'; break;
      case Difficulty::intermediary: file << 'i'; break;
      case Difficulty::advanced: file << 'a'; break;
    }
    file.close();
  }
}  
Difficulty load_difficulty(const std::string config_file){
  Difficulty level;
  std::ifstream file;
  file.open (config_file.c_str(), std::ifstream::in);
  if(file.is_open()){
    char c;
    file >> c;
    switch(c){
      case 'b': level = Difficulty::beginner; break;
      case 'i': level = Difficulty::intermediary; break;
      case 'a': level = Difficulty::advanced; break;
    }
    file.close();
  } else {
    store_difficulty(config_file, Difficulty::beginner);
    level = Difficulty::beginner;
  }
  return level;
}

int main(int argc, char ** argv) {

  if(argc > 1){
    std::string arg = argv[1];
    if(arg == "-h" || arg == "--help"){
      show_usage();
    } else if(arg == "-d" || arg == "--difficulty"){
      
      if(argc > 2){
        std::string newlevel = argv[2];
        if(newlevel == "-b" || newlevel == "--beginner"){
           store_difficulty(CONFIG_FILE, Difficulty::beginner);
        //  exibir_mapa<10,10>(map1);
        } else if(newlevel == "-i" || newlevel == "--intermediary"){
          store_difficulty(CONFIG_FILE, Difficulty::intermediary);
         // exibir_mapa<15,15>(map2);
        } else if(newlevel == "-a" || newlevel == "--advanced"){
          store_difficulty(CONFIG_FILE, Difficulty::advanced);
           //exibir_mapa<15,30>(map3);
        }  else if(newlevel == "-r" || newlevel == "--records"){
          std::cout<<"redorcs";
        }
        else {
          std::cout << "Unknown difficulty argument: " << newlevel << std::endl;
          show_usage();
        }
      } else {
        std::cout << "It was expected a difficulty for: " << argv[1] << std::endl;
        show_usage();
      }
    } else {
      std::cout << "Unknown argument: " << argv[1] << std::endl;
      show_usage();
    }
   
  } else{
       Difficulty level = load_difficulty(CONFIG_FILE);
       start_game(level);
    }
  return 0;
}
//Problema, não está sendo passado o mapa para as funções, apenas mostrado.
// 
