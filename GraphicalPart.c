#include "GraphicalPart.h"
#include <malloc.h>


#define QuadLength 35

Protoblast **ViewStr;
int x,y,iPresKey=0, LocalY;

void OptimumResize(int Line, int Col,int *ByX, int *ByY)
{
	int i,j;
	int counter=0;

//At-X
	for(i=0; i<Line; i++)
	{
		for(j=0; j<Col; j++)
		{
			counter+=ViewStr[i][j].logic;
		}
		if(counter==0)
		{
			*ByX-=1;
			for(j=0; j<Col; j++)
			{
				ViewStr[i][j].word=ViewStr[i][j].color=-2;
			}
		}else counter=0;
	}
//At-Y
	for(i=0; i<Col; i++)
	{
		for(j=0; j<Line; j++)
		{
			counter+=ViewStr[j][i].logic;
		}
		if(counter==0)
		{
			*ByY-=1;
			for(j=0; j<Line; j++)
			{
				ViewStr[j][i].word=ViewStr[j][i].color=-2;
			}
		}else counter=0;
	}
}

void SpecialInput(int key, int posX, int posY)
{
	int i;
	iPresKey=key;
	switch(key)
	{	
	case GLUT_KEY_DOWN:
	{
		glutDestroyWindow(1);
		for(i=0; i<y; i++)
		{
			free(ViewStr[i]);
		}
		free(ViewStr);
		exit(0);
	}
	break;
	}
	glutPostRedisplay();
}

void IfPress()
{
	int i;
	switch(iPresKey)
	{
	case GLUT_KEY_UP:
		glColorMask(GL_FALSE, GL_TRUE, GL_TRUE, GL_TRUE);
	break;	
	case GLUT_KEY_LEFT:
		glColorMask(GL_TRUE, GL_FALSE, GL_TRUE, GL_TRUE);
	break;
	case GLUT_KEY_RIGHT:
		glColorMask(GL_TRUE, GL_TRUE, GL_FALSE, GL_TRUE);
	break;
	}
}

ColorRGB Change(int count)
{
	ColorRGB Palitr;
	int a,b;

	Palitr.r=0.9;
	Palitr.g=0.7;
	Palitr.b=0.0;

	if(count!=-1)
	{
		b=count % 5+0.1;
		a=count/5+0.1;

		Palitr.r+=a*0.2;
		Palitr.g+=a*0.3;
		Palitr.b+=b*0.4;
	}

	if(count==-3)
	{
		Palitr.r=0.9;
		Palitr.g=0.5;
		Palitr.b=0.1;
	}

	while(Palitr.r>1)	Palitr.r-=1;
	while(Palitr.g>1)	Palitr.g-=1;
	while(Palitr.b>1)	Palitr.b-=1;

	return Palitr;
}

void displayDrow()	
{
	int posX=0, posY=(LocalY+1)*QuadLength, iCountX, iCountY;
	ColorRGB Palitr;
	glClear(GL_COLOR_BUFFER_BIT);

	for(iCountY=0; iCountY<y; iCountY++)
	{
		for(iCountX=0; iCountX<x; iCountX++)
		{
			if(ViewStr[iCountY][iCountX].color==-2)	continue;

			posX+=QuadLength;
			Palitr=Change(ViewStr[iCountY][iCountX].color);

			if(ViewStr[iCountY][iCountX].color!=-1)
					glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
			else	glColorMask(GL_TRUE, GL_FALSE, GL_TRUE, GL_TRUE);
			glBegin(GL_QUADS);												//Drow Quad
			if(ViewStr[iCountY][iCountX].color!=0)	glColor4f(Palitr.r, Palitr.g, Palitr.b,1.0);	//Choose Color
			else								glColor4f(0.0, 0.0, 0.0, 0.0);
				glVertex2i(posX+1, posY+QuadLength-1);				//	LeftUp
				if(ViewStr[iCountY][iCountX].color!=0)	glColor4f(Palitr.g, Palitr.r, Palitr.b,1.0);	//Choose Color
			else								glColor4f(0.0, 0.0, 0.0, 0.0);
				glVertex2i(posX+1, posY+1);							//	LeftDown
				if(ViewStr[iCountY][iCountX].color!=0)	glColor4f(Palitr.r, Palitr.g, Palitr.b,1.0);	//Choose Color
			else								glColor4f(0.0, 0.0, 0.0, 0.0);
				glVertex2i(posX+QuadLength-1, posY+1);				//	RightDown
				if(ViewStr[iCountY][iCountX].color!=0)	glColor4f(Palitr.r, Palitr.g, Palitr.b,1.0);	//Choose Color
			else								glColor4f(0.0, 0.0, 0.0, 0.0);
				glVertex2i(posX+QuadLength-1, posY+QuadLength-1);	//	RightUp
			glEnd();
			if(ViewStr[iCountY][iCountX].word==0)	continue;					//There ara nothing

			glBegin(GL_LINE_STRIP);											//Drow frame
				glColor4f(0.0, 0.0, 0.0, 0.0);
				glVertex2i(posX, posY+QuadLength);				//	LeftUp
				glVertex2i(posX, posY);							//	LeftDown
				glVertex2i(posX+QuadLength, posY);				//	RightDown
				glVertex2i(posX+QuadLength, posY+QuadLength);	//	RightUp
			glEnd();

			glColor4f(0.0, 0.0, 0.0, 0.0);
			glRasterPos2i(posX+8, posY+8);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ViewStr[iCountY][iCountX].word);	//Drow text
		}
		if(posX!=0){
			posX=0;
			posY-=QuadLength;
		}
		//posY-=QuadLength;
	}
	glFlush();  
}

void MainInitGraphics(Protoblast **str, int Line, int Col, int argcp, char **argv)
{
	int iScreenHeight, iScreenWidth;
	int iCalX, iCalY;
	int LocalX;
	char i,c;

	//FreeConsole();

	glutInit(&argcp, argv);

	ViewStr=str;
	x=LocalX=Col;
	y=LocalY=Line;

	OptimumResize(Line, Col, &LocalY, &LocalX);

	iCalX=(LocalX+2)*QuadLength;
	iCalY=(LocalY+2)*QuadLength;

	iScreenWidth=glutGet(GLUT_SCREEN_WIDTH);
	iScreenHeight=glutGet(GLUT_SCREEN_HEIGHT);

	glutInitWindowSize(iCalX, iCalY);								//Window Size
	glutInitWindowPosition((iScreenWidth-iCalX)/2, (iScreenHeight-iCalY)/2);	//Windows position
	glutCreateWindow("Crossword");								//Name of the Window
	glClearColor(0.0,0.0,0.0,0.0);								//Start Color
	gluOrtho2D(0.0, iCalX, 0.0, iCalY);							//Range of coordinates

	glutSpecialFunc(SpecialInput);

	glutDisplayFunc(displayDrow);					//In this Funcion we era draw
	
	glutMainLoop();						//i don't know why need this function
}