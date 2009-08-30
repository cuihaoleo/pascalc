/*
    calc.c is a part of PasCalc 2's source.

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

int calcexp(const char* str,cmpxfloat* ans)
{
    readlist rdl;

    if (!filllist(str,rdl))
      printf("    Syntax Error!\n");
    else
    {
        *ans=calcmain(rdl);
        return 1;
    }

    return 0;
}

cmpxfloat funcalc(const char* s,temp prm)
{
    if (!cmpmode)
    {
        if (strcmp(s,"sin")==0) return sinl(prm.savenum[0]);
        else if (strcmp(s,"cos")==0) return cosl(prm.savenum[0]);
        else if (strcmp(s,"tan")==0) return tanl(prm.savenum[0]);
        else if (strcmp(s,"asin")==0) return asinl(prm.savenum[0]);
        else if (strcmp(s,"acos")==0) return acosl(prm.savenum[0]);
        else if (strcmp(s,"atan")==0) return atanl(prm.savenum[0]);

        else if (strcmp(s,"sinh")==0) return sinhl(prm.savenum[0]);
        else if (strcmp(s,"cosh")==0) return coshl(prm.savenum[0]);
        else if (strcmp(s,"tanh")==0) return tanhl(prm.savenum[0]);
        else if (strcmp(s,"asinh")==0) return asinhl(prm.savenum[0]);
        else if (strcmp(s,"acosh")==0) return acoshl(prm.savenum[0]);
        else if (strcmp(s,"atanh")==0) return atanhl(prm.savenum[0]);

        else if (strcmp(s,"abs")==0) return abs(prm.savenum[0]);
        else if (strcmp(s,"hypot")==0) return hypotl(REALPART(prm.savenum[0]),REALPART(prm.savenum[1]));
        else if (strcmp(s,"evo")==0) return exp(1/prm.savenum[1]*log(prm.savenum[0]));
        else if (strcmp(s,"log")==0) return logl(prm.savenum[1])/logl(prm.savenum[0]);
        else if (strcmp(s,"ln")==0) return logl(prm.savenum[0]);
        else if (strcmp(s,"exp")==0) return expl(prm.savenum[0]);
        else if (strcmp(s,"sqr")==0) return prm.savenum[0]*prm.savenum[0];
        else if (strcmp(s,"sqrt")==0) return sqrtl(prm.savenum[0]);

        else if (strcmp(s,"int")==0) return truncl(REALPART(prm.savenum[0]));
        else if (strcmp(s,"rnd")==0) return roundl(REALPART(prm.savenum[0]));
        else if (strcmp(s,"frac")==0) return prm.savenum[0]-truncl(REALPART(prm.savenum[0]));

        else if (strcmp(s,"sum")==0) return sum(prm);
        else if (strcmp(s,"ave")==0) return sum(prm)/(cmpxfloat)(prm.count+1);
        else if (strcmp(s,"median")==0) return median(prm);

        else return NAN;
    }
    else
    {
        if (strcmp(s,"sin")==0) return csinl(prm.savenum[0]);
        else if (strcmp(s,"cos")==0) return ccosl(prm.savenum[0]);
        else if (strcmp(s,"tan")==0) return ctanl(prm.savenum[0]);
        else if (strcmp(s,"asin")==0) return casinl(prm.savenum[0]);
        else if (strcmp(s,"acos")==0) return cacosl(prm.savenum[0]);
        else if (strcmp(s,"atan")==0) return catanl(prm.savenum[0]);

        else if (strcmp(s,"sinh")==0) return csinhl(prm.savenum[0]);
        else if (strcmp(s,"cosh")==0) return ccoshl(prm.savenum[0]);
        else if (strcmp(s,"tanh")==0) return ctanhl(prm.savenum[0]);
        else if (strcmp(s,"asinh")==0) return casinhl(prm.savenum[0]);
        else if (strcmp(s,"acosh")==0) return cacoshl(prm.savenum[0]);
        else if (strcmp(s,"atanh")==0) return catanhl(prm.savenum[0]);

        else if (strcmp(s,"abs")==0) return cabsl(prm.savenum[0]);
        else if (strcmp(s,"evo")==0) return cpowl(prm.savenum[0],1/prm.savenum[1]);
        else if (strcmp(s,"log")==0) return clogl(prm.savenum[1])/logl(prm.savenum[0]);
        else if (strcmp(s,"ln")==0) return clogl(prm.savenum[0]);
        else if (strcmp(s,"exp")==0) return cexpl(prm.savenum[0]);
        else if (strcmp(s,"sqr")==0) return prm.savenum[0]*prm.savenum[0];
        else if (strcmp(s,"sqrt")==0) return csqrtl(prm.savenum[0]);

        else if (strcmp(s,"creal")==0) return REALPART(prm.savenum[0]);
        else if (strcmp(s,"cimag")==0) return IMAGPART(prm.savenum[0]);

        else if (strcmp(s,"conj")==0 && cmpmode) return conjl(prm.savenum[0]);
        else if (strcmp(s,"arg")==0 && cmpmode) return cargl(prm.savenum[0]);
        else if (strcmp(s,"proj")==0 && cmpmode) return cproj(prm.savenum[0]);

        else if (strcmp(s,"sum")==0) return sum(prm);

        else return NAN;
    }
}

cmpxfloat tilcalc(char c,cmpxfloat a)
{
    cmpxfloat tmp=0.0;

    if (c=='%')
      tmp=a/100;
    else if (c=='\'')
      tmp=a*acosl(-1.0)/180.0;
    else if (c=='!')
    {
        int i;

        if (IMAGPART(a) || REALPART(a)>1754 || REALPART(a)<1) return NAN;

        tmp=1.0;
        for (i=2; i<=REALPART(a); i++)
          tmp=tmp*i;
    }

    return tmp;
}

cmpxfloat oprcalc(char c,cmpxfloat a,cmpxfloat b)
{
    switch (c)
    {
        case '+':return a+b;
        case '-':return a-b;
        case '*':return a*b;
        case '/':return a/b;
        case '^':if (cmpmode) return cpowl(a,b); else return powl(a,b);
    }

    return NAN;
}

cmpxfloat calcmain(readlist arr)
{
    cmpxfloat stk_num[100]={0.0};
    char* stk_sym[10]={"\0"};
    short c_num=-1,c_sym=-1;

    while (((*arr).flag!=nothing) &&
            ((*arr).flag!=opr || ((*arr).data.sm[0]!=')' && (*arr).data.sm[0]!=',')))
    {
        if ((*arr).flag==num)
        {
            c_num++;
            stk_num[c_num]=(*arr).data.nm;
        }
        else if ((*arr).flag==fun)
        {
            c_sym++;
            stk_sym[c_sym]=(*arr).data.sm;
        }
        else if ((*arr).flag==til)
        {
            stk_num[c_num]=tilcalc((*arr).data.sm[0],stk_num[c_num]);
        }
        else if ((*arr).flag==opr)
        {
            if ((*arr).data.sm[0]=='(')
            {
                int bra=1;
                temp tmp={0,{0.0}};

                tmp.savenum[tmp.count]=calcmain(arr+1);

                do
                {
                    arr++;

                    if ((*arr).flag==opr)
                    {
                        if ((*arr).data.sm[0]=='(')
                          bra++;

                        if ((*arr).data.sm[0]==')')
                          bra--;

                        if ((*arr).data.sm[0]==',' && bra==1)
                          tmp.savenum[++tmp.count]=calcmain(++arr);
                    }
                }while (bra!=0 && (*arr).flag!=nothing);

                if (c_sym!=-1 && isfun(stk_sym[c_sym]))
                  stk_num[++c_num]=funcalc(stk_sym[c_sym--],tmp);
                else
                  stk_num[++c_num]=tmp.savenum[0];
            }
            else
            {
                while ( c_sym>=0 && yxj((*arr).data.sm[0]) <= yxj(*stk_sym[c_sym]) )
                {
                    if (c_num)
                    {
                        stk_num[c_num-1]=oprcalc(*stk_sym[c_sym],stk_num[c_num-1],stk_num[c_num]);
                        c_num--;
                    }
                    else
                        stk_num[c_num]=oprcalc(*stk_sym[c_sym],0,stk_num[c_num]);

                    c_sym--;
                }

                c_sym++;
                stk_sym[c_sym]=(*arr).data.sm;
            }
        }

        arr++;
    }

    while (c_sym>=0)
    {
        if (c_num)
        {
            stk_num[c_num-1]=oprcalc(*stk_sym[c_sym],stk_num[c_num-1],stk_num[c_num]);
            c_num--;
        }
        else
          stk_num[c_num]=oprcalc(*stk_sym[c_sym],0,stk_num[c_num]);

        c_sym--;
    }

    return stk_num[0];
}

