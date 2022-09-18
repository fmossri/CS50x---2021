#include <stdio.h>
#include <math.h>

int main(void)
{
    int n = round((float) sqrt(13));
    printf("%i", n);
}



// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int gxr = 0;
            int gxg = 0;
            int gxb = 0;
            int gyr = 0;
            int gyg = 0;
            int gyb = 0;

            int red;
            int green;
            int blue;
            for (int c = 0; c < 3; c++)
            {
                for (int r = 0; r < 3; r++)
                {
                    if (h - 1 + c < 0 || h - 1 + c > height - 1 || w - 1 + r < 0 || w - 1 + r > width - 1)
                    {
                        continue;
                    }
                    else
                    {
                        gxr += image[h - 1 + c][w - 1 + r].rgbtRed * Gx[c][r];
                        gxg += image[h - 1 + c][w - 1 + r].rgbtGreen * Gx[c][r];
                        gxb += image[h - 1 + c][w - 1 + r].rgbtBlue * Gx[c][r];

                        gyr += image[h - 1 + c][w - 1 + r].rgbtRed * Gy[c][r];
                        gyg += image[h - 1 + c][w - 1 + r].rgbtGreen * Gy[c][r];
                        gyb += image[h - 1 + c][w - 1 + r].rgbtBlue * Gy[c][r];
                    }
                }
            }
            red = round(sqrt(((float) gxr * gxr) + (gyr * gyr)));
            green = round(sqrt(((float) gxg * gxg) + (gyg * gyg)));
            blue = round(sqrt(((float) gxb * gxb) + (gyb * gyb)));

            if (red > 255)
                red = 255;
            if (green > 255)
                green = 255;
            if (blue > 255)
                blue = 255;

            image[h][w].rgbtRed = red;
            image[h][w].rgbtGreen = green;
            image[h][w].rgbtBlue = blue;
        }
    }
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE holder[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int red = 0;
            int green = 0;
            int blue = 0;
            int counter = 0;
            for (int c = 0; c < 3; c++)
            {
                for (int r = 0; r < 3; r++)
                {
                    if (h - 1 + c < 0 || h - 1 + c > height - 1 || w - 1 + r < 0 || w - 1 + r > width - 1)
                        continue;

                    else
                    {
                        red += image[h - 1 + c][w - 1 + r].rgbtRed;
                        green += image[h - 1 + c][w - 1 + r].rgbtGreen;
                        blue += image[h - 1 + c][w - 1 + r].rgbtBlue;
                        counter++;
                    }
                }
            }
            holder[h][w].rgbtRed = round((float) red / counter);
            holder[h][w].rgbtGreen = round((float)green / counter);
            holder[h][w].rgbtBlue = round((float)blue / counter);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = holder[i][j].rgbtRed;
            image[i][j].rgbtGreen = holder[i][j].rgbtGreen;
            image[i][j].rgbtBlue = holder[i][j].rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE holder[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            if (h == 0)
            {
                if (w == 0)
                {

                    int vpairb = image[h][w].rgbtBlue + image[h][w + 1].rgbtBlue;
                    int npairb = image[h + 1][w].rgbtBlue + image[h + 1][w + 1].rgbtBlue;
                    holder[h][w].rgbtBlue = round(((float)vpairb + npairb) / 4);

                    int vpairg = image[h][w].rgbtGreen + image[h][w + 1].rgbtGreen;
                    int npairg = image[h + 1][w].rgbtGreen + image[h + 1][w + 1].rgbtGreen;
                    holder[h][w].rgbtGreen = round(((float)vpairg + npairg) / 4);

                    int vpairr = image[h][w].rgbtRed + image[h][w + 1].rgbtRed;
                    int npairr = image[h + 1][w].rgbtRed + image[h + 1][w + 1].rgbtRed;
                    holder[h][w].rgbtRed = round(((float)vpairr + npairr) / 4);
                }

                else if (w == width - 1)
                {
                    int vpairb = image[h][w].rgbtBlue + image[h][w - 1].rgbtBlue;
                    int npairb = image[h + 1][w].rgbtBlue + image[h + 1][w - 1].rgbtBlue;
                    holder[h][w].rgbtBlue = round(((float)vpairb + npairb) / 4);

                    int vpairg = image[h][w].rgbtGreen + image[h][w - 1].rgbtGreen;
                    int npairg = image[h + 1][w].rgbtGreen + image[h + 1][w - 1].rgbtGreen;
                    holder[h][w].rgbtGreen = round(((float)vpairg + npairg) / 4);

                    int vpairr = image[h][w].rgbtRed + image[h][w - 1].rgbtRed;
                    int npairr = image[h + 1][w].rgbtRed + image[h + 1][w - 1].rgbtRed;
                    holder[h][w].rgbtRed = round(((float)vpairr + npairr) / 4);
                }

                else
                {
                    int first_rowb = image[h][w].rgbtBlue + image[h][w - 1].rgbtBlue + image[h][w + 1].rgbtBlue;
                    int next_rowb = image[h + 1][w].rgbtBlue + image[h + 1][w - 1].rgbtBlue + image[h + 1][w + 1].rgbtBlue;
                    holder[h][w].rgbtBlue = round(((float)first_rowb + next_rowb) / 6);

                    int first_rowg = image[h][w].rgbtGreen + image[h][w - 1].rgbtGreen + image[h][w + 1].rgbtGreen;
                    int next_rowg = image[h + 1][w].rgbtGreen + image[h + 1][w - 1].rgbtGreen + image[h + 1][w + 1].rgbtGreen;
                    holder[h][w].rgbtGreen = round(((float)first_rowg + next_rowg) / 6);

                    int first_rowr = image[h][w].rgbtRed + image[h][w - 1].rgbtRed + image[h][w + 1].rgbtRed;
                    int next_rowr = image[h + 1][w].rgbtRed + image[h + 1][w - 1].rgbtRed + image[h + 1][w + 1].rgbtRed;
                    holder[h][w].rgbtRed = round(((float)first_rowr + next_rowr) / 6);
                }
            }
            else if (h == height - 1)
            {
                if (w == 0)
                {
                    int vpairb = image[h][w].rgbtBlue + image[h][w + 1].rgbtBlue;
                    int npairb = image[h - 1][w].rgbtBlue + image[h - 1][w + 1].rgbtBlue;
                    holder[h][w].rgbtBlue = round(((float)vpairb + npairb) / 4);

                    int vpairg = image[h][w].rgbtGreen + image[h][w + 1].rgbtGreen;
                    int npairg = image[h - 1][w].rgbtGreen + image[h - 1][w + 1].rgbtGreen;
                    holder[h][w].rgbtGreen = round(((float)vpairg + npairg) / 4);

                    int vpairr = image[h][w].rgbtRed + image[h][w + 1].rgbtRed;
                    int npairr = image[h - 1][w].rgbtRed + image[h - 1][w + 1].rgbtRed;
                    holder[h][w].rgbtRed = round(((float)vpairr + npairr) / 4);
                }
                else if (w == width - 1)
                {
                    int vpairb = image[h][w].rgbtBlue + image[h][w - 1].rgbtBlue;
                    int npairb = image[h - 1][w].rgbtBlue + image[h - 1][w - 1].rgbtBlue;
                    holder[h][w].rgbtBlue = round(((float)vpairb + npairb) / 4);

                    int vpairg = image[h][w].rgbtGreen + image[h][w - 1].rgbtGreen;
                    int npairg = image[h - 1][w].rgbtGreen + image[h - 1][w - 1].rgbtGreen;
                    holder[h][w].rgbtGreen = round(((float)vpairg + npairg) / 4);

                    int vpairr = image[h][w].rgbtRed + image[h][w - 1].rgbtRed;
                    int npairr = image[h - 1][w].rgbtRed + image[h - 1][w - 1].rgbtRed;
                    holder[h][w].rgbtRed = round(((float)vpairr + npairr) / 4);
                }
                else
                {
                    int last_rowb = image[h][w].rgbtBlue + image[h][w - 1].rgbtBlue + image[h][w + 1].rgbtBlue;
                    int ant_rowb = image[h - 1][w].rgbtBlue + image[h - 1][w - 1].rgbtBlue + image[h - 1][w + 1].rgbtBlue;
                    holder[h][w].rgbtBlue = round(((float)last_rowb + ant_rowb) / 6);

                    int last_rowg = image[h][w].rgbtGreen + image[h][w - 1].rgbtGreen + image[h][w + 1].rgbtGreen;
                    int ant_rowg = image[h - 1][w].rgbtGreen + image[h - 1][w - 1].rgbtGreen + image[h - 1][w + 1].rgbtGreen;
                    holder[h][w].rgbtGreen = round(((float)last_rowg + ant_rowg) / 6);

                    int last_rowr = image[h][w].rgbtRed + image[h][w - 1].rgbtRed + image[h][w + 1].rgbtRed;
                    int ant_rowr = image[h - 1][w].rgbtRed + image[h - 1][w - 1].rgbtRed + image[h - 1][w + 1].rgbtRed;
                    holder[h][w].rgbtRed = round(((float)last_rowr + ant_rowr) / 6);
                }
            }
            else
            {
                if (w == 0)
                {
                    int first_columnb = image[h][w].rgbtBlue + image[h + 1][w].rgbtBlue + image[h - 1][w].rgbtBlue;
                    int next_columnb = image[h][w + 1].rgbtBlue + image[h + 1][w + 1].rgbtBlue + image[h - 1][w + 1].rgbtBlue;
                    holder[h][w].rgbtBlue = round(((float)first_columnb + next_columnb) / 6);

                    int first_columng = image[h][w].rgbtGreen + image[h + 1][w].rgbtGreen + image[h - 1][w].rgbtGreen;
                    int next_columng = image[h][w + 1].rgbtGreen + image[h + 1][w + 1].rgbtGreen + image[h - 1][w + 1].rgbtGreen;
                    holder[h][w].rgbtGreen = round(((float)first_columng + next_columng) / 6);

                    int first_columnr = image[h][w].rgbtRed + image[h + 1][w].rgbtRed + image[h - 1][w].rgbtRed;
                    int next_columnr = image[h][w + 1].rgbtRed + image[h + 1][w + 1].rgbtRed + image[h - 1][w + 1].rgbtRed;
                    holder[h][w].rgbtRed = round(((float)first_columnr + next_columnr) / 6);
                }
                else if (w == width - 1)
                {
                    int last_columnb = image[h][w].rgbtBlue + image[h + 1][w].rgbtBlue + image[h - 1][w].rgbtBlue;
                    int ant_columnb = image[h][w - 1].rgbtBlue + image[h + 1][w - 1].rgbtBlue + image[h - 1][w - 1].rgbtBlue;
                    holder[h][w].rgbtBlue = round(((float)last_columnb + ant_columnb) / 6);

                    int last_columng = image[h][w].rgbtGreen + image[h + 1][w].rgbtGreen + image[h - 1][w].rgbtGreen;
                    int ant_columng = image[h][w - 1].rgbtGreen + image[h + 1][w - 1].rgbtGreen + image[h - 1][w - 1].rgbtGreen;
                    holder[h][w].rgbtGreen = round(((float)last_columng + ant_columng) / 6);

                    int last_columnr = image[h][w].rgbtRed + image[h + 1][w].rgbtRed + image[h - 1][w].rgbtRed;
                    int ant_columnr = image[h][w - 1].rgbtRed + image[h + 1][w - 1].rgbtRed + image[h - 1][w - 1].rgbtRed;
                    holder[h][w].rgbtRed = round(((float)last_columnr + ant_columnr) / 6);
                }
                else
                {
                    int main_columnb = image[h][w].rgbtBlue + image[h + 1][w].rgbtBlue + image[h - 1][w].rgbtBlue;
                    int next_columnb = image[h][w + 1].rgbtBlue + image[h + 1][w + 1].rgbtBlue + image[h - 1][w + 1].rgbtBlue;
                    int ant_columnb = image[h][w - 1].rgbtBlue + image[h + 1][w - 1].rgbtBlue + image[h - 1][w - 1].rgbtBlue;
                    holder[h][w].rgbtBlue = round(((float)main_columnb + next_columnb + ant_columnb) / 9);

                    int main_columng = image[h][w].rgbtGreen + image[h + 1][w].rgbtGreen + image[h - 1][w].rgbtGreen;
                    int next_columng = image[h][w + 1].rgbtGreen + image[h + 1][w + 1].rgbtGreen + image[h - 1][w + 1].rgbtGreen;
                    int ant_columng = image[h][w - 1].rgbtGreen + image[h + 1][w - 1].rgbtGreen + image[h - 1][w - 1].rgbtGreen;
                    holder[h][w].rgbtGreen = round(((float)main_columng + next_columng + ant_columng) / 9);

                    int main_columnr = image[h][w].rgbtRed + image[h + 1][w].rgbtRed + image[h - 1][w].rgbtRed;
                    int next_columnr = image[h][w + 1].rgbtRed + image[h + 1][w + 1].rgbtRed + image[h - 1][w + 1].rgbtRed;
                    int ant_columnr = image[h][w - 1].rgbtRed + image[h + 1][w - 1].rgbtRed + image[h - 1][w - 1].rgbtRed;
                    holder[h][w].rgbtRed = round(((float)main_columnr + next_columnr + ant_columnr) / 9);
                }
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = holder[i][j].rgbtRed;
            image[i][j].rgbtGreen = holder[i][j].rgbtGreen;
            image[i][j].rgbtBlue = holder[i][j].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE holder[height][width];
    int gxr;
    int gxg;
    int gxb;
    int gyr;
    int gyg;
    int gyb;

    int red;
    int green;
    int blue;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            if (h == 0)
            {
                if (w == 0)
                {
                    gxr = (2 * image[h][w + 1].rgbtRed) + image[h + 1][w + 1].rgbtRed;
                    gxg = (2 * image[h][w + 1].rgbtGreen) + image[h + 1][w + 1].rgbtGreen;
                    gxb = (2 * image[h][w + 1].rgbtBlue) + image[h + 1][w + 1].rgbtBlue;

                    gyr = (2 * image[h + 1][w].rgbtRed) + image[h + 1][w + 1].rgbtRed;
                    gyg = (2 * image[h + 1][w].rgbtGreen) + image[h + 1][w + 1].rgbtGreen;
                    gyb = (2 * image[h + 1][w].rgbtBlue) + image[h + 1][w + 1].rgbtBlue;
                }
                else if (w == width)
                {
                    gxr = (-2 * image[h][w - 1].rgbtRed) + (-1 * image[h + 1][w - 1].rgbtRed);
                    gxg = (-2 * image[h][w - 1].rgbtGreen) + (-1 * image[h + 1][w - 1].rgbtGreen);
                    gxb = (-2 * image[h][w - 1].rgbtBlue) + (-1 * image[h + 1][w - 1].rgbtBlue);

                    gyr = image[h + 1][w - 1].rgbtRed + (2 * image[h + 1][w].rgbtRed);
                    gyg = image[h + 1][w - 1].rgbtGreen + (2 * image[h + 1][w].rgbtGreen);
                    gyb = image[h + 1][w - 1].rgbtBlue + (2 * image[h + 1][w].rgbtBlue);
                }
                else
                {
                    gxr = (-2 * image[h][w - 1].rgbtRed) + (2 * image[h][w + 1].rgbtRed) + (-1 * image[h + 1][w - 1].rgbtRed) + image[h + 1][w + 1].rgbtRed;
                    gxg = (-2 * image[h][w - 1].rgbtGreen) + (2 * image[h][w + 1].rgbtGreen) + (-1 * image[h + 1][w - 1].rgbtGreen) + image[h + 1][w + 1].rgbtGreen;
                    gxb = (-2 * image[h][w - 1].rgbtBlue) + (2 * image[h][w + 1].rgbtBlue) + (-1 * image[h + 1][w - 1].rgbtBlue) + image[h + 1][w + 1].rgbtBlue;

                    gyr = image[h + 1][w - 1].rgbtRed + (2 * image[h + 1][w].rgbtRed) + image[h + 1][w + 1].rgbtRed;
                    gyg = image[h + 1][w - 1].rgbtGreen + (2 * image[h + 1][w].rgbtGreen) + image[h + 1][w + 1].rgbtGreen;
                    gyb = image[h + 1][w - 1].rgbtBlue + (2 * image[h + 1][w].rgbtBlue) + image[h + 1][w + 1].rgbtBlue;
                }
            }
            else if (h == height)
            {
                if (w == 0)
                {
                    gxr = image[h - 1][w + 1].rgbtRed + (2 * image[h][w + 1].rgbtRed);
                    gxg = image[h - 1][w + 1].rgbtGreen + (2 * image[h][w + 1].rgbtGreen);
                    gxb = image[h - 1][w + 1].rgbtBlue + (2 * image[h][w + 1].rgbtBlue);

                    gyr = (-2 * image[h - 1][w].rgbtRed) + (-1 * image[h - 1][w + 1].rgbtRed);
                    gyg = (-2 * image[h - 1][w].rgbtGreen) + (-1 * image[h - 1][w + 1].rgbtGreen);
                    gyb = (-2 * image[h - 1][w].rgbtBlue) + (-1 * image[h - 1][w + 1].rgbtBlue);
                }
                else if (w == width)
                {
                    gxr = (-1 * image[h - 1][w - 1].rgbtRed) + (-2 * image[h][w - 1].rgbtRed);
                    gxg = (-1 * image[h - 1][w - 1].rgbtGreen) + (-2 * image[h][w - 1].rgbtGreen);
                    gxb = (-1 * image[h - 1][w - 1].rgbtRed) + (-2 * image[h][w - 1].rgbtRed);

                    gyr = (-1 * image[h - 1][w - 1].rgbtRed) + (-2 * image[h - 1][w].rgbtRed);
                    gyg = (-1 * image[h - 1][w - 1].rgbtGreen) + (-2 * image[h - 1][w].rgbtGreen);
                    gyb = (-1 * image[h - 1][w - 1].rgbtBlue) + (-2 * image[h - 1][w].rgbtBlue);
                }
                else
                {
                    gxr = (-1 * image[h - 1][w - 1].rgbtRed) + (-2 * image[h][w - 1].rgbtRed) + image[h - 1][w + 1].rgbtRed + (2 * image[h][w + 1].rgbtRed);
                    gxg = (-1 * image[h - 1][w - 1].rgbtGreen) + (-2 * image[h][w - 1].rgbtGreen) + image[h - 1][w + 1].rgbtGreen + (2 * image[h][w + 1].rgbtGreen);
                    gxb = (-1 * image[h - 1][w - 1].rgbtBlue) + (-2 * image[h][w - 1].rgbtBlue) + image[h - 1][w + 1].rgbtBlue + (2 * image[h][w + 1].rgbtBlue);

                    gyr = (-1 * image[h - 1][w - 1].rgbtRed) + (-2 * image[h - 1][w].rgbtRed) + (-1 * image[h -1][w + 1].rgbtRed);
                    gyg = (-1 * image[h - 1][w - 1].rgbtGreen) + (-2 * image[h - 1][w].rgbtGreen) + (-1 * image[h -1][w + 1].rgbtGreen);
                    gyb = (-1 * image[h - 1][w - 1].rgbtBlue) + (-2 * image[h - 1][w].rgbtBlue) + (-1 * image[h -1][w + 1].rgbtBlue);
                }
            }
            else
            {
                if (w == 0)
                {
                    gxr = image[h - 1][w + 1].rgbtRed + (2* image[h][w + 1].rgbtRed) + image[h + 1][w + 1].rgbtRed;
                    gxg = image[h - 1][w + 1].rgbtGreen + (2* image[h][w + 1].rgbtGreen) + image[h + 1][w + 1].rgbtGreen;
                    gxb = image[h - 1][w + 1].rgbtBlue + (2* image[h][w + 1].rgbtBlue) + image[h + 1][w + 1].rgbtBlue;

                    gyr = (-2 * image[h - 1][w].rgbtRed) + (-1 * image[h - 1][w + 1].rgbtRed) + (2 * image[h + 1][w].rgbtRed) + image[h + 1][w + 1].rgbtRed;
                    gyg = (-2 * image[h - 1][w].rgbtGreen) + (-1 * image[h - 1][w + 1].rgbtGreen) + (2 * image[h + 1][w].rgbtGreen) + image[h + 1][w + 1].rgbtGreen;
                    gyb = (-2 * image[h - 1][w].rgbtBlue) + (-1 * image[h - 1][w + 1].rgbtBlue) + (2 * image[h + 1][w].rgbtBlue) + image[h + 1][w + 1].rgbtBlue;
                }
                else if (w == width)
                {
                    gxr = (-1 * image[h - 1][w - 1].rgbtRed) + (-2* image[h][w - 1].rgbtRed) + (-1 * image[h + 1][w - 1].rgbtRed);
                    gxg = (-1 * image[h - 1][w - 1].rgbtGreen) + (-2* image[h][w - 1].rgbtGreen) + (-1 * image[h + 1][w - 1].rgbtGreen);
                    gxb = (-1 * image[h - 1][w - 1].rgbtBlue) + (-2* image[h][w - 1].rgbtBlue) + (-1 * image[h + 1][w - 1].rgbtBlue);

                    gyr = (-2 * image[h - 1][w].rgbtRed) + (-1 * image[h - 1][w - 1].rgbtRed) + (2 * image[h + 1][w].rgbtRed) + image[h + 1][w - 1].rgbtRed;
                    gyg = (-2 * image[h - 1][w].rgbtGreen) + (-1 * image[h - 1][w - 1].rgbtGreen) + (2 * image[h + 1][w].rgbtGreen) + image[h + 1][w - 1].rgbtGreen;
                    gyb = (-2 * image[h - 1][w].rgbtBlue) + (-1 * image[h - 1][w - 1].rgbtBlue) + (2 * image[h + 1][w].rgbtBlue) + image[h + 1][w - 1].rgbtBlue;
                }
                else
                {
                    gxr = image[h - 1][w + 1].rgbtRed + (2* image[h][w + 1].rgbtRed) + image[h + 1][w + 1].rgbtRed + (-1 * image[h - 1][w - 1].rgbtRed) + (-2* image[h][w - 1].rgbtRed) + (-1 * image[h + 1][w - 1].rgbtRed);
                    gxg = image[h - 1][w + 1].rgbtGreen + (2* image[h][w + 1].rgbtGreen) + image[h + 1][w + 1].rgbtGreen + (-1 * image[h - 1][w - 1].rgbtGreen) + (-2* image[h][w - 1].rgbtGreen) + (-1 * image[h + 1][w - 1].rgbtGreen);
                    gxb = image[h - 1][w + 1].rgbtBlue + (2* image[h][w + 1].rgbtBlue) + image[h + 1][w + 1].rgbtBlue + (-1 * image[h - 1][w - 1].rgbtBlue) + (-2* image[h][w - 1].rgbtBlue) + (-1 * image[h + 1][w - 1].rgbtBlue);

                    gyr = image[h + 1][w - 1].rgbtRed + (2 * image[h + 1][w].rgbtRed) + image[h + 1][w + 1].rgbtRed + (-1 * image[h - 1][w - 1].rgbtRed) + (-2 * image[h - 1][w].rgbtRed) + (-1 * image[h -1][w + 1].rgbtRed);
                    gyg = image[h + 1][w - 1].rgbtGreen + (2 * image[h + 1][w].rgbtGreen) + image[h + 1][w + 1].rgbtGreen + (-1 * image[h - 1][w - 1].rgbtGreen) + (-2 * image[h - 1][w].rgbtGreen) + (-1 * image[h -1][w + 1].rgbtGreen);
                    gyb = image[h + 1][w - 1].rgbtBlue + (2 * image[h + 1][w].rgbtBlue) + image[h + 1][w + 1].rgbtBlue + (-1 * image[h - 1][w - 1].rgbtBlue) + (-2 * image[h - 1][w].rgbtBlue) + (-1 * image[h -1][w + 1].rgbtBlue);
                }
            }
            if (sqrt(((float)gxr * gxr) + (gyr * gyr)) > 255)
            {
                holder[h][w].rgbtRed = 255;
            }
            else
            {
                holder[h][w].rgbtRed = round(sqrt(((float)gxr * gxr) + (gyr * gyr)));
            }
            if (sqrt(((float)gxg * gxg) + (gyg * gyg)) > 255)
            {
                holder[h][w].rgbtGreen = 255;
            }
            else
            {
                holder[h][w].rgbtGreen = round(sqrt(((float)gxg * gxg) + (gyg *gyg)));
            }
            if (sqrt(((float)gxb * gxb) + (gyb * gyb)) > 255)
            {
                holder[h][w].rgbtBlue = 255;
            }
            else
            {
                holder[h][w].rgbtBlue = round(sqrt(((float)gxb * gxb) + (gyb * gyb)));
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = holder[i][j].rgbtRed;
            image[i][j].rgbtGreen = holder[i][j].rgbtGreen;
            image[i][j].rgbtBlue = holder[i][j].rgbtBlue;
        }
    }
    return;
}