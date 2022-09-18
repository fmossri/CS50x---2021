#include <math.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //takes the average of colors of each pixel and set all color values to average
            int average = round(((float)image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3);
            image[h][w].rgbtBlue = average;
            image[h][w].rgbtGreen = average;
            image[h][w].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        //creates an array of pixels to store each row
        RGBTRIPLE holder_row[width];
        for (int w = 0; w < width; w++)
        {
            //stores each pixel of a row in the holder array
            holder_row[w] = image[h][w];
        }
        for (int k = 0; k < width; k++)
        {
            //rearranges the original row backwards
            image[h][k] = holder_row[(width - 1) - k];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Creates a two-dimensional array of pixels
    RGBTRIPLE holder[height][width];

    //for each row in a two-dimensional array (image)
    for (int h = 0; h < height; h++)
    {
        //for each pixel in a row
        for (int w = 0; w < width; w++)
        {
            //creates an int for the sum of each color and a counter for how many elements are being summed, sets all its values to 0;
            int red = 0;
            int green = 0;
            int blue = 0;
            int counter = 0;

            //for each neighboring row + actual row in a 3x3 grid
            for (int c = 0; c < 3; c++)
            {
                //for each pixel in the 3x3 grid of neighbors
                for (int r = 0; r < 3; r++)
                {
                    //discounts out-of-edges neighbors - checks for edges
                    if (h - 1 + c < 0 || h - 1 + c > height - 1 || w - 1 + r < 0 || w - 1 + r > width - 1)
                    {
                        continue;
                    }
                    else
                    {
                        //sums all valid pixel color values
                        red += image[h - 1 + c][w - 1 + r].rgbtRed;
                        green += image[h - 1 + c][w - 1 + r].rgbtGreen;
                        blue += image[h - 1 + c][w - 1 + r].rgbtBlue;
                        counter++;
                    }
                }
            }
            //attributes, in a holder array, color values by dividing its sum by the number of valid elements
            holder[h][w].rgbtRed = round((float) red / counter);
            holder[h][w].rgbtGreen = round((float)green / counter);
            holder[h][w].rgbtBlue = round((float)blue / counter);
        }
    }
    //copies the holder array into the original image, each pixel at a time
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
    //holder array
    RGBTRIPLE holder[height][width];

    //two-dimensional Sobel arrays
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int h = 0; h < height; h++)
    {
        //For each pixel in an image
        for (int w = 0; w < width; w++)
        {
            //sets and int for the sum of each neighboring pixel's color values multiplied by its Gx/Gy position
            int gxr = 0;
            int gxg = 0;
            int gxb = 0;
            int gyr = 0;
            int gyg = 0;
            int gyb = 0;

            //for each roll in a matrix of neighbors
            for (int c = 0; c < 3; c++)
            {
                for (int r = 0; r < 3; r++)
                {
                    //checks for out-of-edges pixels
                    if (h - 1 + c < 0 || h - 1 + c > height - 1 || w - 1 + r < 0 || w - 1 + r > width - 1)
                    {
                        continue;
                    }
                    else
                    {
                        //sums the neighboring color value multiplied by its sobel value in Gx and Gy
                        gxr += image[h - 1 + c][w - 1 + r].rgbtRed * Gx[c][r];
                        gxg += image[h - 1 + c][w - 1 + r].rgbtGreen * Gx[c][r];
                        gxb += image[h - 1 + c][w - 1 + r].rgbtBlue * Gx[c][r];

                        gyr += image[h - 1 + c][w - 1 + r].rgbtRed * Gy[c][r];
                        gyg += image[h - 1 + c][w - 1 + r].rgbtGreen * Gy[c][r];
                        gyb += image[h - 1 + c][w - 1 + r].rgbtBlue * Gy[c][r];
                    }
                }
            }

            //Sets the new color values into the holder array's pixels
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
                holder[h][w].rgbtGreen = round(sqrt(((float)gxg * gxg) + (gyg * gyg)));
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
        //Copies the holder array into the original image one pixel at a time
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = holder[i][j].rgbtRed;
            image[i][j].rgbtGreen = holder[i][j].rgbtGreen;
            image[i][j].rgbtBlue = holder[i][j].rgbtBlue;
        }
    }
    return;
}