#include <freeglut.h>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>
using namespace std;

struct Point {
    float x, y;
};

vector<Point> points;
vector<pair<float, float>> lines;
bool point1Set = false;
Point currentStartPoint, currentEndPoint;

void bresenhamDevansh(Point p0, Point p1, float& m, float& c) {
    int x0 = round(p0.x * 100), y0 = round(p0.y * 100);
    int x1 = round(p1.x * 100), y1 = round(p1.y * 100);

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    bool steep = dy > dx;
    if (steep) {
        swap(x0, y0);
        swap(x1, y1);
        swap(dx, dy);
        swap(sx, sy);
    }

    int err = dx / 2;
    int y = y0;

    glBegin(GL_POINTS);
    for (int x = x0; x != x1; x += sx) {
        if (steep) {
            glVertex2f(y / 100.0f, x / 100.0f);
        }
        else {
            glVertex2f(x / 100.0f, y / 100.0f);
        }

        err -= dy;
        if (err < 0) {
            y += sy;
            err += dx;
        }
    }
    glEnd();

    if (x1 != x0) {
        m = (float)(y1 - y0) / (x1 - x0);
        c = (y0 / 100.0f) - m * (x0 / 100.0f);
    }
    else {
        m = FLT_MAX; // Vertical line
        c = x0 / 100.0f;
    }
}

void displayText(float x, float y, const std::string& text) {
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void drawGrid() {
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_LINES);
    for (float x = -1.0f; x <= 1.0f; x += 0.1f) {
        glVertex2f(x, -1.0f);
        glVertex2f(x, 1.0f);
    }
    for (float y = -1.0f; y <= 1.0f; y += 0.1f) {
        glVertex2f(-1.0f, y);
        glVertex2f(1.0f, y);
    }
    glEnd();
}

void drawAxes() {
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

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    drawAxes();


    float m, c;
    for (size_t i = 0; i < points.size(); i += 2) {
        Point p0 = points[i];
        Point p1 = points[i + 1];
        bresenhamDevansh(p0, p1, m, c);

        // Store calculated slope and intercept
        lines.push_back({ m, c });

        glBegin(GL_POINTS);
        glVertex2f(p0.x, p0.y);
        glVertex2f(p1.x, p1.y);
        glEnd();
    }

    if (!lines.empty()) {
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

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float openGLX = (x / (float)glutGet(GLUT_WINDOW_WIDTH)) * 2.0f - 1.0f;
        float openGLY = 1.0f - (y / (float)glutGet(GLUT_WINDOW_HEIGHT)) * 2.0f;

        if (!point1Set) {
            currentStartPoint = { openGLX, openGLY };
            point1Set = true;
        }
        else {
            currentEndPoint = { openGLX, openGLY };
            point1Set = false;
            points.push_back(currentStartPoint);
            points.push_back(currentEndPoint);
            glutPostRedisplay();
        }
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'c' || key == 'C') {
        points.clear();
        lines.clear();
        glutPostRedisplay();
    }
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(5.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(750, 750);
    glutCreateWindow("Bresenham's Line Algorithm");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}