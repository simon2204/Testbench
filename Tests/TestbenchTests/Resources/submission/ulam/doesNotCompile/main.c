/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: jo31041
 *
 * Created on 24. Oktober 2019, 14:06
 */

#include <stdio.h>
#include<stdbool.h> 
#include<math.h> 

int ulam_max(int a0);
int ulam_twins(int limit);
int ulam_multiples(int limit, int number);


int main(void) 
{
  int max = ulam_multiples(391, 6);
  printf("%d", max);
  return 0;
}

inline int gerade(int a0)
{
  return a0 / 2;
}

inline int ungerade(int a0)
{
  return 3 * a0 + 1;
}

bool isPowerOfTwo(int n) 
{ 
   if (n == 0) 
   {
     return false;   
   }
   double log = log2(n); 
   return (ceil(log) == floor(log)); 
} 

int ulam_max(int a0)
{
  if (a0 <= 0)
  {
    return -1;
  }

  int max = a0;
  while (!isPowerOfTwo(a0))
  {
    if (a0 % 2 == 0)
    {
      a0 = gerade(a0);
    }
    else
    {
      a0 = ungerade(a0);
      if (max < a0)
      {
        max = a0;
      }
    }
  }

  if (max < a0)
  {
    max = a0;
  }
  return max;
}

int ulam_twins(int limit)
{
  int a0 = 1;
  int a1;
  int last = -1;

  for (int i = 1; i < limit; i++)
  {
    a1 = ulam_max(i + 1);
    if (a0 == a1)
    {
      last = i;
    }
    a0 = a1;
  }

  return last;
}

int ulam_multiples(int limit, int number)
{
  int wert = -1;
  int vormax = 1;
  int anzahl = 1;
  int kleinster = 1;

  if (2 < number)
  {
     return wert; 
  }
  
  if (number == 2)
  {
    wert = ulam_twins(limit);
  }
  
  for (int i = 2; i <= limit; i++)
  {
    int max = ulam_max(i);
    
    if (vormax == max)
    {
      anzahl = anzahl + 1;
    }
    else 
    {
      kleinster = i;
      anzahl = 1;
    }

    if (anzahl == number)
    {
      wert = kleinster;
    }

    vormax = max;
  }
  return wert;
}
