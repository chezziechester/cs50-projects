#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //getting average of the three color values and then assigning it to all colors values
            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            //switch pixel from one end to another
            RGBTRIPLE temp[1][1];
            temp[0][0] = image[i][width - j - 1];
            image[i][width - 1 - j] = image[i][j];
            image[i][j] = temp[0][0];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Make a copy of the image to refer to
    RGBTRIPLE copyImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copyImage[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avgRed, avgBlue, avgGreen;
            float count;
            avgRed = 0;
            avgBlue = 0;
            avgGreen = 0;
            count = 1.0; //includes the pixel itself
            //checks to make sure pixels aren't beyond image, hardcoding lmaoo
            if (i - 1 > -1)
            {
                avgRed += copyImage[i - 1][j].rgbtRed;
                avgBlue += copyImage[i - 1][j].rgbtBlue;
                avgGreen += copyImage[i - 1][j].rgbtGreen;
                count++;
            }
            if (i + 1 < height)
            {
                avgRed += copyImage[i + 1][j].rgbtRed;
                avgBlue += copyImage[i + 1][j].rgbtBlue;
                avgGreen += copyImage[i + 1][j].rgbtGreen;
                count++;
            }
            if ((i - 1 > -1) && (j - 1 > -1))
            {
                avgRed += copyImage[i - 1][j - 1].rgbtRed;
                avgBlue += copyImage[i - 1][j - 1].rgbtBlue;
                avgGreen += copyImage[i - 1][j - 1].rgbtGreen;
                count++;
            }
            if ((i - 1 > -1) && (j + 1 < width))
            {
                avgRed += copyImage[i - 1][j + 1].rgbtRed;
                avgBlue += copyImage[i - 1][j + 1].rgbtBlue;
                avgGreen += copyImage[i - 1][j + 1].rgbtGreen;
                count++;
            }
            if (j - 1 > -1)
            {
                avgRed += copyImage[i][j - 1].rgbtRed;
                avgBlue += copyImage[i][j - 1].rgbtBlue;
                avgGreen += copyImage[i][j - 1].rgbtGreen;
                count++;
            }
            if (j + 1 < width)
            {
                avgRed += copyImage[i][j + 1].rgbtRed;
                avgBlue += copyImage[i][j + 1].rgbtBlue;
                avgGreen += copyImage[i][j + 1].rgbtGreen;
                count++;
            }
            if ((i + 1 < height) && (j - 1 > -1))
            {
                avgRed += copyImage[i + 1][j - 1].rgbtRed;
                avgBlue += copyImage[i + 1][j - 1].rgbtBlue;
                avgGreen += copyImage[i + 1][j - 1].rgbtGreen;
                count++;
            }
            if ((i + 1 < height) && (j + 1 < width))
            {
                avgRed += copyImage[i + 1][j + 1].rgbtRed;
                avgBlue += copyImage[i + 1][j + 1].rgbtBlue;
                avgGreen += copyImage[i + 1][j + 1].rgbtGreen;
                count++;
            }
            //takes the average of all the channel values
            image[i][j].rgbtRed = round((avgRed + copyImage[i][j].rgbtRed) / count);
            image[i][j].rgbtBlue = round((avgBlue + copyImage[i][j].rgbtBlue) / count);
            image[i][j].rgbtGreen = round((avgGreen + copyImage[i][j].rgbtGreen) / count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //make a copy of the image to refer to
    RGBTRIPLE copyImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copyImage[i][j] = image[i][j];
        }
    }

    //hard coding once again ;-;, this time it's a bit easier because if it exceeds edge it's just 0
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redgx = 0;
            int bluegx = 0;
            int greengx = 0;
            int redgy = 0;
            int bluegy = 0;
            int greengy = 0;

            if (i - 1 > -1)
            {
                redgy += -2 * copyImage[i - 1][j].rgbtRed;
                bluegy += -2 * copyImage[i - 1][j].rgbtBlue;
                greengy += -2 * copyImage[i - 1][j].rgbtGreen;
            }
            if (i + 1 < height)
            {
                redgy += 2 * copyImage[i + 1][j].rgbtRed;
                bluegy += 2 * copyImage[i + 1][j].rgbtBlue;
                greengy += 2 * copyImage[i + 1][j].rgbtGreen;
            }
            if ((i - 1 > -1) && (j - 1 > -1))
            {
                redgx += -copyImage[i - 1][j - 1].rgbtRed;
                bluegx += -copyImage[i - 1][j - 1].rgbtBlue;
                greengx += -copyImage[i - 1][j - 1].rgbtGreen;

                redgy += -copyImage[i - 1][j - 1].rgbtRed;
                bluegy += -copyImage[i - 1][j - 1].rgbtBlue;
                greengy += -copyImage[i - 1][j - 1].rgbtGreen;
            }
            if ((i - 1 > -1) && (j + 1 < width))
            {
                redgx += copyImage[i - 1][j + 1].rgbtRed;
                bluegx += copyImage[i - 1][j + 1].rgbtBlue;
                greengx += copyImage[i - 1][j + 1].rgbtGreen;

                redgy += -copyImage[i - 1][j + 1].rgbtRed;
                bluegy += -copyImage[i - 1][j + 1].rgbtBlue;
                greengy += -copyImage[i - 1][j + 1].rgbtGreen;
            }
            if (j - 1 > -1)
            {
                redgx += -2 * copyImage[i][j - 1].rgbtRed;
                bluegx += -2 * copyImage[i][j - 1].rgbtBlue;
                greengx += -2 * copyImage[i][j - 1].rgbtGreen;
            }
            if (j + 1 < width)
            {
                redgx += 2 * copyImage[i][j + 1].rgbtRed;
                bluegx += 2 * copyImage[i][j + 1].rgbtBlue;
                greengx += 2 * copyImage[i][j + 1].rgbtGreen;
            }
            if ((i + 1 < height) && (j - 1 > -1))
            {
                redgx += -copyImage[i + 1][j - 1].rgbtRed;
                bluegx += -copyImage[i + 1][j - 1].rgbtBlue;
                greengx += -copyImage[i + 1][j - 1].rgbtGreen;

                redgy += copyImage[i + 1][j - 1].rgbtRed;
                bluegy += copyImage[i + 1][j - 1].rgbtBlue;
                greengy += copyImage[i + 1][j - 1].rgbtGreen;
            }
            if ((i + 1 < height) && (j + 1 < width))
            {
                redgx += copyImage[i + 1][j + 1].rgbtRed;
                bluegx += copyImage[i + 1][j + 1].rgbtBlue;
                greengx += copyImage[i + 1][j + 1].rgbtGreen;

                redgy += copyImage[i + 1][j + 1].rgbtRed;
                bluegy += copyImage[i + 1][j + 1].rgbtBlue;
                greengy += copyImage[i + 1][j + 1].rgbtGreen;
            }
            //Checks to see if the sqrt exceeds 255, otherwise cap at 255
            if (sqrt(redgy * redgy + redgx * redgx) > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = round(sqrt(redgy * redgy + redgx * redgx));
            }
            if (sqrt(bluegy * bluegy + bluegx * bluegx) > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = round(sqrt(bluegy * bluegy + bluegx * bluegx));
            }
            if (sqrt(greengy * greengy + greengx * greengx) > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = round(sqrt(greengy * greengy + greengx * greengx));
            }
        }
    }
    return;
}
