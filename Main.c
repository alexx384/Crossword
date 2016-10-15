#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "GraphicalPart.h"

struct Resault
{
	int Rate;
	int Col;
	int Line;
	int Posit;
}typedef Resault;

struct perf
{
	struct perf *next;
	struct perf *past;
	char *word;
	int key;
	int Line;
	int Col;
	int number;
}typedef Perfect;

struct Words
{
	char *word;
	int length;
	char key;
	struct Words *next, *past;
	int count;
	char flag;
} typedef Words;

Perfect *Origin;
int Rat=0;

void DelPerfect(Perfect *Noname)
{
	Perfect *Dump;
	while(Noname->next!=NULL)	Noname=Noname->next;
	while(Noname->past!=NULL)
	{
		Dump=Noname;
		Noname=Noname->past;
		free(Dump);
	}
	free(Noname);
}

void Ravno(Perfect *Maybe, int Max)
{
	int i;
	Perfect *Dump;
	Dump=Origin;
	//Max--;
	while(Maybe->past)
		Maybe=Maybe->past;

	for(;Max>0; Max--)
	{
		Origin->Col=Maybe->Col;
		Origin->key=Maybe->key;
		Origin->Line=Maybe->Line;
		Origin->word=Maybe->word;
		Origin->number=Maybe->number;
		Origin=Origin->next;
		Maybe=Maybe->next;
	}
	Origin=Dump;
}

void CreatePerfect(Perfect **Top, int max)
{
	Perfect *Dump;
	Dump=Top[0]=(Perfect*)calloc(1,sizeof(Perfect));
	Top[0]->past=NULL;
	for(;max>0; max--)
	{
		Top[0]->next=(Perfect*)calloc(1,sizeof(Perfect));
		Top[0]->next->past=Top[0];
		Top[0]->next->next=NULL;
		Top[0]=Top[0]->next;
	}
	Top[0]=Dump;
}

int Entr(char **str)
{
	int i=0;
	char ch=0;
	*str=(char*)malloc(sizeof(char));
	
	for(i=1; ch = getchar(); i++)
	{
		if(ch!='\n')
		{
			*str=(char*)realloc(*str,sizeof(char)*(i+1));
			str[0][i-1]=ch;
		}else
			if(i!=1)	break;
			else i--;
	}
	i--;
	str[0][i]=0;

	return i;
}

Words *CreateWords(Words *Top, int *count)
{
	Words *Head=Top;
	Head->next=(Words*)malloc(sizeof(Words));
	if(Head->next==NULL){	printf("Error");	getchar();	};
	Head->next->past=Head;
	Head->next->word=NULL;
	Head->next->next=NULL;
	Head->next->flag=0;
	Head->next->key=NULL;
	Head->next->count=*count;
	Head->next->word=(char*)malloc(sizeof(char));
	if(Head->next->word==NULL){	printf("Error");	getchar();	};
	*count+=1;
	return Head->next;
}

void GetWords(Words **data, int *Line, int *Col)
{
	char c;
	int i=0, max=0,n=0;
	int count=1;
	Words *Head=(Words*)malloc(sizeof(Words));
 
	Words *Dump=Head;

	FILE *Output=fopen("Output.txt", "rb+");
	if( !Output ){	printf("File didn't found"); getchar(); exit(EXIT_SUCCESS);}

	Head->flag=NULL;
	Head->past=NULL;
	Head->next=NULL;
	Head->word=NULL;
	Head->key=NULL;
	Head->next=Dump=CreateWords(Dump, &count);

	while(fscanf(Output, "%c",&c)!= EOF)
	{
		i++;
		Dump->word=(char*)realloc(Dump->word, sizeof(char)*i);
		if(c==13)	fscanf(Output, "%c",&c);
		if(c=='\n')
		{
			Dump->word[i-1]=0;
			Dump->length=i-1;
			if((Dump->length)>max)	max=Dump->length;
			//Add(Head, Dump);
			Dump=CreateWords(Dump, &count);
			i=0;
			n++;
		}else	Dump->word[i-1]=c;	
	}
	if(i!=0)
	{
		Dump->word=(char*)realloc(Dump->word, sizeof(char)*(i+1));
		Dump->word[i-1]=c;
		Dump->word[i]=0;	
		Dump->length=i;
		//if((Dump->length)>max)	max=Dump->length;
		//Add(Head, Dump);
		i=0;
		n++;
	}else{
		free(Dump->word);
		free(Dump);
	}
	*Col=max;
	*Line=n;
	*data=Head;
}
//-----------------

int PasteX(Protoblast **Pole, Words *Head, int i, int j, int count)
{
	if(Pole[i][j+count].word==Head->word[count])							
	{														
		if(Pole[i][j+count].logic!=1)	return 1;
	}
	return 0;
}

int PasteY(Protoblast **Pole, Words *Head, int i, int j, int count)
{
	if(Pole[i+count][j].word==Head->word[count])							
	{														
		if(Pole[i+count][j].logic!=2)	return 1;
	}
	return 0;
}

int ZeroPasteX(Protoblast **Pole, Words *Head, int i, int j, int count)
{
	if(Pole[i][j+count].word==0)
	{
		if(Pole[i][j+count].logic!=1) return 1;
	}
	return 0;
}

int ZeroPasteY(Protoblast **Pole, Words *Head, int i, int j, int count)
{
	if(Pole[i+count][j].word==0)
	{
		if(Pole[i+count][j].logic!=2)	return 1;	
	}
	return 0;
}

void ToX(Words *Head,Protoblast **Pole, struct Resault *Stat, int Line, int Col, int MainKey)
{
	int i,j,count,key=0;

	for(i=0; i<Line; i++)
	{
		count=0;
		for(j=0; j<Col; j++)
		{
			if((Head->length+j) <= Col)
			{
				for(count=0; count < (Head->length); count++)
				{
					if(ZeroPasteX(Pole, Head, i, j, count))	;
					else{
						if(PasteX(Pole, Head, i, j, count))
							key++;
						else	break;
					}
				}
				if(count==Head->length)
				{
					if(Stat->Rate<key)
					{
						Stat->Col=j;
						Stat->Line=i;
	//					if(key>1)	
//							i++;
						Stat->Posit=1;
						if(key==1 && MainKey==2){	Stat->Rate=key;	return;}
						if(MainKey==1)	Stat->Rate=key;
						//Stat->Rate=key;
					}
				}
				key=0;
			}
		}
	}
}

void ToY(Words *Head,Protoblast **Pole, struct Resault *Stat, int Line, int Col, int MainKey)
{
	int i,j,count,key=0;

	for(j=0; j<Col; j++)
	{
		count=0;
		for(i=0; i<Line; i++)
		{
			if((Head->length+i) <= Line)
			{
				for(count=0; count<Head->length; count++)
				{
					if(ZeroPasteY(Pole, Head, i, j, count))	;
					else{
						if(PasteY(Pole, Head, i, j, count))
							key++;
						else	break;
					}
				}
				if(count==Head->length)
				{
					if(Stat->Rate<key)
					{
						Stat->Col=j;
						Stat->Line=i;
						Stat->Posit=2;
						if(key==1 && MainKey==2){	Stat->Rate=key;	return;}
						if(MainKey==1)	Stat->Rate=key;
						//Stat->Rate=key;
					}
				}
				key=0;
			}
		}
	}
	return;
}

int Optimiation(Words *Head, Protoblast **Pole, int *sta, int Line, int Col, int key, Resault *Stat)
{
	int i;
	int Second=0;
	
	Stat->Rate=0;
	if(*sta>-1)
	{
		
		ToX(Head, Pole, Stat, Line, Col, key);
		ToY(Head, Pole, Stat, Line, Col, key);
		
//		if(Stat->Rate>1)	
//			key++;

		if(Stat->Rate)
		{
			if(Stat->Posit==1)
			{
				for(i=0; i<Head->length; i++)
				{
					Pole[Stat->Line][Stat->Col+i].word=Head->word[i];
					if(i==0 || Pole[Stat->Line][Stat->Col+i].color==-1)	
								Pole[Stat->Line][Stat->Col+i].color=-1;
					else{ 
						if(Pole[Stat->Line][Stat->Col+i].color!=-3)
							Pole[Stat->Line][Stat->Col+i].color=Head->count;}
					if(Pole[Stat->Line][Stat->Col+i].logic==0)
						Pole[Stat->Line][Stat->Col+i].logic=Stat->Posit;
				}
				return Stat->Rate;
			}else{
				for(i=0; i<Head->length; i++)
				{
					Pole[Stat->Line+i][Stat->Col].word=Head->word[i];
					if(i==0 || Pole[Stat->Line+i][Stat->Col].color==-1)
								Pole[Stat->Line+i][Stat->Col].color=-1;
					else{ 
						if(Pole[Stat->Line+i][Stat->Col].color!=-3)
							Pole[Stat->Line+i][Stat->Col].color=Head->count;}
					if(Pole[Stat->Line+i][Stat->Col].logic==0)
						Pole[Stat->Line+i][Stat->Col].logic=Stat->Posit;
				}
			}
			Head->key=1;
			return Stat->Rate;
		}else{
			return 0;
		}
	}else{	
		*sta=1;
		Stat->Rate=1;
		Stat->Posit=1;
		Stat->Line=Line/=2;
		Stat->Col=Col=Col/2-Head->length/2;
		for(i=0; i<(Head->length); i++)
		{
			Pole[Line][Col+i].word=Head->word[i];
			if(i==0)		Pole[Line][Col+i].color=-1;
			else			Pole[Line][Col+i].color=-3;
			Pole[Line][Col+i].logic=1;
		}
		Head->key=1;
		return 1;
	}
	return 0;
}

int GetNext(Words **Head)
{
	if(Head[0]->next != NULL)
	{	
		Head[0]=Head[0]->next;
		return 1;
	}
	return 0;
}

int IfNotOtherWord(Resault Stat, Words *Head, Protoblast **Pole, int Line, int Col, int count)
{
	if(Stat.Posit==1)
	{
		if(((Stat.Line+1)<Line) && (Pole[Stat.Line+1][Stat.Col+count].logic==2))	return 0;
		if(((Stat.Line-1)>-1)	&& (Pole[Stat.Line-1][Stat.Col+count].logic==2))	return 0;
		
	}else{
		if(((Stat.Col+1)<Col) && (Pole[Stat.Line+count][Stat.Col+1].logic==1))	return 0;
		if(((Stat.Col-1)>-1)	&& (Pole[Stat.Line+count][Stat.Col-1].logic==1))	return 0;
	}
	return 1;
}

void DelWord(Resault Stat, Words *Head, Protoblast **Pole, int Line, int Col)
{
	int count;
	if(Stat.Posit==1)
	{
		for(count=0; count<(Head->length); count++)
		{
			if(Pole[Stat.Line][Stat.Col+count].logic==Stat.Posit)/* && 
				IfNotOtherWord(Stat, Head, Pole, Line, Col, count))*/
			{
				Pole[Stat.Line][Stat.Col+count].color=0;
				Pole[Stat.Line][Stat.Col+count].word=0;
				Pole[Stat.Line][Stat.Col+count].logic=0;
			}
		}
	}else{
		for(count=0; count<(Head->length); count++)
		{
			if(Pole[Stat.Line+count][Stat.Col].logic==Stat.Posit)/* &&
				IfNotOtherWord(Stat, Head, Pole, Line, Col, count))*/
			{
				Pole[Stat.Line+count][Stat.Col].color=0;
				Pole[Stat.Line+count][Stat.Col].word=0;
				Pole[Stat.Line+count][Stat.Col].logic=0;
			}
		}
	}
}

void WriteToMem(Words *Nachalo, Words *Head, Protoblast **Pole, int sta, int Line, int Col,
	int key, int Pos, int Max, int Result, Perfect *Maybe)
{
	int i=0,cic=0;
	Resault Stat;
	Stat.Rate=0;

	Head=Nachalo;
	Pos++;
	while(GetNext(&Head))
	{
		if(Head->flag!=1)
		{
			cic=1;
			Head->flag=1;
			if((i=Optimiation(Head, Pole, &sta, Line, Col, key, &Stat)) == 0)
			{	
				//DelWord(Stat, Head, Pole);
				cic=0;
				Head->flag=0;
				continue;
			}

			Maybe->word=Head->word;
			Maybe->Line=Stat.Line;
			Maybe->Col=Stat.Col;
			Maybe->key=Stat.Posit;
			Maybe->number=Head->count;

			WriteToMem(Nachalo, Head, Pole, sta, Line, Col, key, Pos, Max, i+Result, Maybe->next);
			Head->flag=0;
			if(Result==0)	sta=-1;
			DelWord(Stat, Head, Pole, Line, Col);
		}
	}
	if(cic==0)	return;
	
//	MainInitGraphics(Pole, Line, Col);
	if(Pos==Max)
	{
		if(Rat<(Result+i))
		{
			Rat=Result+i;
			Ravno(Maybe, Max);
		}
	}
	//MainInitGraphics(Pole, Line, Col);
		
		//printf("\n");
	Pos--;

	return;
}

void WriteToPole(Protoblast **Pole, int max, Words *Head)
{
	int i;
	for(;max>0; max--)
	{
		if((Origin->key==0) && (Origin->number==0))	return;

		if(Origin->key==1)
		{
			for(i=0; Origin->word[i]!=0; i++)
			{
				Pole[Origin->Line][Origin->Col+i].word=Origin->word[i];
				if(Pole[Origin->Line][Origin->Col+i].color!=-1)
				{
					if(i==0)	Pole[Origin->Line][Origin->Col+i].color=-1;
					else		Pole[Origin->Line][Origin->Col+i].color=Origin->number;
				}
				Pole[Origin->Line][Origin->Col+i].logic=Origin->key;
			}
		}else{
			for(i=0; Origin->word[i]!=0; i++)
			{
				Pole[Origin->Line+i][Origin->Col].word=Origin->word[i];
				if(Pole[Origin->Line+i][Origin->Col].color!=-1)
				{
					if(i==0)	Pole[Origin->Line+i][Origin->Col].color=-1;
					else		Pole[Origin->Line+i][Origin->Col].color=Origin->number;
				}
				Pole[Origin->Line+i][Origin->Col].logic=Origin->key;
			}
		}
		Head->key=1;
		Head=Head->next;
		Origin=Origin->next;
	}
}

char destr(Words *Head)
{
	char c=1;
	if(Head==NULL)	return c;
	c=Head->key;
	c*=destr(Head->next);
	//c*=destr(Head->right);
	
	if(Head->word!=NULL)	free(Head->word);

	free(Head);
	return c;
}

int main(int argcp, char **argv)
{
	Protoblast **Pole;
	int Col, Line,x,y,i=0, length=0;
	Words *Head, *Nachalo;
	Perfect *Maybe;
	int sta=0,dump=0;
	int Max;
	int answ;
	char *str;
	char prov;

	GetWords(&Head, &Line, &Col);
	Nachalo=Head;
	Max=Line;
	while(length!=1 && (i!=1 || i!=2))
	{
		printf("Choose: 1-Smin, 2-Smax\n");
		length=Entr(&str);
		printf("\n");
		i=atoi(str);
		free(str);
	}
	answ=i;
	CreatePerfect(&Origin, Max);
	CreatePerfect(&Maybe, Max);

		Line*=2;
		Col*=2;

		Pole=(Protoblast**)malloc(sizeof(Protoblast*)*Line);
		for(i=0; i!=Line; i++)
		{
			Pole[i]=(Protoblast*)calloc(1,sizeof(Protoblast)*Col);
		}

		sta=-1;
		if(answ==1)	WriteToMem(Nachalo, Head, Pole, sta, Line, Col, 1, 0, Max, 0, Maybe);
		if(answ==2)	WriteToMem(Nachalo, Head, Pole, sta, Line, Col, 2, 0, Max, 0, Maybe);

		WriteToPole(Pole, Max, Head);

		DelPerfect(Origin);
		DelPerfect(Maybe);

		if(destr(Head))
		{
			MainInitGraphics(Pole, Line, Col, argcp, argv);
		}else{
			for(i=0; i!=Line; i++)
			{
				free(Pole[i]);
			}
			free(Pole);
			printf("Error");
			getchar();
		}
	}