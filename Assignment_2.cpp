#include <freeglut.h>
#include <vector>
#include <cmath>
#include <string>

std::vector<float> points;
const size_t maxPoints = 6;

int currentDepth = 0;
bool drawingComplete = false;
float rotationAngle = 0.0f;
const float rotationSpeed = 0.5f;

// point
void drawCircle(float x, float y, float radius)
{
    const int num_segments = 100;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= num_segments; ++i)
    {
        float angle = 2.0f * 3.1415926f * i / num_segments;
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

// rotation
void applyRotation(float &x, float &y, float angle, float cx, float cy)
{
    float radians = angle * 3.1415926f / 180.0f;
    float s = sinf(radians);
    float c = cosf(radians);
    x -= cx;
    y -= cy;
    float xnew = x * c - y * s;
    float ynew = x * s + y * c;
    x = xnew + cx;
    y = ynew + cy;
}

// Sierpiński triangle with rotation
void drawSierpinski(float x1, float y1, float x2, float y2, float x3, float y3, int depth, float angle)
{
    if (depth == 0)
    {

        float grayValue = 0.2f + 0.8f * (float)currentDepth / 5.0f; // depth
        glColor3f(grayValue, grayValue, grayValue);
        float cx = (x1 + x2 + x3) / 3.0f;
        float cy = (y1 + y2 + y3) / 3.0f;

        applyRotation(x1, y1, angle, cx, cy);
        applyRotation(x2, y2, angle, cx, cy);
        applyRotation(x3, y3, angle, cx, cy);

        glBegin(GL_TRIANGLES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
        glEnd();
    }
    else
    {
        float mx1 = (x1 + x2) / 2.0f;
        float my1 = (y1 + y2) / 2.0f;
        float mx2 = (x2 + x3) / 2.0f;
        float my2 = (y2 + y3) / 2.0f;
        float mx3 = (x1 + x3) / 2.0f;
        float my3 = (y1 + y3) / 2.0f;
        drawSierpinski(x1, y1, mx1, my1, mx3, my3, depth - 1, angle);
        drawSierpinski(mx1, my1, x2, y2, mx2, my2, depth - 1, angle);
        drawSierpinski(mx3, my3, mx2, my2, x3, y3, depth - 1, angle);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (points.size() == maxPoints)
    {
        float cx = (points[0] + points[2] + points[4]) / 3.0f;
        float cy = (points[1] + points[3] + points[5]) / 3.0f;
        float x1 = points[0], y1 = points[1];
        float x2 = points[2], y2 = points[3];
        float x3 = points[4], y3 = points[5];

        applyRotation(x1, y1, rotationAngle, cx, cy);
        applyRotation(x2, y2, rotationAngle, cx, cy);
        applyRotation(x3, y3, rotationAngle, cx, cy);

        // Draw the Sierpiński triangle
        drawSierpinski(x1, y1, x2, y2, x3, y3, currentDepth, rotationAngle);

        if (!drawingComplete)
        {
            glColor3f(1.0, 0.0, 0.0); // point
            for (size_t i = 0; i < points.size(); i += 2)
            {
                drawCircle(points[i], points[i + 1], 0.02f);
            }
        }
    }

    glColor3f(0.8, 0.8, 0.8);
    glRasterPos2f(-0.95f, -0.95f);
    std::string text = "Devansh_500107123";
    for (char c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glFlush();
}

// Timer functio
void timer(int value)
{
    if (drawingComplete)
    {
        rotationAngle += rotationSpeed;
        if (rotationAngle >= 360.0f)
        {
            rotationAngle -= 360.0f;
        }
        glutPostRedisplay();
        glutTimerFunc(16, timer, 0);
    }
    else
    {
        if (currentDepth < 5)
        { // depth
            ++currentDepth;
            glutPostRedisplay();
            glutTimerFunc(500, timer, 0);
        }
        else
        {
            drawingComplete = true;
            glutPostRedisplay();
            glutTimerFunc(16, timer, 0);
        }
    }
}

// mouse
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && points.size() < maxPoints)
    {
        float x_pos = (float)x / (glutGet(GLUT_WINDOW_WIDTH) / 2) - 1.0f;
        float y_pos = 1.0f - (float)y / (glutGet(GLUT_WINDOW_HEIGHT) / 2);
        points.push_back(x_pos);
        points.push_back(y_pos);

        if (points.size() == maxPoints)
        {
            glutTimerFunc(500, timer, 0);
        }
        glutPostRedisplay();
    }
}

void init()
{
    glClearColor(0.1, 0.2, 0.4, 1.0);
    glColor3f(1.0, 0.0, 0.0); //
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(720, 720);
    glutInitWindowPosition(50, 10);
    glutCreateWindow("Animated Sierpinski Triangle");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
