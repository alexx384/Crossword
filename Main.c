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

/* In this structure we are writing the words from OUTPUT.TXT */
struct Words
{
	char *word;				/* The word */
	int length;
	char key;
	struct Words *next, *past;
	int count;
	char flag;
	int divisibility;
} typedef Words;

Perfect *Origin;
int Rat=0;

/* free PERFECT structure */
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
	Perfect *Dump;
	Dump=Origin;
	
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

/* Create MAX count of elements */
void CreatePerfect(Perfect **Top, int max)
{
	Perfect *Dump;
	Dump=Top[0]=(Perfect*)calloc(1,sizeof(Perfect));
	
	for(;max>0; max--)
	{
 /* Create and configure next element */		
		Top[0]->next=(Perfect*)calloc(1,sizeof(Perfect));
		Top[0]->next->past=Top[0];

 /* Switch to the next element */		
		Top[0]=Top[0]->next;
	}

 /* Switch to start element */	
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

/* Initialize WORDS for reading word*/
Words *CreateWords(Words *Head, int *count)
{
	Head->next=(Words*)calloc(1,sizeof(Words));
	if(Head->next==NULL){		printf("[Crossword] Error memory in CreateWords");	exit(EXIT_SUCCESS);};
	
	Head->next->past=Head;
	
	Head->next->count=*count;
	Head->next->word=(char*)malloc(sizeof(char));

	if(Head->next->word==NULL){	printf("[Crossword] Error memory in CreateWords");	exit(EXIT_SUCCESS);}

	*count+=1;
	return Head->next;
}

/* In this function we are reading all word from file OUTPUT.TXT
	and writing result in struct WORDS*/
void GetWords(Words **data, int *Line, int *Col)
{
	int c;
	int i=0, max=0,n=0;
	int count=1;

	Words *Head=(Words*)calloc(1,sizeof(Words));
	Words *Dump=Head;

	FILE *Output=fopen("Output.txt", "rb+");
	if( !Output ){	printf("[Crossword] File didn't found. Error in GetWords");		exit(EXIT_SUCCESS);}

	Head->next=Dump=CreateWords(Dump, &count);

 /* Reading words from Output*/
	c=fgetc(Output);
	while(c!= EOF)
	{
 /* if we are find end of string */		
		if(c=='\n')
		{
			Dump->length=i;
			Dump->divisibility=1;
			if((i % 2) == 0)	Dump->divisibility=2;
			if((i % 3) == 0)	Dump->divisibility=3;
			if((i % 4) == 0)	Dump->divisibility=4;
			i++;
			fseek(Output, -i, SEEK_CUR);
			Dump->word=(char*)realloc(Dump->word, sizeof(char)*i);
			i--;
			if(fread(Dump->word, sizeof(char), i, Output) != i){ printf("[Crossword] Error in GetWords");}
			c=fgetc(Output);
			Dump->word[i]=0;

			/*Calculate maximum length*/
			if((Dump->length)>max)	max=Dump->length;				
			
			Dump=CreateWords(Dump, &count);
			i=-1;
			n++;
		}

		i++;	
		c=fgetc(Output);
	}
	if(i!=0)
	{
		fseek(Output, -i, SEEK_CUR);
		i++;
		Dump->word=(char*)realloc(Dump->word, sizeof(char)*i);
		i--;
		if(fread(Dump->word, sizeof(char), i, Output) != i){ printf("[Crossword] Error in GetWords");}

		Dump->length=i;
		Dump->divisibility=1;
		if((i % 2) == 0)	Dump->divisibility=2;
		if((i % 3) == 0)	Dump->divisibility=3;
		if((i % 4) == 0)	Dump->divisibility=4;
		Dump->word[i]=0;
		if((Dump->length)>max)	max=Dump->length;
		n++;
	}else{
		free(Dump->word);
		free(Dump);
	}
	*Col=max;
	*Line=n;
	*data=Head;
	fclose(Output);
}
//-----------------

/* Check for horizontal position for all field */
void ToX(Words *Head,Protoblast **Pole, struct Resault *Stat, int Line, int Col, int MainKey)
{
	int i,j,count,key=0, jcount, length=Head->length;
	Protoblast *field;
	char *word=Head->word;

	for(i=0; i<Line; i++)
	{
		field=Pole[i];
		for(j=0, jcount=0; j<Col; j++)
		{
 /* if the word is fit to column from( W O R D ..| ) to ( W O R D| )  */
			if(jcount < Col)
			{
 /* Need: j, Head, Pole[i], key */				
				jcount=j;

				for(count=0; count < length; count++, jcount++)
				{
 /* if cell is not empty by x */
		
					if(field[jcount].word!=0)	
					{
						if(field[jcount].logic == 1)		
							break;
					 	/* if other crossing */
						if(field[jcount].word != word[count])
							break;

						key++;
					}
				}

				if(Stat->Rate<key)
				{
					if(count==Head->length)
					{
						Stat->Col=j;
						Stat->Line=i;

						Stat->Posit=1;
						if(key==1 && MainKey==2){	Stat->Rate=key;	return;}
						if(MainKey==1)	Stat->Rate=key;
					}
				}

				if(key==0 && count==Head->length && field[jcount].word==0)
				{
					for(jcount++; jcount<Col; jcount++)
					{
						if(field[jcount].word != 0)
							break;
					}
					j=jcount-count-1;
				}else jcount=j+length+1;
				key=0;
			}else{
				j=Col;
			}
		}
	}
}

void ToY(Words *Head,Protoblast **Pole, struct Resault *Stat, int Line, int Col, int MainKey)
{
	int i,j,count,key=0, icount, length=Head->length;
	char *word=Head->word;
	//Protoblast field;
	Protoblast m1, m2;
	//Line-=Head->length-3;

	for(j=0; j<Col; j++)
	{
		for(i=0, icount=0; i<Line; i++)
		{
			if(icount < Line)
			{
				icount=i;
				
				for(count=0; count < length; )
				{

					//field=Pole[icount][j];
					if((length-count) ==1)
					{
						m1=Pole[icount][j];

						if(m1.word!=0)	
						{
							if(m1.logic == 2)			break;
							if(m1.word != word[count])	break;
							key++;
						}
						count++;
						icount++;
					}else{
						m1=Pole[icount][j];
						m2=Pole[icount+1][j];

						if(m1.word!=0 || m2.word!=0)	
						{
							if(m1.logic == 2 || m2.logic == 2)						break;
							if(m1.word != word[count] && m1.word!=0)	break;
							if(m1.word!=0) key++;
							if(m2.word != word[count+1] && m2.word!=0)	break;
							if(m2.word!=0) key++;
						}	
							count+=2;
							icount+=2;
					}					
					//mm1=Pole[icount][j];
					//mm2=Pole[icount+1][j];
					//mm3=Pole[icount+2][j];
					//mm4=Pole[icount+3][j];
					
				}
				
				if(Stat->Rate<key)
				{
					if(count==Head->length)
					{
						Stat->Col=j;
						Stat->Line=i;
						Stat->Posit=2;
						if(key==1 && MainKey==2){	Stat->Rate=key;	return;}
						if(MainKey==1)	Stat->Rate=key;
					}
				}
				if(key==0 && count==Head->length && Pole[icount][j].word==0)
				{
					for(icount++; icount<Line; icount++)
					{
						if(Pole[icount][j].word != 0)				break;
					}
					i=icount-count-1;
				}else icount=i+length+1;
				key=0;
			}
		}
	}
	return;
}

int Optimiation(Words *Head, Protoblast **Pole, int *sta, int Line, int Col, int key, Resault *Stat)
{
	int i, StatCol, length=Head->length;
	int iStatCol, iStatLine, iCol;
	char *word=Head->word;
	Protoblast *field;

	
	Stat->Rate=0;
	if(*sta>-1)
	{		
		ToX(Head, Pole, Stat, Line, Col, key);
		/*switch(Head->divisibility)
		{
			case 1:
				ToY1(Head, Pole, Stat, Line, Col, key);						
				break;
			case 2:
				ToY2(Head, Pole, Stat, Line, Col, key);						
				break;
			case 3:
				ToY3(Head, Pole, Stat, Line, Col, key);						
				break;
			case 4:
				ToY4(Head, Pole, Stat, Line, Col, key);						
				break;		
		}*/
		ToY(Head, Pole, Stat, Line, Col, key);
		

		if(Stat->Rate)
		{
			StatCol=Stat->Col;
			if(Stat->Posit==1)
			{
				i=0;
				iStatCol=StatCol;
				field=Pole[Stat->Line];

				field[iStatCol].word = word[i];
				if(field[iStatCol].logic==0)
						field[iStatCol].logic=Stat->Posit;

				for(i++, iStatCol++; i<length; i++, iStatCol++)
				{
					field[iStatCol].word = word[i];
					if(field[iStatCol].color!=-1)	
					{ 
						if(field[iStatCol].color!=-3)
							field[iStatCol].color=Head->count;
					}
					if(field[iStatCol].logic==0)
						field[iStatCol].logic=Stat->Posit;
				}

				return Stat->Rate;
			}else{
				i=0;
				iStatLine=Stat->Line;
				Pole[iStatLine][StatCol].word = word[i];

				if(Pole[iStatLine][StatCol].logic==0)
						Pole[iStatLine][StatCol].logic=Stat->Posit;

				for(i++, iStatLine++; i<length; i++, iStatLine++)
				{
					Pole[iStatLine][StatCol].word = word[i];
					if(Pole[iStatLine][StatCol].color!=-1)
					{ 
						if(Pole[iStatLine][StatCol].color!=-3)
							Pole[iStatLine][StatCol].color=Head->count;
					}
					if(Pole[iStatLine][StatCol].logic==0)
						Pole[iStatLine][StatCol].logic=Stat->Posit;
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
		Stat->Col=Col=Col/2-length/2;
 /* Optimal variant */		
	//	Col-=length;
	//	Stat->Col=Col=Col >> 1;

		field=Pole[Line];
		field[Col].color=-1;
		for(i=1, iCol=Col+1; i<length; i++, iCol++)
		{
			field[iCol].word = word[i];
			field[iCol].color=-3;
			field[iCol].logic=1;
		}
		Head->key=1;
		return 1;
	}
	return 0;
}

/* Get the next element of Head. If next element if null return 1 */
int GetNext(Words **Head)
{
	if(Head[0]->next != NULL)
	{	
		Head[0]=Head[0]->next;
		return 1;
	}
	return 0;
}

void DelWord(Resault Stat, Words *Head, Protoblast **Pole, int Line, int Col)
{
	int count, StatCol=Stat.Col, StatLine=Stat.Line, length=Head->length, StatPosit=Stat.Posit;
	Protoblast *field;

	if(Stat.Posit==1)
	{
		field=Pole[StatLine];
		for(count=0; count < length; count++, StatCol++)
		{
			if(Pole[StatLine][StatCol].logic == StatPosit)
			{
				field[StatCol].color=0;
				field[StatCol].word=0;
				field[StatCol].logic=0;
			}
		}
	}else{
		for(count=0; count< length; count++, StatLine++)
		{
			if(Pole[StatLine][StatCol].logic == StatPosit)
			{
				Pole[StatLine][StatCol].color=0;
				Pole[StatLine][StatCol].word=0;
				Pole[StatLine][StatCol].logic=0;
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
	

	if(Pos==Max)
	{
		if(Rat<(Result+i))
		{
			Rat=Result+i;
			Ravno(Maybe, Max);
		}
	}

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

/* free WORDS structure */
char destr(Words *Head)
{
	char c;
	if(Head==NULL)	return 1;
	c=Head->key;
	c=destr(Head->next);
	
	
	if(Head->word!=NULL)	free(Head->word);

	free(Head);
	return 1;
}

int main(int argcp, char **argv)
{
	Protoblast **Pole;

	Words *Head, *Nachalo;

	Perfect *Maybe;

	int Col, Line,i=0, length=0;
	int sta=-1;
	int Max;
	int answ=0;
	char *str;

/* In this function we are reading all word from file OUTPUT.TXT
	and writing result in struct WORDS*/
	GetWords(&Head, &Line, &Col);
	Nachalo=Head;
	Max=Line;
	
	while(length!=1 && (answ!=1 || answ!=2))
	{
		printf("Choose: 1-Smin, 2-Smax\n");
		length=Entr(&str);
		printf("\n");
		answ=atoi(str);
		free(str);
	}

/* Create MAX count of elements */ 
	CreatePerfect(&Origin, Max);
	CreatePerfect(&Maybe, Max);

/* Calculate size for crosswords field */
	Line*=2;
	Col*=2;

/* Create field and initialize with NULL */
	Pole=(Protoblast**)malloc(sizeof(Protoblast*)*Line);

	for(i=0; i!=Line; i++)
	{
		Pole[i]=(Protoblast*)calloc(Col ,sizeof(Protoblast));
	}

/* Version of crossword with Minimum engaged field */
	if(answ==1)	WriteToMem(Nachalo, Head, Pole, sta, Line, Col, 1, 0, Max, 0, Maybe);
/* Version of crossword with Maximum engaged field */	
	if(answ==2)	WriteToMem(Nachalo, Head, Pole, sta, Line, Col, 2, 0, Max, 0, Maybe);

	WriteToPole(Pole, Max, Head);

/* free PERFECT structure */
	DelPerfect(Origin);
	DelPerfect(Maybe);

/* free WORDS structure */

	destr(Head);

/* Drowing field */	
	MainInitGraphics(Pole, Line, Col, argcp, argv);

/* free field (struct PROTOBLAST) */	
	for(i=0; i!=Line; i++)
	{
		free(Pole[i]);
	}
	free(Pole);
}
	