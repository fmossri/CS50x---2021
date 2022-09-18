// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    //Creates an array of HEADER_SIZE bytes, copies the header into it, and then copies it into the output file
    uint8_t byte_holder[HEADER_SIZE];
    fread(byte_holder, sizeof(uint8_t), HEADER_SIZE, input);

    fwrite(byte_holder, sizeof(uint8_t), HEADER_SIZE, output);

    //Creates a buffer to copy the samples one each time into it
    int16_t buffer;
    while (fread(&buffer, sizeof(buffer), 1, input))
    {
        //Multiplies the sample stored in the buffer by the factor, and writes it into the output file
        buffer = buffer * factor;
        fwrite(&buffer, sizeof(buffer), 1, output);
    }
    // Close files
    fclose(input);
    fclose(output);
}


