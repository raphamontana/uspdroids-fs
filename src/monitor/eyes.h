#ifndef EYES_H
#define EYES_H


#include <cmath>
#include <QGLWidget>
#include <QtGui>
#include <QtOpenGL>


typedef struct {
    GLdouble x, y, z, angx, angy, angz;
} PosicaoEspacial;


class Eyes : public QGLWidget
{
    Q_OBJECT

public:
    Eyes(QWidget *parent = 0);
    ~Eyes();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    void atualizar();

    void desenharCampo();
    void desenhaParede(GLdouble centerX, GLdouble centerZ, GLdouble tamanho, GLdouble angulo);
    void desenhaParedeGol(GLdouble centerX, GLdouble centerZ, GLdouble tamanho, GLdouble angulo);
    void desenhaParedeGolInversa(GLdouble centerX, GLdouble centerZ, GLdouble tamanho, GLdouble angulo);
    void desenhaTriangulo(GLdouble x, GLdouble y, GLdouble ang);

    void desenharMarcacoes();
    void marcacaoMais(GLdouble x, GLdouble z1, GLdouble z2, GLdouble z3);

    void desenharRobos();
    void desenharRobo(int id, GLdouble px, GLdouble py, GLdouble pz, GLdouble angx, GLdouble angy, GLdouble angz);

    void desenharBola();

    void solidCube(GLdouble cx, GLdouble cy, GLdouble cz, GLdouble dx, GLdouble dy, GLdouble dz, GLdouble ax, GLdouble ay, GLdouble az);
    void solidCone(GLdouble base, GLdouble height, GLint slices, GLint stacks);

    GLint xRot;
    GLint yRot;
    GLint rotacao;
    QPoint lastPos;
    void normalizeAngle(int *angle);

    static const double zoomMax = 10.0;
    static const double zoomMin = 0.15;
    GLdouble zoom;
    GLdouble fps;

    PosicaoEspacial time[2][3];
    PosicaoEspacial bola;
    QTime cronometro;
};

#endif // EYES_H
