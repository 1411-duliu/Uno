#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uno.h"


char  *stdcolor[]={"NONE","GREEN","RED","YELLOW","BLUE"};
char  *stdface[]={"0","1","2","3","4","5","6","7","8","9","NONE","CALL","REVERSE","SKIP","PLUS2","PLUS4","WILD"};

CARD genCard(char * input)
{
	CARD card;

	int n,m,k,g,a,b,x=0;
    char  content[20];
    char  color[10];
    char  face[10];
    char *r=",",*Ptr,c=',';

	if((Ptr=strchr(input,c))!=NULL){   //判断输入的字符串中是否存在逗号，如果存在将地址赋给Ptr
        n=strcspn(input,r);  //判断逗号是数组中第几个，赋给整形变量n
        strncpy(color,input,n); //从content数组开始复制n为到color中，即为输入的颜色
        color[n]='\0';
        strcpy(face,(Ptr+1));                //从Ptr地址开始将余下的字符串复制到face数组中，即为输入的面值
        

		for(n=0;n<=4;n++)
		{
			if((m=strcmp(*(stdcolor+n),color))==0)    //判断color中字符与标准中是否相等
			{
				for(k=0;k<=16;k++)
				{
					    if((g=strcmp(*(stdface+k),face))==0)  //判断face中字符与标准中是否相等
						{           
							x=1;
							for(a=0;a<=4;a++)
							{                          //分别在标颜色，标面值中判断是第几个并更改card数值
									if((b=strcmp(*(stdcolor+a),color))==0)
									{
											 card.color=a;
									}
							}
							for(a=0;a<=16;a++)
							{
									if((b=strcmp(*(stdface+a),face))==0)
									{
											 card.name=a;
									}
							}     
						}
				}
			}
		}
	}


	if(x==0)
	{
		card.color=0;
		card.name=1411;
	}
	

	return card;
}