#include <stdio.h>
#include <stdlib.h>
// 512 bytes makes for one FAT data chunk
#define CHUNK_SIZE 512

int main(int argc, char *argv[])
{
    // Make a buffer to holod the data we're reading
    FILE *buffer;

    // Open the image file
    buffer = fopen(argv[1], "r");

    // Check that the image file added was valid
    if (buffer == NULL)
    {
        printf("Whoopsiedaisy, ERROR in reading the file!\n");
        return 1;
    }
    // Define one BYTE to check, in an array the size of a FAT-chunk
    unsigned char chunk[CHUNK_SIZE];

    // Initialize a counter for number of jpeg headers we find.
    size_t jpegsFound = 0;
    // Initialize a string to use when printing filenames on .jpg's
    char *filename = NULL;
    // Initialize the new .jpg file we will write onto
    FILE *newjpg = NULL;

    // Read through all data
    while (fread(chunk, sizeof(unsigned char), CHUNK_SIZE, buffer))
    {
        // If we find a .jpeg header
        if ((chunk[0] == 0xff) && (chunk[1] == 0xd8) && (chunk[2] == 0xff) && ((chunk[3] & 0xf0) == 0xe0))
        {
            // And we're already writing on to the previous jpg file
            if (newjpg != NULL)
            {
                // close the previous jpg
                free(filename);
                fclose(newjpg);
                filename = NULL;
                newjpg = NULL;
            }

            // Make a new .jpeg file
            filename = malloc(8);
            sprintf(filename, "%03zu.jpg", jpegsFound);
            newjpg = fopen(filename, "w");
            jpegsFound++;
        }
        // Write the content of chunk onto the .jpg file, if there is one.
        if (newjpg != NULL)
        {
            fwrite(chunk, sizeof(unsigned char), CHUNK_SIZE, newjpg);
        }
    }

    // close down the stuff we've opened
    free(filename);
    fclose(newjpg);
    fclose(buffer);
    filename = NULL;
    newjpg = NULL;

    // And end
    return 0;
}