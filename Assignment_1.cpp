#include <freeglut.h>
float bgColor[3] = {1, 1, 1};
float lampColor[3] = {0.8f, 0.8f, 0.8f};
bool lampOn = false;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glRasterPos2f(-10.0f, -8.0f);

    // Render each character in the string "Devansh_500107123"
    const char *text = "Devansh_500107123";
    for (const char *c = text; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    // sidewall
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(-2.5f, 3.75f);
    glVertex2f(-2.5f, -5);
    glVertex2f(-9.5f, -4.5f);
    glVertex2f(-9.5f, 4);
    glEnd();

    // sideroof
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(-3, 3);
    glVertex2f(-10, 3.5f);
    glVertex2f(-6.5f, 8);
    glVertex2f(0.5f, 8);
    glEnd();

    // frontwall
    glColor3f(0.7f, 0.7f, 0.7);
    glBegin(GL_POLYGON);
    glVertex2f(0.3f, 7.7f);
    glVertex2f(03.5f, 4);
    glVertex2f(3.5f, -4.5f);
    glVertex2f(-2.5f, -5);
    glVertex2f(-2.5f, 3.75f);
    glEnd();

    // backsideroof
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(0.5f, 8);
    glVertex2f(0.3f, 7.7f);
    glVertex2f(3.5f, 4.0f);
    glVertex2f(4, 3.8f);
    glEnd();

    // door
    glColor3f(0.3f, 0.15f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.5f, -1);
    glVertex2f(1.5f, -0.90f);
    glVertex2f(1.5f, -4.7f);
    glVertex2f(-0.5f, -4.9f);
    glEnd();

    // windowsmall
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(0.3f, 6);
    glVertex2f(1, 5);
    glVertex2f(0.3f, 4);
    glVertex2f(-0.4, 4.9f);
    glEnd();

    // window2frame
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(-7.75f, 1);
    glVertex2f(-4.75f, 0.8f);
    glVertex2f(-4.75f, -1.5);
    glVertex2f(-7.75f, -1.3f);
    glEnd();

    // window2
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_QUADS);
    glVertex2f(-7.55f, 0.75f);
    glVertex2f(-4.95f, 0.55f);
    glVertex2f(-4.95f, -1.25);
    glVertex2f(-7.55f, -1.05f);

    // base1
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(-9.5f, -4.5f);
    glVertex2f(-2.5f, -5);
    glVertex2f(-2.5, -6);
    glVertex2f(-10, -5.5);
    glEnd();

    // base2
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(-2.5f, -5);
    glVertex2f(3.5f, -4.5f);
    glVertex2f(3.9, -5.3f);
    glVertex2f(-2.5, -6);
    glEnd();

    // pollbase1
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(8.5, -5);
    glVertex2f(8.5, 6);
    glVertex2f(9, 6);
    glVertex2f(9, -5);
    glVertex2f(9.5, -6);
    glVertex2f(8, -6);
    glEnd();

    // pollbase2
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(8.5, 6);
    glVertex2f(5.5, 6);
    glVertex2f(5.5, 5.5);
    glVertex2f(8.5, 5.5);
    glEnd();

    // pollbase3
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(6, 5.5f);
    glVertex2f(6.5f, 5.5f);
    glVertex2f(6.5f, 4.5f);
    glVertex2f(6, 4.5f);
    glEnd();

    // lamp
    glColor3f(lampColor[0], lampColor[1], lampColor[2]);
    glBegin(GL_POLYGON);
    glVertex2f(6.5f, 4.5f);
    glVertex2f(7, 4);
    glVertex2f(7, 3.5);
    glVertex2f(6.5f, 3);
    glVertex2f(6, 3);
    glVertex2f(5.5, 3.5);
    glVertex2f(5.5, 4);
    glVertex2f(6, 4.5f);
    glEnd();

    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-11.0, 11.0, -9.0, 9.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        float lampXMin = 5.5f, lampXMax = 7.0f, lampYMin = 3.0f, lampYMax = 4.5f;
        float normalizedX = (float)x / glutGet(GLUT_WINDOW_WIDTH) * 22.0f - 11.0f;
        float normalizedY = (float)(glutGet(GLUT_WINDOW_HEIGHT) - y) / glutGet(GLUT_WINDOW_HEIGHT) * 18.0f - 9.0f;

        if (normalizedX >= lampXMin && normalizedX <= lampXMax && normalizedY >= lampYMin && normalizedY <= lampYMax)
        {
            lampOn = !lampOn;
            if (lampOn)
            {
                bgColor[0] = 0.0f;
                bgColor[1] = 0.0f;
                bgColor[2] = 0.0f;
                lampColor[0] = 1.0f;
                lampColor[1] = 1.0f;
                lampColor[2] = 0.0f;
            }
            else
            {
                bgColor[0] = 1.0f;
                bgColor[1] = 1.0f;
                bgColor[2] = 1.0f;
                lampColor[0] = 0.8f;
                lampColor[1] = 0.8f;
                lampColor[2] = 0.8f;
            }
            glClearColor(bgColor[0], bgColor[1], bgColor[2], 1.0f);
            glutPostRedisplay();
        }
    }
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Window size
    glutInitWindowSize(960, 540);
    // Window position
    glutInitWindowPosition(100, 100);

    // Create the window
    glutCreateWindow("Hut");

    // Set the background color
    glClearColor(bgColor[0], bgColor[1], bgColor[2], 1.0f);

    // Set up display and reshape callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);

    // Enter the main loop
    glutMainLoop();
    return 0;
}