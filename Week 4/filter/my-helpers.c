#include "helpers.h"
#include <math.h>
#include <stdio.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // for every collumn
    for (int y = 0; y < height; y++)
    {
        // for every row
        for (int x = 0; x < width; x++)
        {
            // find the pixel colour values
            BYTE r = image[y][x].rgbtRed;
            BYTE g = image[y][x].rgbtGreen;
            BYTE b = image[y][x].rgbtBlue;
            // round them up to find average
            BYTE convertedPixel = round((r + g + b) / 3.0);
            // and set each colour to the rounded average
            image[y][x].rgbtRed = convertedPixel;
            image[y][x].rgbtGreen = convertedPixel;
            image[y][x].rgbtBlue = convertedPixel;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // for every collumn
    for (int y = 0; y < height; y++)
    {
        // for every row
        for (int x = 0; x < width; x++)
        {
            // find the pixel colour values
            BYTE r = image[y][x].rgbtRed;
            BYTE g = image[y][x].rgbtGreen;
            BYTE b = image[y][x].rgbtBlue;
            // apply the sepia colour formula to each colour
            // fmin, to make sure no values loop
            BYTE sepiaRed = fmin(round(.393 * r + .769 * g + .189 * b), 255);
            BYTE sepiaGreen = fmin(round(.349 * r + .686 * g + .168 * b), 255);
            BYTE sepiaBlue = fmin(round(.272 * r + .534 * g + .131 * b), 255);
            // if  the number exceeds 255, we don't want it to loop and reprint the BYTE

            // apply the new value to the original pixels.
            image[y][x].rgbtRed = sepiaRed;
            image[y][x].rgbtGreen = sepiaGreen;
            image[y][x].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // for every collumn
    for (int y = 0; y < height; y++)
    {
        // for every row
        for (int x = 0; x < width / 2; x++)
        {
            // make a copy of original pixel
            RGBTRIPLE pixelcopy = image[y][x];
            // move the last pixel, to current position
            image[y][x] = image[y][width - x - 1];
            // printing the copy back to the last position
            image[y][width - x - 1] = pixelcopy;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of original picture, to collect data from
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Scan down the heigth of the picture
    for (int y = 0; y < height; y++)
    {
        // Scan the width of the picture
        for (int x = 0; x < width; x++)
        {
            // Reset/Prepare sumColor
            float sumRed = 0.0;
            float sumGreen = 0.0;
            float sumBlue = 0.0;
            // Reset counter for number of pixels to average
            float surroundingPixels = 0;

            // Loop over surrounding pixels, starting with top-left corner at
            // (current pixel x - 1 and current pixel y - 1)
            for (int box_y = -1; box_y < 2; box_y++)
            {
                for (int box_x = -1; box_x < 2; box_x++)
                {
                    // If box pixel is not with in bounds, move to next loop-iteration.
                    if (y + box_y < 0 || x + box_x < 0)
                    {
                        continue;
                    }

                    // If box pixel is out of bounds, break out of the inner loop.
                    // i.e (Go to next row)
                    if (y + box_y > height - 1 || x + box_x > width - 1)
                    {
                        break;
                    }

                    // sum all the colors of the pixels, and get ready to avg.
                    sumRed += copy[y + box_y][x + box_x].rgbtRed;
                    sumGreen += copy[y + box_y][x + box_x].rgbtGreen;
                    sumBlue += copy[y + box_y][x + box_x].rgbtBlue;

                    // Count surrounding pixels to divide.
                    surroundingPixels++;
                }
            }

            // Debug remnant - fun times.
            // printf("Valid pixels per pixed : %f \n", surroundingPixels);

            // Place blurred pixels in to image - rounding result of avg.
            image[y][x].rgbtRed = round(sumRed / surroundingPixels);
            image[y][x].rgbtGreen = round(sumGreen / surroundingPixels);
            image[y][x].rgbtBlue = round(sumBlue / surroundingPixels);
        }
    }
    return;
}