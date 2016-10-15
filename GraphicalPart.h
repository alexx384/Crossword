#include "GL/glut.h"


struct Kletka
{
	char word;
	char logic;
	char color;
}typedef Protoblast;

struct Gam
{
	float r,g,b;
}typedef ColorRGB;


void MainInitGraphics(Protoblast **str, int Line, int Col, int argcp, char **argv);