#include <stdio.h>   // For input/output operations
#include <stdlib.h>  // For general utility functions

int main() {
    // Open the input file "dataa.txt" in read mode
    FILE *file = fopen("dataa.txt", "r");
    if (file == NULL) { // Check if the input file was opened successfully
        perror("Error opening input file"); // Print an error message if the file couldn't be opened
        return 1; // Exit the program with a non-zero status
    }

    // Open the output file "output.txt" in write mode
    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) { // Check if the output file was opened successfully
        perror("Error opening output file"); // Print an error message if the file couldn't be opened
        fclose(file); // Close the input file before exiting
        return 1; // Exit the program with a non-zero status
    }


    float value;          // Variable to store valid float values
    int invalidCount = 0; //counter for invalid entries
    char buffer[100];     // Buffer to hold strings for invalid data

    // Read the input file one word at a time (separated by whitespace)
    while (fscanf(file, "%s", buffer) == 1) {
        // Try to parse the word (stored in buffer) as a float value
        if (sscanf(buffer, "%f", &value) == 1) { // If sscanf successfully parses it as a float
            // Write the valid float to the output file with 3 decimal places
            fprintf(outputFile, "%.3f\n", value);
        } else { // If the word is not a valid float
            // Print the invalid entry to the console
            printf("Invalid entry: %s\n", buffer);
            // Increment the counter for invalid entries
            invalidCount++;
        }
    }

    // Check for errors during file reading
    if (ferror(file)) {
        printf("Error reading from input file.\n"); // Print an error message if an issue occurred
    }

    // Close the input and output files
    fclose(file);
    fclose(outputFile);

     // Print the total count of invalid float values
    printf("Number of invalid float values found: %d\n", invalidCount);

    return 0; // Indicate successful program execution
}
