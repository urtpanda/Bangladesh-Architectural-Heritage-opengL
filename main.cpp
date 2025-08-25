#include <windows.h>
#include <GL/glut.h>
#include <cmath>
#include <GL/gl.h>
#define PI  3.14159265358979323846
bool isAnimating = true;  // true means animation runs, false means paused
int currentProject = 0; // Default project
int r=0;
int displayCount =0;
GLfloat position = 0.0f;
GLfloat speed = 0.01f;
GLfloat q=0.0f;
GLfloat speed_ = 0.05f;
GLfloat position2 = 0.0f;//man
GLfloat speed2 = 0.08f;
GLfloat position4 = 0.0f;//cloud
GLfloat speed4 = 0.05f;
GLfloat position5 = 0.0f;//flower
GLfloat speed5 = 0.05f;
GLfloat position6 = 0.0f;//sun
GLfloat speed6 = 0.05f;
float sunY = 1.0f;
float moonY = -1.0f;
float waveOffsets = 0.0f;
float waveTime = 0.0f;
float skyColor =1.0f; // Daylight starts bright
float positionX = 1.0f; // Initial X position
float positionY = 1.0f; // Initial Y position
float speedX = -0.01f;  // Speed in X direction
float speedY = -0.01f;
bool isDay = true;
GLfloat title_fade;


/*Mandatory function */
void renderBitmapString(float x, float y, float z, void *font, char *string){
    char *c;
    glRasterPos3f(x, y,z);
    for (c=string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}


void update(int value){
    if (isAnimating) {
    waveOffsets += 0.1f;
    waveTime += 0.03f;
    if (waveOffsets > 2 * PI) {
        waveOffsets -= 2 * PI;
    }
    if(position > 1.0)
        position = -1.0f;
    if(position <-0.7)
        position = 1.0f;
    if(position < -2.0)
            position = 4.0f;

    if(position2 > .59)
            position2 = -1.0f;

    positionX += speedX;
    positionY += speedY;

    // Reset position if the bird exits the screen
    if (positionX < -1.0f || positionY < -1.0f) {
        positionX = 1.0f; // Reset to start from top-right
        positionY = 1.0f;
    }
    if(position4 < -1.0)
            position4 = 1.0f;
    if(position5 > .59)
            position5 = -1.0f;
    if(position6 > 2.0f)
            position6 = -0.3f;
        position -= speed;
    position2 += speed;
    //position3 -= speed;
    position4 -= speed;
    position5 +=speed;
    position6 +=speed;
    position -= speed;

        position += speed;
        // and all other position/angle updates...
    }



	glutPostRedisplay();
	glutTimerFunc(50, update, 0);
}
///////////////////++***+++////////////////
void sceneTitle() {
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f); // White text
    renderBitmapString(-0.4f, 0.6f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "BANGLADESH ARCHITECTURAL HERITAGE");
    renderBitmapString(-0.4f, 0.4f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Keys: 1-History | 2-Parliament | 3-Shaheed Minar");
    renderBitmapString(-0.4f, 0.3f, 0.0f, GLUT_BITMAP_HELVETICA_18, "4-Sriti Shoudh | 5-Moral | Esc-Exit");
    renderBitmapString(-0.4f, 0.1f, 0.0f, GLUT_BITMAP_HELVETICA_12, "Press any key to continue...");
    glFlush();
}
///////////////////////****+++++----////////////////
void drawCircle(float x, float y, float radius) {
    int triangleAmount = 100;
    float twicePi = 2.0f * 3.14159265359f;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center of the circle
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}
void circle(float a, float b, float radius, float r, float g, float bb) {
    int i;
    int lineAmount = 1000;
    GLfloat twicePi = 2.0f * PI;

    glColor3f(r, g, bb);
    glBegin(GL_TRIANGLE_FAN);
    for (i = 0; i <= lineAmount; i++) {
        glVertex2f(
            a + (radius * cos(i * twicePi / lineAmount)),
            b + (radius * sin(i * twicePi / lineAmount))
        );
    }
    glEnd();
}
void Cloud(float x, float y, float scale) {
    // Background layer: 3 gray circles
    glColor3f(0.7f, 0.7f, 0.7f);
    drawCircle(x - 0.55f * scale, y + 0.29f* scale, 0.35f * scale); // Left-back gray circle
    drawCircle(x - 0.0f * scale, y + 0.25f * scale, 0.56f * scale);  // Middle-back gray circle
    drawCircle(x + 0.55f * scale, y + 0.25f * scale, 0.35f * scale);  // Right-back gray circle
    // Background layer: 3 gray circles


    // Foreground layer: 5 white circles
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x - 0.63f * scale, y + 0.4f * scale, 0.3f * scale); // Left-front white circle
    drawCircle(x - 0.3f * scale, y + 0.5f * scale, 0.4f * scale); // Middle-left white circle
    drawCircle(x + 0.2f * scale, y + 0.5f * scale, 0.4f * scale);  // Middle-right white circle
    drawCircle(x + 0.63f * scale, y + 0.4f * scale, 0.3f * scale);  // Right-front white circle
    drawCircle(x + 0.0f * scale, y + 0.3f * scale, 0.5f * scale);  // Bottom white circle
    drawCircle(x - 0.0f * scale, y + 0.68f * scale, 0.35f * scale);  // Middle-back gray circle
}
void xCloud(float x, float y, float scale) {

    // Background layer: 3 gray circles
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x - 0.55f * scale, y + 0.29f* scale, 0.35f * scale); // Left-back gray circle
    drawCircle(x - 0.0f * scale, y + 0.25f * scale, 0.56f * scale);  // Middle-back gray circle
    drawCircle(x + 0.55f * scale, y + 0.25f * scale, 0.35f * scale);  // Right-back gray circle


    // Foregund layer: 5 white circles
    glColor3f(8.0f, 8.0f, 8.0f);
    drawCircle(x - 0.63f * scale, y + 0.4f * scale, 0.3f * scale); // Left-front white circle
    drawCircle(x - 0.3f * scale, y + 0.5f * scale, 0.4f * scale); // Middle-left white circle
    drawCircle(x + 0.2f * scale, y + 0.5f * scale, 0.4f * scale);  // Middle-right white circle
    drawCircle(x + 0.63f * scale, y + 0.4f * scale, 0.3f * scale);  // Right-front white circle
    drawCircle(x + 0.0f * scale, y + 0.3f * scale, 0.5f * scale);  // Bottom white circle
    drawCircle(x - 0.0f * scale, y + 0.68f * scale, 0.35f * scale);  // Middle-back gray circle
}
void sunmoon(int value) {
    if (isAnimating) {
        if (isDay) {
            sunY -= 0.01f;
            if (sunY <= -1.0f) {
                isDay = false;
                moonY = -1.0f;
            }
        } else {
            moonY += 0.01f;
            if (moonY >= 1.2f) {
                isDay = true;
                sunY = 1.2f;
            }
        }
        glutPostRedisplay();
    }

    glutTimerFunc(100, sunmoon, 0); // always keep timer going
}

void update1(int value) {
    waveTime += 0.02f;
    glutPostRedisplay();
    glutTimerFunc(16, update1, 0);
}
void drawCircle(GLfloat x, GLfloat y, GLfloat radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 223, 0);
    glVertex2f(x, y);
    for(int i = 0; i <= segments; i++) {
        GLfloat angle = 2.0f * PI * i / segments;
        GLfloat dx = cosf(angle) * radius;
        GLfloat dy = sinf(angle) * radius;
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

/*Static Code*/
/* Code Of Project 1*/
void grass(){
    GLfloat a=-0.72f; GLfloat b=-0.75f; GLfloat radius =0.05f;
	int i;
	int lineAmount = 1000;
	GLfloat twicePi = 2.0f * PI;

    glColor3f(0.7f,0.7f,0.7f);
	glBegin(GL_TRIANGLE_FAN);
		for(i = 0; i <= lineAmount;i++) {
			glVertex2f(
			    a + (radius * cos(i *  twicePi / lineAmount)),
			    b + (radius* sin(i * twicePi / lineAmount))
			);
		}
	glEnd();

	GLfloat c=-0.5f; GLfloat d=-0.76f; GLfloat r =0.05f;
	int j;
	int lineAmount1 = 1000;
	GLfloat twicePi1 = 2.0f * PI;

    glColor3f(0.0f,0.8f,0.0f);
	glBegin(GL_TRIANGLE_FAN);
		for(j = 0; j <= lineAmount; j++) {
			glVertex2f(
			    c + (radius * cos(j *  twicePi1 / lineAmount1)),
			    d + (radius* sin(j * twicePi1 / lineAmount1))
			);
		}
	glEnd();

	GLfloat e=-0.58f; GLfloat f=-0.75f; GLfloat r1 =0.05f;
	int k;
	int lineAmount2 = 100;
	GLfloat twicePi2 = 2.0f * PI;

    glColor3f(0.0f,0.8f,0.0f);
	glBegin(GL_TRIANGLE_FAN);
		for(k = 0; k <= lineAmount2; k++) {
			glVertex2f(
			    e + (radius * cos(k *  twicePi2 / lineAmount2)),
			    f + (radius* sin(k * twicePi2 / lineAmount2))
			);
		}
	glEnd();
}
void grass1(){
    GLfloat a=-0.78f; GLfloat b=-0.75f; GLfloat radius =0.05f;
	int i;
	int lineAmount = 1000;
	GLfloat twicePi = 2.0f * PI;

    glColor3f(0.1f,0.8f,0.1f);
	glBegin(GL_TRIANGLE_FAN);
		for(i = 0; i <= lineAmount;i++) {
			glVertex2f(
			    a + (radius * cos(i *  twicePi / lineAmount)),
			    b + (radius* sin(i * twicePi / lineAmount))
			);
		}
	glEnd();

	GLfloat c=-0.64f; GLfloat d=-0.76f; GLfloat r =0.05f;
	int j;
	int lineAmount1 = 1000;
	GLfloat twicePi1 = 2.0f * PI;

    glColor3f(0.0f,0.8f,0.0f);
	glBegin(GL_TRIANGLE_FAN);
		for(j = 0; j <= lineAmount; j++) {
			glVertex2f(
			    c + (radius * cos(j *  twicePi1 / lineAmount1)),
			    d + (radius* sin(j * twicePi1 / lineAmount1))
			);
		}
	glEnd();

	GLfloat e=-0.68f; GLfloat f=-0.75f; GLfloat r1 =0.05f;
	int k;
	int lineAmount2 = 100;
	GLfloat twicePi2 = 2.0f * PI;

    glColor3f(0.0f,0.8f,0.0f);
	glBegin(GL_TRIANGLE_FAN);
		for(k = 0; k <= lineAmount2; k++) {
			glVertex2f(
			    e + (radius * cos(k *  twicePi2 / lineAmount2)),
			    f + (radius* sin(k * twicePi2 / lineAmount2))
			);
		}
	glEnd();
}
void grass2(){
    GLfloat a=-0.99f; GLfloat b=-0.75f; GLfloat radius =0.05f;
	int i;
	int lineAmount = 1000;
	GLfloat twicePi = 2.0f * PI;

    glColor3f(0.0f,0.8f,0.0f);
	glBegin(GL_TRIANGLE_FAN);
		for(i = 0; i <= lineAmount;i++) {
			glVertex2f(
			    a + (radius * cos(i *  twicePi / lineAmount)),
			    b + (radius* sin(i * twicePi / lineAmount))
			);
		}
	glEnd();

	GLfloat c=-0.87f;
	GLfloat d=-0.76f;
	GLfloat r =0.05f;
	int j;
	int lineAmount1 = 1000;
	GLfloat twicePi1 = 2.0f * PI;

    glColor3f(0.0f,0.8f,0.0f);
	glBegin(GL_TRIANGLE_FAN);
		for(j = 0; j <= lineAmount; j++) {
			glVertex2f(
			    c + (radius * cos(j *  twicePi1 / lineAmount1)),
			    d + (radius* sin(j * twicePi1 / lineAmount1))
			);
		}
	glEnd();

	GLfloat e=-0.93f;
	GLfloat f=-0.75f;
	GLfloat r1 =0.05f;
	int k;
	int lineAmount2 = 100;
	GLfloat twicePi2 = 2.0f * PI;

    glColor3f(0.0f,0.8f,0.0f);
	glBegin(GL_TRIANGLE_FAN);
		for(k = 0; k <= lineAmount2; k++) {
			glVertex2f(
			    e + (radius * cos(k *  twicePi2 / lineAmount2)),
			    f + (radius* sin(k * twicePi2 / lineAmount2))
			);
		}
	glEnd();
}
void grass3(){
    GLfloat a=0.97f; GLfloat b=-0.75f; GLfloat radius =0.05f;
	int i;
	int lineAmount = 1000;
	GLfloat twicePi = 2.0f * PI;

    glColor3f(0.0f,0.8f,0.0f);
	glBegin(GL_TRIANGLE_FAN);
		for(i = 0; i <= lineAmount;i++) {
			glVertex2f(
			    a + (radius * cos(i *  twicePi / lineAmount)),
			    b + (radius* sin(i * twicePi / lineAmount))
			);
		}
	glEnd();

	GLfloat c=0.82f; GLfloat d=-0.76f; GLfloat r =0.05f;
	int j;
	int lineAmount1 = 1000;
	GLfloat twicePi1 = 2.0f * PI;

    glColor3f(0.0f,0.8f,0.0f);
	glBegin(GL_TRIANGLE_FAN);
		for(j = 0; j <= lineAmount; j++) {
			glVertex2f(
			    c + (radius * cos(j *  twicePi1 / lineAmount1)),
			    d + (radius* sin(j * twicePi1 / lineAmount1))
			);
		}
	glEnd();

	GLfloat e=0.9f; GLfloat f=-0.75f; GLfloat r1 =0.05f;
	int k;
	int lineAmount2 = 100;
	GLfloat twicePi2 = 2.0f * PI;

    glColor3f(0.0f,0.8f,0.0f);
	glBegin(GL_TRIANGLE_FAN);
		for(k = 0; k <= lineAmount2; k++) {
			glVertex2f(
			    e + (radius * cos(k *  twicePi2 / lineAmount2)),
			    f + (radius* sin(k * twicePi2 / lineAmount2))
			);
		}
	glEnd();
}
void SpecialInput(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP: // Up arrow toggles day/night
            isDay = true; // Set to day mode
            break;
        case GLUT_KEY_DOWN: // Down arrow toggles day/night
            isDay = false; // Set to night mode
            break;
        case GLUT_KEY_LEFT: // Left arrow slows animation
            speed *= 0.05f;
            break;
        case GLUT_KEY_RIGHT: // Right arrow increases animation speed
            speed /= 0.05f;
            break;
    }
    glutPostRedisplay(); // Request a redraw
}
void birds(){
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.5f, 0.77f);
    glVertex2f(-0.47f, 0.75f);
    glVertex2f(-0.47f, 0.74f);
    glVertex2f(-0.5f, 0.77f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.44f, 0.77f);
    glVertex2f(-0.47f, 0.75f);
    glVertex2f(-0.47f, 0.74f);
    glVertex2f(-0.44f, 0.77f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.4f, 0.77f);
    glVertex2f(-0.37f, 0.75f);
    glVertex2f(-0.37f, 0.74f);
    glVertex2f(-0.4f, 0.77f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.34f, 0.77f);
    glVertex2f(-0.37f, 0.75f);
    glVertex2f(-0.37f, 0.74f);
    glVertex2f(-0.34f, 0.77f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.45f, 0.82f);
    glVertex2f(-0.42f, 0.8f);
    glVertex2f(-0.42f, 0.79f);
    glVertex2f(-0.45f, 0.82f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.39f, 0.82f);
    glVertex2f(-0.42f, 0.8f);
    glVertex2f(-0.42f, 0.79f);
    glVertex2f(-0.39f, 0.82f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.45f, 0.72f);
    glVertex2f(-0.42f, 0.7f);
    glVertex2f(-0.42f, 0.69f);
    glVertex2f(-0.45f, 0.72f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.39f, 0.72f);
    glVertex2f(-0.42f, 0.7f);
    glVertex2f(-0.42f, 0.69f);
    glVertex2f(-0.39f, 0.72f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.5f, 0.77f);
    glVertex2f(0.47f, 0.75f);
    glVertex2f(0.47f, 0.74f);
    glVertex2f(0.5f, 0.77f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.44f, 0.77f);
    glVertex2f(0.47f, 0.75f);
    glVertex2f(0.47f, 0.74f);
    glVertex2f(0.44f, 0.77f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.4f, 0.77f);
    glVertex2f(0.37f, 0.75f);
    glVertex2f(0.37f, 0.74f);
    glVertex2f(0.4f, 0.77f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.34f, 0.77f);
    glVertex2f(0.37f, 0.75f);
    glVertex2f(0.37f, 0.74f);
    glVertex2f(0.34f, 0.77f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.45f, 0.82f);
    glVertex2f(0.42f, 0.8f);
    glVertex2f(0.42f, 0.79f);
    glVertex2f(0.45f, 0.82f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.39f, 0.82f);
    glVertex2f(0.42f, 0.8f);
    glVertex2f(0.42f, 0.79f);
    glVertex2f(0.39f, 0.82f);
    glEnd();
}
void drawtree2(){


    glBegin(GL_QUADS);
	glColor3f(0.55f, 0.27f, 0.07f);
	glVertex2f(-0.29f, -0.77f);
	glVertex2f(-0.29f, -0.41f);
	glVertex2f(-0.32f, -0.41f);
	glVertex2f(-0.32f, -0.77f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.8f, 0.0f);
	glVertex2f(-0.38f, -0.55f);
	glVertex2f(-0.22f, -0.55f);
	glVertex2f(-0.3f, -0.27f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2f(-0.38f, -0.48f);
	glVertex2f(-0.22f, -0.48f);
	glVertex2f(-0.3f, -0.22f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2f(-0.38f, -0.41f);
	glVertex2f(-0.22f, -0.41f);
	glVertex2f(-0.3f, -0.17f);
	glEnd();

}
void drawtree(){

    glBegin(GL_QUADS);
	glColor3f(0.55f, 0.27f, 0.07f);
	glVertex2f(-0.49f, -0.77f);
	glVertex2f(-0.49f, -0.41f);
	glVertex2f(-0.52f, -0.41f);
	glVertex2f(-0.52f, -0.77f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.8f, 0.0f);
	glVertex2f(-0.58f, -0.55f);
	glVertex2f(-0.42f, -0.55f);
	glVertex2f(-0.5f, -0.27f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2f(-0.58f, -0.48f);
	glVertex2f(-0.42f, -0.48f);
	glVertex2f(-0.5f, -0.22f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2f(-0.58f, -0.41f);
	glVertex2f(-0.42f, -0.41f);
	glVertex2f(-0.5f, -0.17f);
	glEnd();

}
void drawtree1(){

    glBegin(GL_QUADS);
	glColor3f(0.55f, 0.27f, 0.07f);
	glVertex2f(-0.69f, -0.77f);
	glVertex2f(-0.69f, -0.41f);
	glVertex2f(-0.72f, -0.41f);
	glVertex2f(-0.72f, -0.77f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.8f, 0.0f);
	glVertex2f(-0.78f, -0.55f);
	glVertex2f(-0.62f, -0.55f);
	glVertex2f(-0.7f, -0.27f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2f(-0.78f, -0.48f);
	glVertex2f(-0.62f, -0.48f);
	glVertex2f(-0.7f, -0.22f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2f(-0.78f, -0.41f);
	glVertex2f(-0.62f, -0.41f);
	glVertex2f(-0.7f, -0.17f);
	glEnd();

}
void drawtree3(){

    glBegin(GL_QUADS);
	glColor3f(0.55f, 0.27f, 0.07f);
	glVertex2f(-0.89f, -0.77f);
	glVertex2f(-0.89f, -0.41f);
	glVertex2f(-0.92f, -0.41f);
	glVertex2f(-0.92f, -0.77f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.8f, 0.0f);
	glVertex2f(-0.98f, -0.55f);
	glVertex2f(-0.82f, -0.55f);
	glVertex2f(-0.9f, -0.27f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2f(-0.98f, -0.48f);
	glVertex2f(-0.82f, -0.48f);
	glVertex2f(-0.9f, -0.22f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2f(-0.98f, -0.41f);
	glVertex2f(-0.82f, -0.41f);
	glVertex2f(-0.9f, -0.17f);
	glEnd();

}
void drawtree4(){

    glBegin(GL_QUADS);
	glColor3f(0.55f, 0.27f, 0.07f);
	glVertex2f(0.89f, -0.77f);
	glVertex2f(0.89f, -0.41f);
	glVertex2f(0.92f, -0.41f);
	glVertex2f(0.92f, -0.77f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.8f, 0.0f);
	glVertex2f(0.98f, -0.55f);
	glVertex2f(0.82f, -0.55f);
	glVertex2f(0.9f, -0.27f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2f(0.98f, -0.48f);
	glVertex2f(0.82f, -0.48f);
	glVertex2f(0.9f, -0.22f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2f(0.98f, -0.41f);
	glVertex2f(0.82f, -0.41f);
	glVertex2f(0.9f, -0.17f);
	glEnd();

}
void drawtree5(){

    glBegin(GL_QUADS);
	glColor3f(0.55f, 0.27f, 0.07f);
	glVertex2f(0.69f, -0.77f);
	glVertex2f(0.69f, -0.41f);
	glVertex2f(0.72f, -0.41f);
	glVertex2f(0.72f, -0.77f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.8f, 0.0f);
	glVertex2f(0.78f, -0.55f);
	glVertex2f(0.62f, -0.55f);
	glVertex2f(0.7f, -0.27f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2f(0.78f, -0.48f);
	glVertex2f(0.62f, -0.48f);
	glVertex2f(0.7f, -0.22f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2f(0.78f, -0.41f);
	glVertex2f(0.62f, -0.41f);
	glVertex2f(0.7f, -0.17f);
	glEnd();

}

/*
* Scene 0 - Introduction Screen
*/
void introduction() {
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f); // White text

    // Adjusted positions to OpenGL's -1 to 1 coordinate range
    renderBitmapString(-0.4f,  0.6f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Visualization of Bangladeshi Architectural Heritage");

    glFlush();
}



void monument(){
    glBegin(GL_POLYGON);  //1st
	glColor3f(1.0f, 0.92f, 0.70f);
	glVertex2f(-0.55f, -0.77f);
	glVertex2f(-0.40f, -0.72f);
	glVertex2f(-0.45f, -0.77f);
	glVertex2f(-0.55f, -0.77f);
	glEnd();

	glBegin(GL_POLYGON);  //2nd
	glColor3f(0.74f, 0.74f, 0.74f);
	glVertex2f(-0.47f, -0.77f);
	glVertex2f(-0.25f, -0.63f);
	glVertex2f(-0.36f, -0.77f);
	glVertex2f(-0.47f, -0.77f);
	glEnd();

	glBegin(GL_POLYGON);  //3rd
	glColor3f(1.0f, 0.92f, 0.70f);
	glVertex2f(-0.36f, -0.77f);
	glVertex2f(-0.11f, -0.47f);
	glVertex2f(-0.27f, -0.77f);
	glVertex2f(-0.36f, -0.77f);
	glEnd();

	glBegin(GL_POLYGON);  //4th
	glColor3f(0.74f, 0.74f, 0.74f);
	glVertex2f(-0.27f, -0.77f);
	glVertex2f(-0.01f, -0.27f);
	glVertex2f(-0.17f, -0.77f);
	glVertex2f(-0.27f, -0.77f);
	glEnd();

	glBegin(GL_POLYGON);  //5th
	glColor3f(1.0f, 0.92f, 0.70f);
	glVertex2f(-0.17f, -0.77f);
	glVertex2f(0.06f, -0.05f);
	glVertex2f(-0.07f, -0.77f);
	glVertex2f(-0.17f, -0.77f);
	glEnd();

	glBegin(GL_POLYGON);  //6th
	glColor3f(0.74f, 0.74f, 0.74f);
	glVertex2f(-0.07f, -0.77f);
	glVertex2f(0.12f, 0.25f);
	glVertex2f(0.03f, -0.77f);
	glVertex2f(-0.07f, -0.77f);
	glEnd();

	glBegin(GL_POLYGON);  //7th
	glColor3f(1.0f, 0.92f, 0.70f);
	glVertex2f(0.03f, -0.77f);
	glVertex2f(0.13f, -0.68f);
	glVertex2f(0.17f, 0.80f);
	glVertex2f(0.03f, -0.77f);
	glEnd();

	glBegin(GL_POLYGON);  //8th
	glColor3f(1.0f, 0.92f, 0.70f);
	glVertex2f(0.13f, -0.68f);
	glVertex2f(0.23f, -0.77f);
	glVertex2f(0.17f, 0.80f);
	glVertex2f(0.13f, -0.68f);
	glEnd();

	glBegin(GL_POLYGON);  //9th
	glColor3f(0.74f, 0.74f, 0.74f);
	glVertex2f(0.23f, -0.77f);
	glVertex2f(0.19f, 0.25f);
	glVertex2f(0.33f, -0.77f);
	glVertex2f(0.23f, -0.77f);
	glEnd();

	glBegin(GL_POLYGON);  //10th
	glColor3f(1.0f, 0.92f, 0.70f);
	glVertex2f(0.33f, -0.77f);
	glVertex2f(0.23f, -0.05f);
	glVertex2f(0.43f, -0.77f);
	glVertex2f(0.33f, -0.77f);
	glEnd();

	glBegin(GL_POLYGON);  //11th
	glColor3f(0.74f, 0.74f, 0.74f);
	glVertex2f(0.43f, -0.77f);
	glVertex2f(0.29f, -0.27f);
	glVertex2f(0.52f, -0.77f);
	glVertex2f(0.43f, -0.77f);
	glEnd();

	glBegin(GL_POLYGON);  //12th
	glColor3f(1.0f, 0.92f, 0.70f);
	glVertex2f(0.52f, -0.77f);
	glVertex2f(0.38f, -0.47f);
	glVertex2f(0.61f, -0.77f);
	glVertex2f(0.52f, -0.77f);
	glEnd();

	glBegin(GL_POLYGON);  //13th
	glColor3f(0.74f, 0.74f, 0.74f);
	glVertex2f(0.61f, -0.77f);
	glVertex2f(0.50f, -0.63f);
	glVertex2f(0.71f, -0.77f);
	glVertex2f(0.51f, -0.77f);
	glEnd();

	glBegin(GL_POLYGON);  //14th
	glColor3f(1.0f, 0.92f, 0.70f);
	glVertex2f(0.71f, -0.77f);
	glVertex2f(0.63f, -0.72f);
	glVertex2f(0.81f, -0.77f);
	glVertex2f(0.71f, -0.77f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.92f, 0.70f);
	glVertex2f(0.08f, -0.20f);
	glVertex2f(0.21f, -0.20f);
	glVertex2f(0.21f, -0.25f);
	glVertex2f(0.075f, -0.25f);
	glEnd();

	glBegin(GL_TRIANGLES);  //Upper
	glColor3f(0.74f, 0.74f, 0.74f);
	glVertex2f(0.15f, 0.15f);
	glVertex2f(0.21f, -0.20f);
	glVertex2f(0.08f, -0.20f);
	glEnd();

	glBegin(GL_TRIANGLES);  //Downer
	glColor3f(0.74f, 0.74f, 0.74f);
	glVertex2f(0.13f, -0.68f);
	glVertex2f(0.21f, -0.25f);
	glVertex2f(0.075f, -0.25f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.79f, 0.15f);
	glVertex2f(0.13f, -0.68f);
	glVertex2f(0.03f, -0.77f);
	glVertex2f(0.23f, -0.77f);
	glEnd();

	glBegin(GL_LINE_STRIP);  //Floor Shading
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-1.0f, -0.77f);
	glVertex2f(-0.55f, -0.77f);
	glVertex2f(0.03f, -0.77f);
	glVertex2f(0.13f, -0.68f);
	glVertex2f(0.23f, -0.77f);
	glVertex2f(0.81f, -0.77f);
	glVertex2f(1.0f, -0.77f);
	glEnd();
}
void nationalflag(){
    glBegin(GL_QUADS);  //Pole
    glColor3f(0.42f, 0.29f, 0.25f);  //Brown
    glVertex2f(0.45f, -0.2f);
    glVertex2f(0.44f, -0.2f);
    glVertex2f(0.44f, -0.82f);
    glVertex2f(0.45f, -0.82f);
    glEnd();

    float waveAmplitude = 0.02f;
    float waveFrequency = 10.0f;

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.41f, 0.30f); // Green
    glVertex2f(0.45f, -0.21f);
    glVertex2f(0.45f, -0.35f);
    glVertex2f(0.62f, -0.35f+ waveAmplitude * sin(waveFrequency * 0.62f + waveTime));
    glVertex2f(0.62f, -0.21f+ waveAmplitude * sin(waveFrequency * 0.62f + waveTime));
    glEnd();

    GLfloat x = 0.53f, y = -0.28f, r = 0.04f;
    float circleWave = waveAmplitude * sin(waveFrequency * 0.53 + waveTime);
    glColor3f(1.0f, 0.0f, 0.0f); // Red circle
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 100; i++) {
        float angle = 2.0f * 3.14159f * i / 100;
        glVertex2f(x + cos(angle) * r, y + sin(angle) * r);
    }
    glEnd();
}
void floor(){
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.79f, 0.15f);
    glVertex2f(-1.0f, -0.85f);
    glVertex2f(-1.0f, -0.77f);
    glVertex2f(1.0f, -0.77f);
    glVertex2f(1.0f, -0.85f);
    glEnd();

/* Road */

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-1.0f, -0.85f);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, -0.85f);
    glEnd();

/* White Divider */
    glBegin(GL_QUADS);  //1st
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-1.0f, -0.92f);
    glVertex2f(-0.9f, -0.92f);
    glVertex2f(-0.9f, -0.93f);
    glVertex2f(-1.0f, -0.93f);
    glEnd();

    glBegin(GL_QUADS);  //2nd
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.8f, -0.92f);
    glVertex2f(-0.65f, -0.92f);
    glVertex2f(-0.65f, -0.93f);
    glVertex2f(-0.8f, -0.93f);
    glEnd();

    glBegin(GL_QUADS);  //3nd
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.55f, -0.92f);
    glVertex2f(-0.40f, -0.92f);
    glVertex2f(-0.40f, -0.93f);
    glVertex2f(-0.55f, -0.93f);
    glEnd();

    glBegin(GL_QUADS);  //4th
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.3f, -0.92f);
    glVertex2f(-0.15f, -0.92f);
    glVertex2f(-0.15f, -0.93f);
    glVertex2f(-0.3f, -0.93f);
    glEnd();

    glBegin(GL_QUADS);  //5th
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.05f, -0.92f);
    glVertex2f(0.1f, -0.92f);
    glVertex2f(0.1f, -0.93f);
    glVertex2f(-0.05f, -0.93f);
    glEnd();

    glBegin(GL_QUADS);  //6th
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.2f, -0.92f);
    glVertex2f(0.35f, -0.92f);
    glVertex2f(0.35f, -0.93f);
    glVertex2f(0.2f, -0.93f);
    glEnd();

    glBegin(GL_QUADS);  //7th
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.45f, -0.92f);
    glVertex2f(0.6f, -0.92f);
    glVertex2f(0.6f, -0.93f);
    glVertex2f(0.45f, -0.93f);
    glEnd();

    glBegin(GL_QUADS);  //8th
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.7f, -0.92f);
    glVertex2f(0.85f, -0.92f);
    glVertex2f(0.85f, -0.93f);
    glVertex2f(0.7f, -0.93f);
    glEnd();

    glBegin(GL_QUADS);  //9th
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.95f, -0.92f);
    glVertex2f(1.0f, -0.92f);
    glVertex2f(1.0f, -0.93f);
    glVertex2f(0.95f, -0.93f);
    glEnd();
/* End of road */
}

/* Code of Project 2*/

void fullsky(){
     glLoadIdentity();
    glBegin(GL_POLYGON);
	glColor3ub(52, 152, 219);
	glVertex2f(-1.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);
	glVertex2f(1.0f, -0.5f);
	glVertex2f(-1.0f, -0.5f);


	glEnd();
}
void grass4(){
    glBegin(GL_POLYGON);
	glColor3ub(34, 153, 84);
        glVertex2f(-1.0f, -0.7f);
        glVertex2f(1.0f, -.7f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(-1.0f, -1.0f);
	glEnd();

	//road
	glBegin(GL_QUADS);
    glColor3ub(0,0,0);
        glVertex2f(-1.0f, -.85f);
        glVertex2f(1.0f, -.85f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(-1.0f, -1.0f);
    glEnd();

	//road divider 1
	glBegin(GL_QUADS);
	glColor3ub(255,255,255);
		glVertex2f(-1.0f, -.92f);
		glVertex2f(-0.9f, -.92f);
		glVertex2f(-0.9f, -0.95f);
		glVertex2f(-1.0f, -0.95f);
	glEnd();

	//road divider 2
	glBegin(GL_QUADS);
	glColor3ub(255,255,255);
		glVertex2f(-0.8f, -.92f);
		glVertex2f(-0.7f, -.92f);
		glVertex2f(-0.7f, -0.95f);
		glVertex2f(-0.8f, -0.95f);
	glEnd();

	//road divider 3
	glBegin(GL_QUADS);
	glColor3ub(255,255,255);
		glVertex2f(-0.6f, -.92f);
		glVertex2f(-0.5f, -.92f);
		glVertex2f(-0.5f, -0.95f);
		glVertex2f(-0.6f, -0.95f);
	glEnd();

	//road divider 4
	glBegin(GL_QUADS);
	glColor3ub(255,255,255);
		glVertex2f(-0.4f, -.92f);
		glVertex2f(-0.3f, -.92f);
		glVertex2f(-0.3f, -0.95f);
		glVertex2f(-0.4f, -0.95f);
	glEnd();

	//road divider 5
	glBegin(GL_QUADS);
	glColor3ub(255,255,255);
		glVertex2f(-0.2f, -.92f);
		glVertex2f(-0.1f, -.92f);
		glVertex2f(-0.1f, -0.95f);
		glVertex2f(-0.2f, -0.95f);
	glEnd();

	//road divider 6
	glBegin(GL_QUADS);
	glColor3ub(255,255,255);
		glVertex2f(0.0f, -.92f);
		glVertex2f(0.1f, -.92f);
		glVertex2f(0.1f, -0.95f);
		glVertex2f(0.0f, -0.95f);
	glEnd();

	//road divider 7
	glBegin(GL_QUADS);
	glColor3ub(255,255,255);
		glVertex2f(0.2f, -.92f);
		glVertex2f(0.3f, -.92f);
		glVertex2f(0.3f, -0.95f);
		glVertex2f(0.2f, -0.95f);
	glEnd();

	//road divider 8
	glBegin(GL_QUADS);
	glColor3ub(255,255,255);
		glVertex2f(0.4f, -.92f);
		glVertex2f(0.5f, -.92f);
		glVertex2f(0.5f, -0.95f);
		glVertex2f(0.4f, -0.95f);
	glEnd();

	//road divider 9
	glBegin(GL_QUADS);
	glColor3ub(255,255,255);
		glVertex2f(0.6f, -.92f);
		glVertex2f(0.7f, -.92f);
		glVertex2f(0.7f, -0.95f);
		glVertex2f(0.6f, -0.95f);
	glEnd();

	//road divider 10
	glBegin(GL_QUADS);
	glColor3ub(255,255,255);
		glVertex2f(0.8f, -.92f);
		glVertex2f(0.9f, -.92f);
		glVertex2f(0.9f, -0.95f);
		glVertex2f(0.8f, -0.95f);
	glEnd();



}
void stairs(){
    glBegin(GL_POLYGON);
	glColor3ub(150,40,27);
	glVertex2f(-1.0f, -0.7f);
	glVertex2f(1.0f, -.7f);
	glVertex2f(1.0f, -.5f);
	glVertex2f(-1.0f, -.5f);


	glEnd();
	glBegin(GL_LINES);
	glLineWidth(8);
	glColor3ub(0,0,0);
	glVertex2f(-1.0f, -0.533f);
	glVertex2f(1.0f, -.533f);


	glColor3ub(0,0,0);
	glVertex2f(-1.0f, -0.566f);
	glVertex2f(1.0f, -.566f);


	glColor3ub(0,0,0);
	glVertex2f(-1.0f, -0.6f);
	glVertex2f(1.0f, -.6f);


	glColor3ub(0,0,0);
	glVertex2f(-1.0f, -0.633f);
	glVertex2f(1.0f, -.633f);


	glColor3ub(0,0,0);
	glVertex2f(-1.0f, -0.666f);
	glVertex2f(1.0f, -.666f);


	glColor3ub(0,0,0);
	glVertex2f(-1.0f, -0.7f);
	glVertex2f(1.0f, -.7f);


	glColor3ub(0,0,0);
	glVertex2f(-1.0f, -0.5f);
	glVertex2f(1.0f, -.5f);


	glEnd();


	glBegin(GL_POLYGON);
	glColor3ub(255,255,255);
	glVertex2f(-.50f, -0.5f);
	glVertex2f(-.53f, -.5f);
	glVertex2f(-.63f, -.7f);
	glVertex2f(-.60f, -.7f);


	glEnd();


	glBegin(GL_POLYGON);
	glColor3ub(255,255,255);
	glVertex2f(.50f, -0.5f);
	glVertex2f(.53f, -.5f);
	glVertex2f(.63f, -.7f);
	glVertex2f(.60f, -.7f);


	glEnd();


	glBegin(GL_POLYGON);
	glColor3ub(255,255,255);
	glVertex2f(.01f, -0.5f);
	glVertex2f(-.01f, -.5f);
	glVertex2f(-.035f, -.7f);
	glVertex2f(.035f, -.7f);

	glEnd();


}
void parliament(){


    glBegin(GL_POLYGON);
	glColor3ub(156, 150, 130);
	glVertex2f(0.4f, 0.3f);
	glVertex2f(-0.4f, 0.3f);
	glVertex2f(-0.4f, 0.48f);
	glVertex2f(-0.2f, 0.51f);
	glVertex2f(0.2f, 0.51f);
	glVertex2f(0.4f, 0.48f);
	glEnd();


	glBegin(GL_LINES);
	glColor3ub(0,0,0);
	glVertex2f(-0.4f, 0.3f);
	glVertex2f(-0.4f, 0.48f);


	glColor3ub(0,0,0);
	glVertex2f(0.4f, 0.3f);
	glVertex2f(0.4f, 0.48f);


	glColor3ub(0,0,0);
	glVertex2f(-0.4f, 0.48f);
	glVertex2f(-0.2f, 0.51f);


	glColor3ub(0,0,0);
	glVertex2f(0.4f, 0.48f);
	glVertex2f(0.2f, 0.51f);


	glColor3ub(0,0,0);
	glVertex2f(-0.2f, 0.51f);
	glVertex2f(0.2f, 0.51f);
	glEnd();


	 glBegin(GL_POLYGON);
	glColor3ub(0,0,0);
	glVertex2f(0.25f, 0.4f);
	glVertex2f(-0.25f, 0.4f);
	glVertex2f(-0.25f, 0.46f);
	glVertex2f(0.25f, 0.46f);
	glEnd();

   glBegin(GL_POLYGON);
	glColor3ub(156, 150, 130);
	glVertex2f(-0.1f, -0.5f);
	glVertex2f(0.1f, -0.5f);
	glVertex2f(0.1, .4f);
	glVertex2f(-0.1f, .4f);
	glEnd();
    glBegin(GL_POLYGON);
	glColor3ub(0,0,0);
	glVertex2f(-0.08f, -0.5f);
	glVertex2f(0.08f, -0.5f);
	glVertex2f(0.08, -0.35f);
	glVertex2f(-0.08f, -0.35f);
    glEnd();


    glBegin(GL_POLYGON);
	glColor3ub(156, 150, 130);
	glVertex2f(-0.1f, -0.5f);
	glVertex2f(-0.3f, -0.5f);
	glVertex2f(-0.3, .43f);
	glVertex2f(-0.1f, .4f);
	glEnd();


	 glBegin(GL_POLYGON);
	glColor3ub(0,0,0);
	glVertex2f(-0.11f, -0.5f);
	glVertex2f(-0.12f, -0.5f);
	glVertex2f(-0.12, .4f);
	glVertex2f(-0.11f, .4f);
	glEnd();


	 glBegin(GL_POLYGON);
	glColor3ub(156, 150, 130);
	glVertex2f(0.1f, -0.5f);
	glVertex2f(0.3f, -0.5f);
	glVertex2f(0.3, .43f);
	glVertex2f(0.1f, .4f);
	glEnd();


	 glBegin(GL_POLYGON);
	glColor3ub(0,0,0);
	glVertex2f(0.11f, -0.5f);
	glVertex2f(0.12f, -0.5f);
	glVertex2f(0.12, .4f);
	glVertex2f(0.11f, .4f);
	glEnd();


	 glBegin(GL_POLYGON);
	glColor3ub(156, 150, 130);
	glVertex2f(-0.3f, -0.5f);
	glVertex2f(-0.3f, 0.33f);
	glVertex2f(-0.45f, 0.36f);
	glVertex2f(-0.60f, 0.33f);
	glVertex2f(-0.60f, -0.5f);
	glEnd();


	glBegin(GL_LINES);
	glColor3ub(0,0,0);
	glVertex2f(-0.45f, -0.5f);
	glVertex2f(-0.45f, 0.36f);


	glColor3ub(0,0,0);
	glVertex2f(-0.3f, -0.5f);
	glVertex2f(-0.3f, 0.43f);


    glEnd();


     glBegin(GL_POLYGON);
	glColor3ub(156, 150, 130);
	glVertex2f(0.3f, -0.5f);
	glVertex2f(0.3f, 0.33f);
	glVertex2f(0.45f, 0.36f);
	glVertex2f(0.60f, 0.33f);
	glVertex2f(0.60f, -0.5f);
	glEnd();


	glBegin(GL_LINES);
	glColor3ub(0,0,0);
	glVertex2f(0.45f, -0.5f);
	glVertex2f(0.45f, 0.36f);


	glColor3ub(0,0,0);
	glVertex2f(0.3f, -0.5f);
	glVertex2f(0.3f, 0.43f);


    glEnd();

//left side polygon
    glBegin(GL_POLYGON);
	glColor3ub(156, 150, 130);
        glVertex2f(-0.6f, -0.5f);///////////////////////////////////////////////////////
        glVertex2f(-0.8f, -0.5f);
        glVertex2f(-0.8f, 0.29f);
        glVertex2f(-0.60f, 0.33f);
	glEnd();

    glBegin(GL_POLYGON);
	glColor3ub(156, 150, 130);
        glVertex2f(-0.6f, -0.5f);
        glVertex2f(-0.9f, -0.5f);
        glVertex2f(-0.9f, 0.18f);
        glVertex2f(-0.60f, 0.33f);
	glEnd();

    glBegin(GL_POLYGON);
	glColor3ub(0,0,0);
        glVertex2f(-0.65f, -0.5f);
        glVertex2f(-0.66f, -0.5f);
        glVertex2f(-0.66f, 0.31f);
        glVertex2f(-0.65f, 0.316f);
	glEnd();


	glBegin(GL_LINES);
	glColor3ub(0,0,0);
        glVertex2f(-0.8f, -0.5f);
        glVertex2f(-0.8f, 0.29f);
	glEnd();


    glBegin(GL_LINES);
	glColor3ub(0,0,0);
	glVertex2f(-0.9f, -0.5f);
	glVertex2f(-0.9f, 0.18f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(156, 150, 130);
	glVertex2f(0.6f, -0.5f);
	glVertex2f(0.9f, -0.5f);
	glVertex2f(0.9f, 0.18f);
	glVertex2f(0.60f, 0.33f);
	glEnd();


            glBegin(GL_POLYGON);
	glColor3ub(156, 150, 130);
	glVertex2f(0.6f, -0.5f);
	glVertex2f(0.8f, -0.5f);
	glVertex2f(0.8f, 0.29f);
	glVertex2f(0.60f, 0.33f);
	glEnd();


	glBegin(GL_LINES);
	glColor3ub(0,0,0);
	glVertex2f(0.8f, -0.5f);
	glVertex2f(0.8f, 0.29f);
	glEnd();

            glBegin(GL_LINES);
	glColor3ub(0,0,0);
	glVertex2f(0.9f, -0.5f);
	glVertex2f(0.9f, 0.18f);
	glEnd();


	 glBegin(GL_POLYGON);
	glColor3ub(0,0,0);
	glVertex2f(0.65f, -0.5f);
	glVertex2f(0.66f, -0.5f);
	glVertex2f(0.66f, 0.31f);
	glVertex2f(0.65f, 0.316f);
	glEnd();


	glBegin(GL_TRIANGLES);
	glColor3ub(0,0,0);
	glVertex2f(0.48f, -0.3f);
	glVertex2f(0.63f, -0.31f);
	glVertex2f(0.57f, 0.28f);
	glEnd();


	glBegin(GL_TRIANGLES);
	glColor3ub(0,0,0);
	glVertex2f(-0.48f, -0.3f);
	glVertex2f(-0.63f, -0.31f);
	glVertex2f(-0.57f, 0.28f);
	glEnd();


	 glBegin(GL_POLYGON);
	glColor3ub(0,0,0);
	glVertex2f(0.48f, -0.5f);
	glVertex2f(0.63f, -0.5f);
	glVertex2f(0.63f, -0.35f);
	glVertex2f(0.48f, -0.34f);
	glEnd();


	 glBegin(GL_POLYGON);
	glColor3ub(0,0,0);
	glVertex2f(-0.48f, -0.5f);
	glVertex2f(-0.63f, -0.5f);
	glVertex2f(-0.63f, -0.35f);
	glVertex2f(-0.48f, -0.34f);
	glEnd();


	 glBegin(GL_POLYGON);
	glColor3ub(0,0,0);
	glVertex2f(-0.05f, -0.3f);
	glVertex2f(0.05f, -0.3f);
	glVertex2f(0.05f, -0.25f);
	glVertex2f(-0.05f, -0.25f);
	glEnd();


    glBegin(GL_LINES);

	glColor3ub(0,0,0);
	glVertex2f(-0.11f, 0.4f);
	glVertex2f(0.11f, 0.4f);


	glColor3ub(0,0,0);
	glVertex2f(-0.3f, 0.43f);
	glVertex2f(-0.1f, 0.4f);


	glColor3ub(0,0,0);
	glVertex2f(0.3f, 0.43f);
	glVertex2f(0.1f, 0.4f);


	glColor3ub(0,0,0);
	glVertex2f(-0.3f, 0.33f);
	glVertex2f(-0.45f, 0.36f);


	glColor3ub(0,0,0);
	glVertex2f(0.3f, 0.33f);
	glVertex2f(0.45f, 0.36f);


	glColor3ub(0,0,0);
	glVertex2f(0.45f, 0.36f);
	glVertex2f(0.80f, 0.29f);


	glColor3ub(0,0,0);
	glVertex2f(-0.45f, 0.36f);
	glVertex2f(-0.80f, 0.29f);
	glEnd();



}
void Flag() {
float waveAmplitude = 0.02f;  // Amplitude of the wave
    float waveFrequency = 10.0f; // Frequency of the wave

    glBegin(GL_QUADS);
    glColor3f(0.42f, 0.29f, 0.25f);
    glVertex2f(-0.01f, -0.5f);
    glVertex2f(0.005f, -0.5f);
    glVertex2f(0.005f, 0.5f);
    glVertex2f(-0.01f, 0.5f);
    glEnd();
    // Draw the waving flag
    glBegin(GL_QUADS);

    glColor3ub(0, 153, 51);
        glColor3f(0.0f, 0.41f, 0.30f);

    glVertex2f(0.005f, 0.4f);
    glVertex2f(0.4f, 0.4f + waveAmplitude * sin(waveFrequency * 0.4f + waveOffsets));
    glVertex2f(0.4f, 0.2f + waveAmplitude * sin(waveFrequency * 0.4f + waveOffsets));
    glVertex2f(0.005f, 0.2f);
    glEnd();

    float radius = 0.05f;
    int numSegments = 100;
    float circleWaveY = 0.3f + waveAmplitude * sin(waveFrequency * 0.4f + waveOffsets);

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(244, 42, 65); // Red circle
    glVertex2f(0.2f, circleWaveY); // Center of circle
    for (int i = 0; i <= numSegments; i++) {
        float angle = i * 2.0f * PI / numSegments;
        float dx = radius * cos(angle);
        float dy = radius * sin(angle);
        glVertex2f(0.2f + dx, circleWaveY + dy);
    }
    glEnd();
}
/* Code of Project 3*/

void display1() {
    //Background Color
    if (isDay) {
        glClearColor(0.5f, 0.8f, 1.0f, 1.0f); //Day sky
    } else {
        glClearColor(0.0f, 0.0f, 0.1f, 1.0f); //Night sky
    }
    // Draw the sun
    if (isDay) {
        circle(-0.75f, sunY, 0.1f, 1.0f, 1.0f, 0.0f);
    }

   // Draw the moon
   if (!isDay) {
       circle(-0.75f, moonY, 0.1f, 0.9f, 0.9f, 0.9f);
    }

	glPushMatrix();
    glTranslatef(position,0.0f, 0.0f);
    Cloud(0.5f,0.8f,0.11f);
    Cloud(-0.22f,0.8f,0.14f);
    Cloud(-1.3f,0.7f,0.14f);
    Cloud(0.98f,0.7f,0.14f);
    xCloud(0.65f,0.6f,0.09f);
    xCloud(-.28f,0.8f,0.14f);

    glPopMatrix();

    glPushMatrix();
    glTranslatef(-position,0.0f, 0.0f);

    birds();
    glPopMatrix();

    grass();
    grass1();
    grass2();
    grass3();
    drawtree();
    drawtree1();
    drawtree2();
    drawtree3();
    drawtree4();
    drawtree5();

	monument();
    nationalflag();
    floor();

    glPushMatrix();
    glTranslatef(-position, 0.0f, 0.0f);
        glPopMatrix();
}
void showMonumentText() {
    glClearColor(0,0,0,1); glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    renderBitmapString(-0.55f, 0.5f, 0, GLUT_BITMAP_TIMES_ROMAN_24, "National Martyrs' Monument");
    renderBitmapString(-0.55f, 0.3f, 0, GLUT_BITMAP_HELVETICA_18, "This is the symbol of the 1971 Liberation War.");
    renderBitmapString(-0.55f, -0.8f, 0, GLUT_BITMAP_HELVETICA_12, "Press 2 .......");
}

void showParliamentText() {
    glClearColor(0,0,0,1); glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    renderBitmapString(-0.55f, 0.5f, 0, GLUT_BITMAP_TIMES_ROMAN_24, "National Parliament House");
    renderBitmapString(-0.55f, 0.3f, 0, GLUT_BITMAP_HELVETICA_18, "which is the masterpiece by Louis Kahn.");
    renderBitmapString(-0.55f, -0.8f, 0, GLUT_BITMAP_HELVETICA_12, "Press 4 .......");
}

void showShaheedText() {
    glClearColor(0,0,0,1); glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    renderBitmapString(-0.55f, 0.5f, 0, GLUT_BITMAP_TIMES_ROMAN_24, "Shaheed Minar");
    renderBitmapString(-0.55f, 0.3f, 0, GLUT_BITMAP_HELVETICA_18, "This is the Memorial of the 1952 Language Movement.");
    renderBitmapString(-0.55f, -0.8f, 0, GLUT_BITMAP_HELVETICA_12, "Press 6 .......");
}

void display2(){
    //Background Color
    if (isDay) {
        glClearColor(0.5f, 0.8f, 1.0f, 1.0f); //Day sky
    } else {
        glClearColor(0.0f, 0.0f, 0.2f, 1.0f); //Night sky
    }
     //Draw the sun
    if (isDay) {
        circle(-0.75f, sunY, 0.1f, 1.0f, 1.0f, 0.0f);
    }

    // Draw the moon
    if (!isDay) {
        circle(-0.75f, moonY, 0.1f, 0.9f, 0.9f, 0.9f);
    }
    grass4();
    stairs();
    parliament();
    Flag();
    drawtree1();
    drawtree3();
    drawtree4();
    drawtree5();

	glPushMatrix();
    glTranslatef(position,0.0f, 0.0f);
    Cloud(0.5f,0.8f,0.11f);
    Cloud(-0.22f,0.8f,0.14f);
    Cloud(-1.3f,0.7f,0.14f);
    Cloud(0.98f,0.7f,0.14f);
    xCloud(0.65f,0.6f,0.09f);
    xCloud(-.28f,0.8f,0.14f);
    Cloud(-.39f,0.8f,0.14f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-position,0.0f, 0.0f);

    birds();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-position, 0.0f, 0.0f);
    glPopMatrix();
}

void display3() {


    // Transition the clear background color based on skyColor
    // Clear the background color (sky)
if (isDay) {
    // Transition from light sky blue to black (sunset) or black to light sky blue (sunrise)
    glClearColor(
        (1.0f - skyColor) * 0.0f + skyColor * 0.53f, // Red: Interpolate from 0.0 to 0.53
        (1.0f - skyColor) * 0.0f + skyColor * 0.91f, // Green: Interpolate from 0.0 to 0.81
        (1.0f - skyColor) * 0.0f + skyColor * 0.92f, // Blue: Interpolate from 0.0 to 0.92
        1.0f
    );
} else {
    // Night: Sky is black
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
}
glClear(GL_COLOR_BUFFER_BIT);

// Draw the sky quad color
glBegin(GL_QUADS);
if (isDay) {
    glColor3f(
        (1.0f - skyColor) * 0.0f + skyColor * 0.53f, // Red: Light sky blue to black
        (1.0f - skyColor) * 0.0f + skyColor * 0.91f, // Green
        (1.0f - skyColor) * 0.0f + skyColor * 0.92f  // Blue
    );
} else {
    glColor3f(0.005f, 0.005f, 0.08f); // Night: Black sky
}
glVertex2f(-1.0f, -0.22f);
glVertex2f(1.0f, -0.22f);
glVertex2f(1.0f, 1.0f);
glVertex2f(-1.0f, 1.0f);
glEnd();

// Draw the sun or moon
if (isDay) {
    circle(0.5f, sunY, 0.1f, 1.0f, 1.0f, 0.0f); // Yellow sun
} else {
    circle(0.5f, moonY, 0.1f, 0.9f, 0.9f, 0.9f); // Gray moon
}
   /////////////////////////////////BLACK DROP/////////////////////////////////
        glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-1.0f, -0.22f);
	glVertex2f(-0.36f,-0.22f);
	glVertex2f(-0.36f,0.15f);
	glVertex2f(-0.45f,0.15f);
	glVertex2f(-0.46f,0.25f);
	glVertex2f(-1.0f, 0.25f);
	glEnd();
	//////////////////////////////MIDDLE RED CIRCLE//////////////////////////////
    int i;

	GLfloat x1=0.005f; GLfloat y1=0.2f; GLfloat radius1 =.155f;
	int triangleAmount = 200; //# of lines used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x1, y1); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f( x1 + (radius1 * cos(i *  twicePi / triangleAmount)),
                        y1 + (radius1 * sin(i * twicePi / triangleAmount)) );
		}
	glEnd();

	GLfloat x2=-0.25f; GLfloat y2=0.9f; GLfloat radius2 =.08f;
	int triangleAmount2 = 1000; //# of lines used to draw circle

	//GLfloat radius = 0.8f; //rad

///////////////////////////////SUN/////////////////////////////


////////////////////////////////PILLEE/////////////////////////
    glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.04f, -0.2f);
	glVertex2f(0.04f,0.5f);
	glVertex2f(0.06f, -0.2f);
	glVertex2f(0.06f,0.5f);
	glVertex2f(0.08f, -0.2f);
	glVertex2f(0.08f,0.5f);
    glVertex2f(-0.04f, -0.2f);
	glVertex2f(-0.04f,0.5f);
	glVertex2f(-0.06f, -0.2f);
	glVertex2f(-0.06f,0.5f);
	glVertex2f(-0.08f, -0.2f);
	glVertex2f(-0.08f,0.5f);
	//second
    glVertex2f(0.20f, -0.2f);
	glVertex2f(0.20f,0.28f);
	glVertex2f(0.21f, -0.2f);
	glVertex2f(0.21f,0.28f);
	glVertex2f(-0.20f, -0.2f);
	glVertex2f(-0.20f,0.28f);
	glVertex2f(-0.21f, -0.2f);
	glVertex2f(-0.21f,0.28f);
	//third
	glVertex2f(0.312f, -0.2f);
	glVertex2f(0.312f,0.2f);
	glVertex2f(0.33f, -0.2f);
	glVertex2f(0.33f,0.2f);
	glVertex2f(-0.312f, -0.2f);
	glVertex2f(-0.312f,0.2f);
	glVertex2f(-0.33f, -0.2f);
	glVertex2f(-0.33f,0.2f);



	glEnd();

	//first
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.01f, -0.2f);
	glVertex2f(0.015f,-0.2f);
	glVertex2f(0.015f, 0.32f);
	glVertex2f(-0.01f, 0.32f);
	glEnd();
	//second
		glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.1f, -0.2f);
	glVertex2f(0.13f,-0.2f);
	glVertex2f(0.13f, 0.32f);
	glVertex2f(0.1f, 0.32f);
	glEnd();
	//left second
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.1f, -0.2f);
	glVertex2f(-0.13f,-0.2f);
	glVertex2f(-0.13f, 0.32f);
	glVertex2f(-0.1f, 0.32f);
	glEnd();
	//down middle three
		glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.1f, -0.2f);
	glVertex2f(-0.1f,-0.17f);
	glVertex2f(0.13f, -0.17f);
	glVertex2f(0.13f, -0.2f);
	glEnd();
	//upper middle
		glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.01f, 0.32f);
	glVertex2f(-0.005f, 0.5f);
	glVertex2f(0.008f, 0.5f);
	glVertex2f(0.015f, 0.32f);
	glEnd();
	//upper first
		glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.1f, 0.32f);
	glVertex2f(0.11f,0.5f);
	glVertex2f(0.15f, 0.5f);
	glVertex2f(0.13f, 0.32f);
	glEnd();
	//left upper
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.1f, 0.32f);
	glVertex2f(-0.11f,0.5f);
	glVertex2f(-0.15f, 0.5f);
	glVertex2f(-0.13f, 0.32f);
	glEnd();
	//upper up
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.13f, 0.48f);
	glVertex2f(-0.15f,0.5f);
	glVertex2f(0.15f, 0.5f);
	glVertex2f(0.13f, 0.48f);
	glEnd();
	//third
    glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.17f, -0.2f);
	glVertex2f(0.17f,0.28f);
	glVertex2f(0.19f, 0.28f);
	glVertex2f(0.19f, -0.2f);
	glEnd();
	//left third
	    glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.17f, -0.2f);
	glVertex2f(-0.17f,0.28f);
	glVertex2f(-0.19f, 0.28f);
	glVertex2f(-0.19f, -0.2f);
	glEnd();
	//forth
    glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.22f, -0.2f);
	glVertex2f(0.22f,0.28f);
	glVertex2f(0.24f, 0.28f);
	glVertex2f(0.24f, -0.2f);
	glEnd();
	//left forth
    glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.22f, -0.2f);
	glVertex2f(-0.22f,0.28f);
	glVertex2f(-0.24f, 0.28f);
	glVertex2f(-0.24f, -0.2f);
	glEnd();
	//upper third forth
	    glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.17f, 0.28f);
	glVertex2f(0.24f,0.28f);
	glVertex2f(0.24f, 0.26f);
	glVertex2f(0.17f, 0.26f);
	glEnd();
	    glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.17f, 0.28f);
	glVertex2f(-0.24f,0.28f);
	glVertex2f(-0.24f, 0.26f);
	glVertex2f(-0.17f, 0.26f);
	glEnd();
    //lower third forth
    glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.17f, -0.18f);
	glVertex2f(0.17f,-0.2f);
	glVertex2f(0.24f, -0.2f);
	glVertex2f(0.24f, -0.18f);
	glEnd();
    //lower left third forth
    glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.17f, -0.18f);
	glVertex2f(-0.17f,-0.2f);
	glVertex2f(-0.24f, -0.2f);
	glVertex2f(-0.24f, -0.18f);
	glEnd();
    //fifth
    glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.28f, -0.2f);
	glVertex2f(0.28f, 0.2f);
	glVertex2f(0.30f, 0.2f);
	glVertex2f(0.30f, -0.2f);
	glEnd();
	//sixth
    glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.34f, -0.2f);
	glVertex2f(0.34f, 0.2f);
	glVertex2f(0.36f, 0.2f);
	glVertex2f(0.36f, -0.2f);
	glEnd();
    //left fifth
    glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.28f, -0.2f);
	glVertex2f(-0.28f, 0.2f);
	glVertex2f(-0.30f, 0.2f);
	glVertex2f(-0.30f, -0.2f);
	glEnd();
	//left sixth
    glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.34f, -0.2f);
	glVertex2f(-0.34f, 0.2f);
	glVertex2f(-0.36f, 0.2f);
	glVertex2f(-0.36f, -0.2f);
	glEnd();
	//upper fifth
    glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.28f, 0.18f);
	glVertex2f(0.28f, 0.2f);
	glVertex2f(0.36f, 0.2f);
	glVertex2f(0.36f, 0.18f);
	glEnd();
	//sixth
    glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.28f, 0.18f);
	glVertex2f(-0.28f, 0.2f);
	glVertex2f(-0.36f, 0.2f);
	glVertex2f(-0.36f, 0.18f);
	glEnd();
	//lower
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.28f, -0.2f);
	glVertex2f(0.28f, -0.18f);
	glVertex2f(0.36f, -0.18f);
	glVertex2f(0.36f, -0.2f);
	glEnd();
	//sixth
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.28f, -0.2f);
	glVertex2f(-0.28f, -0.18f);
	glVertex2f(-0.36f, -0.18f);
	glVertex2f(-0.36f, -0.2f);
	glEnd();
	////////////////////////////////////////platform & STAIR/////////////////////////////////////////
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.36f, -0.2f);
	glVertex2f(-0.36f, -0.22f);
	glVertex2f(0.36f, -0.22f);
	glVertex2f(0.36f, -0.2f);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.3f, 0.137f, 0.06f);
	glVertex2f(0.0f, -0.22f);
	glVertex2f(1.0f, -0.22f);
	glVertex2f(1.0f, -1.0f);
	glVertex2f(0.0f, -1.0f);
	glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.3f, 0.137f, 0.06f);
	glVertex2f(0.0f, -0.22f);
	glVertex2f(-1.0f, -0.22f);
	glVertex2f(-1.0f, -1.0f);
	glVertex2f(0.0f, -1.0f);
    glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.66f, 0.48f, 0.38f);
	glVertex2f(0.0f, -0.28f);
	glVertex2f(-1.0f, -0.28f);
	glVertex2f(-1.0f, -0.34f);
	glVertex2f(0.0f, -0.34f);
    glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.66f, 0.48f, 0.38f);
	glVertex2f(0.0f, -0.28f);
	glVertex2f(1.0f, -0.28f);
	glVertex2f(1.0f, -0.34f);
	glVertex2f(0.0f, -0.34f);
    glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.66f, 0.48f, 0.38f);
	glVertex2f(1.0f, -0.42f);
	glVertex2f(-1.0f, -0.42f);
	glVertex2f(-1.0f, -0.48f);
	glVertex2f(1.0f, -0.48f);
    glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.66f, 0.48f, 0.38f);
	glVertex2f(1.0f, -0.54f);
	glVertex2f(-1.0f, -0.54f);
	glVertex2f(-1.0f, -0.60f);
	glVertex2f(1.0f, -0.60f);
    glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.66f, 0.48f, 0.38f);
	glVertex2f(1.0f, -0.66f);
	glVertex2f(-1.0f, -0.66f);
	glVertex2f(-1.0f, -0.72f);
	glVertex2f(1.0f, -0.72f);
    glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.66f, 0.48f, 0.38f);
	glVertex2f(1.0f, -0.78f);
	glVertex2f(-1.0f, -0.78f);
	glVertex2f(-1.0f, -0.84f);
	glVertex2f(1.0f, -0.84f);
    glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.66f, 0.48f, 0.38f);
	glVertex2f(1.0f, -0.90f);
	glVertex2f(-1.0f, -0.90f);
	glVertex2f(-1.0f, -0.96f);
	glVertex2f(1.0f, -0.96f);
    glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex2f(0.12f, -0.28f);
	glVertex2f(0.14f, -0.28f);
	glVertex2f(0.16f, -0.54f);
	glVertex2f(0.14f, -0.54f);
    glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex2f(0.14f, -0.54f);
	glVertex2f(0.16f, -0.54f);
	glVertex2f(0.28f, -1.0f);
	glVertex2f(0.22f, -1.0f);
    glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex2f(0.3f, -0.28f);
	glVertex2f(0.32f, -0.28f);
	glVertex2f(0.36f, -0.54f);
	glVertex2f(0.34f, -0.54f);
    glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex2f(0.34f, -0.54f);
	glVertex2f(0.36f, -0.54f);
	glVertex2f(0.54f, -1.0f);
	glVertex2f(0.48f, -1.0f);
    glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex2f(0.46f, -0.28f);
	glVertex2f(0.48f, -0.28f);
	glVertex2f(0.58f, -0.54f);
	glVertex2f(0.56f, -0.54f);
    glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex2f(0.56f, -0.54f);
	glVertex2f(0.58f, -0.54f);
	glVertex2f(0.94f, -1.0f);
	glVertex2f(0.88f, -1.0f);
    glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex2f(0.62f, -0.28f);
	glVertex2f(0.64f, -0.28f);
	glVertex2f(0.8f, -0.54f);
	glVertex2f(0.78f, -0.54f);
    glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex2f(0.78f, -0.54f);
	glVertex2f(0.8f, -0.54f);
	glVertex2f(1.0f, -0.7f);
	glVertex2f(0.98f, -0.7f);
    glEnd();
//left platform
    glBegin(GL_QUADS);
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex2f(-0.12f, -0.28f);
	glVertex2f(-0.14f, -0.28f);
	glVertex2f(-0.16f, -0.54f);
	glVertex2f(-0.14f, -0.54f);
    glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex2f(-0.14f, -0.54f);
	glVertex2f(-0.16f, -0.54f);
	glVertex2f(-0.28f, -1.0f);
	glVertex2f(-0.22f, -1.0f);
    glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex2f(-0.3f, -0.28f);
	glVertex2f(-0.32f, -0.28f);
	glVertex2f(-0.36f, -0.54f);
	glVertex2f(-0.34f, -0.54f);
    glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex2f(-0.34f, -0.54f);
	glVertex2f(-0.36f, -0.54f);
	glVertex2f(-0.54f, -1.0f);
	glVertex2f(-0.48f, -1.0f);
    glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex2f(-0.46f, -0.28f);
	glVertex2f(-0.48f, -0.28f);
	glVertex2f(-0.58f, -0.54f);
	glVertex2f(-0.56f, -0.54f);
    glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex2f(-0.56f, -0.54f);
	glVertex2f(-0.58f, -0.54f);
	glVertex2f(-0.94f, -1.0f);
	glVertex2f(-0.88f, -1.0f);
    glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex2f(-0.62f, -0.28f);
	glVertex2f(-0.64f, -0.28f);
	glVertex2f(-0.8f, -0.54f);
	glVertex2f(-0.78f, -0.54f);
    glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex2f(-0.78f, -0.54f);
	glVertex2f(-0.8f, -0.54f);
	glVertex2f(-1.0f, -0.7f);
	glVertex2f(-0.98f, -0.7f);
    glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex2f(-1.0f, 0.0f);
	glVertex2f(-0.36f,0.0f);
	glVertex2f(-0.36f,0.05f);
	glVertex2f(-1.0f, 0.05f);
	glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex2f(-0.5f, 0.0f);
	glVertex2f(-0.53f,0.0f);
	glVertex2f(-0.53f,-0.22f);
	glVertex2f(-0.5f, -0.22f);
	glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex2f(-0.97f, 0.0f);
	glVertex2f(-1.0f,0.0f);
	glVertex2f(-1.0f,-0.22f);
	glVertex2f(-0.97f, -0.22f);
	glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex2f(-0.75f, 0.0f);
	glVertex2f(-0.78f,0.0f);
	glVertex2f(-0.78f,-0.22f);
	glVertex2f(-0.75f, -0.22f);
	glEnd();
///////////////////////////////////////////////////cloud//////////////////////////////////////////////////////
   glPushMatrix();
glTranslatef(position,0.0f, 0.0f);
    Cloud(0.5f,0.8f,0.11f);
    Cloud(-0.22f,0.8f,0.14f);
    Cloud(-1.3f,0.7f,0.14f);
    Cloud(0.98f,0.7f,0.14f);
    xCloud(0.65f,0.6f,0.09f);
    xCloud(-.28f,0.8f,0.14f);
    Cloud(-.39f,0.8f,0.14f);

    glPopMatrix();
    ////////////////////////////////////////////////////tree////////////////////////////////////////////

    glBegin(GL_QUADS);
	glColor3f(0.26f, 0.07f, 0.02f);
	glVertex2f(0.52f, 0.0f);
	glVertex2f(0.56f,0.00f);
	glVertex2f(0.56f,-0.22f);
	glVertex2f(0.52f, -0.22f);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.26f, 0.07f, 0.02f);
	glVertex2f(0.64f, 0.0f);
	glVertex2f(0.68f,0.00f);
	glVertex2f(0.68f,-0.22f);
	glVertex2f(0.64f, -0.22f);
	glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.26f, 0.07f, 0.02f);
	glVertex2f(0.72f, 0.0f);
	glVertex2f(0.76f,0.20f);
	glVertex2f(0.77f,-0.22f);
	glVertex2f(0.71f, -0.22f);
	glEnd();
	    //circle 11
    GLfloat t11=0.75f, r11=0.25f, radi11=.1f;

    glColor3f(0.1f, 0.9f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t11, r11);// center of circle
    for(int i12 = 0; i12 <= triangleAmount; i12++)
    {
        glVertex2f( t11 + (radi11 * cos(i12 *  twicePi / triangleAmount)),
                    r11 + (radi11 * sin(i12 * twicePi / triangleAmount)) );
    }
    glEnd();
    // Circle 12
    GLfloat t12 = 0.73f, r12 = 0.12f, radi12 = 0.1f;
    glColor3f(0.1f, 0.9f, 0.0f);  // Green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t11, r11);  // center of circle
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t12 + (radi12 * cos(i12 * twicePi / triangleAmount)),
               r12 + (radi12 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();

// Circle 13
    GLfloat t13 = 0.83f, r13 = 0.1f, radi13 = 0.1f;
    glColor3f(0.1f, 0.9f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t13, r13);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t13 + (radi13 * cos(i12 * twicePi / triangleAmount)),
               r13 + (radi13 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
// Circle 14
    GLfloat t14 = 0.9f, r14 = 0.25f, radi14 = 0.12f;
    glColor3f(0.1f, 0.9f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t14, r14);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t14 + (radi14 * cos(i12 * twicePi / triangleAmount)),
               r14 + (radi14 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
// Circle 15
    GLfloat t15 = 0.52f, r15 = 0.1f, radi15 = 0.12f;
    glColor3f(0.1f, 0.9f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t15, r15);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t15 + (radi15 * cos(i12 * twicePi / triangleAmount)),
               r15 + (radi15 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
// Circle 16
    GLfloat t16 = 0.52f, r16 = 0.2f, radi16 = 0.12f;
    glColor3f(0.1f, 0.9f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t16, r16);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t16 + (radi16 * cos(i12 * twicePi / triangleAmount)),
               r16 + (radi16 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
// Circle 17
    GLfloat t17 = 0.62f, r17 = 0.2f, radi17 = 0.12f;
    glColor3f(0.1f, 0.9f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t17, r17);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t17 + (radi17 * cos(i12 * twicePi / triangleAmount)),
               r17 + (radi17 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
// Circle 18
    GLfloat t18 = 0.65f, r18 = 0.1f, radi18 = 0.12f;
    glColor3f(0.1f, 0.9f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t18, r18);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t18 + (radi18 * cos(i12 * twicePi / triangleAmount)),
               r18 + (radi18 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
    // Circle 19
    GLfloat t19 = 0.65f, r19 = 0.3f, radi19 = 0.15f;
    glColor3f(0.1f, 0.9f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t19, r19);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t19 + (radi19 * cos(i12 * twicePi / triangleAmount)),
               r19 + (radi19 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
        // Circle 19
    GLfloat t40 = 0.85f, r40 = 0.3f, radi40 = 0.15f;
    glColor3f(0.1f, 0.9f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t40, r40);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t40 + (radi40 * cos(i12 * twicePi / triangleAmount)),
               r40 + (radi40 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
    GLfloat t41 = 0.65f, r41 = 0.35f, radi41 = 0.2f;
    glColor3f(0.1f, 0.9f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t41, r41);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t41 + (radi41 * cos(i12 * twicePi / triangleAmount)),
               r41 + (radi41 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
    GLfloat t42 = 0.65f, r42 = 0.25f, radi42 = 0.12f;
    glColor3f(0.0f, 0.39f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t42, r42);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t42 + (radi42 * cos(i12 * twicePi / triangleAmount)),
               r42 + (radi42 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
    GLfloat t43 = 0.64f, r43 = 0.25f, radi43 = 0.12f;
    glColor3f(0.1f, 0.9f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t43, r43);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t43 + (radi43 * cos(i12 * twicePi / triangleAmount)),
               r43 + (radi43 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
    GLfloat t44 = 0.68f, r44 = 0.35f, radi44 = 0.12f;
    glColor3f(0.1f, 0.9f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t44, r44);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t44 + (radi44 * cos(i12 * twicePi / triangleAmount)),
               r44 + (radi44 * sin(i12 * twicePi / triangleAmount)));
    }

    glEnd();
    GLfloat t45 = 0.58f, r45 = 0.35f, radi45 = 0.12f;
    glColor3f(0.0f, 0.39f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t45, r45);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t45 + (radi45 * cos(i12 * twicePi / triangleAmount)),
               r45 + (radi45 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
    GLfloat t46 = 0.59f, r46 = 0.38f, radi46 = 0.12f;
    glColor3f(0.1f, 0.9f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t46, r46);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t46 + (radi46 * cos(i12 * twicePi / triangleAmount)),
               r46 + (radi46 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
    GLfloat t47 = 0.79f, r47 = 0.38f, radi47 = 0.12f;
    glColor3f(0.0f, 0.34f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t47, r47);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t47 + (radi47 * cos(i12 * twicePi / triangleAmount)),
               r47 + (radi47 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
    GLfloat t48 = 0.79f, r48 = 0.4f, radi48 = 0.12f;
    glColor3f(0.1f, 0.9f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t48, r48);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t48 + (radi48 * cos(i12 * twicePi / triangleAmount)),
               r48 + (radi48 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
        GLfloat t49 = 0.59f, r49 = 0.15f, radi49 = 0.12f;
    glColor3f(0.0f, 0.39f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t49, r49);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t49 + (radi49 * cos(i12 * twicePi / triangleAmount)),
               r49 + (radi49 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
            GLfloat t50 = 0.59f, r50 = 0.17f, radi50 = 0.12f;
    glColor3f(0.1f, 0.9f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t50, r50);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t50 + (radi50 * cos(i12 * twicePi / triangleAmount)),
               r50 + (radi50 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();


        glBegin(GL_QUADS);
	glColor3f(0.26f, 0.07f, 0.02f);
	glVertex2f(-0.52f, 0.3f);
	glVertex2f(-0.56f,0.3f);
	glVertex2f(-0.56f,-0.22f);
	glVertex2f(-0.52f, -0.22f);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.26f, 0.07f, 0.02f);
	glVertex2f(-0.64f, 0.3f);
	glVertex2f(-0.68f,0.3f);
	glVertex2f(-0.68f,-0.22f);
	glVertex2f(-0.64f, -0.22f);
	glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.26f, 0.07f, 0.02f);
	glVertex2f(-0.72f, 0.2f);
	glVertex2f(-0.76f,0.20f);
	glVertex2f(-0.77f,-0.22f);
	glVertex2f(-0.71f, -0.22f);
	glEnd();    ///circle 22
    GLfloat t22=-0.75f, r22=0.5f, radi22=.1f;

    glColor3f(0.1f, 0.9f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t22, r22);// center of circle
    for(int i12 = 0; i12 <= triangleAmount; i12++)
    {
        glVertex2f( t22 + (radi22 * cos(i12 *  twicePi / triangleAmount)),
                    r22 + (radi22 * sin(i12 * twicePi / triangleAmount)) );
    }
    glEnd();
    // Circle 23
    GLfloat t23 = -0.73f, r23 = 0.372f, radi23 = 0.1f;
    glColor3f(0.1f, 0.9f, 0.0f);  // Green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t23, r23);  // center of circle
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t23 + (radi23 * cos(i12 * twicePi / triangleAmount)),
               r23 + (radi23 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();

// Circle 24
    GLfloat t24 =-0.83f, r24 = 0.25f, radi24 = 0.14f;
    glColor3f(0.1f, 0.9f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t24, r24);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t24 + (radi24 * cos(i12 * twicePi / triangleAmount)),
               r24 + (radi24 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
// Circle 25
    GLfloat t25 =-0.9f, r25 = 0.5f, radi25 = 0.18f;
    glColor3f(0.1f, 0.9f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t25, r25);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t25 + (radi25 * cos(i12 * twicePi / triangleAmount)),
               r25 + (radi25 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
// Circle 26
    GLfloat t26 = -0.52f, r26 = 0.35f, radi26 = 0.15f;
    glColor3f(0.1f, 0.9f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t26, r26);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t26 + (radi26 * cos(i12 * twicePi / triangleAmount)),
               r26 + (radi26 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
// Circle 27
    GLfloat t27 = -0.52f, r27 = 0.45f, radi27 = 0.12f;
    glColor3f(0.1f, 0.9f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t27, r27);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t27 + (radi27 * cos(i12 * twicePi / triangleAmount)),
               r27 + (radi27 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
// Circle 28
    GLfloat t28 = -0.62f, r28 = 0.45f, radi28 = 0.12f;
    glColor3f(0.2f, 0.9f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t28, r28);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t28 + (radi28 * cos(i12 * twicePi / triangleAmount)),
               r28 + (radi28 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
// Circle 29
    GLfloat t29 = -0.65f, r29 = 0.35f, radi29 = 0.18f;
    glColor3f(0.1f, 0.9f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t29, r29);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t29 + (radi29 * cos(i12 * twicePi / triangleAmount)),
               r29 + (radi29 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
    // Circle 30
    GLfloat t30 = -0.65f, r30 = 0.6f, radi30 = 0.15f;
    glColor3f(0.1f, 0.9f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t30, r30);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t30 + (radi30 * cos(i12 * twicePi / triangleAmount)),
               r30 + (radi30 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
                GLfloat t51 = -0.59f, r51 = 0.27f, radi51 = 0.12f;
    glColor3f(0.0f, 0.39f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t51, r51);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t51 + (radi51 * cos(i12 * twicePi / triangleAmount)),
               r51 + (radi51 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
                GLfloat t52 = -0.59f, r52 = 0.27f, radi52 = 0.12f;
    glColor3f(0.0f, 0.39f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t52, r52);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t52 + (radi52 * cos(i12 * twicePi / triangleAmount)),
               r52 + (radi52 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
                GLfloat t53 = -0.59f, r53 = 0.25f, radi53 = 0.12f;
    glColor3f(0.1f, 0.9f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t53, r53);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t53 + (radi53 * cos(i12 * twicePi / triangleAmount)),
               r53 + (radi53 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
        GLfloat t54 = -0.8f, r54 = 0.4f, radi54 = 0.12f;
    glColor3f(0.0f, 0.39f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t54, r54);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t54 + (radi54 * cos(i12 * twicePi / triangleAmount)),
               r54 + (radi54 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
                GLfloat t55 = -0.8f, r55 = 0.42f, radi55 = 0.12f;
    glColor3f(0.1f, 0.9f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t55, r55);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t55 + (radi55 * cos(i12 * twicePi / triangleAmount)),
               r55 + (radi55 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
                GLfloat t56 = -0.65f, r56 = 0.52f, radi56 = 0.12f;
    glColor3f(0.0f, 0.39f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t56, r56);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t56 + (radi56 * cos(i12 * twicePi / triangleAmount)),
               r56 + (radi56 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
    GLfloat t57 = -0.65f, r57 = 0.48f, radi57 = 0.12f;
    glColor3f(0.1f, 0.9f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t57, r57);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t57 + (radi57 * cos(i12 * twicePi / triangleAmount)),
               r57 + (radi57 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
        ////////////////////////flower in platform
    glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.06f, -0.225f);
	glVertex2f(-0.07f,-0.24f);
	glVertex2f(0.07f, -0.24f);
	glVertex2f(0.06f,-0.225f);
	glEnd();
// Circle 34
    GLfloat t34 = 0.0f, r34 = -0.22f, radi34 = 0.05f;
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t34, r34);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t34 + (radi34 * cos(i12 * twicePi / triangleAmount)),
               r34 + (radi34 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();

    glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.22f, -0.22f);
	glVertex2f(-0.08f,-0.22f);
	glVertex2f(-0.08f, -0.24f);
	glVertex2f(-0.22f,-0.24f);
	glEnd();
// Circle 35
    GLfloat t35 = -0.15f, r35 = -0.22f, radi35 = 0.058f;
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t35, r35);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t35 + (radi35 * cos(i12 * twicePi / triangleAmount)),
               r35 + (radi35 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();

    glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.22f, -0.22f);
	glVertex2f(0.08f,-0.22f);
	glVertex2f(0.08f, -0.24f);
	glVertex2f(0.22f,-0.24f);
	glEnd();
// Circle 35
    GLfloat t36 = 0.15f, r36 = -0.22f, radi36 = 0.058f;
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t36, r36);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t36 + (radi36 * cos(i12 * twicePi / triangleAmount)),
               r36 + (radi36 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
    //////////////////////////////////////////////////////////////man/////////////////////////////////////////////////

    // Circle 20
    glPushMatrix();
        glTranslatef(0.0f, position2, 0.0f);
    GLfloat t20 = -0.12f, r20 = -0.7f, radi20= 0.05f;
    glColor3f(0.0f, 0.0f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t20, r20);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t20 + (radi20 * cos(i12 * twicePi / triangleAmount)),
               r20 + (radi20 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.12f, -0.7f);
	glVertex2f(-0.11f,-0.7f);
	glVertex2f(-0.11f,-0.95f);
	glVertex2f(-0.12f, -0.95f);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.12f, -0.75f);
	glVertex2f(-0.11f,-0.76f);
	glVertex2f(-0.18f,-0.83f);
	glVertex2f(-0.18f, -0.83f);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.11f, -0.76f);
	glVertex2f(-0.04f,-0.83f);
	glVertex2f(-0.12f,-0.76f);
	glVertex2f(-0.11f, -0.75f);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.12f, -0.95f);
	glVertex2f(-0.14f,-1.0f);
	glVertex2f(-0.13f,-0.99f);
	glVertex2f(-0.11f, -0.95f);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.12f, -0.95f);
	glVertex2f(-0.11f,-0.95f);
	glVertex2f(-0.09f, -1.0f);
	glVertex2f(-0.11f,-0.98f);
	glEnd();
	    // Circle 21
    GLfloat t21 = 0.12f, r21 = -0.7f, radi21= 0.05f;
    glColor3f(0.0f, 0.0f, 0.0f);  // A different green
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t21, r21);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t21 + (radi21 * cos(i12 * twicePi / triangleAmount)),
               r21 + (radi21 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
    glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.12f, -0.7f);
	glVertex2f(0.11f,-0.7f);
	glVertex2f(0.11f,-0.95f);
	glVertex2f(0.12f, -0.95f);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.12f, -0.75f);
	glVertex2f(0.11f,-0.76f);
	glVertex2f(0.18f,-0.83f);
	glVertex2f(0.18f, -0.83f);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.11f, -0.76f);
	glVertex2f(0.04f,-0.83f);
	glVertex2f(0.12f,-0.76f);
	glVertex2f(0.11f, -0.75f);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.12f, -0.95f);
	glVertex2f(0.14f,-1.0f);
	glVertex2f(0.13f,-0.99f);
	glVertex2f(0.11f, -0.95f);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.12f, -0.95f);
	glVertex2f(0.11f,-0.95f);
	glVertex2f(0.09f, -1.0f);
	glVertex2f(0.11f,-0.98f);
	glEnd();
	glPopMatrix();
////////////////////////////////////////////////////Birds/////////////////////////////////////////////////////
//1st
    glPushMatrix();
    glScalef(1.0, 1.0, 0);               // Scale for desired aspect ratio
    glTranslatef(positionX, positionY, 0.0f); // Update position

    // Draw the first bird
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.060f, 0.825f);
    glVertex2f(-0.055f, 0.825f);
    glVertex2f(-0.05f, 0.82f);
    glVertex2f(-0.045f, 0.8f);
    glVertex2f(-0.04f, 0.825f);
    glVertex2f(-0.035f, 0.825f);
    glVertex2f(-0.025f, 0.825f);
    glEnd();

    // Draw the second bird
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.097f, 0.825f);
    glVertex2f(-0.095f, 0.825f);
    glVertex2f(-0.09f, 0.82f);
    glVertex2f(-0.085f, 0.8f);
    glVertex2f(-0.08f, 0.825f);
    glVertex2f(-0.075f, 0.825f);
    glVertex2f(-0.065f, 0.825f);
    glEnd();

    // Draw the third bird
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.125f, 0.825f);
    glVertex2f(-0.120f, 0.825f);
    glVertex2f(-0.115f, 0.82f);
    glVertex2f(-0.110f, 0.8f);
    glVertex2f(-0.105f, 0.825f);
    glVertex2f(-0.100f, 0.825f);
    glVertex2f(-0.100f, 0.825f);
    glEnd();

    // Draw the fourth bird
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.118f, 0.79f);
    glVertex2f(-0.11f, 0.79f);
    glVertex2f(-0.105f, 0.775f);
    glVertex2f(-0.10f, 0.76f);
    glVertex2f(-0.095f, 0.79f);
    glVertex2f(-0.090f, 0.79f);
    glVertex2f(-0.085f, 0.79f);
    glEnd();

    // Draw the fifth bird
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.08f, 0.79f);
    glVertex2f(-0.075f, 0.79f);
    glVertex2f(-0.07f, 0.775f);
    glVertex2f(-0.065f, 0.76f);
    glVertex2f(-0.060f, 0.79f);
    glVertex2f(-0.055f, 0.79f);
    glVertex2f(-0.05f, 0.79f);
    glEnd();

    glPopMatrix();

//////////////////////////////////////////////////////////flower///////////////////////////////////////////////////////
    glPushMatrix();
    glTranslatef(0.0f,position5, 0.0f);
    glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.06f, -0.825f);
	glVertex2f(-0.07f,-0.845f);
	glVertex2f(0.07f, -0.845f);
	glVertex2f(0.06f,-0.825f);
	glEnd();
// Circle 31
    GLfloat t31 = 0.0f, r31 = -0.838f, radi31 = 0.05f;
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t31, r31);
    for (int i12 = 0; i12 <= triangleAmount; i12++) {
    glVertex2f(t31 + (radi31 * cos(i12 * twicePi / triangleAmount)),
               r31 + (radi31 * sin(i12 * twicePi / triangleAmount)));
    }
    glEnd();
    glPopMatrix();
}

// Summary

void display4() {
    // Background
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Title
    glColor3f(1.0f, 1.0f, 1.0f); // White color
    renderBitmapString(-0.3f, 0.6f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Bangladesh's Architectural Heritage");

    // Summary paragraph (split across multiple lines for rendering but feels like one paragraph)
    renderBitmapString(-0.9f, 0.4f, 0.0f, GLUT_BITMAP_HELVETICA_18,
        "Bangladesh is enriched with monuments that echo its glorious past and cultural pride. The National ");
    renderBitmapString(-0.9f, 0.3f, 0.0f, GLUT_BITMAP_HELVETICA_18,
        "Monument in Savar stands tall as a tribute to the valiant souls who embraced martyrdom during the ");
    renderBitmapString(-0.9f, 0.2f, 0.0f, GLUT_BITMAP_HELVETICA_18,
        "Liberation War. Equally symbolic is the National Parliament House, a masterpiece by Louis Kahn, ");
    renderBitmapString(-0.9f, 0.1f, 0.0f, GLUT_BITMAP_HELVETICA_18,
        "representing democratic ideals through its striking architecture. The Shahid Minar, another iconic ");
    renderBitmapString(-0.9f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_18,
        "structure, commemorates the Language Movement martyrs and their brave stance for linguistic rights. ");
    renderBitmapString(-0.9f, -0.1f, 0.0f, GLUT_BITMAP_HELVETICA_18,
        "These landmarks not only tell the story of our nation's struggle and identity but also serve as ");
    renderBitmapString(-0.9f, -0.2f, 0.0f, GLUT_BITMAP_HELVETICA_18,
        "powerful sources of inspiration for generations to come.");

    glFlush(); // Ensure all OpenGL commands are executed
}

void showIntro() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // black background
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);                       // white text

    renderBitmapString(-0.55f, 0.70f, 0, GLUT_BITMAP_TIMES_ROMAN_24,
                       (char*)"BANGLADESH ARCHITECTURAL HERITAGE");


    renderBitmapString(-0.55f,-0.75f, 0, GLUT_BITMAP_HELVETICA_12,
                       (char*)"Press 1 to start .....");
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    switch (currentProject) {
        case 0:  showIntro();            break;   // Intro
        case 1:  showMonumentText();     break;
        case 2:  display1();             break;   // Monument animation
        case 3:  showParliamentText();   break;
        case 4:  display2();             break;   // Parliament animation
        case 5:  showShaheedText();      break;
        case 6:  display3();             break;   // Shaheed animation
        case 7:  display4();             break;   // Summary
    }
    glutSwapBuffers();   // double‑buffered
}


void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}
void handleKeyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: exit(0);          break;   // ESC
        case '1': currentProject = 1; break; // Monument desc
        case '2': currentProject = 2; break; // Monument anim
        case '3': currentProject = 3; break; // Parliament desc
        case '4': currentProject = 4; break; // Parliament anim
        case '5': currentProject = 5; break; // Shaheed desc
        case '6': currentProject = 6; break; // Shaheed anim
        case '7': currentProject = 7; break; // Summary
        case '0': currentProject = 0; break; // (optional) back to intro
        case 'p': // Press 'p' to pause/resume animation
            isAnimating = !isAnimating;
            break;
    }
    glutPostRedisplay();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(40, 30);
	glutCreateWindow("3 IMPORTANT HISTORICAL AND MEMORABLE PLACES OF BANGLADESH");
	glutDisplayFunc(display);

    glutReshapeFunc(reshape);
    glutKeyboardFunc(handleKeyboard);
	glutTimerFunc(0, update, 0);
	glutTimerFunc(0, sunmoon, 0); // FOR SUN MOON
	glutSpecialFunc(SpecialInput);
   	glutMainLoop();
	return 0;
}

