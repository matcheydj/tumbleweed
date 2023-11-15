#include <stdio.h>
#include <math.h>
#include <sys/utsname.h>

int main() {
    int input;
    struct utsname os_info;

    // Get user input
    printf("Enter an integer: ");
    scanf("%d", &input);

    // Calculate square root
    double sqrt_input = sqrt(input);

    // Get OS version
    uname(&os_info);
    printf("OS version: %s\n", os_info.release);

    // Extract major and minor version numbers
    int major, minor;
    sscanf(os_info.release, "%d.%d", &major, &minor);

    // Factor against version numbers
    double factor_major = sqrt_input / major;
    double factor_minor = sqrt_input / minor;

    // Output results
    printf("Square root of input: %.2f\n", sqrt_input);
    printf("Factor against major version number: %.2f\n", factor_major);
    printf("Factor against minor version number: %.2f\n", factor_minor);

    return 0;
}
