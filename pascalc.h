/*
    pascalc.h is a part of PasCalc 2's source.

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

#ifndef PASCALC_H_INCLUDED
#define PASCALC_H_INCLUDED

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <complex.h>
#include <stdlib.h>

//#define LINUX

#ifdef LINUX
#define FLOAT long double
#define DFout "Lg"
#else
#define FLOAT double
#define DFout "g"
#endif

#define READLIST 100

#define true 1
#define false 0

#ifdef __MINGW_H
#define REALPART(X) __real X
#define IMAGPART(X) __imag X
#endif

typedef unsigned char byte;

typedef FLOAT complex cmpxfloat;

typedef union RDDATA
{
    char sm[10];
    cmpxfloat nm;
} rddata;

typedef enum {nothing,num,fun,til,opr} kind;

typedef struct RDNODE
{
    kind flag;
    rddata data;
} rdnode;

typedef rdnode readlist[READLIST];

typedef struct TEMP
{
    int count;
    cmpxfloat savenum[100];
} temp;

extern cmpxfloat var[26];
extern cmpxfloat answer;
extern _Bool cmpmode;

//symname.c
byte isfun(const char *s);
byte istil(char c);
byte isopr(char c);
byte yxj(char c);

//calc.c
int calcexp(const char* str,cmpxfloat* ans);
cmpxfloat funcalc(const char* s,temp prm);
cmpxfloat tilcalc(char c,cmpxfloat a);
cmpxfloat oprcalc(char c,cmpxfloat a,cmpxfloat b);
cmpxfloat calcmain(readlist arr);

//stdinput.c
byte filllist(const char* src,readlist arr);
void init(readlist arr);
void addchar(kind f,char ch,rdnode *node);

//functions.c
cmpxfloat sum(temp data);
int comparedata(const void* a,const void* b);
cmpxfloat median(temp data);

//constnum.c
byte getnumber(rdnode* node);
long double getpi(void);

#endif // PASCALC_H_INCLUDED
