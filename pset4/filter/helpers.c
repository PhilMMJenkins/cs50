#include "helpers.h"
#include "math.h"

//declare function used
int maxcap(int x);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue);
            if (sum % 3 == 2)
            {
                sum++;
            }
            else if (sum % 3 == 1)
            {
                sum--;
            }
            int grey = sum / 3;
            image[i][j].rgbtRed = grey;
            image[i][j].rgbtGreen = grey;
            image[i][j].rgbtBlue = grey;
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
            int k = width - 1 - j;
            RGBTRIPLE tmp = image[i][k];
            image[i][k] = image[i][j];
            image[i][j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //iterate over each pixel of the image
    RGBTRIPLE blimage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int r = 0;
            int g = 0;
            int b = 0;
            int sp = 0;
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int ix = i + x;
                    int jy = j + y;
                    if (ix >=0 && ix < height && jy >=0 && jy < width)
                    {
                        r += image[ix][jy].rgbtRed;
                        g += image[ix][jy].rgbtGreen;
                        b += image[ix][jy].rgbtBlue;
                        sp++;
                    }
                }
            }
            blimage[i][j].rgbtRed = round((float) r / sp);
            blimage[i][j].rgbtGreen = round((float) g / sp);
            blimage[i][j].rgbtBlue = round((float) b / sp);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blimage[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE eimage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //having iterated for image[i][j], iterate a kernel
            //create sobel array
            int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
            int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
            int rx = 0;
            int gx = 0;
            int bx = 0;
            int ry = 0;
            int gy = 0;
            int by = 0;
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int ix = i + x;
                    int jy = j + y;
                    if (ix >=0 && ix < height && jy >=0 && jy < width)
                    {
                        int w = Gx[x + 1][y + 1];
                        rx += w * image[ix][jy].rgbtRed;
                        gx += w * image[ix][jy].rgbtGreen;
                        bx += w * image[ix][jy].rgbtBlue;
                        
                        int v = Gy[x + 1][y + 1];
                        ry += v * image[ix][jy].rgbtRed;
                        gy += v * image[ix][jy].rgbtGreen;
                        by += v * image[ix][jy].rgbtBlue;
                    }
                }
            }
            eimage[i][j].rgbtRed = maxcap(round(sqrt(rx*rx + ry*ry)));
            eimage[i][j].rgbtGreen = maxcap(round(sqrt(gx*gx + gy*gy)));
            eimage[i][j].rgbtBlue = maxcap(round(sqrt(bx*bx + by*by)));
        }
    }
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                image[i][j] = eimage[i][j];
            }
        }
    return;
}

int maxcap(int x)
{
    if(x > 255)
    {
        return 255;
    }
    else
    {
        return x;
    }
}

