#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//Define constant buffer size
const int BUFFER_SIZE = 512;

//Define byte data type
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //Checks for correct usage
    if (argc - 1 != 1)
    {
        printf("Usage: ./recover [file]\n");
        return 1;
    }
    //Opens to-be-recovered data file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
    }
    //Allocates buffer memory for reading
    BYTE *buffer = malloc(sizeof(BYTE) * 512);
    if (buffer == NULL)
    {
        return 1;
    }
    //Counts how many JPEGS were opened
    int open_counter = 0;

    //Counts how many JPEGS were closed
    int close_counter = 0;

    //Allocates memory for file naming
    char *image_name = malloc(sizeof(char) * 7);

    //sets a shared pointer to use among fwrite and fclose
    FILE *holder;

    //Reads data from file to buffer 512B each time while fread returns full buffer
    while ((fread(buffer, sizeof(BYTE), BUFFER_SIZE, file) == BUFFER_SIZE))
    {
        //Checks for JPEG files' header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //Checks if a new JPEG file can be opened
            if (open_counter == close_counter)
            {
                //Names each JPEG accordingly using a counter
                sprintf(image_name, "%03i.jpg", open_counter);

                //Opens a new file for writing the JPEG into
                FILE *image = fopen(image_name, "w");
                if (image == NULL)
                {
                    return 1;
                }
                //sets the *holder pointer to the *image pointer's adress
                holder = image;

                open_counter++;

                //Writes from buffer to new JPEG file 512B each time
                fwrite(buffer, sizeof(BYTE), BUFFER_SIZE, image);
                if (image == NULL)
                {
                    return 1;
                }
            }
            //If a new JPEG was found, but another one is still open, close it and start a new one
            else
            {
                //Close latest JPEG file trough shared pointer *holder
                fclose(holder);

                close_counter++;

                //Names the new JPEG accordingly
                sprintf(image_name, "%03i.jpg", open_counter);

                //Opens a new file for writing the new JPEG into
                FILE *image = fopen(image_name, "w");
                if (image == NULL)
                {
                    return 1;
                }

                holder = image;
                open_counter++;

                fwrite(buffer, sizeof(BYTE), BUFFER_SIZE, image);
                if (image == NULL)
                {
                    return 1;
                }
            }
        }
        //If a new JPEG wasn't found, but a file is still open, keep writing it
        else if (close_counter < open_counter)
        {
            //Writes into JPEG file using shared pointer *holder
            fwrite(buffer, sizeof(BYTE), BUFFER_SIZE, holder);
            if (holder == NULL)
            {
                return 1;
            }
        }
    }
    //If the card is done, but a JPEG file is still open, close it
    if (close_counter < open_counter)
    {
        fclose(holder);
    }
    //close source file and free allocated memory
    fclose(file);
    free(buffer);
    free(image_name);
}

