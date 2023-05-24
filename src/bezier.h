#ifndef _BEZIER_H
#define _BEZIER_H

double lerp(double a, double b, double factor) { return a + (b - a) * factor; }

void bezier(uint8_t* buffer, int width, int height, int points[5][2]) {
    /* Clear buffer */
    for (int i = 0; i < width * height * 4; i += 4) {
        buffer[i + 0] = 245; /* R */
        buffer[i + 1] = 245; /* G */
        buffer[i + 2] = 245; /* B */
        buffer[i + 3] = 255; /* A */
    }

    /* Draw curve */
    for (double t = 0; t <= 1; t += 0.0001f) {
        double x1 = lerp(points[0][0], points[1][0], t);
        double x2 = lerp(points[1][0], points[2][0], t);
        double x3 = lerp(points[2][0], points[3][0], t);
        double x4 = lerp(points[3][0], points[4][0], t);

        double x1x2 = lerp(x1, x2, t);
        double x2x3 = lerp(x2, x3, t);
        double x3x4 = lerp(x3, x4, t);

        double x1x2x2x3 = lerp(x1x2, x2x3, t);
        double x2x3x3x4 = lerp(x2x3, x3x4, t);

        double x = lerp(x1x2x2x3, x2x3x3x4, t);

        double y1 = lerp(points[0][1], points[1][1], t);
        double y2 = lerp(points[1][1], points[2][1], t);
        double y3 = lerp(points[2][1], points[3][1], t);
        double y4 = lerp(points[3][1], points[4][1], t);

        double y1y2 = lerp(y1, y2, t);
        double y2y3 = lerp(y2, y3, t);
        double y3y4 = lerp(y3, y4, t);

        double y1y2y2y3 = lerp(y1y2, y2y3, t);
        double y2y3y3y4 = lerp(y2y3, y3y4, t);

        double y = lerp(y1y2y2y3, y2y3y3y4, t);

        int xpos = std::min((int)x, width);
        int ypos = std::min((int)y, height);

        int radius = 8;

        for (int i = ypos - radius; i < ypos + radius; i++) {
            for (int j = xpos - radius; j < xpos + radius; j++) {
                if (i < 0 || i >= height) continue;
                if (j < 0 || j >= width) continue;

                int pixel = (i * width + j) * 4;

                buffer[pixel + 0] = 157; /* R */
                buffer[pixel + 1] = 166; /* G */
                buffer[pixel + 2] = 93;  /* B */
                buffer[pixel + 3] = 255; /* A */
            }
        }
    }
}

#endif