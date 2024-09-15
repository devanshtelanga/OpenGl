#include <freeglut.h>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

struct Point
{
    float x, y;
};

vector<Point> points;
vector<pair<float, float>> lines;
const int numPoints = 300;
bool point1Set = false;
Point currentStartPoint, currentEndPoint;

void calculateLine(Point p0, Point p1, float &m, float &c)
{
    m = (p1.y - p0.y) / (p1.x - p0.x);
    c = p0.y - m * p0.x;
}

void displayText(float x, float y, const std::string &text)
{
    glRasterPos2f(x, y);
    for (char c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void drawLine(Point p0, Point p1, float m, float c)
{
    glBegin(GL_POINTS);
    for (int i = 0; i <= numPoints; ++i)
    {
        float x = p0.x + i * (p1.x - p0.x) / numPoints;
        float y = m * x + c;
        glVertex2f(x, y);
    }
    glEnd();
}

void drawGrid()
{
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_LINES);
    for (float x = -1.0f; x <= 1.0f; x += 0.1f)
    {
        glVertex2f(x, -1.0f);
        glVertex2f(x, 1.0f);
    }
    for (float y = -1.0f; y <= 1.0f; y += 0.1f)
    {
        glVertex2f(-1.0f, y);
        glVertex2f(1.0f, y);
    }
    glEnd();
}

void drawAxes()
{
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(0.0f, -1.0f);
    glVertex2f(0.0f, 1.0f);
    glEnd();
    glLineWidth(1.0f);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    drawAxes();

    float m, c;
    for (size_t i = 0; i < points.size(); i += 2)
    {
        Point p0 = points[i];
        Point p1 = points[i + 1];
        m = lines[i / 2].first;
        c = lines[i / 2].second;
        glColor3f(0.0f, 0.0f, 0.0f);
        drawLine(p0, p1, m, c);
        glBegin(GL_POINTS);
        glVertex2f(p0.x, p0.y);
        glVertex2f(p1.x, p1.y);
        glEnd();
    }

    if (!lines.empty())
    {
        Point lastP0 = points[points.size() - 2];
        Point lastP1 = points.back();
        float lastM = lines.back().first;
        float lastC = lines.back().second;

        ostringstream oss;
        oss << "Slope: " << fixed << setprecision(2) << lastM
            << ", Intercept (c): " << lastC;
        displayText(-0.95f, -0.95f, oss.str());

        ostringstream cordText;
        cordText << "Start: (" << fixed << setprecision(2) << 10 * lastP0.x << ", " << 10 * lastP0.y << "), "
                 << "End: (" << 10 * lastP1.x << ", " << 10 * lastP1.y << ")";
        displayText(-0.95f, -0.90f, cordText.str());
    }

    displayText(-0.95f, 0.95f, "Devansh_500107123");

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        float openGLX = (x / (float)glutGet(GLUT_WINDOW_WIDTH)) * 2.0f - 1.0f;
        float openGLY = 1.0f - (y / (float)glutGet(GLUT_WINDOW_HEIGHT)) * 2.0f;

        if (!point1Set)
        {
            currentStartPoint = {openGLX, openGLY};
            point1Set = true;
        }
        else
        {
            currentEndPoint = {openGLX, openGLY};
            point1Set = false;
            points.push_back(currentStartPoint);
            points.push_back(currentEndPoint);
            float m, c;
            calculateLine(currentStartPoint, currentEndPoint, m, c);
            lines.push_back({m, c});
            glutPostRedisplay();
        }
    }
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'c' || key == 'C')
    {
        points.clear();
        lines.clear();
        glutPostRedisplay();
    }
}

void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(5.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(750, 750);
    glutCreateWindow("DDA Algorithm");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
