#include <freeglut.h>
#include <cmath>
#include <iostream>

using namespace std;

float x_center = 0, y_center = 0;  
float rx = 0.1, ry = 0.1;          
bool centerSet = false, radiusSet = false; 


void draP(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(static_cast<int>(x_center + x), static_cast<int>(y_center + y));
    glEnd();
    glFlush();
}


void drawEllipse() {
    if (!radiusSet) return; 

    glColor3f(0.0, 0.0, 0.0); 

    float x = 0;
    float y = ry * 400; 

    float rxSq = rx * rx * 400 * 400; 
    float rySq = ry * ry * 400 * 400;

    float p = rySq - (rxSq * y) + (0.25 * rxSq);  

    while (2 * rySq * x <= 2 * rxSq * y) {
        
        draP(x, y);    
        draP(-x, y);    
        draP(-x, -y);   
        draP(x, -y);   

        x++;  
        if (p < 0) {
            p += (2 * rySq * x) + rySq; 
        }
        else {
            y--; 
            p += (2 * rySq * x) - (2 * rxSq * y) + rySq;  
        }
    }

  
    p = rySq * (x + 0.5) * (x + 0.5) + rxSq * (y - 1) * (y - 1) - rxSq * rySq;

    while (y >= 0) {
        
        draP(x, y);     
        draP(-x, y);    
        draP(-x, -y);   
        draP(x, -y);   

        y--;  
        if (p > 0) {
            p -= (2 * rxSq * y) + rxSq;  
        }
        else {
            x++;  
            p += (2 * rySq * x) - (2 * rxSq * y) + rxSq;  
        }
    }
}


void drawGridAndAxes() {
    glColor3f(0.8, 0.8, 0.8); 
    glBegin(GL_LINES);

    for (int i = -400; i <= 400; i += 40) {
        glVertex2i(i, -400);
        glVertex2i(i, 400);
    }

    for (int i = -400; i <= 400; i += 40) {
        glVertex2i(-400, i);
        glVertex2i(400, i);
    }

    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);

    glVertex2i(-400, 0);
    glVertex2i(400, 0);

    glVertex2i(0, -400);
    glVertex2i(0, 400);

    glEnd();
    glFlush();
}


void displayText(float x, float y, const char* text) {
    glRasterPos2f(x, y); 

    void* font = GLUT_BITMAP_HELVETICA_18;

    while (*text) {
        glutBitmapCharacter(font, *text++);
    }
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (!centerSet) {
 
            x_center = (x - glutGet(GLUT_WINDOW_WIDTH) / 2) / 400.0; 
            y_center = (glutGet(GLUT_WINDOW_HEIGHT) / 2 - y) / 400.0;
            centerSet = true;
            cout << "Center set at: (" << x_center*10 << ", " << y_center*10 << ")" << endl;
        }
        else if (!radiusSet) {

            float xDist = (x - glutGet(GLUT_WINDOW_WIDTH) / 2) / 400.0;
            float yDist = (glutGet(GLUT_WINDOW_HEIGHT) / 2 - y) / 400.0;
            rx = abs(xDist - x_center);
            ry = abs(yDist - y_center);
            radiusSet = true;
            cout << "Radii set to: rx = " << rx*10 << ", ry = " << ry*10 << endl;
            glutPostRedisplay();
        }
    }
}


void menu(int option) {
    switch (option) {
    case 1:
        rx += 0.1;  
        ry += 0.1;  
        break;
    case 2:
        if (rx > 0.1 && ry > 0.1) {  
            rx -= 0.1;
            ry -= 0.1;
        }
        break;
    }
    glutPostRedisplay();   
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawGridAndAxes(); 
    drawEllipse();     
    displayText(-380, 380, "Devansh_500107123");
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); 
    glColor3f(0.0, 0.0, 0.0);         
    glPointSize(2.0);                 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-400, 400, -400, 400); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);  
    glutCreateWindow("Midpoint Ellipse_Devansh");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse); 
    glutCreateMenu(menu);
    glutAddMenuEntry("Increase radius", 1);
    glutAddMenuEntry("Decrease radius", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);  
    glutMainLoop();
    return 0;
}
