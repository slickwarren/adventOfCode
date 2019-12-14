#include <fstream>
#include <string>
#include <cstdlib>
#include "calcFuel.h"
#include <array>
#include <iostream>
#include <cmath>

int CalcFuel::totalFuel(const char *name) {
  std::ifstream inputFile;
  int total = 0;
  std::string line;
  int extra_fuel=0;
  inputFile.open(name);
  if (inputFile.is_open()){
    while (getline (inputFile, line)){
      extra_fuel=(std::atoi(line.c_str()) / 3) - 2;
      total+=extra_fuel;
      while (extra_fuel > 8){
        extra_fuel=(extra_fuel / 3) - 2;
        total+=extra_fuel;
      }
    }

    inputFile.close();
  }
  return total;
}

int CalcFuel::runProgram(int arr[], int n, int v, int input ){
  int i = 0;
  if (n>-1) {
    arr[1]=n;
  }
  if (v>-1) {
    arr[2]=v;
  }

  int value = 0;
  int v1=0;
  int v2=0;
  int v3=0;
  int mode = 0;
  int bigMode = 0;
  int current_operator = arr[i];
  while(arr[i] != 99) {
    if (current_operator > 10){
      std::cout << " i: " << i << " O " << current_operator << " -> M: " << bigMode << std::endl;
      bigMode=current_operator / 100;
      current_operator=current_operator % 100;
    }
    else{
      bigMode=0;
    }
    std::cout << " i: " << i << " O " << current_operator << " -> M: " << bigMode  << " arr[i+1] " << arr[1] << std::endl;

    v1 = (bigMode % 10 > 0) ? i+1 : arr[i+1];
    v2 = (bigMode/10 % 10 > 0) ? i+2 : arr[i+2];
    v3 = ((bigMode/100) % 10 > 0) ? i+3 : arr[i+3];
    //old code should still work
    switch (current_operator) {
      case (1):
        value = arr[v1] + arr[v2];
        arr[v3]=value;
        i+=4;
        break;
      case (2):
        value = arr[v1] * arr[v2];
        arr[v3]=value;
        i+=4;
        break;
      case (3):
        arr[v1]=input;
        i+=2;
        break;
      case (4):
        if (arr[v1] !=0 && arr[i+2] != 99){
          return -1;
        }
        else if (arr[i+2] == 99){
          return arr[v1];
        }
        i+=2;
        break;
      case (5):
        if (arr[v1] != 0){
          i=arr[v2];
        }
        else {
          i+=2;
        }
        break;
      case (6):
        if (v1 == 0) {
          i=arr[v2];
        }
        else {
          i+=2;
        }
        break;
      case (7):
        if (arr[v1] < arr[v2]) {
          arr[v3] = 1;
        }
        else{
          arr[v3] = 0;
        }
        i+=4;
        break;
      case (8):
        if (arr[v1] == arr[v2]){
          arr[v3] = 1;
        }
        else{
          arr[v3] = 0;
        }
        i+=4;
        break;
      default:
        return -1;
    }
    current_operator=arr[i];
    std::cout << " x: " << bigMode % 10 << " y: " << (bigMode / 10) % 10  << " z: " << current_operator << std::endl;

  }
  return arr[0];
}


void CalcFuel::findProgram(int* pair, int finalVar){
  finalVar -= 106644;
  if (finalVar >0){
    pair[0] = finalVar / 576000 -1;
    pair[1] =  (finalVar % 576000);
  }
  else{
    pair[0]=-1;
    pair[1]=-1;
  }
}

int CalcFuel::mapWires(int** lines){
  int l=9;
  int shortest = 200000000;
  int temp = 0;
  int lastValx1=0;
  int lastValx2=0;
  int lastValy1=0;
  int lastValy2=0;
  for (int c=0; c<l; c++) {
    lastValx2=0;
    for (int d=0; d<l; d++) {
      //
      if ((lastValx1<=lines[2][d] && lines[0][c]>lastValx2)) {// || (lines[0][c]<=lines[2][d] && lines[0][c]>lastValx2)){

         //std::cout << lines[0][c]<< " : " << lines[2][d] << std::endl;
         //std::cout << c << " i " << d << std::endl;

        if (lines[3][d] < lines[1][c+1] && lastValy2 > lines[1][c]){
          //std::cout << lines[0][c]<< " : " << lines[2][d] << std::endl;
          //std::cout << lastValy2 << std::endl;
          //std::cout << c << " i " << d << std::endl;
          temp=std::abs(lastValy2) + std::abs(lines[0][d]);
          if (temp < shortest) {
            shortest=temp;
            std::cout << temp << std::endl;
          }
        }
        /*
        for (int e=0; c<l; c++) {
          for (int f=0; d<l; d++) {
            if (lines[1][e]==lines[3][f]){
              temp=std::abs(lines[0][e]) + std::abs(lines[1][e]);
              if (temp > shortest){
                std::cout << "hit" << std::endl;
                shortest=temp;
              }
            }
          }
        }
        */
      }
      if ((lastValx2<=lines[0][c] && lines[2][d]>lastValx1)) {// || (lines[0][c]<=lines[2][d] && lines[0][c]>lastValx2)){

         //std::cout << lines[0][c]<< " : " << lines[2][d] << std::endl;
         //std::cout << c << " i " << d << std::endl;

        if (lines[1][c] < lines[3][d+1] && lastValy1 > lines[3][d]){
          //std::cout << lines[0][c]<< " : " << lines[2][d] << std::endl;
          //std::cout << lastValy1 << std::endl;
          //std::cout << c << " i " << d << std::endl;
          temp=std::abs(lastValy1) + std::abs(lines[2][c]);
          if (temp < shortest) {
            shortest=temp;
            std::cout << temp << std::endl;
          }
        }
        /*
        for (int e=0; c<l; c++) {
          for (int f=0; d<l; d++) {
            if (lines[1][e]==lines[3][f]){
              temp=std::abs(lines[0][e]) + std::abs(lines[1][e]);
              if (temp > shortest){
                std::cout << "hit" << std::endl;
                shortest=temp;
              }
            }
          }
        }
        */
      }
      lastValx2=lines[2][d];
      lastValy2=lines[3][d];
    }
    lastValx1=lines[0][c];
    lastValx1=lines[1][c];
  }
  return shortest;
}

int CalcFuel::closestIntersection(const char* filename){
  std::ifstream inputFile;
  int linex1[30000]={};
  int liney1[30000]={};
  int linex2[30000]={};
  int liney2[30000]={};
  int lastx=0;
  int lasty=0;
  int current_number=0;
  int line_counter=0;
  int len_counter=0;
  int* all_lines[4]={linex1, liney1, linex2, liney2};
  int* current_line;
  int* next_line;
  std::string line;
  inputFile.open(filename);
  int pair[2]={0,0};
  if (inputFile.is_open()){
    while (getline (inputFile, line)){
      current_line=all_lines[line_counter];
      next_line=all_lines[line_counter+1];
      len_counter=0;
      lastx=0;
      lasty=0;
      current_number=0;
      for(int i=0; i<line.length(); i++){
        //std::cout << i << std::endl;
        switch (line[i]){
          case 'R':
            pair[0]= 1;
            pair[1]= 0;
            break;
          case 'L':
            pair[0]= -1;
            pair[1]= 0;
            break;
          case 'U':
            pair[1]= 1;
            pair[0]= 0;
            break;
          case 'D':
            pair[1]= -1;
            pair[0]= 0;
            break;
          case ',':
            //do work here
            if (pair[0]==0){
              current_number*=pair[1];

              current_line[len_counter]=lastx;
              lasty+=current_number;

              next_line[len_counter]=lasty;

            }
            else{
              current_number*=pair[0];
              lastx+=current_number;

              current_line[len_counter]=lastx;

              next_line[len_counter]=lasty;

            }
            //std::cout << current_line[len_counter] << " : " << next_line[len_counter] << std::endl;
            len_counter++;
            current_number=0;
            break;
          case ' ':
            std::cout << "space?" << std::endl;
            break;
          case '\n':
            std::cout << "newline?" << std::endl;
            break;
          default:
            current_number = current_number*10 + std::stoi(line.substr(i, 1));
        }
      }
      if (pair[0]==0){
        current_number*=pair[1];

        current_line[len_counter]=lastx;
        lasty+=current_number;

        next_line[len_counter]=lasty;

      }
      else{
        current_number*=pair[0];
        lastx+=current_number;

        current_line[len_counter]=lastx;

        next_line[len_counter]=lasty;

      }
      //std::cout << current_line[len_counter] << " : " << next_line[len_counter] << std::endl;
      len_counter++;
      current_number=0;
      line_counter++;
      line_counter++;
    }
    inputFile.close();
  }

  return mapWires(all_lines);
}

int CalcFuel::isValid(int number){
  int hasDouble=0;
  int lastNum=-1;
  int lastLastNum;
  int currentNum=-1;
  int div=10;
  while(number > 0){
    lastLastNum=lastNum;
    lastNum=currentNum;
    currentNum=number % div;
    //std::cout << currentNum << std::endl;
    number/=div;
    if (lastNum==currentNum){
      if (lastNum==currentNum && hasDouble !=1 & lastLastNum!=currentNum && lastLastNum!=-1){
        //std::cout << lastLastNum << " : " << currentNum << " : " << number << std::endl;
        hasDouble=1;
      }
      else if (lastLastNum==currentNum && lastLastNum==lastNum){
        hasDouble=0;
      }
    }
    if (currentNum>lastNum && lastNum!=-1){
      return 0;
    }
  }
  if (hasDouble == 1) return 1;
  else return 0;
}
/*



*/
