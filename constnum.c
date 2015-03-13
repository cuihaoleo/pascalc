/*
    constnum.c is a part of PasCalc 2's source.

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

byte getnumber(rdnode* node)
{
    cmpxfloat ans;

    if (!strcmp(node->data.sm,"ans"))
        ans=answer;
    else if (!strcmp(node->data.sm,"pi"))
        ans=getpi();
    else if (!strcmp(node->data.sm,"e"))
        ans=expl(1.0);
    else if (!strcmp(node->data.sm,"fai"))
        ans=(sqrtl(5.0)+1)/2.0;
    else if (!strcmp(node->data.sm,"c"))
        ans=2.997925E8;
    else if (!strcmp(node->data.sm,"i") && cmpmode)
        ans=I;
    else
      return false;

    node->flag=num;
    node->data.nm=ans;

    return true;
}

long double getpi(void)
{
    long double pi;

#ifdef __MINGW_H
    __asm__("fldpi;"
        :"=t"(pi):);
#else
    pi=3.1415926535897932384626;
#endif

    return pi;
}
