#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

//declare new data types
typedef uint8_t BYTE;

//function prototypes
bool jpeg_start(BYTE *buffer);

int main(int argc, char *argv[])
{
    int jpeg_count = -1;
    
    //validation steps. return 1 if incorrect argument count and unable to open file.
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    if (!fopen(argv[1], "r"))
    {
        printf("invalid file\n");
        return 1;
    }

    //load file into memory at address with pointer, file.
    FILE *file = fopen(argv[1], "r");
    
    //create a buffer of 512 bytes to be read at a time.
    BYTE buffer[512];
    
    FILE *image;
    
    //create a while loop which reads the buffer and determines what should happen to it
    while (fread(buffer, 512, 1, file))
    {
        char n[7];//creates an array of 7 characters e.g. 000.jpg n for name
        
        
        if (jpeg_start(buffer) && jpeg_count == -1) //look for the first jpeg
        {
            jpeg_count++; //if we have found a jpeg, start a filename and increment the count by one
            sprintf(n, "%03i.jpg", jpeg_count);
            image = fopen(n, "w");
            fwrite(buffer, 512, 1, image);
            
        }
        else if (jpeg_start(buffer) && jpeg_count != -1)//look for subsequent jpegs
        {
            fclose(image); //close the previous file
            jpeg_count++; // increment the jpeg count
            sprintf(n, "%03i.jpg", jpeg_count);
            image = fopen(n, "w");
            fwrite(buffer, 512, 1, image);
        }
        else if (!jpeg_start(buffer) && jpeg_count != -1) 
            // if the buffer follows a jpeg start and does not contain one itself, write to the current jpeg
        {
            fwrite(buffer, 512, 1, image);
        }
    }
}

bool jpeg_start(BYTE buffer[])
//reads the first 4 bytes
{
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {
        return true;
    }
    return false;
}


