#pragma #ifndef CALCFUEL_H

#ifndef CALCFUEL_H



#define CALCFUEL_H

class CalcFuel
{
public:
  int totalFuel(const char *name);
  int runProgram(int arr[], int n=-1, int v=-1, int input=-1);
  void findProgram(int*p, int finalVar);
  int mapWires(int** allLines);
  int closestIntersection(const char *filename);
  int isValid(int num);
};



#endif /* end of include guard: PRIME_H */
