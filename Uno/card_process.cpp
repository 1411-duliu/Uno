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

	if((Ptr=strchr(input,c))!=NULL){   //�ж�������ַ������Ƿ���ڶ��ţ�������ڽ���ַ����Ptr
        n=strcspn(input,r);  //�ж϶����������еڼ������������α���n
        strncpy(color,input,n); //��content���鿪ʼ����nΪ��color�У���Ϊ�������ɫ
        color[n]='\0';
        strcpy(face,(Ptr+1));                //��Ptr��ַ��ʼ�����µ��ַ������Ƶ�face�����У���Ϊ�������ֵ
        

		for(n=0;n<=4;n++)
		{
			if((m=strcmp(*(stdcolor+n),color))==0)    //�ж�color���ַ����׼���Ƿ����
			{
				for(k=0;k<=16;k++)
				{
					    if((g=strcmp(*(stdface+k),face))==0)  //�ж�face���ַ����׼���Ƿ����
						{           
							x=1;
							for(a=0;a<=4;a++)
							{                          //�ֱ��ڱ���ɫ������ֵ���ж��ǵڼ���������card��ֵ
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