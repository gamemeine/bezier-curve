#include <GLFW/glfw3.h>
#include <stdio.h>
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#define NAME "Bezier curve"
#define DEFAULT_HEIGHT 480
#define DEFAULT_WIDTH 640

struct {
    double x;
    double y;
} controlPoints[5];

int activePoint = 0;

double lerp(double a, double b, double factor) { return a + (b - a) * factor; }

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_1 && action == GLFW_PRESS) activePoint = 0;
    if (key == GLFW_KEY_2 && action == GLFW_PRESS) activePoint = 1;
    if (key == GLFW_KEY_3 && action == GLFW_PRESS) activePoint = 2;
    if (key == GLFW_KEY_4 && action == GLFW_PRESS) activePoint = 3;
    if (key == GLFW_KEY_5 && action == GLFW_PRESS) activePoint = 4;
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double x, y;
        glfwGetCursorPos(window, &x, &y); /* Get cursor position */

        int width, height;
        glfwGetWindowSize(window, &width, &height); /* Get window size */

        /* Translate to real world position */
        x = (x - (width / 2)) / (width / 2);
        y = (-y + (height / 2)) / (height / 2);

        /* Set selected control point coordinates */
        controlPoints[activePoint].x = x;
        controlPoints[activePoint].y = y;
    }
}

void bezier() {
    glPointSize(4);
    glBegin(GL_POINTS);

    double accuracy = 0.001f;

    /* Draw curve */
    for (double t = 0; t <= 1; t += accuracy) {
        double x1 = lerp(controlPoints[0].x, controlPoints[1].x, t);
        double x2 = lerp(controlPoints[1].x, controlPoints[2].x, t);
        double x3 = lerp(controlPoints[2].x, controlPoints[3].x, t);
        double x4 = lerp(controlPoints[3].x, controlPoints[4].x, t);

        double x1x2 = lerp(x1, x2, t);
        double x2x3 = lerp(x2, x3, t);
        double x3x4 = lerp(x3, x4, t);

        double x1x2x2x3 = lerp(x1x2, x2x3, t);
        double x2x3x3x4 = lerp(x2x3, x3x4, t);

        double x = lerp(x1x2x2x3, x2x3x3x4, t);

        double y1 = lerp(controlPoints[0].y, controlPoints[1].y, t);
        double y2 = lerp(controlPoints[1].y, controlPoints[2].y, t);
        double y3 = lerp(controlPoints[2].y, controlPoints[3].y, t);
        double y4 = lerp(controlPoints[3].y, controlPoints[4].y, t);

        double y1y2 = lerp(y1, y2, t);
        double y2y3 = lerp(y2, y3, t);
        double y3y4 = lerp(y3, y4, t);

        double y1y2y2y3 = lerp(y1y2, y2y3, t);
        double y2y3y3y4 = lerp(y2y3, y3y4, t);

        double y = lerp(y1y2y2y3, y2y3y3y4, t);

        glVertex2d(x, y);
    }

    glEnd();
}

void draw() {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit()) return;

    /* Create a windowed mode window and its OpenGL contpoints[4].xt */
    window = glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, NAME, 0, 0);

    if (!window) {
        glfwTerminate();
        return;
    }

    /* Set callbacks */
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    /* Make the window's contpoints[4].xt current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Draw control points */
        glPointSize(24);
        glBegin(GL_POINTS);

        for (int i = 0; i < 5; i++) {
            glVertex2d(controlPoints[i].x, controlPoints[i].y);
        }

        glEnd();

        /* Draw Bezier Curve */
        bezier();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}

int main(void) {
    draw();
    return 0;
}