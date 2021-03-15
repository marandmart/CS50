#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Condition for accepting only one word after the function call
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open file
    FILE *photo_card = fopen(argv[1], "r");

    // If the file is corrupt, the program is ended
    if (photo_card == NULL)
    {
        return 1;
    }

    // Counter for the number of jpegs found
    int jpeg_found_counter = 0;

    // Creates an array of 512 spaces
    BYTE buffer[512];

    // Creates an array to be worked on
    char new_image[8];

    // Creates the file being worked on the loop
    FILE *img = NULL;

    // Reads the first 4 bits in a 512 byte chunks
    while (fread(buffer, 512, 1, photo_card) == 1)
    {
        // Checks for the jpeg header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If it's the first image
            if (jpeg_found_counter == 0)
            {
                // Creates a new image file
                sprintf(new_image, "%03i.jpg", jpeg_found_counter);

                // Opens new file for writing the data to
                img = fopen(new_image, "w");

                // Updates the counter
                jpeg_found_counter += 1;

                // Writes to that file the data of the image
                fwrite(&buffer, 512, 1, img);
            }
            // If it's not the first image, it closes the previous and begins writing to a new file
            else
            {
                // Closes the previous jpeg file
                fclose(img);

                // Creates a new image file
                sprintf(new_image, "%03i.jpg", jpeg_found_counter);

                // Opens new file for writing the data to
                img = fopen(new_image, "w");

                // Updates the counter
                jpeg_found_counter += 1;

                // Writes to that file the data of the image
                fwrite(&buffer, 512, 1, img);
            }
        }
        // If it didn't found a new jpeg header
        else
        {
            // And if it isn't the first image, it keeps writing the data
            if (jpeg_found_counter != 0)
            {
                // Continues writing the data of the image
                fwrite(&buffer, 512, 1, img);
            }
        }
    }

    // Closes the opened file being worked on the loop
    fclose(img);

    // Closes the raw card image
    fclose(photo_card);

    return 0;
}