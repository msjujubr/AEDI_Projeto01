#include "jogodavida.hpp"

void iniciar_JDV() {
  cout << "INICIANDO JOGO..." << endl;
  
  ofstream arq("src/output.mps", ios::trunc);
  arq.close();
  
  ifstream arquivo("src/input.mps"); 

  string line;
  vector<string> vec;
  int cont = 0, m;
  
  if (arquivo.is_open()) {
    while (getline(arquivo, line)){
      if(cont == 0){
        m = stoi(line);
      } else{
      vec.push_back(line);
      }
      cont++;
    }
    arquivo.close();
  } else cout << "Nao foi possivel abrir o arquivo" << endl;

  m = vec.size();

  int **tab = new int*[m];
  int **tabaux = new int*[m];

  for (int i = 0; i < m; ++i) {
      tab[i] = new int[m]; 
      tabaux[i] = new int[m];
  }

  int i =0;
  for (auto linha : vec){
    int j=0;
    for (auto var : linha){
          tab[i][j++] = var-'0';
      }
    i++;
    }

  relatorio_JVD(tab, m);

  cout << "TABULEIRO INICIAL" << endl;
  for (int i = 0; i < m; ++i) {
      for (int j = 0; j < m; ++j) {
          cout << tab[i][j] << " ";
      }
      cout << endl;
  }

  cout << "quantas geracoes? " << endl;
  int g;
  cin >> g;

  for(int i = 0; i < g; i++){
    if(!(executar_JDV(tab, tabaux, m))){
      break;
    }
  }

  liberar_mem(tab, m);
  cout << "JOGO ENCERRADO!" << endl;

}

bool executar_JDV(int **&mat, int **&mataux, int tam){

  for(int i = 0; i < tam; i++){
    for( int j = 0; j < tam; j++){
      int viv = contagem(mat, i, j, tam);

      if(viv == 2 || viv == 3){
        mataux[i][j] = 1;
      }
      else if(viv < 2 || viv > 3){
        mataux[i][j] = 0;
      }
    }
  }

  int tot = vivos(mataux, tam);
  estado_JDV(tot, tam);
  relatorio_JVD(mataux, tam);
  
  if(equivalencia(mat, mataux, tam)){
    for(int i = 0; i < tam; i++){
      for( int j = 0; j < tam; j++){
        mat[i][j] = mataux[i][j];
      }
    }
    return 1;
  }
  cout << "ULTIMAS MATRIZES IGUAIS" << endl;
  return 0;

}

void estado_JDV(int v, int w){
  cout << "ESTADO DO JOGO" << endl;
  int mortos = w*w - v;
  cout << "Vivos: " << v << " " << "Mortos: " << mortos << endl << endl;
  ofstream arquivo("src/output.mps", ios::app); 
  if (!arquivo) { return; }
  arquivo << "Vivos: " << v << " " << "Mortos: " << mortos << endl;
}

int contagem(int **&tab, int x, int y, int t){
  int cont = 0;
  if(x+1 < t){
    if(tab[x+1][y+1] == 1){
      cont++;
    }
    if(tab[x+1][y-1] == 1){
      cont++;
    }
    if(tab[x+1][y] == 1){
      cont++;
    }
  }

  if(x-1 >= 0){
    if(tab[x-1][y] == 1){
      cont++;
    }
    if(tab[x-1][y+1] == 1){
      cont++;
    }
    if(tab[x-1][y-1] == 1){
      cont++;
    }
  }

  if(y+1 < t && tab[x][y+1] == 1){
      cont++;
  }
  
  if(y-1 >= 0 &&  tab[x][y-1] == 1){
      cont++;
  }
  return cont;
}

void relatorio_JVD(int **&mat, int tam){
  ofstream arquivo("src/output.mps", ios::app); 
  if (!arquivo) { 
      cerr << "Erro ao abrir o arquivo." << endl;
      return;
  }

  for (int i = 0; i < tam; ++i) {
    for(int j = 0; j < tam; j++){
      arquivo << mat[i][j] << " ";
    }
    arquivo << endl;
  }

  arquivo << endl;

  arquivo.close();
}

void liberar_mem(int **&mat,int l){
  for (int i = 0; i < l; ++i) {
      delete[] mat[i];
  }
  delete[] mat;
}

int vivos(int **&mataux, int tam){
  int cont = 0;
  for(int i = 0; i < tam; i++){
    for( int j = 0; j < tam; j++){
      if(mataux[i][j] == 1){
        cont++;
      }
    }
  }
  return cont;
}

bool equivalencia(int **&tab, int **&tabaux, int tam){
  for(int i = 0; i < tam; i++){
    for(int j = 0; j < tam; j++){
      if(tab[i][j] != tabaux[i][j]){
        return 1;
      }
    }
  }
  return 0;
}
