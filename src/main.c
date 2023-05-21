#include <stdio.h>
#include <GLFW/glfw3.h>
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#define WINDOW_NAME "Bezier curve"

double lerp(double a, double b, double factor) 
{ 
    return a + (b - a) * factor;
}

void draw()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, WINDOW_NAME, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Define control points */
        double ax = 0.5f, ay = 0.5f;
        double bx = 0.2f, by = -0.8f;
        double cx = -0.1f, cy = 1.6f;
        double dx = -0.6f, dy = -0.8f;
        double ex = -0.8f, ey = 0.4f;

        glPointSize(4);

        /* Draw shapes here */
        glBegin(GL_POINTS);
        
        /* Draw control points */
        // glVertex2d(ax, ay);
        // glVertex2d(bx, by);
        // glVertex2d(cx, cy);
        // glVertex2d(dx, dy);
        // glVertex2d(ex, ey);

        /* Draw curve */
        for(double t = 0; t <= 1; t += 0.001f)
        {
            double x1 = lerp(ax, bx, t);
            double x2 = lerp(bx, cx, t);
            double x3 = lerp(cx, dx, t);
            double x4 = lerp(dx, ex, t);

            double x1x2 = lerp(x1, x2, t);
            double x2x3 = lerp(x2, x3, t);
            double x3x4 = lerp(x3, x4, t);

            double x1x2x2x3 = lerp(x1x2, x2x3, t);
            double x2x3x3x4 = lerp(x2x3, x3x4, t);


            double x = lerp(x1x2x2x3, x2x3x3x4, t);

            double y1 = lerp(ay, by, t);
            double y2 = lerp(by, cy, t);
            double y3 = lerp(cy, dy, t);
            double y4 = lerp(dy, ey, t);

            double y1y2 = lerp(y1, y2, t);
            double y2y3 = lerp(y2, y3, t);
            double y3y4 = lerp(y3, y4, t);

            double y1y2y2y3 = lerp(y1y2, y2y3, t);
            double y2y3y3y4 = lerp(y2y3, y3y4, t);

            double y = lerp(y1y2y2y3, y2y3y3y4, t);

            glVertex2d(x, y);
        }

        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}


int main(void)
{
    draw();
    return 0;
}