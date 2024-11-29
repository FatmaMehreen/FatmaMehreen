#include <stdio.h>  // For file input/output functions
#include <stdlib.h> // For memory allocation and general utilities

// Structure to represent an image
typedef struct {
    int width;             // Width of the image
    int height;            // Height of the image
    int maxGrayValue;      // Maximum gray value for pixels (e.g., 255)
    unsigned char *pixels; // Pointer to pixel data
} Image;

// Function to read a PGM (text-based) file
int readPGMText(const char *filename, int *width, int *height, int *maxGrayValue, unsigned char **pixels) {
    FILE *file = fopen(filename, "r"); // Open file in read mode
    if (!file) { // Check if file opening was successful
        printf("Error opening file: %s\n", filename);
        return -1;
    }

    char format[3];
    // Read the file format (should be "P2" for text-based PGM)
    if (fscanf(file, "%s", format) != 1 || (format[0] != 'P' || format[1] != '2')) {
        printf("Invalid PGM file format\n");
        fclose(file); // Close file if invalid format
        return -1;
    }

    char c;
    // Skip comments in the file (lines starting with '#')
    while ((c = fgetc(file)) == '#') {
        while ((c = fgetc(file)) != '\n' && c != EOF); // Skip to end of the comment line
    }

    fseek(file, -1, SEEK_CUR); // Rewind one character to process the dimensions
    fscanf(file, "%d %d %d", width, height, maxGrayValue); // Read width, height, and max gray value

    // Allocate memory for pixel data
    *pixels = (unsigned char *)malloc((*width) * (*height) * sizeof(unsigned char));
    if (*pixels == NULL) { // Check if memory allocation was successful
        printf("Memory allocation failed for pixel data.\n");
        fclose(file);
        return -1;
    }

    // Read pixel values into the allocated array
    for (int i = 0; i < *width * *height; i++) {
        fscanf(file, "%hhu", &((*pixels)[i]));
    }

    fclose(file); // Close the file after reading
    return 0; // Success
}

// Function to write an image to a text-based PGM file
int writePGMText(const char *filename, int width, int height, int maxGrayValue, unsigned char *pixels) {
    FILE *file = fopen(filename, "w"); // Open file in write mode
    if (!file) { // Check if file opening was successful
        printf("Error opening file: %s\n", filename);
        return -1;
    }

    // Write the PGM header
    fprintf(file, "P2\n"); // Text-based PGM identifier
    fprintf(file, "# Created by stego_lsb\n"); // Comment line
    fprintf(file, "%d %d\n", width, height); // Image dimensions
    fprintf(file, "%d\n", maxGrayValue); // Maximum gray value

    // Write pixel data
    for (int i = 0; i < width * height; i++) {
        fprintf(file, "%d ", pixels[i]);
    }

    fclose(file); // Close the file
    return 0; // Success
}

// Function to write an image to a binary PGM file
int writePGMBinary(const char *filename, int width, int height, int maxGrayValue, unsigned char *pixels) {
    FILE *file = fopen(filename, "wb"); // Open file in binary write mode
    if (!file) { // Check if file opening was successful
        printf("Error opening file: %s\n", filename);
        return -1;
    }

    // Write the PGM header
    fprintf(file, "P5\n"); // Binary PGM identifier
    fprintf(file, "# Created by stego_lsb\n"); // Comment line
    fprintf(file, "%d %d\n", width, height); // Image dimensions
    fprintf(file, "%d\n", maxGrayValue); // Maximum gray value

    // Write pixel data in binary format
    fwrite(pixels, sizeof(unsigned char), width * height, file);

    fclose(file); // Close the file
    return 0; // Success
}

// Function to embed secret image data into the least significant bits (LSB) of a cover image
void embedLSB(int width, int height, unsigned char *coverPixels, unsigned char *secretPixels, unsigned char *stegoPixels) {
    for (int i = 0; i < width * height; i++) {
        stegoPixels[i] = (coverPixels[i] & 0xF0) | (secretPixels[i] >> 4); // Combine 4 MSBs of cover with 4 LSBs of secret
    }
}

// Function to extract the secret image from the least significant bits (LSB) of the stego image
void extractLSB(int width, int height, unsigned char *stegoPixels, unsigned char *outputPixels) {
    for (int i = 0; i < width * height; i++) {
        outputPixels[i] = (stegoPixels[i] & 0x0F) << 4; // Extract 4 LSBs and shift them to the 4 MSBs
    }
}

// Main function
int main() {
    int width = 512, height = 512; // Image dimensions
    int maxGrayValue; // Maximum gray value for images
    unsigned char *coverPixels, *secretPixels, *stegoPixels, *outputPixels;

    // Allocate memory for stego and output image pixel data
    stegoPixels = (unsigned char *)malloc(width * height * sizeof(unsigned char));
    outputPixels = (unsigned char *)malloc(width * height * sizeof(unsigned char));
    if (readPGMText("baboon.pgm", &width, &height, &maxGrayValue, &coverPixels) != 0) { // Read the cover image
        return -1; // Exit if error occurs
    }

    if (readPGMText("farm.pgm", &width, &height, &maxGrayValue, &secretPixels) != 0) { // Read the secret image
        return -1; // Exit if error occurs
    }

    if (!stegoPixels || !outputPixels) { // Check if memory allocation was successful
        printf("Memory allocation failed for stego or output images.\n");
        return -1; // Exit if memory allocation fails
    }

    // Embed secret image into cover image
    embedLSB(width, height, coverPixels, secretPixels, stegoPixels);
    // Extract secret image from stego image
    extractLSB(width, height, stegoPixels, outputPixels);

    // Write stego image to a binary PGM file
    writePGMBinary("stego_image_bin.pgm", width, height, maxGrayValue, stegoPixels);
    // Write extracted secret image to a text-based PGM file
    writePGMText("extracted_secret.pgm", width, height, maxGrayValue, outputPixels);

    // Free allocated memory
    free(coverPixels);
    free(secretPixels);
    free(stegoPixels);
    free(outputPixels);

    return 0; // Program executed successfully
}
