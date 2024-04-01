#include <iostream>
#include <vector>
#include <conio.h>
#include "Funciones.hpp"

int main(){

  int bombas = 30;
  int xy = 16;

  vector<vector<pose>> board(xy, vector<pose>(xy, new_pose(false,0)));
  system("cls");
  std::cout << "/------------------------------------WELCOME------------------------------------/";

  Update(&board);
    
  int posex;
  int posey;
  std::cout << "Posicion para empezar: " << endl;
  std::cout << "pose x: ";
  std::cin >> posex;
  while(posex > xy || posex < 0){
    std::cout << "pose x: ";
    std::cin >> posex;
  }

  std::cout << "pose y: ";
  std::cin >> posey;
    while(posey > xy || posey < 0){
    std::cout << "pose y: ";;
    std::cin >> posey;
  }

  Generar_bombas(&board,posex,posey,bombas);

  Calcular_bombas(&board);
  bool revelo;
  Revelar_perdio(&board,posex,posey,&revelo,true);
  bool gano;
  while(true){
    system("cls");

    Update(&board);
     
    int px;
    int py;
    int action;

    std::cout << "que queres hacer: " << endl << "[1] Marcar" << endl << "[2] Revelar" << endl;
    std::cin >> action;
    std::cout << "pose x: ";
    std::cin >> px;
    std::cout << "pose y: ";
    std::cin >> py;

    bool marco = true;
    bool revelo = false;
    bool perdio = false;
    switch (action)
    {
    case 1:
      marco = Marcar(&board,px,py);
      break;
    case 2:
      perdio = Revelar_perdio(&board,px,py,&revelo,true);
      break;
    default:
    
      break;
    }
    if(!marco)continue;
    if(!revelo)continue;
    if(perdio){
      gano = false;
      break;
    }
    if(ya_gano(&board)){
      gano = true;
      break;
    }
  }
  if(gano){
    std::cout << "ganaste" << std::endl;
  }else{
    std::cout << "perdiste" << std::endl;
  }
  std::cout << "ggs..." << std::endl;
  getch();
 
  




}