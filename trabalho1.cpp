#include <GL/glut.h>
#include <iostream>
GLfloat angle, fAspect, largura, altura, xcamera, ycamera, zcamera;

void desenharMesa() {
    // Cor do tampo da mesa
    glColor3f(0.6f, 0.3f, 0.0f);
    glPushMatrix();
        glTranslatef(0.0, 0.0, 1.0);
        glScalef(2.0, 3.0, 0.2);
        glutSolidCube(1.0);
    glPopMatrix();

    // Cor das pernas
    glColor3f(0.4f, 0.2f, 0.0f);
    float pernaX = 0.8;
    float pernaY = 1.3;

    glPushMatrix();
        glTranslatef(-0.8, -1.3, 0.5);
        glScalef(0.1, 0.1, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.8, -1.3, 0.5);
        glScalef(0.1, 0.1, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.8, 1.3, 0.5);
        glScalef(0.1, 0.1, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.8, 1.3, 0.5);
        glScalef(0.1, 0.1, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();
}

void desenharCPU() {
    // Cor do gabinete
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
        float alturaMesa = 1.0;
        float alturaGabinete = 0.7;
        glTranslatef(0.0, 1.2, alturaMesa + alturaGabinete / 2.0); 
        glScalef(0.8, 0.5, alturaGabinete);
        glutSolidCube(1.0);
    glPopMatrix();
}

void desenharMonitor() {
    // Cor da tela
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
        glTranslatef(0.0, 0.0, 1.55);
        glScalef(0.05, 1.0, 0.6);
        glutSolidCube(1.0);
    glPopMatrix();

    // Cor do suporte
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
        glTranslatef(-0.08, 0.0, 1.3);
        glScalef(0.1, 0.1, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();
}

void desenharTeclado() {
    // Cor do teclado
    glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix();
        // Centralizado no eixo X, perto da borda da frente da mesa (Z positivo maior)
        // Dimensões mais finas para parecer teclado
        glTranslatef(0.7, 0.15, 1.1); 
        glScalef(0.4, 0.8, 0.05);
        glutSolidCube(1.0);
    glPopMatrix();
}

void desenharMouse() {
    // Cor do mouse (cinza escuro)
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
        // Um pouco para a direita do teclado
        glTranslatef(0.75, 0.9, 1.1);
        glScalef(0.1, 0.15, 0.1);
        glutSolidCube(1.0);
    glPopMatrix();
}

void Desenha() {

	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(xcamera, ycamera, zcamera,
              0.0, 0.0, 1.0,
              0.0, 0.0, 1.0);

    desenharMesa();
    desenharCPU();
    desenharMonitor();
    desenharTeclado();
    desenharMouse();

    glutSwapBuffers();
}

void Inicializa(void) {

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 

    glEnable(GL_DEPTH_TEST);   //ativa o zBuffer

    angle = 45;
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();
	// Especifica a projeção perspectiva
	gluPerspective(angle, fAspect, 0.1, 1000);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador e do alvo
	gluLookAt(xcamera, ycamera, zcamera,  // posição da câmera
              0, 0, 0,          // posição do alvo
              0, 1, 0);         // vetor UP da câmera
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLint largura, GLint altura)
{
	// Para previnir uma divisão por zero
	if (altura == 0) altura = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, largura, altura);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)largura / (GLfloat)altura;

	EspecificaParametrosVisualizacao();
}

// Função callback chamada para gerenciar teclas especiais
void TeclasEspeciais(int key, int x, int y)
{
	if (key == GLUT_KEY_UP) {
		zcamera += 0.5;  
	}
	if (key == GLUT_KEY_DOWN) {
		zcamera -= 0.5;  
	}
	/*
	if (key == GLUT_KEY_RIGHT) {
		 
	}
	if (key == GLUT_KEY_LEFT) {
		  
	}
	*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   //aplica o zBuffer  
    EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

// Função callback chamada para gerenciar teclado
void GerenciaTeclado(unsigned char key, int x, int y) {
	switch (key) {
		case ' ': // restaura posição inicial da camera
            xcamera = 10;
            ycamera = 2;
			zcamera = 2;
			break;
		case 'w':
        case 'W':
            xcamera += -0.5;
            break;
        case 's':
        case 'S':
            xcamera -= -0.5;
            break;
        case 'a':
        case 'A':
            ycamera -= 0.5;
            break;
        case 'd':
        case 'D':
            ycamera += 0.5;
            break;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   //aplica o zBuffer  
    EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

void GerenciaMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
	
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
	
	}
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   //aplica o zBuffer  
    EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    largura = 500;
    altura = 500;
    glutInitWindowSize(largura, altura);
    fAspect = (GLfloat)largura / (GLfloat)altura;

    xcamera = 10;
    ycamera = 2;
    zcamera = 2;
    
    angle = 45;
    glutCreateWindow("Cena 3D - Mesa, CPU, Monitor, Teclado e Mouse");

    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutMouseFunc(GerenciaMouse);
    glutKeyboardFunc(GerenciaTeclado);
    glutSpecialFunc(TeclasEspeciais);

    Inicializa();
    glutMainLoop();

    return 0;
}
