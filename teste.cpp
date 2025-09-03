#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <iostream>

void init() {
    glClearColor(0.8, 0.8, 0.8, 1.0); // Cor de fundo (cinza claro)
    glEnable(GL_DEPTH_TEST);          // Ativar profundidade
}

void desenharMesa() {
    // Cor do tampo da mesa (marrom claro)
    glColor3f(0.6f, 0.3f, 0.0f);
    glPushMatrix();
        glTranslatef(0.0, 1.0, 0.0);
        glScalef(3.0, 0.2, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Cor das pernas (marrom escuro)
    glColor3f(0.4f, 0.2f, 0.0f);
    float pernaAltura = 1.0;
    float pernaX = 1.3;
    float pernaZ = 0.8;

    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            glPushMatrix();
                glTranslatef(i * pernaX, pernaAltura / 2.0, j * pernaZ);
                glScalef(0.1, pernaAltura, 0.1);
                glutSolidCube(1.0);
            glPopMatrix();
        }
    }
}

void desenharCPU() {
    // Cor do gabinete (cinza escuro)
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
        float alturaMesa = 1.0;
        float alturaGabinete = 0.7;
        glTranslatef(1.2, alturaMesa + alturaGabinete / 2.0, 0.0); 
        glScalef(0.5, alturaGabinete, 0.8);
        glutSolidCube(1.0);
    glPopMatrix();
}

void desenharMonitor() {
    // Cor da tela (preta)
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
        glTranslatef(0.0, 1.4, 0.0);
        glScalef(1.0, 0.6, 0.05);
        glutSolidCube(1.0);
    glPopMatrix();

    // Cor do suporte (cinza)
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
        glTranslatef(0.0, 1.15, -0.5);
        glScalef(0.1, 0.3, 0.1);
        glutSolidCube(1.0);
    glPopMatrix();
}

void desenharTeclado() {
    // Cor do teclado (cinza claro)
    glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix();
        // Centralizado no eixo X, perto da borda da frente da mesa (Z positivo maior)
        // Dimensões mais finas para parecer teclado
        glTranslatef(0.15, 1.15, 0.7); 
        glScalef(0.8, 0.05, 0.4);
        glutSolidCube(1.0);
    glPopMatrix();
}

void desenharMouse() {
    // Cor do mouse (cinza escuro)
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
        // Um pouco para a direita do teclado
        glTranslatef(0.9, 1.0, 0.75);
        glScalef(0.15, 0.35, 0.1);
        glutSolidCube(1.0);
    glPopMatrix();
}



void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(5.0, 4.0, 5.0,
              0.0, 1.0, 0.0,
              0.0, 1.0, 0.0);

    desenharMesa();
    desenharCPU();
    desenharMonitor();
    desenharTeclado();
    desenharMouse();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / (float)h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, aspect, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Cena 3D - Mesa, CPU, Monitor, Teclado e Mouse");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
