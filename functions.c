/*
    functions.c is a part of PasCalc 2's source.

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

cmpxfloat sum(temp data)
{
    byte i;
    cmpxfloat ans=0.0;

    for (i=0; i<=data.count; i++)
      ans=ans+data.savenum[i];

    return ans;
}

int comparedata(const void* a,const void* b)
{
    cmpxfloat *aa,*bb;

    aa=(cmpxfloat*)a;
    bb=(cmpxfloat*)b;

    return (REALPART(*aa)) > (REALPART(*bb)) ? 1:0;
}

cmpxfloat median(temp data)
{
    qsort(data.savenum,(size_t)(data.count+1),sizeof(cmpxfloat),comparedata);

    if (data.count%2)
      return (data.savenum[data.count/2]+data.savenum[data.count/2+1])/2;
    else
      return data.savenum[data.count/2];
}

