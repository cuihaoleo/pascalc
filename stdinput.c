/*
    stdinput.c is a part of PasCalc 2's source.

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

byte filllist(const char* src,readlist arr)
{
    byte i=0;
    byte j=0;
    char s[256];

    init(arr);

    while (*src)
    {
        if (i>=READLIST)
          return false;

        if (islower(*src))
        {
            if (arr[i-1].flag==num || (arr[i-1].flag==opr && arr[i-1].data.sm[0]==')'))
              addchar(opr,'*',&arr[i++]);

            j=0;
            while (!isopr(*src) && !isupper(*src) && *src)
              arr[i].data.sm[j++]=*(src++);

            arr[i].data.sm[j]='\0';

            if (!getnumber(&arr[i]))
            {
                if (isfun(arr[i].data.sm))
                  arr[i].flag=fun;
                else
                  return false;
            }

            i++;
        }
        else if (isupper(*src))
        {
            if (arr[i-1].flag==num || (arr[i-1].flag==opr && arr[i-1].data.sm[0]==')'))
              addchar(opr,'*',&arr[i++]);

            arr[i].flag=num;
            arr[i++].data.nm=var[*(src++)-'A'];
        }
        else if (isopr(*src))
        {
            if (arr[i-1].flag==opr && arr[i-1].data.sm[0]!=')'
                && arr[i-1].data.sm[0]!='(' && *src!='(')
              return false;

            if (arr[i-1].flag==num && *src=='(')
              addchar(opr,'*',&arr[i++]);

            addchar(opr,*(src++),&arr[i++]);
        }
        else if (isdigit(*src)||*src=='.')
        {
            j=0;

            while (isdigit(*src) || *src=='.')
            {
                if (j>=254)
                  return false;

                s[j++]=*(src++);
                s[j]='\0';
            }

            arr[i].flag=num;
            arr[i++].data.nm=strtold(s,NULL);
        }
        else if (istil(*src))
          addchar(til,*(src++),&arr[i++]);
        else
          return false;
    }

    if (i==0 || arr[i-1].flag==num || arr[i-1].flag==til ||
        (arr[i-1].flag==opr && arr[i-1].data.sm[0]==')'))
      return true;
    else
      return false;
}

void init(readlist arr)
{
    int i;

    for (i=0; i<READLIST; i++)
      arr[i].flag=nothing;
}

void addchar(kind f,char ch,rdnode *node)
{
    node->flag=f;
    node->data.sm[0]=ch;
    node->data.sm[1]='\0';
}
