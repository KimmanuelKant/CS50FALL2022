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

    // TODO: Copy header from input file to output file
    // Make a temporary storage
    uint8_t header[HEADER_SIZE];

    // Reads the content of input, and stores it in header
    fread(header, HEADER_SIZE, 1, input);
    // Writes the output of header, and stores it in output
    fwrite(header, HEADER_SIZE, 1, output);

    // TODO: Read samples from input file and write updated data to output file
    // Make a temporary storage
    int16_t buffer;

    // While fread still has things to read, copy those to the temp storage
    while (fread(&buffer, sizeof(buffer), 1, input))
    {
        // Multiply it by factor
        buffer *= factor;
        // and  print it to output
        fwrite(&buffer, sizeof(buffer), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
