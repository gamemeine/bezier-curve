#include <GLFW/glfw3.h>

#include <iostream>

#pragma clang diagnostic ignored "-Wdeprecated-declarations"

extern "C" void bezier(uint8_t* buffer, unsigned int width, unsigned int height, unsigned int points[5][2], float t);

int width = 640, height = 480;
uint8_t* pixels;

unsigned int points[5][2]{
    {100, 500}, {300, 150}, {600, 700}, {800, 100}, {1200, 500},
};

int activePoint = 4;

void reallocate_pixels() {
    delete pixels;
    pixels = new uint8_t[width * height * 4]();  // multiply by 4 for RGBA standard
}

void framebuffer_size_callback(GLFWwindow* window, int new_width, int new_height) {
    width = new_width;
    height = new_height;

    reallocate_pixels();
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double x, y;
        glfwGetCursorPos(window, &x, &y); /* Get cursor position */

        int size_x, size_y;
        glfwGetWindowSize(window, &size_x, &size_y);

        int pos_x = x * width / size_x;
        int pos_y = height - y * height / size_y;

        points[activePoint][0] = pos_x;
        points[activePoint][1] = pos_y;
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_1 && action == GLFW_PRESS) activePoint = 0;
    if (key == GLFW_KEY_2 && action == GLFW_PRESS) activePoint = 1;
    if (key == GLFW_KEY_3 && action == GLFW_PRESS) activePoint = 2;
    if (key == GLFW_KEY_4 && action == GLFW_PRESS) activePoint = 3;
    if (key == GLFW_KEY_5 && action == GLFW_PRESS) activePoint = 4;
}

void draw_points() {
    /* Draw controll points*/
    for (int p = 0; p < 5; p++) {
        int radius = 16;

        for (int i = points[p][1] - radius; i < points[p][1] + radius; i++) {
            for (int j = points[p][0] - radius; j < points[p][0] + radius; j++) {
                if (i < 0 || i >= height) continue;
                if (j < 0 || j >= width) continue;

                if ((j - points[p][0]) * (j - points[p][0]) + (i - points[p][1]) * (i - points[p][1]) > radius * radius) continue;

                int pixel = (i * width + j) * 4;

                pixels[pixel + 0] = 50;  /* R */
                pixels[pixel + 1] = 50;  /* G */
                pixels[pixel + 2] = 50;  /* B */
                pixels[pixel + 3] = 255; /* A */
            }
        }
    }
}

void erase() {
    for (int i = 0; i < width * height * 4; i++) pixels[i] = 255;
}

int draw() {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) return -1;

    /* Create a windowed mode window and its OpenGL contpoints[4].xt */
    window = glfwCreateWindow(width, height, "Bezier curve", 0, 0);

    /* Set window limits */
    glfwSetWindowSizeLimits(window, width, height, GLFW_DONT_CARE, GLFW_DONT_CARE);

    /* Get actual window size */
    glfwGetFramebufferSize(window, &width, &height);

    /* Realocate pixels */
    reallocate_pixels();

    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's contpoints[4].xt current */
    glfwMakeContextCurrent(window);

    /* Set callbacks */
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Erase board */
        erase();

        /* Calculate Bezier curve */
        for (float t = 0; t <= 1; t += 0.001f) bezier(pixels, width, height, points, t);

        /* Draw control points here */
        draw_points();

        /* Draw pixels here */
        glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

int main() { return draw(); }