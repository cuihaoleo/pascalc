/*
    symname.c is a part of PasCalc 2's source.

    PasCalc 2 is a simple command-line calculator¡£
    Copyright (C) 2009 Cui Hao

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Author: Cui Hao
    E-mail£ºcuihao1994@hotmail.com
    QQ£º515166698
    MSN£ºcuihao1994@hotmail.com
    Address: No.25 Jing'er Road, Zhengzhou, Henan, PRC
*/

#include "pascalc.h"

#define FUN_NOR 26
#define FUN_CMP 25
#define TIL 3
#define OPR 8

static const char* Funname_n[FUN_NOR]=
                   {"sin","cos","tan","asin","acos","atan", //6
                    "sinh","cosh","tanh","asinh","acosh","atanh", //6
                    "abs","log","ln","exp","evo","sqr","sqrt","hypot",  //8
                    "int","rnd","frac",  //3
                    "sum","ave","median"};  //3

static const char* Funname_c[FUN_CMP]=
                   {"sin","cos","tan","asin","acos","atan", //6
                    "sinh","cosh","tanh","asinh","acosh","atanh",  //6
                    "abs","evo","log","ln","exp","sqr","sqrt",  //7
                    "creal","cimag",  //2
                    "conj","arg","proj",  //3
                    "sum"};  //1

static const char Tilname[TIL]={'%','\'','!'};

static const char Oprname[OPR]={'(',')',',','+','-','*','/','^'};

byte isfun(const char *s)
{
    byte i;

    if (!cmpmode)
    {
      for (i=0; i<FUN_NOR; i++)
        if (strcmp(s,Funname_n[i])==0)
          return true;
    }
    else
    {
      for (i=0; i<FUN_CMP; i++)
        if (strcmp(s,Funname_c[i])==0)
          return true;
    }

    return false;
}

byte istil(char c)
{
    byte i;

    for (i=0; i<TIL; i++)
      if (c==Tilname[i])
        return true;

    return false;
}

byte isopr(char c)
{
    byte i;

    for (i=0; i<OPR; i++)
      if (c==Oprname[i])
        return true;

    return false;
}

byte yxj(char c)
{
    if (c=='+' || c=='-') return 1;
      else if (c=='*' || c=='/') return 2;
        else if (c=='^') return 3;

    return 0;
}
