#include "eyes.h"


Eyes::Eyes(QWidget *parent) : QGLWidget(parent)
{
    fps  = 20.0f;
    zoom =  0.4f;
    xRot = yRot = rotacao = 0;
    time[0][0].x = -0.10;    time[0][0].y = 0.8;    time[0][0].z = 0.03500;    time[0][0].angx = 0.0;    time[0][0].angy = 0.0;    time[0][0].angz = 45.0;
    time[0][1].x = -0.30;    time[0][1].y = 0.8;    time[0][1].z = 0.03500;    time[0][1].angx = 0.0;    time[0][1].angy = 0.0;    time[0][1].angz = 0.0;
    time[0][2].x = -0.50;    time[0][2].y = 0.8;    time[0][2].z = 0.03500;    time[0][2].angx = 0.0;    time[0][2].angy = 0.0;    time[0][2].angz = 0.0;
    time[1][0].x =  0.10;    time[1][0].y = 0.8;    time[1][0].z = 0.03500;    time[1][0].angx = 0.0;    time[1][0].angy = 0.0;    time[1][0].angz = 0.0;
    time[1][1].x =  0.30;    time[1][1].y = 0.8;    time[1][1].z = 0.03500;    time[1][1].angx = 0.0;    time[1][1].angy = 0.0;    time[1][1].angz = 0.0;
    time[1][2].x =  0.50;    time[1][2].y = 0.8;    time[1][2].z = 0.03500;    time[1][2].angx = 0.0;    time[1][2].angy = 0.0;    time[1][2].angz = 0.0;
    bola.x       =  0.00;    bola.y       = 0.0;    bola.z       = 0.02135;
    cronometro.start();
}


Eyes::~Eyes()
{
}


void Eyes::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
}


void Eyes::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        // Rotaciona a camera
        glRotated(xRot / 16.0f, 1.0f, 0.0f, 0.0f);
        glRotated(yRot / 16.0f, 0.0f, 1.0f, 0.0f);
        desenharCampo();
        desenharMarcacoes();
        desenharRobos();
        desenharBola();
    glPopMatrix();
}


void Eyes::resizeGL(int width, int height)
{
    int side = qMin(4*width, 3*height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.01f, 0.01f, -0.01f, 0.01f, 0.005f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, -0.05f, -1.0f/zoom);
}


void Eyes::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}


void Eyes::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case '+':
            if (zoom < zoomMax) zoom += 0.1f;
            resizeGL(width(), height());
            updateGL();
            break;
        case '-':
            if (zoom > zoomMin) zoom -= 0.1f;
            resizeGL(width(), height());
            updateGL();
            break;
        case Qt::Key_F11:
            if (isFullScreen()) showNormal();
            else showFullScreen();
            break;
        default: break;
    }
}


void Eyes::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() && Qt::LeftButton) {
        int dx = event->x() - lastPos.x();
        int dy = event->y() - lastPos.y();

        rotacao += dy;
        if ((rotacao < 0) || (rotacao > 180)) {
            rotacao -= dy;
            dy = 0;
        }

        int angle = xRot + 8 * dy;
        normalizeAngle(&angle);
        if (angle != xRot) {
            xRot = angle;
            if (xRot < 0) xRot = 0;
        }
        angle = yRot + 8 * dx;
        normalizeAngle(&angle);
        if (angle != yRot) {
            yRot = angle;
            if (yRot < 0) yRot = 0;
        }
        updateGL();
    }
    lastPos = event->pos();
}


void Eyes::wheelEvent(QWheelEvent *event)
{
    if (event->delta() > 0) {
        if (zoom < zoomMax) zoom += 0.1f;
    }
    else if (zoom > zoomMin)
        zoom -= 0.1f;
    resizeGL(width(), height());
    updateGL();
}


void Eyes::normalizeAngle(int *angle)
{
    while (*angle < 0) *angle += 360 * 16;
    while (*angle > 360 * 16) *angle -= 360 * 16;
}


void Eyes::atualizar()
{
    if (cronometro.elapsed() > 1000.0f/fps) {
        updateGL();
        cronometro.restart();
    }
}


void Eyes::desenharCampo()
{
    // Constantes do campo - unidade em metros
    #define CAMPO_LARGURA           1.50
    #define CAMPO_ALTURA            1.30
    #define CAMPO_LADO_TRIANGULO    0.07
    #define CAMPO_GOL_TAMANHO       0.40
    #define CAMPO_GOL_PROFUNDIDADE  0.10
    #define CAMPO_X_MIN            -0.75
    #define CAMPO_X_MAX             0.75
    #define CAMPO_Y_MIN            -0.65
    #define CAMPO_Y_MAX             0.65
    #define CAMPO_DIAGONAL          sqrtf(powf(CAMPO_ALTURA, 2) + powf(CAMPO_LARGURA, 2))
    #define CAMPO_AREA_GOL_ALTURA   0.70
    #define CAMPO_AREA_GOL_LARGURA  0.15
    #define MEIA_LARGURA            CAMPO_LARGURA/2.0
    #define MEIA_ALTURA             CAMPO_ALTURA/2.0
    #define ESPESSURA_PAREDE        0.025    //largura das paredes laterais
    #define ALTURA_PAREDE           0.05  //largura das paredes laterais
    #define MEIA_ESPESSURA_PAREDE   ESPESSURA_PAREDE/2.0
    #define MEIA_ALTURA_PAREDE      ALTURA_PAREDE/2.0

    glColor3f(0.1f, 0.1f, 0.1f);
    solidCube(CAMPO_LARGURA+2*ESPESSURA_PAREDE, 0.01, CAMPO_ALTURA+2*ESPESSURA_PAREDE, 0.0, -0.005, 0.0, 0.0, 0.0, 0.0);
    solidCube(CAMPO_GOL_PROFUNDIDADE, 0.01, CAMPO_GOL_TAMANHO+2*ESPESSURA_PAREDE, CAMPO_X_MIN-CAMPO_GOL_PROFUNDIDADE/2-ESPESSURA_PAREDE, -0.005, 0.0, 0.0, 0.0, 0.0);
    solidCube(CAMPO_GOL_PROFUNDIDADE, 0.01, CAMPO_GOL_TAMANHO+2*ESPESSURA_PAREDE, CAMPO_X_MAX+CAMPO_GOL_PROFUNDIDADE/2+ESPESSURA_PAREDE, -0.005, 0.0, 0.0, 0.0, 0.0);
    desenhaParede(0, MEIA_ALTURA+MEIA_ESPESSURA_PAREDE, CAMPO_LARGURA+2*ESPESSURA_PAREDE, 0);   // Lateral inferior
    desenhaParede(0, MEIA_ALTURA+MEIA_ESPESSURA_PAREDE, CAMPO_LARGURA+2*ESPESSURA_PAREDE, 180); // Lateral superior
    desenhaParede(0, MEIA_LARGURA+CAMPO_GOL_PROFUNDIDADE+MEIA_ESPESSURA_PAREDE, 0.4+2*ESPESSURA_PAREDE,  90);    // Fundo gol direito
    desenhaParede(0, MEIA_LARGURA+CAMPO_GOL_PROFUNDIDADE+MEIA_ESPESSURA_PAREDE, 0.4+2*ESPESSURA_PAREDE, -90);    // Fundo gol esquerdo

    // Inferior
    desenhaParede(-0.4375, MEIA_LARGURA+MEIA_ESPESSURA_PAREDE, 0.45-ESPESSURA_PAREDE,  90);
    desenhaParede(-0.4375, MEIA_LARGURA+MEIA_ESPESSURA_PAREDE, 0.45-ESPESSURA_PAREDE, -90);
    // Superior
    desenhaParede( 0.4375, MEIA_LARGURA+MEIA_ESPESSURA_PAREDE, 0.45-ESPESSURA_PAREDE,  90);
    desenhaParede( 0.4375, MEIA_LARGURA+MEIA_ESPESSURA_PAREDE, 0.45-ESPESSURA_PAREDE, -90);

    desenhaParedeGol(MEIA_LARGURA+0.05,  (0.2+MEIA_ESPESSURA_PAREDE), 0.1,   0);
    desenhaParedeGol(MEIA_LARGURA+0.05,  (0.2+MEIA_ESPESSURA_PAREDE), 0.1, 180);
    desenhaParedeGolInversa(MEIA_LARGURA+0.05, -(0.2+MEIA_ESPESSURA_PAREDE), 0.1,   0);
    desenhaParedeGolInversa(MEIA_LARGURA+0.05, -(0.2+MEIA_ESPESSURA_PAREDE), 0.1, 180);

    // Triangulos
    desenhaTriangulo(-MEIA_LARGURA+2*ESPESSURA_PAREDE, -MEIA_ALTURA+2*ESPESSURA_PAREDE, 180);
    desenhaTriangulo(-MEIA_LARGURA+2*ESPESSURA_PAREDE,  MEIA_ALTURA-2*ESPESSURA_PAREDE, 270);
    desenhaTriangulo( MEIA_LARGURA-2*ESPESSURA_PAREDE,  MEIA_ALTURA-2*ESPESSURA_PAREDE,   0);
    desenhaTriangulo( MEIA_LARGURA-2*ESPESSURA_PAREDE, -MEIA_ALTURA+2*ESPESSURA_PAREDE,  90);
}


void Eyes::desenharMarcacoes()
{
        // Marcacoes
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
        glVertex3f(0.0, 0.0005, -CAMPO_ALTURA/2.0);
        glVertex3f(0.0, 0.0005,  CAMPO_ALTURA/2.0);
    glEnd();

    // Circulo Central
    glBegin(GL_LINE_LOOP);
    for (int i=0; i < 360; i++)
    {
        GLdouble degInRad = i*M_PI/180.0;
        glVertex3f(cos(degInRad)*0.20, 0.0005, sin(degInRad)*0.20);
    }
    glEnd();

    // Desenha os +
    marcacaoMais(-CAMPO_LARGURA,  0.45,  0.425,  0.475);
    marcacaoMais(-CAMPO_LARGURA,  0.00, -0.025,  0.025);
    marcacaoMais(-CAMPO_LARGURA, -0.45, -0.425, -0.475);
    marcacaoMais( CAMPO_LARGURA,  0.45,  0.425,  0.475);
    marcacaoMais( CAMPO_LARGURA,  0.00, -0.025,  0.025);
    marcacaoMais( CAMPO_LARGURA, -0.45, -0.425, -0.475);

    // Areas do gol
    glBegin(GL_LINES);
        // um gol
        glVertex3f(-CAMPO_LARGURA/2.0 - 0.005,  0.0005, -CAMPO_AREA_GOL_ALTURA/2.0);
        glVertex3f(-CAMPO_LARGURA/2.0 - 0.005,  0.0005,  CAMPO_AREA_GOL_ALTURA/2.0);

        glVertex3f(-CAMPO_LARGURA/2.0,                          0.0005,  CAMPO_AREA_GOL_ALTURA/2.0);
        glVertex3f(-CAMPO_LARGURA/2.0 + CAMPO_AREA_GOL_LARGURA, 0.0005,  CAMPO_AREA_GOL_ALTURA/2.0);

        glVertex3f(-CAMPO_LARGURA/2.0,                          0.0005,  -CAMPO_AREA_GOL_ALTURA/2.0);
        glVertex3f(-CAMPO_LARGURA/2.0 + CAMPO_AREA_GOL_LARGURA, 0.0005,  -CAMPO_AREA_GOL_ALTURA/2.0);

        glVertex3f(-CAMPO_LARGURA/2.0 + CAMPO_AREA_GOL_LARGURA, 0.0005, -CAMPO_AREA_GOL_ALTURA/2.0);
        glVertex3f(-CAMPO_LARGURA/2.0 + CAMPO_AREA_GOL_LARGURA, 0.0005,  CAMPO_AREA_GOL_ALTURA/2.0);

        // outro gol
        glVertex3f(CAMPO_LARGURA/2.0 + 0.005,  0.0005, -CAMPO_AREA_GOL_ALTURA/2.0);
        glVertex3f(CAMPO_LARGURA/2.0 + 0.005,  0.0005,  CAMPO_AREA_GOL_ALTURA/2.0);

        glVertex3f(CAMPO_LARGURA/2.0,                          0.0005,  CAMPO_AREA_GOL_ALTURA/2.0);
        glVertex3f(CAMPO_LARGURA/2.0 - CAMPO_AREA_GOL_LARGURA, 0.0005,  CAMPO_AREA_GOL_ALTURA/2.0);

        glVertex3f(CAMPO_LARGURA/2.0,                          0.0005,  -CAMPO_AREA_GOL_ALTURA/2.0);
        glVertex3f(CAMPO_LARGURA/2.0 - CAMPO_AREA_GOL_LARGURA, 0.0005,  -CAMPO_AREA_GOL_ALTURA/2.0);

        glVertex3f(CAMPO_LARGURA/2.0 - CAMPO_AREA_GOL_LARGURA, 0.0005, -CAMPO_AREA_GOL_ALTURA/2.0);
        glVertex3f(CAMPO_LARGURA/2.0 - CAMPO_AREA_GOL_LARGURA, 0.0005,  CAMPO_AREA_GOL_ALTURA/2.0);
    glEnd();

    // Meias luas
    glBegin(GL_LINE_LOOP);
        for (int i=-48; i <= 48; i++)
        {
            GLdouble degInRad = i*M_PI/180.0;
            glVertex3f(-CAMPO_LARGURA/2.0 + CAMPO_AREA_GOL_LARGURA - 0.10 + cos(degInRad)*0.15, 0.0005, sin(degInRad)*0.15);
        }
    glEnd();
    glBegin(GL_LINE_LOOP);
        for (int i=132; i <= 228; i++)
        {
            GLdouble degInRad = i*M_PI/180.0;
            glVertex3f(CAMPO_LARGURA/2.0 - CAMPO_AREA_GOL_LARGURA + 0.10 + cos(degInRad)*0.15, 0.0005, sin(degInRad)*0.15);
        }
    glEnd();

    // Marcacoes circulares
    glBegin(GL_POLYGON);
        for (int i=0; i <= 360; i++)
        {
            GLdouble degInRad = i*M_PI/180.0;
            glVertex3f(-3*CAMPO_LARGURA/8.0 + cos(degInRad)*0.01, 0.0005, -0.45 + sin(degInRad)*0.01);
        }
    glEnd();
    glBegin(GL_POLYGON);
        for (int i=0; i <= 360; i++)
        {
            GLdouble degInRad = i*M_PI/180.0;
            glVertex3f(-3*CAMPO_LARGURA/8.0 + cos(degInRad)*0.01, 0.0005, 0.45 + sin(degInRad)*0.01);
        }
    glEnd();
    glBegin(GL_POLYGON);
        for (int i=0; i <= 360; i++)
        {
            GLdouble degInRad = i*M_PI/180.0;
            glVertex3f(-CAMPO_LARGURA/8.0 + cos(degInRad)*0.01, 0.0005, -0.45 + sin(degInRad)*0.01);
        }
    glEnd();
    glBegin(GL_POLYGON);
        for (int i=0; i <= 360; i++)
        {
            GLdouble degInRad = i*M_PI/180.0;
            glVertex3f(-CAMPO_LARGURA/8.0 + cos(degInRad)*0.01, 0.0005, 0.45 + sin(degInRad)*0.01);
        }
    glEnd();
    glBegin(GL_POLYGON);
        for (int i=0; i <= 360; i++)
        {
            GLdouble degInRad = i*M_PI/180.0;
            glVertex3f(3*CAMPO_LARGURA/8.0 + cos(degInRad)*0.01, 0.0005, -0.45 + sin(degInRad)*0.01);
        }
    glEnd();
    glBegin(GL_POLYGON);
        for (int i=0; i <= 360; i++)
        {
            GLdouble degInRad = i*M_PI/180.0;
            glVertex3f(3*CAMPO_LARGURA/8.0 + cos(degInRad)*0.01, 0.0005, 0.45 + sin(degInRad)*0.01);
        }
    glEnd();
    glBegin(GL_POLYGON);
        for (int i=0; i <= 360; i++)
        {
            GLdouble degInRad = i*M_PI/180.0;
            glVertex3f(CAMPO_LARGURA/8.0 + cos(degInRad)*0.01, 0.0005, -0.45 + sin(degInRad)*0.01);
        }
    glEnd();
    glBegin(GL_POLYGON);
        for (int i=0; i <= 360; i++)
        {
            GLdouble degInRad = i*M_PI/180.0;
            glVertex3f(CAMPO_LARGURA/8.0 + cos(degInRad)*0.01, 0.0005, 0.45 + sin(degInRad)*0.01);
        }
    glEnd();
}


void Eyes::marcacaoMais(GLdouble x, GLdouble z1, GLdouble z2, GLdouble z3)
{
    glBegin(GL_LINES);
        glVertex3f(x/4.0 - 0.025,  0.0005, z1);
        glVertex3f(x/4.0 + 0.025,  0.0005, z1);
        glVertex3f(x/4.0,          0.0005, z2);
        glVertex3f(x/4.0,          0.0005, z3);
    glEnd();
}


void Eyes::desenharBola()
{
    #define RAIO_BOLA               0.02135
    glPushMatrix();
        glTranslatef(bola.x, bola.z, -bola.y);
        glColor3f(1, 0.5, 0);
        gluSphere(gluNewQuadric(), RAIO_BOLA, 16, 10);
    glPopMatrix();
}


void Eyes::desenharRobos() {
    for (int i = 0; i < 3; i++) {
        desenharRobo(i,   time[0][i].x, time[0][i].y, time[0][i].z, time[0][i].angx, time[0][i].angy, time[0][i].angz);
        desenharRobo(i+3, time[1][i].x, time[1][i].y, time[1][i].z, time[1][i].angx, time[1][i].angy, time[1][i].angz);
    }
}


void Eyes::desenharRobo(int id, GLdouble px, GLdouble py, GLdouble pz, GLdouble angx, GLdouble angy, GLdouble angz)
{
    const GLdouble ROBO_ARESTA   = 0.075;
    const GLdouble DIAMETRO_RODA = 0.025;

    // Tabela de cores
    #define AZUL                    0.0, 0.0, 1.0
    #define AMARELO                 1.0, 1.0, 0.0
    #define CYAN                    1.0, 0.0, 1.0
    #define LARANJA                 0.8, 0.6, 0.1
    #define VERDE                   0.0, 1.0, 0.0
    #define VERMELHO                1.0, 0.0, 0.0

    glColor3f(0.4f, 0.4f, 0.4f);
    solidCube(ROBO_ARESTA, ROBO_ARESTA, ROBO_ARESTA, px, pz, py, angx, angz, angy);

    glPushMatrix();
        glTranslatef(px, pz, py);
        glRotatef(angx, 0.0f, 1.0f, 0.0f);
        glRotatef(angy, 0.0f, 1.0f, 0.0f);
        glRotatef(angz, 0.0f, 1.0f, 0.0f);

        // desenho do cilindro ("eixo" das rodas)
        glColor3f(0, 0, 0);
        glTranslatef(0, -0.0125, -0.045);
        gluCylinder(gluNewQuadric(), DIAMETRO_RODA, DIAMETRO_RODA, 0.09, 20, 20);

        // calota da roda esquerda
        glColor3f(0.5, 0.5, 0.5);
        glPushMatrix();
            glTranslatef(0.5625, -0.45, 0);
            glRotatef(90, 1, 0, 0);
            glBegin(GL_POLYGON);
                for (int i = 0; i <= 360; i++) {
                    GLdouble degInRad = i*M_PI/180.0;
                    glVertex3f(-3*CAMPO_LARGURA/8.0 + cos(degInRad)*0.025, 0.0005, -0.45 + sin(degInRad)*0.025);
                }
            glEnd();
        glPopMatrix();

        // calota da roda esquerda
        glColor3f(0.5, 0.5, 0.5);
        glPushMatrix();
            glTranslatef(0.5625, -0.45, 0.09);
            glRotatef(90, 1, 0, 0);
            glBegin(GL_POLYGON);
                for (int i = 0; i <= 360; i++) {
                    GLdouble degInRad = i*M_PI/180.0;
                    glVertex3f(-3*CAMPO_LARGURA/8.0 + cos(degInRad)*0.025, 0.0005, -0.45 + sin(degInRad)*0.025);
                }
            glEnd();
        glPopMatrix();

        // face superior do cubo
        if (id <= 2) glColor3f(AMARELO); //define a cor do time de acordo com o id do robo
        else glColor3f(AZUL);
        glBegin(GL_POLYGON);
            glVertex3f( 0.03750f, 0.075f, -0.03750f);
            glVertex3f( 0.01875f, 0.075f, -0.03750f);
            glVertex3f(-0.03750f, 0.075f,  0.01875f);
            glVertex3f(-0.03750f, 0.075f,  0.03750f);
            glVertex3f(-0.01875f, 0.075f,  0.03750f);
            glVertex3f( 0.03750f, 0.075f, -0.01875f);
        glEnd();
    glPopMatrix();
}


void Eyes::desenhaParede(GLdouble centerX, GLdouble centerZ, GLdouble tamanho, GLdouble angulo)
{
    double x1 = centerX + tamanho/2;
    double x2 = centerX - tamanho/2;
    double y1 = 0.05;
    double y2 = 0.00;
    double z1 = centerZ + 0.0125;
    double z2 = centerZ - 0.0125;
    glPushMatrix();
        glRotatef(angulo, 0.0f, 1.0f, 0.0f);
        glBegin(GL_QUADS);
                //frente
            glColor3f(0.1f, 0.1f, 0.1f);
            glVertex3f(x2, y2, z1);
            glVertex3f(x1, y2, z1);
            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y1, z1);
                //direita
            glVertex3f(x1, y2, z1);
            glVertex3f(x1, y2, z2);
            glVertex3f(x1, y1, z2);
            glVertex3f(x1, y1, z1);
                //tras
            glColor3f(1.0, 1.0, 1.0);
            glVertex3f(x1, y2, z2);
            glVertex3f(x2, y2, z2);
            glVertex3f(x2, y1, z2);
            glVertex3f(x1, y1, z2);
                //esquerda
            glColor3f(0.1f, 0.1f, 0.1f);
            glVertex3f(x2, y2, z2);
            glVertex3f(x2, y2, z1);
            glVertex3f(x2, y1, z1);
            glVertex3f(x2, y1, z2);
                //superior
            glVertex3f(x2, y1, z1);
            glVertex3f(x1, y1, z1);
            glVertex3f(x1, y1, z2);
            glVertex3f(x2, y1, z2);
                //inferior
            glVertex3f(x2, y2, z2);
            glVertex3f(x1, y2, z2);
            glVertex3f(x1, y2, z1);
            glVertex3f(x2, y2, z1);
        glEnd();
    glPopMatrix();
}

void Eyes::desenhaParedeGol(GLdouble centerX, GLdouble centerZ, GLdouble tamanho, GLdouble angulo)
{
    double x1 = centerX + tamanho/2;
    double x2 = centerX - tamanho/2;
    double y1 = 0.05;
    double y2 = 0.00;
    double z1 = centerZ + 0.0125;
    double z2 = centerZ - 0.0125;
    glPushMatrix();
        glRotatef(angulo, 0.0f, 1.0f, 0.0f);
        glBegin(GL_QUADS);
                //frente
            glColor3f(0.1f, 0.1f, 0.1f);
            glVertex3f(x2, y2, z1);
            glVertex3f(x1, y2, z1);
            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y1, z1);
                //direita
            glColor3f(1.0, 1.0, 1.0);
            glVertex3f(x1, y2, z1);
            glVertex3f(x1, y2, z2);
            glVertex3f(x1, y1, z2);
            glVertex3f(x1, y1, z1);
                //tras
            glVertex3f(x1, y2, z2);
            glVertex3f(x2, y2, z2);
            glVertex3f(x2, y1, z2);
            glVertex3f(x1, y1, z2);
                //esquerda
            glVertex3f(x2, y2, z2);
            glVertex3f(x2, y2, z1);
            glVertex3f(x2, y1, z1);
            glVertex3f(x2, y1, z2);
                //superior
            glColor3f(0.1f, 0.1f, 0.1f);
            glVertex3f(x2, y1, z1);
            glVertex3f(x1, y1, z1);
            glVertex3f(x1, y1, z2);
            glVertex3f(x2, y1, z2);
                //inferior
            glVertex3f(x2, y2, z2);
            glVertex3f(x1, y2, z2);
            glVertex3f(x1, y2, z1);
            glVertex3f(x2, y2, z1);
        glEnd();
    glPopMatrix();
}

void Eyes::desenhaParedeGolInversa(GLdouble centerX, GLdouble centerZ, GLdouble tamanho, GLdouble angulo)
{
    double x1 = centerX + tamanho/2;
    double x2 = centerX - tamanho/2;
    double y1 = 0.05;
    double y2 = 0.00;
    double z1 = centerZ + 0.0125;
    double z2 = centerZ - 0.0125;
    glPushMatrix();
        glRotatef(angulo, 0.0f, 1.0f, 0.0f);
        glBegin(GL_QUADS);
                //direita
            glColor3f(0.1f, 0.1f, 0.1f);
            glVertex3f(x1, y2, z1);
            glVertex3f(x1, y2, z2);
            glVertex3f(x1, y1, z2);
            glVertex3f(x1, y1, z1);
                //tras
            glVertex3f(x1, y2, z2);
            glVertex3f(x2, y2, z2);
            glVertex3f(x2, y1, z2);
            glVertex3f(x1, y1, z2);
                //frente
            glColor3f(1.0, 1.0, 1.0);
            glVertex3f(x2, y2, z1);
            glVertex3f(x1, y2, z1);
            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y1, z1);
                //esquerda
            glVertex3f(x2, y2, z2);
            glVertex3f(x2, y2, z1);
            glVertex3f(x2, y1, z1);
            glVertex3f(x2, y1, z2);
                //superior
            glColor3f(0.1f, 0.1f, 0.1f);
            glVertex3f(x2, y1, z1);
            glVertex3f(x1, y1, z1);
            glVertex3f(x1, y1, z2);
            glVertex3f(x2, y1, z2);
                //inferior
            glVertex3f(x2, y2, z2);
            glVertex3f(x1, y2, z2);
            glVertex3f(x1, y2, z1);
            glVertex3f(x2, y2, z1);
        glEnd();
    glPopMatrix();
}

void Eyes::solidCone(GLdouble base, GLdouble height, GLint slices, GLint stacks)
{
    glBegin(GL_LINE_LOOP);
        GLUquadricObj* quadric = gluNewQuadric();
        gluQuadricDrawStyle(quadric, GLU_FILL);
        gluCylinder(quadric, base, 0, height, slices, stacks);
        gluDeleteQuadric(quadric);
    glEnd();
}

void Eyes::desenhaTriangulo(GLdouble x, GLdouble y, GLdouble ang) {
    glPushMatrix();
        glColor3f(0.1f, 0.1f, 0.1f);
        glTranslatef(x, MEIA_ALTURA_PAREDE, y);
        glRotatef(ang, 0, 1, 0);
        glBegin(GL_TRIANGLES);
            glVertex3f(2*ESPESSURA_PAREDE,  MEIA_ALTURA_PAREDE,  0);
            glVertex3f(2*ESPESSURA_PAREDE,  MEIA_ALTURA_PAREDE,  2*ESPESSURA_PAREDE);
            glVertex3f(0,                   MEIA_ALTURA_PAREDE,  2*ESPESSURA_PAREDE);
        glEnd();
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);
            glVertex3f(2*ESPESSURA_PAREDE,  MEIA_ALTURA_PAREDE,  0);
            glVertex3f(0,                   MEIA_ALTURA_PAREDE,  2*ESPESSURA_PAREDE);
            glVertex3f(0,                  -MEIA_ALTURA_PAREDE,  2*ESPESSURA_PAREDE);
            glVertex3f(2*ESPESSURA_PAREDE, -MEIA_ALTURA_PAREDE,  0);
        glEnd();
    glPopMatrix();
}


void Eyes::solidCube(GLdouble cx, GLdouble cy, GLdouble cz, GLdouble dx, GLdouble dy, GLdouble dz, GLdouble ax, GLdouble ay, GLdouble az)
{
    glPushMatrix();
        glTranslatef(dx, dy, dz);				// Move Right And Into The Screen
        glRotatef(ax, 1.0f, 0.0f, 0.0f);			// Rotate The Cube On X, Y & Z
        glRotatef(ay, 0.0f, 1.0f, 0.0f);			// Rotate The Cube On X, Y & Z
        glRotatef(az, 0.0f, 0.0f, 1.0f);			// Rotate The Cube On X, Y & Z
        glScalef(cx/2.0f, cy/2.0f, cz/2.0f);

        glBegin(GL_QUADS);                              // Start Drawing The Cube
            glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Top)
            glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Top)
            glVertex3f(-1.0f, 1.0f, 1.0f);			// Bottom Left Of The Quad (Top)
            glVertex3f( 1.0f, 1.0f, 1.0f);			// Bottom Right Of The Quad (Top)
            glVertex3f( 1.0f,-1.0f, 1.0f);			// Top Right Of The Quad (Bottom)
            glVertex3f(-1.0f,-1.0f, 1.0f);			// Top Left Of The Quad (Bottom)
            glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Bottom)
            glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Bottom)
            glVertex3f( 1.0f, 1.0f, 1.0f);			// Top Right Of The Quad (Front)
            glVertex3f(-1.0f, 1.0f, 1.0f);			// Top Left Of The Quad (Front)
            glVertex3f(-1.0f,-1.0f, 1.0f);			// Bottom Left Of The Quad (Front)
            glVertex3f( 1.0f,-1.0f, 1.0f);			// Bottom Right Of The Quad (Front)
            glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Back)
            glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Back)
            glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Back)
            glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Back)
            glVertex3f(-1.0f, 1.0f, 1.0f);			// Top Right Of The Quad (Left)
            glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Left)
            glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Left)
            glVertex3f(-1.0f,-1.0f, 1.0f);			// Bottom Right Of The Quad (Left)
            glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Right)
            glVertex3f( 1.0f, 1.0f, 1.0f);			// Top Left Of The Quad (Right)
            glVertex3f( 1.0f,-1.0f, 1.0f);			// Bottom Left Of The Quad (Right)
            glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Right)
        glEnd();                                        // Done Drawing The Quad
    glPopMatrix();
}
