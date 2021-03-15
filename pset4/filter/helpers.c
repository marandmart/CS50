#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //Loops through every line
    for (int i = 0; i < height; i++)
    {
        //Loops through every columm of every line
        for (int j = 0; j < width; j++)
        {
            //Gets the individual RGB values of each pixel
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;
            //Averages them out
            int average = round((red + green + blue)/3.0);
            //Re-assigns them back to their correspoding pixel
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy;
    //Image with an even ammount of height and width
    if (height % 2 == 0 || width % 2 == 0)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width/2; j++)
            {
                copy.rgbtRed = image[i][j].rgbtRed; copy.rgbtGreen = image[i][j].rgbtGreen; copy.rgbtBlue = image[i][j].rgbtBlue;
                image[i][j] = image[i][width - 1 - j];
                image[i][width - 1 - j] = copy;
            }
        }
    }
    //Image with a non even resolution
    else
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width/2 + 1; j++)
            {
                copy.rgbtRed = image[i][j].rgbtRed; copy.rgbtGreen = image[i][j].rgbtGreen; copy.rgbtBlue = image[i][j].rgbtBlue;
                image[i][j] = image[i][width - 1 - j];
                image[i][width - 1 - j] = copy;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    //Creates a copy of the original image value for reference
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }
    //img heigth: 400, width: 600
    int avgRed, avgGreen, avgBlue = 0;
    //Makes the calculations and returns the correct value to each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //First line and first column
            if (i == 0 && j == 0)
            {
                //Averages of each of the color values
                avgRed = round((copy[i][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j + 1].rgbtRed)/4.0);
                avgGreen = round((copy[i][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen)/4.0);
                avgBlue = round((copy[i][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue)/4.0);
                //Assings the averages to the corresponding pixel
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
            //First line and last column
            else if (i == 0 && j == width - 1)
            {
                //Averages of each of the color values
                avgRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed)/4.0);
                avgGreen = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen)/4.0);
                avgBlue = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue)/4.0);
                //Assings the averages to the corresponding pixel
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
            //Everything in between first line/first column and first line/last column
            else if (i == 0 && j != 0 && j != width - 1)
            {
                //Averages of each of the color values
                avgRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed)/6.0);
                avgGreen = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen)/6.0);
                avgBlue = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue)/6.0);
                //Assings the averages to the corresponding pixel
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
            //Last line and first column
            else if (i == height - 1 && j == 0)
            {
                //Averages of each of the color values
                avgRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed)/4.0);
                avgGreen = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen)/4.0);
                avgBlue = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue)/4.0);
                //Assings the averages to the corresponding pixel
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
            //Last line and last column
            else if (i == height - 1 && j == width - 1)
            {
                //Averages of each of the color values
                avgRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed)/4.0);
                avgGreen = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen)/4.0);
                avgBlue = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue)/4.0);
                //Assings the averages to the corresponding pixel
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
            //Everything in between last line/first column and last line/last column
            else if (i == height - 1 && j != 0 && j != width - 1)
            {
                //Averages of each of the color values
                avgRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j + 1].rgbtRed)/6.0);
                avgGreen = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen)/6.0);
                avgBlue = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue)/6.0);
                //Assings the averages to the corresponding pixel
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
            //When the values are at the left border
            else if (j == 0 && i != 0 && i != height - 1)
            {
                //Averages of each of the color values
                avgRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed)/6.0);
                avgGreen = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen)/6.0);
                avgBlue = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue)/6.0);
                //Assings the averages to the corresponding pixel
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
            //When the values are at the right border
            else if (j == width - 1 && i != 0 && i != height - 1)
            {
                //Averages of each of the color values
                avgRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed)/6.0);
                avgGreen = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen)/6.0);
                avgBlue = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue)/6.0);
                //Assings the averages to the corresponding pixel
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
            //Values not at any border or edge
            else if (i != 0 && i != height - 1 && j != 0 && j != width - 1)
            {
                //Averages of each of the color values
                avgRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j + 1].rgbtRed)/9.0);
                avgGreen = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen)/9.0);
                avgBlue = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue)/9.0);
                //Assings the averages to the corresponding pixel
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    //Creates a copy of the original image value for reference
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }
    //Sobel operator in x direction
    int gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    //Sobel operator in y direction
    int gy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };
    int valueX, valueY, valueCalc = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //First line and first column
            if (i == 0 && j == 0)
            {
                //Results for the red values
                valueX = copy[i][j].rgbtRed*gx[1][1] + copy[i + 1][j].rgbtRed*gx[2][1] + copy[i][j + 1].rgbtRed*gx[1][2] + copy[i + 1][j + 1].rgbtRed*gx[2][2];
                valueY = copy[i][j].rgbtRed*gy[1][1] + copy[i + 1][j].rgbtRed*gy[2][1] + copy[i][j + 1].rgbtRed*gy[1][2] + copy[i + 1][j + 1].rgbtRed*gy[2][2];
                valueCalc = round(sqrt(valueX*valueX + valueY*valueY));
                //Checks if the calculated value is over 255
                if (valueCalc > 255)
                    image[i][j].rgbtRed = 255;
                else
                    image[i][j].rgbtRed = valueCalc;
                //Results for the green values
                valueX = copy[i][j].rgbtGreen*gx[1][1] + copy[i + 1][j].rgbtGreen*gx[2][1] + copy[i][j + 1].rgbtGreen*gx[1][2] + copy[i + 1][j + 1].rgbtGreen*gx[2][2];
                valueY = copy[i][j].rgbtGreen*gy[1][1] + copy[i + 1][j].rgbtGreen*gy[2][1] + copy[i][j + 1].rgbtGreen*gy[1][2] + copy[i + 1][j + 1].rgbtGreen*gy[2][2];
                valueCalc = round(sqrt(valueX*valueX + valueY*valueY));
                //Checks if the calculated value is over 255
                if (valueCalc > 255)
                    image[i][j].rgbtGreen = 255;
                else
                    image[i][j].rgbtGreen = valueCalc;
                //Results for the blue values
                valueX = copy[i][j].rgbtBlue*gx[1][1] + copy[i + 1][j].rgbtBlue*gx[2][1] + copy[i][j + 1].rgbtBlue*gx[1][2] + copy[i + 1][j + 1].rgbtBlue*gx[2][2];
                valueY = copy[i][j].rgbtBlue*gy[1][1] + copy[i + 1][j].rgbtBlue*gy[2][1] + copy[i][j + 1].rgbtBlue*gy[1][2] + copy[i + 1][j + 1].rgbtBlue*gy[2][2];
                valueCalc = round(sqrt(valueX*valueX + valueY*valueY));
                //Checks if the calculated value is over 255
                if (valueCalc > 255)
                    image[i][j].rgbtBlue = 255;
                else
                    image[i][j].rgbtBlue = valueCalc;
            }
            //First line and last column
            else if (i == 0 && j == width - 1)
            {
                //Results for the red values
                valueX = copy[i][j].rgbtRed*gx[1][1] + copy[i][j - 1].rgbtRed*gx[1][0] + copy[i + 1][j].rgbtRed*gx[2][1] + copy[i + 1][j - 1].rgbtRed*gx[2][0];
                valueY = copy[i][j].rgbtRed*gy[1][1] + copy[i][j - 1].rgbtRed*gy[1][0] + copy[i + 1][j].rgbtRed*gy[2][1] + copy[i + 1][j - 1].rgbtRed*gy[2][0];
                valueCalc = round(sqrt(valueX*valueX + valueY*valueY));
                //Checks if the calculated value is over 255
                if (valueCalc > 255)
                    image[i][j].rgbtRed = 255;
                else
                    image[i][j].rgbtRed = valueCalc;
                //Results for the green values
                valueX = copy[i][j].rgbtGreen*gx[1][1] + copy[i][j - 1].rgbtGreen*gx[1][0] + copy[i + 1][j].rgbtGreen*gx[2][1] + copy[i + 1][j - 1].rgbtGreen*gx[2][0];
                valueY = copy[i][j].rgbtGreen*gy[1][1] + copy[i][j - 1].rgbtGreen*gy[1][0] + copy[i + 1][j].rgbtGreen*gy[2][1] + copy[i + 1][j - 1].rgbtGreen*gy[2][0];
                valueCalc = round(sqrt(valueX*valueX + valueY*valueY));
                //Checks if the calculated value is over 255
                if (valueCalc > 255)
                    image[i][j].rgbtGreen = 255;
                else
                    image[i][j].rgbtGreen = valueCalc;
                //Results for the blue values
                valueX = copy[i][j].rgbtBlue*gx[1][1] + copy[i][j - 1].rgbtBlue*gx[1][0] + copy[i + 1][j].rgbtBlue*gx[2][1] + copy[i + 1][j - 1].rgbtBlue*gx[2][0];
                valueY = copy[i][j].rgbtBlue*gy[1][1] + copy[i][j - 1].rgbtBlue*gy[1][0] + copy[i + 1][j].rgbtBlue*gy[2][1] + copy[i + 1][j - 1].rgbtBlue*gy[2][0];
                valueCalc = round(sqrt(valueX*valueX + valueY*valueY));
                //Checks if the calculated value is over 255
                if (valueCalc > 255)
                    image[i][j].rgbtBlue = 255;
                else
                    image[i][j].rgbtBlue = valueCalc;
            }
            //Everything in between first line/first column and first line/last column
            else if (i == 0 && j != 0 && j != width - 1)
            {
                //Results for the red values
                valueX = copy[i][j].rgbtRed*gx[1][1] + copy[i][j + 1].rgbtRed*gx[1][2] + copy[i][j - 1].rgbtRed*gx[1][0] + copy[i + 1][j].rgbtRed*gx[2][1] + copy[i + 1][j + 1].rgbtRed*gx[2][2] + copy[i + 1][j - 1].rgbtRed*gx[2][0];
                valueY = copy[i][j].rgbtRed*gy[1][1] + copy[i][j + 1].rgbtRed*gy[1][2] + copy[i][j - 1].rgbtRed*gy[1][0] + copy[i + 1][j].rgbtRed*gy[2][1] + copy[i + 1][j + 1].rgbtRed*gy[2][2] + copy[i + 1][j - 1].rgbtRed*gy[2][0];
                valueCalc = round(sqrt(valueX*valueX + valueY*valueY));
                //Checks if the calculated value is over 255
                if (valueCalc > 255)
                    image[i][j].rgbtRed = 255;
                else
                    image[i][j].rgbtRed = valueCalc;
                //Results for the green values
                valueX = copy[i][j].rgbtGreen*gx[1][1] + copy[i][j + 1].rgbtGreen*gx[1][2] + copy[i][j - 1].rgbtGreen*gx[1][0] + copy[i + 1][j].rgbtGreen*gx[2][1] + copy[i + 1][j + 1].rgbtGreen*gx[2][2] + copy[i + 1][j - 1].rgbtGreen*gx[2][0];
                valueY = copy[i][j].rgbtGreen*gy[1][1] + copy[i][j + 1].rgbtGreen*gy[1][2] + copy[i][j - 1].rgbtGreen*gy[1][0] + copy[i + 1][j].rgbtGreen*gy[2][1] + copy[i + 1][j + 1].rgbtGreen*gy[2][2] + copy[i + 1][j - 1].rgbtGreen*gy[2][0];
                valueCalc = round(sqrt(valueX*valueX + valueY*valueY));
                //Checks if the calculated value is over 255
                if (valueCalc > 255)
                    image[i][j].rgbtGreen = 255;
                else
                    image[i][j].rgbtGreen = valueCalc;
                //Results for the blue values
                valueX = copy[i][j].rgbtBlue*gx[1][1] + copy[i][j + 1].rgbtBlue*gx[1][2] + copy[i][j - 1].rgbtBlue*gx[1][0] + copy[i + 1][j].rgbtBlue*gx[2][1] + copy[i + 1][j + 1].rgbtBlue*gx[2][2] + copy[i + 1][j - 1].rgbtBlue*gx[2][0];
                valueY = copy[i][j].rgbtBlue*gy[1][1] + copy[i][j + 1].rgbtBlue*gy[1][2] + copy[i][j - 1].rgbtBlue*gy[1][0] + copy[i + 1][j].rgbtBlue*gy[2][1] + copy[i + 1][j + 1].rgbtBlue*gy[2][2] + copy[i + 1][j - 1].rgbtBlue*gy[2][0];
                valueCalc = round(sqrt(valueX*valueX + valueY*valueY));
                //Checks if the calculated value is over 255
                if (valueCalc > 255)
                    image[i][j].rgbtBlue = 255;
                else
                    image[i][j].rgbtBlue = valueCalc;
            }
            //Last line and first column
            else if (i == height - 1 && j == 0)
            {
                //Results for the red values
                valueX = copy[i][j].rgbtRed*gx[1][1] + copy[i][j + 1].rgbtRed*gx[1][2] + copy[i - 1][j].rgbtRed*gx[0][1] + copy[i - 1][j + 1].rgbtRed*gx[0][2];
                valueY = copy[i][j].rgbtRed*gy[1][1] + copy[i][j + 1].rgbtRed*gy[1][2] + copy[i - 1][j].rgbtRed*gy[0][1] + copy[i - 1][j + 1].rgbtRed*gy[0][2];
                valueCalc = round(sqrt(valueX*valueX + valueY*valueY));
                //Checks if the calculated value is over 255
                if (valueCalc > 255)
                    image[i][j].rgbtRed = 255;
                else
                    image[i][j].rgbtRed = valueCalc;
                //Results for the green values
                valueX = copy[i][j].rgbtGreen*gx[1][1] + copy[i][j + 1].rgbtGreen*gx[1][2] + copy[i - 1][j].rgbtGreen*gx[0][1] + copy[i - 1][j + 1].rgbtGreen*gx[0][2];
                valueY = copy[i][j].rgbtGreen*gy[1][1] + copy[i][j + 1].rgbtGreen*gy[1][2] + copy[i - 1][j].rgbtGreen*gy[0][1] + copy[i - 1][j + 1].rgbtGreen*gy[0][2];
                valueCalc = round(sqrt(valueX*valueX + valueY*valueY));
                //Checks if the calculated value is over 255
                if (valueCalc > 255)
                    image[i][j].rgbtGreen = 255;
                else
                    image[i][j].rgbtGreen = valueCalc;
                //Results for the blue values
                valueX = copy[i][j].rgbtBlue*gx[1][1] + copy[i][j + 1].rgbtBlue*gx[1][2] + copy[i - 1][j].rgbtBlue*gx[0][1] + copy[i - 1][j + 1].rgbtBlue*gx[0][2];
                valueY = copy[i][j].rgbtBlue*gy[1][1] + copy[i][j + 1].rgbtBlue*gy[1][2] + copy[i - 1][j].rgbtBlue*gy[0][1] + copy[i - 1][j + 1].rgbtBlue*gy[0][2];
                valueCalc = round(sqrt(valueX*valueX + valueY*valueY));
                //Checks if the calculated value is over 255
                if (valueCalc > 255)
                    image[i][j].rgbtBlue = 255;
                else
                    image[i][j].rgbtBlue = valueCalc;
            }
            //Last line and last column
            else if (i == height - 1 && j == width - 1)
            {
                //Results for the red values
                valueX = copy[i][j].rgbtRed*gx[1][1] + copy[i][j - 1].rgbtRed*gx[1][0] + copy[i - 1][j].rgbtRed*gx[0][1] + copy[i - 1][j - 1].rgbtRed*gx[0][0];
                valueY = copy[i][j].rgbtRed*gy[1][1] + copy[i][j - 1].rgbtRed*gy[1][0] + copy[i - 1][j].rgbtRed*gy[0][1] + copy[i - 1][j - 1].rgbtRed*gy[0][0];
                valueCalc = round(sqrt(valueX*valueX + valueY*valueY));
                //Checks if the calculated value is over 255
                if (valueCalc > 255)
                    image[i][j].rgbtRed = 255;
                else
                    image[i][j].rgbtRed = valueCalc;
                //Results for the green values
                valueX = copy[i][j].rgbtGreen*gx[1][1] + copy[i][j - 1].rgbtGreen*gx[1][0] + copy[i - 1][j].rgbtGreen*gx[0][1] + copy[i - 1][j - 1].rgbtGreen*gx[0][0];
                valueY = copy[i][j].rgbtGreen*gy[1][1] + copy[i][j - 1].rgbtGreen*gy[1][0] + copy[i - 1][j].rgbtGreen*gy[0][1] + copy[i - 1][j - 1].rgbtGreen*gy[0][0];
                valueCalc = round(sqrt(valueX*valueX + valueY*valueY));
                //Checks if the calculated value is over 255
                if (valueCalc > 255)
                    image[i][j].rgbtGreen = 255;
                else
                    image[i][j].rgbtGreen = valueCalc;
                //Results for the blue values
                valueX = copy[i][j].rgbtBlue*gx[1][1] + copy[i][j - 1].rgbtBlue*gx[1][0] + copy[i - 1][j].rgbtBlue*gx[0][1] + copy[i - 1][j - 1].rgbtBlue*gx[0][0];
                valueY = copy[i][j].rgbtBlue*gy[1][1] + copy[i][j - 1].rgbtBlue*gy[1][0] + copy[i - 1][j].rgbtBlue*gy[0][1] + copy[i - 1][j - 1].rgbtBlue*gy[0][0];
                valueCalc = round(sqrt(valueX*valueX + valueY*valueY));
                //Checks if the calculated value is over 255
                if (valueCalc > 255)
                    image[i][j].rgbtBlue = 255;
                else
                    image[i][j].rgbtBlue = valueCalc;
            }
            //Everything in between last line/first column and last line/last column
            else if (i == height - 1 && j != 0 && j != width - 1)
            {
                //Results for the red values
                valueX = copy[i][j].rgbtRed*gx[1][1] + copy[i][j + 1].rgbtRed*gx[1][2] + copy[i][j - 1].rgbtRed*gx[1][0] + copy[i - 1][j].rgbtRed*gx[0][1] + copy[i - 1][j - 1].rgbtRed*gx[0][0] + copy[i - 1][j + 1].rgbtRed*gx[0][2];
                valueY = copy[i][j].rgbtRed*gy[1][1] + copy[i][j + 1].rgbtRed*gy[1][2] + copy[i][j - 1].rgbtRed*gy[1][0] + copy[i - 1][j].rgbtRed*gy[0][1] + copy[i - 1][j - 1].rgbtRed*gy[0][0] + copy[i - 1][j + 1].rgbtRed*gy[0][2];
                valueCalc = round(sqrt(valueX*valueX + valueY*valueY));
                //Checks if the calculated value is over 255
                if (valueCalc > 255)
                    image[i][j].rgbtRed = 255;
                else
                    image[i][j].rgbtRed = valueCalc;
                //Results for the green values
                valueX = copy[i][j].rgbtGreen*gx[1][1] + copy[i][j + 1].rgbtGreen*gx[1][2] + copy[i][j - 1].rgbtGreen*gx[1][0] + copy[i - 1][j].rgbtGreen*gx[0][1] + copy[i - 1][j - 1].rgbtGreen*gx[0][0] + copy[i - 1][j + 1].rgbtGreen*gx[0][2];
                valueY = copy[i][j].rgbtGreen*gy[1][1] + copy[i][j + 1].rgbtGreen*gy[1][2] + copy[i][j - 1].rgbtGreen*gy[1][0] + copy[i - 1][j].rgbtGreen*gy[0][1] + copy[i - 1][j - 1].rgbtGreen*gy[0][0] + copy[i - 1][j + 1].rgbtGreen*gy[0][2];
                valueCalc = round(sqrt(valueX*valueX + valueY*valueY));
                //Checks if the calculated value is over 255
                if (valueCalc > 255)
                    image[i][j].rgbtGreen = 255;
                else
                    image[i][j].rgbtGreen = valueCalc;
                //Results for the blue values
                valueX = copy[i][j].rgbtBlue*gx[1][1] + copy[i][j + 1].rgbtBlue*gx[1][2] + copy[i][j - 1].rgbtBlue*gx[1][0] + copy[i - 1][j].rgbtBlue*gx[0][1] + copy[i - 1][j - 1].rgbtBlue*gx[0][0] + copy[i - 1][j + 1].rgbtBlue*gx[0][2];
                valueY = copy[i][j].rgbtBlue*gy[1][1] + copy[i][j + 1].rgbtBlue*gy[1][2] + copy[i][j - 1].rgbtBlue*gy[1][0] + copy[i - 1][j].rgbtBlue*gy[0][1] + copy[i - 1][j - 1].rgbtBlue*gy[0][0] + copy[i - 1][j + 1].rgbtBlue*gy[0][2];
                valueCalc = round(sqrt(valueX*valueX + valueY*valueY));
                //Checks if the calculated value is over 255
                if (valueCalc > 255)
                    image[i][j].rgbtBlue = 255;
                else
                    image[i][j].rgbtBlue = valueCalc;
            }
            //When the values are at the left border
            else if (j == 0 && i != 0 && i != height - 1)
            {
                //Results for the red values
                valueX = copy[i][j].rgbtRed*gx[1][1] + copy[i][j + 1].rgbtRed*gx[1][2] + copy[i + 1][j].rgbtRed*gx[2][1] + copy[i + 1][j + 1].rgbtRed*gx[2][2] + copy[i - 1][j].rgbtRed*gx[0][1] + copy[i - 1][j + 1].rgbtRed*gx[0][2];
                valueY = copy[i][j].rgbtRed*gy[1][1] + copy[i][j + 1].rgbtRed*gy[1][2] + copy[i + 1][j].rgbtRed*gy[2][1] + copy[i + 1][j + 1].rgbtRed*gy[2][2] + copy[i - 1][j].rgbtRed*gy[0][1] + copy[i - 1][j + 1].rgbtRed*gy[0][2];
                valueCalc = round(sqrt(valueX*valueX + valueY*valueY));
                //Checks if the calculated value is over 255
                if (valueCalc > 255)
                    image[i][j].rgbtRed = 255;
                else
                    image[i][j].rgbtRed = valueCalc;
                //Results for the green values
                valueX = copy[i][j].rgbtGreen*gx[1][1] + copy[i][j + 1].rgbtGreen*gx[1][2] + copy[i + 1][j].rgbtGreen*gx[2][1] + copy[i + 1][j + 1].rgbtGreen*gx[2][2] + copy[i - 1][j].rgbtGreen*gx[0][1] + copy[i - 1][j + 1].rgbtGreen*gx[0][2];
                valueY = copy[i][j].rgbtGreen*gy[1][1] + copy[i][j + 1].rgbtGreen*gy[1][2] + copy[i + 1][j].rgbtGreen*gy[2][1] + copy[i + 1][j + 1].rgbtGreen*gy[2][2] + copy[i - 1][j].rgbtGreen*gy[0][1] + copy[i - 1][j + 1].rgbtGreen*gy[0][2];
                valueCalc = round(sqrt(valueX*valueX + valueY*valueY));
                //Checks if the calculated value is over 255
                if (valueCalc > 255)
                    image[i][j].rgbtGreen = 255;
                else
                    image[i][j].rgbtGreen = valueCalc;
                //Results for the blue values
                valueX = copy[i][j].rgbtBlue*gx[1][1] + copy[i][j + 1].rgbtBlue*gx[1][2] + copy[i + 1][j].rgbtBlue*gx[2][1] + copy[i + 1][j + 1].rgbtBlue*gx[2][2] + copy[i - 1][j].rgbtBlue*gx[0][1] + copy[i - 1][j + 1].rgbtBlue*gx[0][2];
                valueY = copy[i][j].rgbtBlue*gy[1][1] + copy[i][j + 1].rgbtBlue*gy[1][2] + copy[i + 1][j].rgbtBlue*gy[2][1] + copy[i + 1][j + 1].rgbtBlue*gy[2][2] + copy[i - 1][j].rgbtBlue*gy[0][1] + copy[i - 1][j + 1].rgbtBlue*gy[0][2];
                valueCalc = round(sqrt(valueX*valueX + valueY*valueY));
                //Checks if the calculated value is over 255
                if (valueCalc > 255)
                    image[i][j].rgbtBlue = 255;
                else
                    image[i][j].rgbtBlue = valueCalc;
            }
            //When the values are at the right border
            else if (j == width - 1 && i != 0 && i != height - 1)
            {
                //Results for the red values
                valueX = copy[i][j].rgbtRed*gx[1][1] + copy[i][j - 1].rgbtRed*gx[1][0] + copy[i + 1][j].rgbtRed*gx[2][1] + copy[i + 1][j - 1].rgbtRed*gx[2][0] + copy[i - 1][j].rgbtRed*gx[0][1] + copy[i - 1][j - 1].rgbtRed*gx[0][0];
                valueY = copy[i][j].rgbtRed*gy[1][1] + copy[i][j - 1].rgbtRed*gy[1][0] + copy[i + 1][j].rgbtRed*gy[2][1] + copy[i + 1][j - 1].rgbtRed*gy[2][0] + copy[i - 1][j].rgbtRed*gy[0][1] + copy[i - 1][j - 1].rgbtRed*gy[0][0];
                valueCalc = round(sqrt(valueX*valueX + valueY*valueY));
                //Checks if the calculated value is over 255
                if (valueCalc > 255)
                    image[i][j].rgbtRed = 255;
                else
                    image[i][j].rgbtRed = valueCalc;
                //Results for the green values
                valueX = copy[i][j].rgbtGreen*gx[1][1] + copy[i][j - 1].rgbtGreen*gx[1][0] + copy[i + 1][j].rgbtGreen*gx[2][1] + copy[i + 1][j - 1].rgbtGreen*gx[2][0] + copy[i - 1][j].rgbtGreen*gx[0][1] + copy[i - 1][j - 1].rgbtGreen*gx[0][0];
                valueY = copy[i][j].rgbtGreen*gy[1][1] + copy[i][j - 1].rgbtGreen*gy[1][0] + copy[i + 1][j].rgbtGreen*gy[2][1] + copy[i + 1][j - 1].rgbtGreen*gy[2][0] + copy[i - 1][j].rgbtGreen*gy[0][1] + copy[i - 1][j - 1].rgbtGreen*gy[0][0];
                valueCalc = round(sqrt(valueX*valueX + valueY*valueY));
                //Checks if the calculated value is over 255
                if (valueCalc > 255)
                    image[i][j].rgbtGreen = 255;
                else
                    image[i][j].rgbtGreen = valueCalc;
                //Results for the blue values
                valueX = copy[i][j].rgbtBlue*gx[1][1] + copy[i][j - 1].rgbtBlue*gx[1][0] + copy[i + 1][j].rgbtBlue*gx[2][1] + copy[i + 1][j - 1].rgbtBlue*gx[2][0] + copy[i - 1][j].rgbtBlue*gx[0][1] + copy[i - 1][j - 1].rgbtBlue*gx[0][0];
                valueY = copy[i][j].rgbtBlue*gy[1][1] + copy[i][j - 1].rgbtBlue*gy[1][0] + copy[i + 1][j].rgbtBlue*gy[2][1] + copy[i + 1][j - 1].rgbtBlue*gy[2][0] + copy[i - 1][j].rgbtBlue*gy[0][1] + copy[i - 1][j - 1].rgbtBlue*gy[0][0];
                valueCalc = round(sqrt(valueX*valueX + valueY*valueY));
                //Checks if the calculated value is over 255
                if (valueCalc > 255)
                    image[i][j].rgbtBlue = 255;
                else
                    image[i][j].rgbtBlue = valueCalc;
            }
            //Values not at any border or edge
            else if (i != 0 && i != height - 1 && j != 0 && j != width - 1)
            {
                //Results for the red values
                valueX = copy[i][j].rgbtRed*gx[1][1] + copy[i][j - 1].rgbtRed*gx[1][0] + copy[i][j + 1].rgbtRed*gx[1][2] + copy[i + 1][j].rgbtRed*gx[2][1] + copy[i + 1][j - 1].rgbtRed*gx[2][0] + copy[i + 1][j + 1].rgbtRed*gx[2][2] + copy[i - 1][j].rgbtRed*gx[0][1] + copy[i - 1][j - 1].rgbtRed*gx[0][0] + copy[i - 1][j + 1].rgbtRed*gx[0][2];
                valueY = copy[i][j].rgbtRed*gy[1][1] + copy[i][j - 1].rgbtRed*gy[1][0] + copy[i][j + 1].rgbtRed*gy[1][2] + copy[i + 1][j].rgbtRed*gy[2][1] + copy[i + 1][j - 1].rgbtRed*gy[2][0] + copy[i + 1][j + 1].rgbtRed*gy[2][2] + copy[i - 1][j].rgbtRed*gy[0][1] + copy[i - 1][j - 1].rgbtRed*gy[0][0] + copy[i - 1][j + 1].rgbtRed*gy[0][2];
                valueCalc = round(sqrt(valueX*valueX + valueY*valueY));
                //Checks if the calculated value is over 255
                if (valueCalc > 255)
                    image[i][j].rgbtRed = 255;
                else
                    image[i][j].rgbtRed = valueCalc;
                //Results for the green values
                valueX = copy[i][j].rgbtGreen*gx[1][1] + copy[i][j - 1].rgbtGreen*gx[1][0] + copy[i][j + 1].rgbtGreen*gx[1][2] + copy[i + 1][j].rgbtGreen*gx[2][1] + copy[i + 1][j - 1].rgbtGreen*gx[2][0] + copy[i + 1][j + 1].rgbtGreen*gx[2][2] + copy[i - 1][j].rgbtGreen*gx[0][1] + copy[i - 1][j - 1].rgbtGreen*gx[0][0] + copy[i - 1][j + 1].rgbtGreen*gx[0][2];
                valueY = copy[i][j].rgbtGreen*gy[1][1] + copy[i][j - 1].rgbtGreen*gy[1][0] + copy[i][j + 1].rgbtGreen*gy[1][2] + copy[i + 1][j].rgbtGreen*gy[2][1] + copy[i + 1][j - 1].rgbtGreen*gy[2][0] + copy[i + 1][j + 1].rgbtGreen*gy[2][2] + copy[i - 1][j].rgbtGreen*gy[0][1] + copy[i - 1][j - 1].rgbtGreen*gy[0][0] + copy[i - 1][j + 1].rgbtGreen*gy[0][2];
                valueCalc = round(sqrt(valueX*valueX + valueY*valueY));
                //Checks if the calculated value is over 255
                if (valueCalc > 255)
                    image[i][j].rgbtGreen = 255;
                else
                    image[i][j].rgbtGreen = valueCalc;
                //Results for the blue values
                valueX = copy[i][j].rgbtBlue*gx[1][1] + copy[i][j - 1].rgbtBlue*gx[1][0] + copy[i][j + 1].rgbtBlue*gx[1][2] + copy[i + 1][j].rgbtBlue*gx[2][1] + copy[i + 1][j - 1].rgbtBlue*gx[2][0] + copy[i + 1][j + 1].rgbtBlue*gx[2][2] + copy[i - 1][j].rgbtBlue*gx[0][1] + copy[i - 1][j - 1].rgbtBlue*gx[0][0] + copy[i - 1][j + 1].rgbtBlue*gx[0][2];
                valueY = copy[i][j].rgbtBlue*gy[1][1] + copy[i][j - 1].rgbtBlue*gy[1][0] + copy[i][j + 1].rgbtBlue*gy[1][2] + copy[i + 1][j].rgbtBlue*gy[2][1] + copy[i + 1][j - 1].rgbtBlue*gy[2][0] + copy[i + 1][j + 1].rgbtBlue*gy[2][2] + copy[i - 1][j].rgbtBlue*gy[0][1] + copy[i - 1][j - 1].rgbtBlue*gy[0][0] + copy[i - 1][j + 1].rgbtBlue*gy[0][2];
                valueCalc = round(sqrt(valueX*valueX + valueY*valueY));
                //Checks if the calculated value is over 255
                if (valueCalc > 255)
                    image[i][j].rgbtBlue = 255;
                else
                    image[i][j].rgbtBlue = valueCalc;
            }
        }
    }
    return;
}
