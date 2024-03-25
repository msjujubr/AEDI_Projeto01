#ifndef __JOGODAVIDA_HPP
#define __JOGODAVIDA_HPP

#include <iostream>
#include <fstream>
using namespace std;

//funcoes atribuidas

void iniciar_JDV();
void liberar_mem(int **&mat,int l);
void estado_JDV(int v, int w);
bool executar_JDV(int **&mat, int **&mataux, int l);
void relatorio_JVD(int **&mat, int tam);
int contagem(int **&tab, int x, int y, int t);
bool equivalencia(int **&tab, int **&tabaux, int tam);
int vivos(int **&mataux, int tam);
#endif