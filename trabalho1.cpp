#include <GLUT/glut.h>
#include <iostream>
#include <cmath>
GLfloat angle, fAspect, largura, altura, xcamera, ycamera, zcamera;
GLfloat ajusteMonitor = 0;
bool ledAceso = true;
GLfloat alturaMesa = 1.0;
GLfloat alturaGabinete = 0.7;
GLfloat posicaoBolaX = 0.0;
GLfloat posicaoBolaY = -1.3;

// Bola
GLfloat rotacaoBola = 0.0;
GLfloat anguloTrajetoria = 0.0;   
GLfloat raioCirculo = 0.8;        
GLfloat velocidadeAngular = 0.05; 
GLfloat centroX = 0.1;
GLfloat centroY = 0.0;

void desenharMesa() {
    // Tampo da mesa
    glColor3f(0.6f, 0.3f, 0.0f);
    glPushMatrix();
        glTranslatef(0.0, 0.0, 1.0);
        glScalef(2.0, 3.0, 0.2);
        glutSolidCube(1.0);
    glPopMatrix();

    // Pernas da mesa
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

void desenharBola() {
    // Normaliza a rotação (0°–360°) para 0–1
    float t = fmod(rotacaoBola, 360.0f) / 360.0;

    // Fator de velocidade da cor (quanto maior, mais lento)
    float speed = 0.2;

    float r = fabs(sin(t * M_PI * 2 * speed));
    float g = fabs(sin(t * M_PI * 2 * speed + 2.0));
    float b = fabs(sin(t * M_PI * 2 * speed + 4.0));

    glColor3f(r, g, b); // cor muda conforme a rotação

    glPushMatrix();
        // posição sobre a mesa
        glTranslatef(posicaoBolaX, posicaoBolaY, alturaMesa + 0.16); 
        
        // rotação em torno do eixo Y (como se estivesse rolando no eixo X)
        glRotatef(rotacaoBola, 0, 1, 0);          
        glutSolidSphere(0.06, 30, 30);             
    glPopMatrix();
}


void desenharGabinete() {
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
        glTranslatef(0.0, 1.2, alturaMesa + alturaGabinete / 2.0); 
        glScalef(0.8, 0.5, alturaGabinete);
        glutSolidCube(1.0);
    glPopMatrix();
}

void desenharLedGabinete() {
    if (ledAceso) {
        glColor3f(0.0f, 1.0f, 0.0f);  // Verde aceso
    } else {
        glColor3f(0.0f, 0.2f, 0.0f);  // Verde apagado
    }

    glPushMatrix();
        glTranslatef(0.35, 1.4, alturaMesa + 0.6);
        glScalef(0.15, 0.01, 0.03);
        glutSolidCube(1.0);
    glPopMatrix();
}


void desenharMonitor() {
    // Tela
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
        glTranslatef(0.0, 0.0, 1.55);
        glScalef(0.05, 1.0 + ajusteMonitor, 0.6);
        glutSolidCube(1.0);
    glPopMatrix();

    // Suporte
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
        glTranslatef(-0.08, 0.0, 1.3);
        glScalef(0.1, 0.1, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();
}

void desenharTeclado() {
    glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix();
        glTranslatef(0.5, 0, 1.1); 
        glScalef(0.4, 0.8, 0.05);
        glutSolidCube(1.0);
    glPopMatrix();
}

void desenharMouse() {
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
        glTranslatef(0.5, 0.5, 1.1);
        glScalef(0.15, 0.1, 0.1);
        glutSolidCube(1.0);
    glPopMatrix();
}

void timerBola(int value) {
    // atualiza ângulo da trajetória
    anguloTrajetoria += velocidadeAngular;
    if (anguloTrajetoria > 360.0f) anguloTrajetoria -= 360.0f;

    // posição da bola em círculo
    posicaoBolaX = centroX + raioCirculo * cos(anguloTrajetoria);
    posicaoBolaY = centroY + raioCirculo * sin(anguloTrajetoria);

    // rotação da bola em si (rolando)
    rotacaoBola += 10.0;
    if (rotacaoBola > 360.0) rotacaoBola -= 360.0;

    glutPostRedisplay();
    glutTimerFunc(30, timerBola, 0); // ~33 fps
}

void timerLed(int value) {
    ledAceso = !ledAceso;
    glutPostRedisplay();

    // Reagenda o timer
    glutTimerFunc(1000, timerLed, 0);
}



void Desenha() {

	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(xcamera, ycamera, zcamera,
              0.0, 0.0, 1.0,
              0.0, 0.0, 1.0);

    desenharMesa();
    desenharBola();
    desenharGabinete();
    desenharLedGabinete();
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

        // monitor
        case '+':
            if (ajusteMonitor < 0.8) {
                ajusteMonitor += 0.1;
            }
            break;

        case '-':
            if (ajusteMonitor > -0.2) {
                ajusteMonitor -= 0.1;
            }
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
    glutCreateWindow("Cena 3D - Mesa, Gabinete, Monitor, Teclado e Mouse");

    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutMouseFunc(GerenciaMouse);
    glutKeyboardFunc(GerenciaTeclado);
    glutSpecialFunc(TeclasEspeciais);

    Inicializa();
    glutTimerFunc(0, timerBola, 0);
    glutTimerFunc(0, timerLed, 0);
    glutMainLoop();

    return 0;
}
