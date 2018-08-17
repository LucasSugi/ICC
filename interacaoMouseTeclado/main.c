#include <GL/glut.h>

GLfloat R = 0,G = 0,B = 0;

void Draw(){
	
	//Define a cor da janela
	glClearColor(R,G,B,0);

	//Pinta a tela com a cor acima
	glClear(GL_COLOR_BUFFER_BIT);

	//Libera o fluxo
	glFlush();
}

void MyMouse(int button, int state, int x, int y){

	if(state == GLUT_DOWN){
		if(button == GLUT_LEFT_BUTTON){
			if(R >0){
				R -= 0.1;
			}
		}
		else if(button == GLUT_RIGHT_BUTTON){
			if(R<1){
				R += 0.1;
			}
		}
		glutPostRedisplay();
	}
}

void MyKeyboard(unsigned char key, int x, int y){
	
	if(key == 'a'){
		if(G >0){
			G -= 0.1;
		}
	}
	else if(key == 'b'){
		if(G<1){
			G += 0.1;
		}
	}	
	glutPostRedisplay();
}

void MySpecial(int key,int x, int y){
	
	if(key == GLUT_KEY_DOWN){
		if(B>0){
			B -= 0.1;
		}
	}
	else if(key == GLUT_KEY_UP){
		if(B<1){
			B += 0.1;
		}
	}
	
	glutPostRedisplay();
}

int main(int argc, char *argv[]){
	
	//Inicia uma instancia da glut
	glutInit(&argc,argv);
	
	//Modo de display
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	//Tamanho da janela
	glutInitWindowSize(400,300);

	//Posicao da janela
	glutInitWindowPosition(450,100);

	//Titulo da janela
	glutCreateWindow("Interacao");

	//Rendering
	glutDisplayFunc(Draw);
	
	//Funcao de tratamento do mouse
	glutMouseFunc(MyMouse);
	
	//Funcao de tratamento do teclado
	glutKeyboardFunc(MyKeyboard);
	
	//Funcao de tratamento para teclas especiais
	glutSpecialFunc(MySpecial);

	//Define o plano ortogonal
	gluOrtho2D(-200,200,-200,200);

	//Inica as operacoes
	glutMainLoop();

	return 0;
}
