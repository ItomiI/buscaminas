#include <iostream>
#include <vector>
#include <math.h>
#include <conio.h>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono_literals;

#ifndef Funciones
#define Funciones

struct pose{
  bool b;//bomba
  bool r;//revelado
  bool m;//marcado
  int v;//valor
};
#endif// Funciones

pose new_pose(bool b, int v);

void Update_all(vector<vector<pose>> *board);

void Update(vector<vector<pose>> *board);

bool hay_espacio(vector<vector<pose>> *board,int x, int y);

void Generar_bombas(vector<vector<pose>> *board,int x, int y,int bombas);

void Calcular_bombas(vector<vector<pose>> *board);

bool Revelar_perdio(vector<vector<pose>> *board,int x, int y,bool *revelo,bool p);

bool ya_gano(vector<vector<pose>> *board);

bool Marcar(vector<vector<pose>> *board,int x,int y);