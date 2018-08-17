#include <GL/glut.h>
#include <math.h>
 
void Draw(void){ 

	float inc,theta,a,b,x,y;

	//Define a cor de fundo da cena
	glClearColor(0,0,0,1);
	
	//Pinta a tela com a cor definida acima
	glClear(GL_COLOR_BUFFER_BIT);   
	
	//Define vermelho como a cor inicial do desenho
	glColor3f(0.6,0,0);

	//Centro da elipse
	x = y = 0;

	//Raios da elipse
	a = 160;
	b = 80;

	//Incremento do angulo	
	inc = 0.00001;

	//Angulo inicial
	theta = 0;

	for(;theta<=2*3.14;theta+=inc){
		glBegin(GL_TRIANGLES); 
			glVertex2f(x,y);
			glVertex2f(x + a*cos(theta),y + b*sin(theta));
			glVertex2f(x + a*cos(theta+inc),y + b*sin(theta+inc));
		glEnd();
	}
	
	//Libere o fluxo na tela
 	glFlush();     
}

int main(int argc, char *argv[]){
		
	//Inicia uma instacia da glut
	glutInit(&argc,argv);

	//Define o modo de display do buffer
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	//Define o tamanho da janela em pixels
	glutInitWindowSize(400,300);
	
	//Define a posicao da janela
	glutInitWindowPosition(450,100);

	//Define o titulo da janela
	glutCreateWindow("Elipse");

	//Rendering
	glutDisplayFunc(Draw);

	//Define o plano ortogonal em que a cena sera construida
	gluOrtho2D(-200,200,-200,200);

	//Inicia as operacoes conforme as espeficicacoes anteriores
	glutMainLoop();

	return 0;
}
