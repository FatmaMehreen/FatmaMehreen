#include <iostream>  // For input-output operations
#include <iomanip>   // For manipulating the output format

// Function to print a floating-point number with specific field width and precision
void print_real(float number, int fieldspace, int precision) {
    // Set output to fixed-point notation
    // Set precision (number of digits after the decimal point)
    // Set field width for the output
    // Print number, followed by a new line
    std::cout << std::fixed << std::setprecision(precision) << std::setw(fieldspace) << number << std::endl;
}

// Template function to update and scale two variables
template <typename T>
void update_scale(T& m1, T& m2, T m3 = 10) {  // Default value for m3 is 10
    T temp1 = m1;  // Store the original value of m1
    T temp2 = m2;  // Store the original value of m2

    // Update m1 and m2 based on the given formula
    m1 = (temp1 + temp2) * m3;  // m1 becomes the scaled sum of m1 and m2
    m2 = (temp1 - temp2) * m3;  // m2 becomes the scaled difference of m1 and m2
}

int main() {
    float a = 1.2345, b = 6.7890;  // Initialize two floating-point variables

    // Print the initial values of 'a' and 'b' with field width of 10 and precision of 3
    print_real(a, 10, 3);
    print_real(b, 10, 3);

    // Update 'a' and 'b' using the update_scale function
    update_scale(a, b);

    // Print the updated values of 'a' and 'b' with the same formatting
    print_real(a, 10, 3);
    print_real(b, 10, 3);

    return 0;  // Indicate successful execution
}
