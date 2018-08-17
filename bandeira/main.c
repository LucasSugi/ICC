#include <GL/glut.h>
#include <math.h>

void Draw(){
	
	int a,b,r;
	float theta,h;
		
	///Define cor de fundo
	glClearColor(1,1,1,0);

	//Pinta a tela com a cor de cima
	glClear(GL_COLOR_BUFFER_BIT);
	
	//Cor verde
	glColor3f(0,1,0);
	
	glBegin(GL_QUADS);
		glVertex2f(-150,150);
		glVertex2f(150,150);
		glVertex2f(150,-150);
		glVertex2f(-150,-150);
	glEnd();

	//Cor amarelo
	glColor3f(1,1,0);
	
	glBegin(GL_QUADS);
		glVertex2f(-140,0);
		glVertex2f(0,140);
		glVertex2f(140,-0);
		glVertex2f(0,-140);
	glEnd();

	//Centro da esfera
	a = b = 0;

	//Raio da esfera
	r = 50;

	//Angulo inicial
	theta = 0;

	//Incremento de angulo
	h = 0.1;

	for(;theta<= 2 * 3.14;theta+=h){	
		//Cor azul
		glColor3f(0,0,1);
		glBegin(GL_TRIANGLES);
			glVertex2f(a,b);
			glVertex2f(a + r*cos(theta),b + r*sin(theta));
			glVertex2f(a + r*cos(theta+h),b + r*sin(theta+h));
		glEnd();
	}
	
	//Descarrega o glut
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
	glutCreateWindow("Bandeira");

	//Define a funcao de rendering
	glutDisplayFunc(Draw);

	//Define o plano ortogonal
	gluOrtho2D(-200,200,-200,200);

	//Inicia as operacoes da glut
	glutMainLoop();

	return 0;
}
