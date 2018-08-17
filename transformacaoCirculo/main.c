#include <GL/glut.h>
#include <math.h>

void Draw(){

	int a,b,r;
	float theta,h;
	
	//Cor do fundo
	glClearColor(1,1,1,0);

	//Aplica a cor acima
	glClear(GL_COLOR_BUFFER_BIT);
	//TRANSFORMACAO

	//Iniciar a matriz de transformacoes
	glMatrixMode(GL_MODELVIEW);

	//Carrega a matriz identidade
	glLoadIdentity();
	
	glScalef(1.0/5.0,1.0/5.0,0);
	glTranslatef(-10,-10,0);

	//Cor da circunferencia
	glColor3f(0,0,0);

	//Centro do circulo
	a = b = 10;

	//Raio
	r = 5;

	//Angulo inicial
	theta = 0;

	//Incremento
	h = 0.01;

	//Circunferencia
	for(;theta<=2*3.14;theta+=h){	
		glBegin(GL_TRIANGLES);
			glVertex2f(a,b);
			glVertex2f(a + r*cos(theta),b + r*sin(theta));
			glVertex2f(a + r*cos(theta+h),b + r*sin(theta+h));
		glEnd();
	}

	glFlush();
}

int main(int argc, char *argv[]){

	//Define a glut
	glutInit(&argc,argv);
	
	//Define o buffer da glut
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	//Define o tamanho em pixels da janela
	glutInitWindowSize(400,300);

	//Define a posicao da janela
	glutInitWindowPosition(450,100);

	//Define o titulo da janela
	glutCreateWindow("Circle");

	//Funcao de rendering
	glutDisplayFunc(Draw);
	
	//Especificacoes de projecoes de cena
	glMatrixMode(GL_PROJECTION);
	
	//Define o plano ortogonal
	gluOrtho2D(-20,20,-20,20);

	glutMainLoop();

	return 0;
}
