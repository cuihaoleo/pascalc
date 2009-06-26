/*
    pascalc.c is a part of PasCalc 2's source.

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

cmpxfloat var[26];
cmpxfloat answer=0.0;
_Bool cmpmode=false;

void vardim(void);
void show(void);
void clr(void);
void func(void);
void chmode(void);
void prncpx(cmpxfloat num);

int main(void)
{
    char rd[256];

    printf("PasCalc 2 Beta(090626)\n");
    printf("Copyright (C) 2009 Cui Hao\n");

    clr();

    do
    {
        printf("> ");
        scanf("%256s",rd);

        if (strcmp(rd,"quit"))
        {
            if (!strcmp(rd,"dim"))
              vardim();
            else if (!strcmp(rd,"show"))
              show();
            else if (!strcmp(rd,"clr"))
              clr();
            else if (!strcmp(rd,"func"))
              func();
            else if (!strcmp(rd,"chmode"))
              chmode();
            else if (!strcmp(rd,"m+"))
              var['M'-'A']=var['M'-'A']+answer;
            else if (!strcmp(rd,"m-"))
              var['M'-'A']=var['M'-'A']-answer;
            else if (!strcmp(rd,"mc"))
              var['M'-'A']=0.0;
            else
            {
                if (calcexp(rd,&answer))
                  prncpx(answer);
            }
        }
    }
    while (strcmp(rd,"quit"));

    return 0;
}

void vardim(void)
{
    char c;
    char rd[256];

    while ((c=getchar())==' ')
      continue;

    if (!isupper(c))
    {
        printf("    Syntax Error!\n");
        return;
    }

    printf("%c = ",c);
    scanf("%256s",rd);

    if (calcexp(rd,&var[c-'A']))
      prncpx(var[c-'A']);
}

void show(void)
{
    byte i;

    for (i=0; i<26; i++)
    {
        printf("%c = ",i+'A');
        prncpx(var[i]);
    }
}

void clr(void)
{
    byte i;

    for (i=0; i<26; i++)
      var[i]=0;

    answer=0.0;
}

void func(void)
{
    double start=0,end=0,step=0;
    cmpxfloat savex=0,tmp=0;
    char rd[256],rdexp[256];

    printf("f(X)=");
    scanf("%256s",rd);

    printf("Start: ");
    scanf("%256s",rdexp);
    if (!calcexp(rdexp,&tmp))
      return;
    start=REALPART(tmp);

    printf("End: ");
    scanf("%256s",rdexp);
    if (!calcexp(rdexp,&tmp))
      return;
    end=REALPART(tmp);

    printf("Step: ");
    scanf("%256s",rdexp);
    if (!calcexp(rdexp,&tmp))
      return;
    step=REALPART(tmp);

    savex=var['X'-'A'];

    for (REALPART(var['X'-'A'])=start; REALPART(var['X'-'A'])<=end; REALPART(var['X'-'A'])+=step)
    {
        printf("    %0.8"DFout,REALPART(var['X'-'A']));

        calcexp(rdexp,&tmp);
        prncpx(tmp);
    }

    var['X'-'A']=savex;
}

void chmode(void)
{
    if (cmpmode)
      printf("    Normal Mode\n");
    else
      printf("    Complex Mode\n");

    cmpmode=!cmpmode;
}

void prncpx(cmpxfloat num)
{
    printf("    ");

    if (!isnormal(REALPART(num)) || (!isnormal(IMAGPART(num)) && cmpmode))

    if ((!isnormal(creall(num)) && creall(num)!=0) || (!isnormal(cimagl(num)) && cmpmode && cimagl(num)!=0))
    {
        printf("Math Error!\n");
        return;
    }

    if (REALPART(num) || !IMAGPART(num) || !cmpmode) printf("%0.16"DFout,REALPART(num));

    if (cmpmode)
    {
        if (REALPART(num) && IMAGPART(num) && IMAGPART(num)>0) printf("+");

        if (IMAGPART(num))
        {
            if (IMAGPART(num)==1)
              printf("i");
            else if (IMAGPART(num)==-1)
              printf("-i");
            else
              printf("%0.16"DFout"i",IMAGPART(num));
        }
    }

    printf("\n");
}
