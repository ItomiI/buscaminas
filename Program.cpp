#include <iostream>
#include <vector>
#include <math.h>
#include <conio.h>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono_literals;
struct pose{
  bool b;//bomba
  bool r;//revelado
  bool m;//marcado
  int v;//valor
};

pose new_pose(bool b, int v){
  pose p;
  p.b = b;
  p.r = false;
  p.v = v;
  p.m = false;
  return p;
  
}
void Update_all(vector<vector<pose>> *board){
  cout << "" << endl;
  for(int y = 0; y < (*board).size();y++){
    cout << "|";
    for(int x = 0; x < (*board).size(); x++){

        cout << " " << (*board)[y][x].v << " |";

    }
    cout << endl;
  }
}
void Update(vector<vector<pose>> *board){
  std::cout << "" << endl;
  std::cout << "   |";
  for(int g = 0;g<(*board).size();g++){
    if(g < 10){
      std::cout << " " << g << " |" ;
    }else{
      std::cout << g << " |" ;
    }
    
  }
  std::cout << endl;
  for(int y = 0; y < (*board).size();y++){
    if(y < 10){
      std::cout << y << "  |";
    }else{
      std::cout << y << " |";
    }
    
    for(int x = 0; x < (*board).size(); x++){
      if((*board)[y][x].m){
        std::cout << " X";
      }else if(!(*board)[y][x].r){
       std::cout << " *";
      }else{
        if((*board)[y][x].v == 0){
          std::cout << "  ";
        }else{
          std::cout << " " << (*board)[y][x].v;
        }
        
      }
      std::cout << " |";
    }
    std::cout << endl;
  }
}

bool hay_espacio(vector<vector<pose>> *board,int x, int y){
  int count = 0;

  for(int j = 0; j < 2; j++){
    for(int i = 0; i < 2;i++){
      if(y+j < (*board).size() && y+j >= 0 && x+i < (*board).size() && x+i >= 0){
        if((*board)[y+j][x+i].b)count++;
      }
    }
  }


  return count < 5;
}

void Generar_bombas(vector<vector<pose>> *board,int x, int y,int bombas){
  for(int i = 0; i < bombas; i++){
    int xr = rand()*time(NULL) % (*board).size();
    int yr = rand()*time(NULL) % (*board).size();

    if(sqrt((xr-x)*(xr-x) + (yr-y)*(yr-y)) > 1.5){//! ( al lado o en el lugar)
      if(!(*board)[yr][xr].b && hay_espacio(board,xr,yr)){//no es bomba
        (*board)[yr][xr].b = true;//ahora si
        (*board)[yr][xr].v = 9;
      }else{//era asi q al sig
      std::this_thread::sleep_for(200ms);
        i--;
        continue;
      }
    }else{
      //cout << "el x=" << xr << " y=" << yr << " esta cerca del x=" << x << " y=" << y << endl;
      i--;
      continue;
    }

  }
}

void Calcular_bombas(vector<vector<pose>> *board){
  for(int y = 0; y < (*board).size();y++){
    for(int x = 0; x < (*board).size();x++){
      if(!(*board)[y][x].b)continue;

      for(int j = -1;j < 2;j++){
        for(int i = -1;i < 2;i++){
          if(y+j < (*board).size() && y+j >= 0 && x+i < (*board).size() && x+i >= 0 && !(*board)[y+j][x+i].b){
            (*board)[y+j][x+i].v += 1;
          }
        }
      }
    }
  }

}

bool Revelar_perdio(vector<vector<pose>> *board,int x, int y,bool *revelo,bool p){
  if(!p && !(y < (*board).size() && y >= 0 && x < (*board).size() && x >= 0 )){//esta afuera
    *revelo = false;
    return false;
  }
  if(p)*revelo = true;
  if((*board)[y][x].m && !p)
  {
    return false;//en los recursivos
  }
  if((*board)[y][x].m ){// si esta marcado no revelo
    *revelo = false;
    return false;
  }
  if(p && (*board)[y][x].b)
  {
    return true;//pego bomba perdio
  }

  if((*board)[y][x].v != 0){// si es un numero  revelo
    (*board)[y][x].r = true;
    return false;
  }
  if((*board)[y][x].v == 0 && (*board)[y][x].r == false){
    (*board)[y][x].r = true;

    for(int j = -1;j<2;j++){
      for(int i = -1;i<2;i++){
        if(y+j < (*board).size() && y+j >= 0 && x+i < (*board).size() && x+i >= 0 && (*board)[y+j][x+i].m == false){
          Revelar_perdio(board,x+i,y+j,nullptr,false);
        }
      }
    }
  }

  return false;
}

bool ya_gano(vector<vector<pose>> *board){
  for(int i = 0; i<(*board).size();i++){
    for(int j = 0;i<(*board).size();j++){
      if((*board)[i][j].r == false && !(*board)[i][j].b)return false;
    }
  }
  return true;
}

bool Marcar(vector<vector<pose>> *board,int x,int y){
  try
  {
    if((*board)[y][x].r ==false){
      (*board)[y][x].m = !(*board)[y][x].m ;
      return true;
    }else{
      return false;
    }
  }
  catch(const std::exception& e)
  {
    return false;
  }
  
}


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
    std::cout << "ganaste" << endl;
  }else{
    std::cout << "perdiste" << endl;
  }
  std::cout << "ggs..." << endl;
  getch();
 
  




}