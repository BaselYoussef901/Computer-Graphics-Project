#include <GL/glut.h>	// Include the GLUT library for OpenGL
#include <stdio.h>	// Include the standard I/O library
#include <math.h>
#define M_PI 3.14159265358979323846

float cameraX = 3.0f;
float cameraY = 1.0f;
float cameraZ = 8.0f;
float cameraAngleX = 0.0f;
float cameraAngleY = 0.0f;
float cameraDistance = 12.0f;
float cameraSpeed = 0.1f;
void adjustCamera() {
    // Calculate the camera position based on angles and distance
    cameraX = cameraDistance * sinf(cameraAngleY) * cosf(cameraAngleX);
    cameraY = cameraDistance * sinf(cameraAngleX);
    cameraZ = cameraDistance * cosf(cameraAngleY) * cosf(cameraAngleX);

    // Camera 
    float adjustedCameraY = cameraY + 3.0f;
    float adjustedCameraAngleX = cameraAngleX - M_PI / 4.0f;
    gluLookAt(cameraX, adjustedCameraY, cameraZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}


























void drawCylinder(float radius, float height, int slices, int stacks) {
    GLUquadricObj* cylinder = gluNewQuadric();
    gluQuadricDrawStyle(cylinder, GLU_FILL);
    gluCylinder(cylinder, radius, radius, height, slices, stacks);
    gluDeleteQuadric(cylinder);
}
void drawTree(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, 0.0f, z);
    // trunk
    glColor3f(0.5f, 0.35f, 0.05f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    drawCylinder(0.1f, 1.0f, 20, 20);

    // leaves
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.9f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.5f, 0.8f, 0.5f);
    glutSolidSphere(0.5f, 20, 20);
    glPopMatrix();

    glPopMatrix();
}

void drawBush(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, 0.2f, z);
    // Draw bush
    glColor3f(0.5f, 0.8f, 0.5f);
    glutSolidSphere(0.3f, 20, 20);
    glPopMatrix();
}






















float rotateHandlebars = 0.0f;
float speedRatio = 0.1f;
float bicycleX = 0.0f;
float bicycleY = 0.2f;
float bicycleZ = 5.52f;
float pedalAngle = 0.0f;
float bikeAngle = 0.0f;

void drawBicycle() {
    // Crossbar
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(bicycleX - 0.35f, bicycleY, bicycleZ);
    glVertex3f(bicycleX - 0.35f, bicycleY + 0.1f, bicycleZ);
    glVertex3f(bicycleX + 0.35f, bicycleY + 0.1f, bicycleZ);
    glVertex3f(bicycleX + 0.35f, bicycleY, bicycleZ);
    glEnd();

    // Pedals
    glColor3f(1.0f, 1.0f, 0.1f);
    glPushMatrix();
    glTranslatef(bicycleX - 0.3f, bicycleY + 0.05f, bicycleZ);
    glutSolidSphere(0.05f, 20, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(bicycleX + 0.3f, bicycleY + 0.05f, bicycleZ);
    glutSolidSphere(0.05f, 20, 20);
    glPopMatrix();

    // Handlebars
    glColor3f(1.0f, 1.0f, 0.1f);
    glPushMatrix();
    glTranslatef(bicycleX - 0.25f, bicycleY + 0.28f, bicycleZ - 0.15f);
    glRotatef(rotateHandlebars, 0.0f, 1.0f, 0.0f);
    drawCylinder(0.02f, 0.3f, 20, 20);
    glPopMatrix();

    // Wheels
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(bicycleX - 0.35f, bicycleY, bicycleZ);
    glRotatef(rotateHandlebars, 0.0f, 1.0f, 0.0f);
    glutSolidTorus(0.03, 0.2, 20, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(bicycleX + 0.35f, bicycleY, bicycleZ);
    glutSolidTorus(0.03, 0.2, 20, 20);
    glPopMatrix();

    // Seat
    glColor3f(1.0f, 1.0f, 0.1f);
    glPushMatrix();
    glTranslatef(bicycleX, bicycleY + 0.18f, bicycleZ);
    glScalef(0.06f, 0.025f, 0.06f);
    glBegin(GL_POLYGON);
    glVertex3f(-0.1f, 1.0f, -0.5f);
    glVertex3f(1.0f, 1.0f, -0.3f);
    glVertex3f(1.0f, 1.0f, 0.3f);
    glVertex3f(-0.1f, 1.0f, 0.5f);
    glVertex3f(-0.5f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-0.5f, 1.0f, -1.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(-0.1f, -1.0f, -0.5f);
    glVertex3f(1.0f, -1.0f, -0.3f);
    glVertex3f(1.0f, -1.0f, 0.3f);
    glVertex3f(-0.1f, -1.0f, 0.5f);
    glVertex3f(-0.5f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-0.5f, -1.0f, -1.0f);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3f(1.0f, 1.0f, -0.3f);
    glVertex3f(1.0f, 1.0f, 0.3f);
    glVertex3f(1.0f, -1.0f, 0.3f);
    glVertex3f(1.0f, -1.0f, -0.3f);
    glVertex3f(1.0f, 1.0f, 0.3f);
    glVertex3f(-0.1f, 1.0f, 0.5f);
    glVertex3f(-0.1f, -1.0f, 0.5f);
    glVertex3f(1.0f, -1.0f, 0.3f);
    glVertex3f(1.0f, 1.0f, -0.3f);
    glVertex3f(-0.1f, 1.0f, -0.5f);
    glVertex3f(-0.1f, -1.0f, -0.5f);
    glVertex3f(1.0f, -1.0f, -0.3f);
    glVertex3f(-0.1f, 1.0f, 0.5f);
    glVertex3f(-0.5f, 1.0f, 1.0f);
    glVertex3f(-0.5f, -1.0f, 1.0f);
    glVertex3f(-0.1f, -1.0f, 0.5f);
    glVertex3f(-0.1f, 1.0f, -0.5f);
    glVertex3f(-0.5f, 1.0f, -1.0f);
    glVertex3f(-0.5f, -1.0f, -1.0f);
    glVertex3f(-0.1f, -1.0f, -0.5f);
    glVertex3f(-0.5f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-0.5f, -1.0f, 1.0f);
    glVertex3f(-0.5f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-0.5f, -1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glEnd();
    glPopMatrix();

    // Feet Pedals
    glPushMatrix();
    glTranslatef(bicycleX, bicycleY + 0.07f, bicycleZ);
    glScalef(0.3f, 0.3f, 0.3f);
    glColor3f(1.0f, 1.0f, 0.1f);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.105f);
    glRotatef(-pedalAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.25f, 0.0f, 0.0f);
    glPushMatrix();
    glScalef(0.4f, 0.1f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.25f, 0.0f, 0.15f);
    glRotatef(pedalAngle, 0.0f, 0.0f, 1.0f);
    glScalef(0.25f, 0.02f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -0.105f);
    glRotatef(180.0f - pedalAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.25f, 0.0f, 0.0f);
    glPushMatrix();
    glScalef(0.4f, 0.1f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.25f, 0.0f, -0.15f);
    glRotatef(pedalAngle - 180.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.25f, 0.02f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

}

void Bicycle() {
    drawBicycle();
}




























void drawRoad() {
    // Draw Road Street - Black
    int numSegments = 100;
    float outerRadius = 5.1f;
    float innerRadius = 6.0f;
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= numSegments; ++i) {
        float angle = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(numSegments);
        float outerX = outerRadius * cosf(angle);
        float outerZ = outerRadius * sinf(angle);
        float innerX = innerRadius * cosf(angle);
        float innerZ = innerRadius * sinf(angle);
        glVertex3f(outerX, 0.0f, outerZ);
        glVertex3f(innerX, 0.0f, innerZ);
    }
    glEnd();

    // Draw White Landmark - White
    glColor3f(1.0f, 1.0f, 1.0f);
    float outerRadiusSign = 5.52f;
    float innerRadiusSign = 5.56f;
    float heightOffset = 0.01f;
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= numSegments; ++i) {
        float angle = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(numSegments);
        float outerX = outerRadiusSign * cosf(angle);
        float outerZ = outerRadiusSign * sinf(angle);
        float innerX = innerRadiusSign * cosf(angle);
        float innerZ = innerRadiusSign * sinf(angle);
        glVertex3f(outerX, heightOffset, outerZ);
        glVertex3f(innerX, heightOffset, innerZ);
    }
    glEnd();

    // Draw Road Boundary - Black
    glColor3f(0.0f, 0.0f, 0.0f);
    float outerRadiusBrick = 6.0f;
    float innerRadiusBrick = 6.1f;
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= numSegments; ++i) {
        float angle = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(numSegments);
        float outerX = outerRadiusBrick * cosf(angle);
        float outerZ = outerRadiusBrick * sinf(angle);
        float innerX = innerRadiusBrick * cosf(angle);
        float innerZ = innerRadiusBrick * sinf(angle);
        glVertex3f(outerX, 0.0f, outerZ);
        glVertex3f(innerX, 0.0f, innerZ);
    }
    glEnd();
}


















void drawGround() {
    // Draw Ground Base - Green
    glColor3f(0.0f, 0.4f, 0.0f);
    int numSegments = 100;
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 0.0f);
    for (int i = 0; i <= numSegments; ++i) {
        float angle = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(numSegments);
        float x = 5.0f * cosf(angle);
        float z = 5.0f * sinf(angle);
        glVertex3f(x, 0.0f, z);
    }
    glEnd();


    // Draw Ground Boundary - Black
    glColor3f(0.0f, 0.0f, 0.0f);
    float outerRadius = 5.0f;
    float innerRadius = 5.1f;
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= numSegments; ++i) {
        float angle = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(numSegments);
        float outerX = outerRadius * cosf(angle);
        float outerZ = outerRadius * sinf(angle);
        float innerX = innerRadius * cosf(angle);
        float innerZ = innerRadius * sinf(angle);
        glVertex3f(outerX, 0.0f, outerZ);  // Outer vertex
        glVertex3f(innerX, 0.0f, innerZ);  // Inner vertex
    }
    glEnd();
}





















float doorAngle = 0.0f;
float doorFactor = 0.0f;
float windowFactor = 0.0f;
void drawHouse() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    // First floor
    // Front face
    glVertex3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 2.0f, 1.0f);
    glVertex3f(-1.0f, 2.0f, 1.0f);
    // Back face
    glVertex3f(1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 2.0f, -1.0f);
    glVertex3f(1.0f, 2.0f, -1.0f);
    // Left face
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 2.0f, 1.0f);
    glVertex3f(-1.0f, 2.0f, -1.0f);
    // Right face
    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, -1.0f);
    glVertex3f(1.0f, 2.0f, -1.0f);
    glVertex3f(1.0f, 2.0f, 1.0f);

    // Second floor (smaller)
    // Front face
    glVertex3f(-1.0f, 2.0f, 1.0f);
    glVertex3f(1.0f, 2.0f, 1.0f);
    glVertex3f(1.0f, 3.0f, 1.0f);
    glVertex3f(-1.0f, 3.0f, 1.0f);
    // Back face
    glVertex3f(1.0f, 2.0f, -1.0f);
    glVertex3f(-1.0f, 2.0f, -1.0f);
    glVertex3f(-1.0f, 3.0f, -1.0f);
    glVertex3f(1.0f, 3.0f, -1.0f);
    // Left face
    glVertex3f(-1.0f, 2.0f, -1.0f);
    glVertex3f(-1.0f, 2.0f, 1.0f);
    glVertex3f(-1.0f, 3.0f, 1.0f);
    glVertex3f(-1.0f, 3.0f, -1.0f);
    // Right face
    glVertex3f(1.0f, 2.0f, 1.0f);
    glVertex3f(1.0f, 2.0f, -1.0f);
    glVertex3f(1.0f, 3.0f, -1.0f);
    glVertex3f(1.0f, 3.0f, 1.0f);
    glEnd();

    // Roof
    glColor3f(0.7f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    // Front roof
    glVertex3f(-1.2f, 3.0f, 1.2f);
    glVertex3f(1.2f, 3.0f, 1.2f);
    glVertex3f(1.0f, 3.5f, 1.0f);
    glVertex3f(-1.0f, 3.5f, 1.0f);
    // Back roof
    glVertex3f(1.2f, 3.0f, -1.2f);
    glVertex3f(-1.2f, 3.0f, -1.2f);
    glVertex3f(-1.0f, 3.5f, -1.0f);
    glVertex3f(1.0f, 3.5f, -1.0f);
    // Left roof
    glVertex3f(-1.2f, 3.0f, -1.2f);
    glVertex3f(-1.2f, 3.0f, 1.2f);
    glVertex3f(-1.0f, 3.5f, 1.0f);
    glVertex3f(-1.0f, 3.5f, -1.0f);
    // Right roof
    glVertex3f(1.2f, 3.0f, 1.2f);
    glVertex3f(1.2f, 3.0f, -1.2f);
    glVertex3f(1.0f, 3.5f, -1.0f);
    glVertex3f(1.0f, 3.5f, 1.0f);
    // Top roof
    glVertex3f(-1.0f, 3.5f, 1.0f);
    glVertex3f(1.0f, 3.5f, 1.0f);
    glVertex3f(1.0f, 3.5f, -1.0f);
    glVertex3f(-1.0f, 3.5f, -1.0f);
    glEnd();

    // Door
    glPushMatrix();
    glTranslatef(-doorFactor, 0.0f, 1.01f + doorFactor);
    glRotatef(doorAngle, 0.0f, 1.0f, 0.0f);
    glColor3f(0.9f, 0.4f, 0.2f);
    glBegin(GL_QUADS);
    glVertex3f(-0.2f, 0.0f, 0.0f);
    glVertex3f(0.2f, 0.0f, 0.0f);
    glVertex3f(0.2f, 1.0f, 0.0f);
    glVertex3f(-0.2f, 1.0f, 0.0f);
    glEnd();
    glPopMatrix();

    // Windows
    glColor3f(0.6f, 0.8f, 0.9f);
    glBegin(GL_QUADS);
    // First floor windows
    // Window 1
    glVertex3f(-0.8f, 1.5f + windowFactor, 1.01f);
    glVertex3f(-0.4f, 1.5f + windowFactor, 1.01f);
    glVertex3f(-0.4f, 1.9f, 1.01f); // Adjusted bottom coordinate
    glVertex3f(-0.8f, 1.9f, 1.01f); // Adjusted bottom coordinate
    // Window 2
    glVertex3f(0.4f, 1.5f + windowFactor, 1.01f);
    glVertex3f(0.8f, 1.5f + windowFactor, 1.01f);
    glVertex3f(0.8f, 1.9f, 1.01f);
    glVertex3f(0.4f, 1.9f, 1.01f);

    // Second floor windows
    // Window 3
    glVertex3f(-0.8f, 2.5f + windowFactor, 1.01f);
    glVertex3f(-0.4f, 2.5f + windowFactor, 1.01f);
    glVertex3f(-0.4f, 2.9f, 1.01f);
    glVertex3f(-0.8f, 2.9f, 1.01f);
    // Window 4
    glVertex3f(0.4f, 2.5f + windowFactor, 1.01f);
    glVertex3f(0.8f, 2.5f + windowFactor, 1.01f);
    glVertex3f(0.8f, 2.9f, 1.01f);
    glVertex3f(0.4f, 2.9f, 1.01f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Black color for the edges
    glLineWidth(1.0f); // Set line width to 2 pixels (adjust as needed)
    glBegin(GL_LINE_LOOP);
    // Top edge of the door
    glVertex3f(-0.2f, 0.0f, 1.01f);
    glVertex3f(0.2f, 0.0f, 1.01f);
    glEnd();

    glBegin(GL_LINES);
    // Left edge of the door
    glVertex3f(-0.2f, 0.0f, 1.01f);
    glVertex3f(-0.2f, 1.0f, 1.01f);
    // Right edge of the door
    glVertex3f(0.2f, 0.0f, 1.01f);
    glVertex3f(0.2f, 1.0f, 1.01f);
    glEnd();

    // Draw black edges around the windows
    glColor3f(0.0f, 0.0f, 0.0f); // Black color for the edges
    glBegin(GL_LINE_LOOP);
    // Top edge of Window 1
    glVertex3f(-0.8f, 1.9f, 1.01f);
    glVertex3f(-0.4f, 1.9f, 1.01f);
    glVertex3f(-0.4f, 1.5f, 1.01f);
    glVertex3f(-0.8f, 1.5f, 1.01f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    // Top edge of Window 2
    glVertex3f(0.4f, 1.9f, 1.01f);
    glVertex3f(0.8f, 1.9f, 1.01f);
    glVertex3f(0.8f, 1.5f, 1.01f);
    glVertex3f(0.4f, 1.5f, 1.01f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    // Top edge of Window 3
    glVertex3f(-0.8f, 2.9f, 1.01f);
    glVertex3f(-0.4f, 2.9f, 1.01f);
    glVertex3f(-0.4f, 2.5f, 1.01f);
    glVertex3f(-0.8f, 2.5f, 1.01f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    // Top edge of Window 4
    glVertex3f(0.4f, 2.9f, 1.01f);
    glVertex3f(0.8f, 2.9f, 1.01f);
    glVertex3f(0.8f, 2.5f, 1.01f);
    glVertex3f(0.4f, 2.5f, 1.01f);
    glEnd();
}




























bool motion = false;
float animationSpeed = 0.02f;
void circular_motion() {
    static float time = 0.0f;
    float radius = 5.5f;
    float centerX = 0.0f;
    float centerY = 0.0f;
    float angularSpeed = animationSpeed;

    // Calculate the initial angle based on the initial position
    static float initialAngle = atan2(bicycleZ, bicycleX);

    // Update angle over time for animation
    float angle = initialAngle + angularSpeed * time;

    // Calculate new X and Z positions for horizontal circular motion
    bicycleX = radius * cos(angle);
    bicycleZ = radius * sin(angle);

    // Calculate orientation based on tangent to the circle
    float tangentAngle = atan2(-radius * sin(angle), radius * cos(angle));
    bikeAngle = tangentAngle * (180.0f / M_PI); // Convert to degrees
    pedalAngle -= speedRatio;

    time += animationSpeed;
    glutPostRedisplay();
}





















































float zoomFactor = 0.5f;
float rotationSpeed = 0.003f;
int lastMouseX = -1;
int lastMouseY = -1;
bool isLeftMouseDown = false;
bool isRightMouseDown = false;
bool isMiddleMouseDown = false;
void handleMouseClick() {
    if (isLeftMouseDown) {
        // Start Animation Function
        glutPostRedisplay();
    }
    else if (isRightMouseDown) {
        // End Animation Function
        glutPostRedisplay();
    }
}
void handleMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isLeftMouseDown = true;
            motion = true;
        }
        else if (state == GLUT_UP) {
            isLeftMouseDown = false;
        }
    }
    else if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) {
            isRightMouseDown = true;
            motion = false;
        }
        else if (state == GLUT_UP) {
            isRightMouseDown = false;
        }
    }
    else if (button == GLUT_MIDDLE_BUTTON) {
        if (state == GLUT_DOWN) {
            isMiddleMouseDown = true;
            lastMouseX = x;
            lastMouseY = y;
        }
        else if (state == GLUT_UP) {
            isMiddleMouseDown = false;
        }
    }
    handleMouseClick();
}
void handleMouseMove(int x, int y) {
    if (isMiddleMouseDown) {
        cameraAngleY += rotationSpeed * (x - lastMouseX);
        cameraAngleX += rotationSpeed * (y - lastMouseY);
        lastMouseX = x;
        lastMouseY = y;
        glutPostRedisplay();
    }
}
void handleKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        cameraDistance -= zoomFactor; // Zoom in
        if (zoomFactor < 0.1f) zoomFactor = 0.1f; // Prevent too much zoom in
        break;
    case 's':
        cameraDistance += zoomFactor; // Zoom out
        if (zoomFactor > 10.0f) zoomFactor = 10.0f; // Prevent too much zoom out
        break;
    case 'f':
        bicycleX -= speedRatio;     // Move Bicycle forward
        pedalAngle -= 10.0f;
        break;
    case 'b':
        bicycleX += speedRatio;     // Move Bicycle backword
        pedalAngle += 10.0f;
        break;
    case 'r':
        rotateHandlebars -= 5.0f;
        if (rotateHandlebars < -45.0f)
            rotateHandlebars = -45.0f;
        break;
    case 'i':
        rotateHandlebars += 5.0f;
        if (rotateHandlebars > 45.0f)
            rotateHandlebars = 45.0f;
        break;
    case 'q':
        doorAngle = 80.0f;
        doorFactor = 0.243f;
        break;
    case 'e':
        doorAngle = 0.0f;
        doorFactor = 0.0f;
        break;
    case 'd':
        windowFactor = 0.0f;
        break;
    case 'a':
        windowFactor = 0.15f;
        break;
    }

    glutPostRedisplay();
}













// Function to handle window resizing
void reshape(int width, int height) {
    if (height == 0) height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void drawScene() {
    glClearColor(0.9f, 0.95f, 1.0f, 1.0f);  // Back-ground color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Camera Position
    adjustCamera();

    // Draw Street
    drawGround();       // House Base Ground
    drawRoad();         // House Front Road


    // Draw House
    drawHouse();
    drawTree(2.0f, -2.5f, 1.0f);
    drawTree(-2.0f, -2.5f, 2.0f);
    drawBush(2.0f, -4.5f, -3.0f);
    drawBush(-1.0f, -4.5f, 4.0f);

    // Draw Bicycle
    Bicycle();

    glutSwapBuffers();
}
void idle() {
    if (motion) {
        circular_motion();
    }
}













int main(int argc, char** argv) {
    // Initialize GLUT and create a window
    glutInit(&argc, argv);	// Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);	// Set display mode
    glutInitWindowSize(800, 600);	// Set window size
    glutCreateWindow("3D Building and Bicycle");	// Create a window with the given title
    glEnable(GL_DEPTH_TEST);	// Enable depth testing for drawing order

    // Register callback functions
    glutDisplayFunc(drawScene);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMouseFunc(handleMouse);
    glutMotionFunc(handleMouseMove);
    glutKeyboardFunc(handleKeyboard);

    glutMainLoop();	// Enter the event processing loop

    return 0;
}