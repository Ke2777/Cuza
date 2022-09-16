#include <GL/gl.h>
#include <GL/glut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(240.0, 240.0, 0.0);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 240.0, 0.0);
    glVertex3f(240.0, 0.0, 1.0);
    glEnd();

    glFlush();
    glFinish();
}

void reshape(int w, int h) // функция обработки изменения размеров окна
{
	;
}

void visibility(int state) // функция обработки изменения состояния видимости окна
{

}

void keyboard(unsigned char key, int x, int y) // функция обработки нажатия клавиш клавиатуры (только тех, что генерируют ascii-символы)
{
	;
}

void special(int key, int x, int y) // функция обработки нажатия клавиш клавиатуры (тех, что не генерируют ascii-символы)
{
	;
}

void idle() // функция, вызываемая при отсутствии других событий
{
	;
}

void mouse(int button, int state, int x, int y) // функция, обрабатывающая команды мыши
{
	;
}

void motion(int x, int y) // функция, обрабатывающая движение курсора мыши, когда зажата какая-либо кнопка мыши
{
	;
}

void passiveMotion(int x, int y) // функция, обрабатывающая движение курсора мыши, когда не зажато ни одной кнопки мыши
{
	;
}

void entry(int state) // функция, обрабатывающая движение курсора за пределы окна и его возвращение
{
	;
}

void timer(int value) // функция, вызываемая по таймеру
{
	;
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitWindowSize(240, 240);
    glutInitWindowPosition(100, 100);

    //glDepthFunc(GL_LESS);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH);
    glutCreateWindow("Test");

    glClearColor(0, 0, 0.2, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 240.0, 0.0, 240.0, -240.0, 240.0);
   // glMatrixMode(GL_MODELVIEW);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    /*
    void glutDisplayFunc (void (*func) (void)) — задает функцию рисования изображения
    void glutReshapeFunc (void (*func) (int width, int height)) — задает функцию обработки изменения размеров окна
    void glutVisibilityFunc (void (*func)(int state)) — задает функцию обработки изменения состояния видимости окна
    void glutKeyboardFunc (void (*func)(unsigned char key, int x, int y)) — задает функцию обработки нажатия клавиш клавиатуры (только тех, что генерируют ascii-символы)
    void glutSpecialFunc (void (*func)(int key, int x, int y)) — задает функцию обработки нажатия клавиш клавиатуры (тех, что не генерируют ascii-символы)
    void glutIdleFunc (void (*func) (void)) — задает функцию, вызываемую при отсутствии других событий
    void glutMouseFunc (void (*func) (int button, int state, int x, int y)) — задает функцию, обрабатывающую команды мыши
    void glutMotionFunc (void (*func)(int x, int y)) — задает функцию, обрабатывающую движение курсора мыши, когда зажата какая-либо кнопка мыши
    void glutPassiveMotionFunc (void (*func)(int x, int y)) — задает функцию, обрабатывающую движение курсора мыши, когда не зажато ни одной кнопки мыши
    void glutEntryFunc (void (*func)(int state)) — задает функцию, обрабатывающую движение курсора за пределы окна и его возвращение
    void glutTimerFunc (unsigned int msecs, void (*func)(int value), value) — задает функцию, вызываемую по таймеру
    */

    glutMainLoop();
    return 0;
}
