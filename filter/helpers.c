#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gray = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtRed = gray;
            image[i][j].rgbtBlue = gray;
            image[i][j].rgbtGreen = gray;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, k = width - 1; j < width; j++, k--)
        {
            temp[i][j].rgbtRed = image[i][k].rgbtRed;
            temp[i][j].rgbtGreen = image[i][k].rgbtGreen;
            temp[i][j].rgbtBlue = image[i][k].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue =  temp[i][j].rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = 0, green = 0, blue = 0;
            float count = 0;
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    if (i + x >= 0 && i + x < height && j + y >= 0 && j + y < width)
                    {
                        red += image[i + x][j + y].rgbtRed;
                        blue += image[i + x][j + y].rgbtBlue;
                        green += image[i + x][j + y].rgbtGreen;
                        count++;
                    }
                }
            }
            temp[i][j].rgbtRed = (int) round(red / count);
            temp[i][j].rgbtBlue = (int) round(blue / count);
            temp[i][j].rgbtGreen = (int) round(green / count);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redX = 0, greenX = 0, blueX = 0, redY = 0, greenY = 0, blueY = 0;
            float red, green, blue;
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    if (i + x >= 0 && i + x < height && j + y >= 0 && j + y < width)
                    {
                        redX += image[i + x][j + y].rgbtRed * Gx[x + 1][y + 1];
                        blueX += image[i + x][j + y].rgbtBlue * Gx[x + 1][y + 1];
                        greenX += image[i + x][j + y].rgbtGreen * Gx[x + 1][y + 1];
                        redY += image[i + x][j + y].rgbtRed * Gy[x + 1][y + 1];
                        blueY += image[i + x][j + y].rgbtBlue * Gy[x + 1][y + 1];
                        greenY += image[i + x][j + y].rgbtGreen * Gy[x + 1][y + 1];
                    }
                }
            }
            red = sqrt(pow(redX, 2) + pow(redY, 2));
            blue = sqrt(pow(blueX, 2) + pow(blueY, 2));
            green = sqrt(pow(greenX, 2) + pow(greenY, 2));

            if (red > 255)
            {
                red = 255;
            }

            if (blue > 255)
            {
                blue = 255;
            }

            if (green > 255)
            {
                green = 255;
            }

            temp[i][j].rgbtRed = (int) round(red);
            temp[i][j].rgbtBlue = (int) round(blue);
            temp[i][j].rgbtGreen = (int) round(green);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
        }
    }
    return;
}
