#include <GL/glut.h>

void Draw(){
	
	//Define a cor de fundo da cena
	glClearColor(1,1,1,0);

	//Pinta a tela com a cor acima
	glClear(GL_COLOR_BUFFER_BIT);
	
	//Cor do muro
	glColor3f(0,0,1);

	//Muro
	glBegin(GL_POLYGON);
		//Top left
		glVertex2f(40,20);
		//Top right
		glVertex2f(60,20);
		//Bottom right
		glVertex2f(60,0);
		//Bottom left
		glVertex2f(40,0);
	glEnd();

	//Cor do telhado
	glColor3f(1,0,0);
	
	//Telhado
	glBegin(GL_TRIANGLES);
		glVertex2f(40,20);
		glVertex2f(60,20);
		glVertex2f(50,30);
	glEnd();

	//Cor da porta
	glColor3f(1,1,1);
	
	//Porta
	glBegin(GL_QUADS);
		//Top left
		glVertex2f(45,10);
		//Top right
		glVertex2f(50,10);
		//Bottom right
		glVertex2f(50,0);
		//Bottom left
		glVertex2f(45,0);
	glEnd();
	
	//Cor da janela
	glColor3f(1,1,1);

	//Porta
	glBegin(GL_QUADS);
		//Top left
		glVertex2f(52,11);
		//Top right
		glVertex2f(56,11);
		//Bottom right
		glVertex2f(56,7);
		//Bottom left
		glVertex2f(52,7);
	glEnd();	

	//Cor da grade da janela
	glColor3f(0,0,1);

	//Grade 1
	glBegin(GL_LINES);
		//Top left
		glVertex2f(54,11);
		//Top right
		glVertex2f(54,7);
	glEnd();

	//Cor da grade da janela
	glColor3f(0,0,1);

	//Grade 1
	glBegin(GL_LINES);
		//Top left
		glVertex2f(52,9);
		//Top right
		glVertex2f(56,9);
	glEnd();	

	//Forca o glut
	glFlush();

}

int main(int argc, char *argv[]){

	//Iniciando uma instancia da glut
	glutInit(&argc,argv);

	//Deifne o modo de display do buffer
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	//Define o tamanho da tela em pixels
	glutInitWindowSize(400,300);

	//Define a posicao da tela
	glutInitWindowPosition(450,100);

	//Define o titulo da janela
	glutCreateWindow("Casa");

	//Define a funcao de rendering
	glutDisplayFunc(Draw);

	//Define o plano ortogonal
	gluOrtho2D(0,100,0,100);

	//Inicia as operacoes da glut
	glutMainLoop();

	return 0;
}
