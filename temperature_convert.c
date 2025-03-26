/*
File Name: temperature_convert.c

Description:
    This program reads a temperature value and its scale, converts it to a user-specified target scale, and then
    categorizes the temperature (in Celsius) into:
        - Freezing (< 0°C)
        - Cold (0°C to 10°C)
        - Comfortable (10°C to 25°C)
        - Hot (25°C to 35°C)
        - Extreme Heat (> 35°C)
    An advisory message is also displayed.
*/

#include <stdio.h>
#include <stdlib.h>

// function prototypes for temperature conversions. Converts between two specific temp scales.
float celsius_to_fahrenheit(float c);
float fahrenheit_to_celsius(float f);
float celsius_to_kelvin(float c);
float kelvin_to_celsius(float k);

// function to categorize temperature (in Celsius) and provide an advisory message.
void categorize_temperature(float celsius);

int main(void) {
    float inputTemp;               // temperature input value from the user
    char inputScale, targetScale;  // scales for the input temp and the desired conversion

    // prompts user for the temperature value
    printf("Enter temperature value: ");
    scanf("%f", &inputTemp);

    // repeatedly prompts the user for a valid input scale (F, C, or K).
    while (1) {
        printf("Enter input scale (F, C, K): ");
        scanf(" %c", &inputScale);

        // checks if inputScale is valid (F, C, or K in either case)
        if (inputScale == 'F' || inputScale == 'f' ||
            inputScale == 'C' || inputScale == 'c' ||
            inputScale == 'K' || inputScale == 'k') {
            break;  // valid, so break out of loop
        } else {
            printf("Error: Invalid input scale '%c'. Must be F, C, or K.\n", inputScale);
        }
    }

    // repeatedly prompts for a valid target scale.
    while (1) {
        printf("Enter target scale (F, C, K): ");
        scanf(" %c", &targetScale);

        if (targetScale == 'F' || targetScale == 'f' ||
            targetScale == 'C' || targetScale == 'c' ||
            targetScale == 'K' || targetScale == 'k') {
            break;
        } else {
            printf("Error: Invalid target scale '%c'. Must be F, C, or K.\n", targetScale);
        }
    }

    // checks if the user is attempting to convert from a scale to the exact same scale If so, considered invalid.
    if ((inputScale == targetScale) ||
        (inputScale == targetScale + 32) ||
        (inputScale == targetScale - 32)) {
        printf("Error: Converting from %c to %c is invalid (same scale).\n", inputScale, targetScale);
        return 1;  // exits with an error code
    }

    // convert the input temperature to Celsius as an intermediate step so that it can then be converted to the desired target scale.
    float tempC;
    switch (inputScale) {
        case 'F':  // if input scale is Fahrenheit
        case 'f':
            tempC = fahrenheit_to_celsius(inputTemp);
            break;
        case 'C':  // if input scale is already Celsius
        case 'c':
            tempC = inputTemp;
            break;
        case 'K':  // input scale is Kelvin
        case 'k':
            tempC = kelvin_to_celsius(inputTemp);
            // checks if inputTemp corresponds to below absolute zero in Celsius
            if (tempC < -273.15f) {
                printf("Error: That Kelvin value is below absolute zero!\n");
                return 1;
            }
            break;
        default:
            // outdated but kept in for redundancy
            printf("Error: Invalid input scale '%c'. Must be F, C, or K.\n", inputScale);
            return 1;
    }

    // converts from the Celsius value to the target scale
    float converted;
    switch (targetScale) {
        case 'F':  // target scale: Fahrenheit
        case 'f':
            converted = celsius_to_fahrenheit(tempC);
            break;
        case 'C':  // target scale: Celsius
        case 'c':
            converted = tempC;  // already in Celsius
            break;
        case 'K':  // target scale: Kelvin
        case 'k':
            converted = celsius_to_kelvin(tempC);
            // validates that the resulting Kelvin is not below zero
            if (converted < 0.0f) {
                printf("Error: Resulting Kelvin is below zero, invalid conversion.\n");
                return 1;
            }
            break;
        default:
            // also outdated but kept in for redundancy
            printf("Error: Invalid target scale '%c'. Must be F, C, or K.\n", targetScale);
            return 1;
    }

    // print the conversion results to the user
    printf("\n--- Temperature Conversion ---\n");
    printf("Original: %.2f %c\n", inputTemp, inputScale);
    printf("Converted: %.2f %c\n", converted, targetScale);

    // categorizes the temperature based on the intermediate Celsius value (tempC) and display the advisory message.
    categorize_temperature(tempC);

    return 0;  // indicates successful program termination
}

// conversion functions implementation

// converts C to F
float celsius_to_fahrenheit(float c) {
    // formula: F = (9/5)*C + 32
    return (9.0f / 5.0f) * c + 32.0f;
}

// converts F to C
float fahrenheit_to_celsius(float f) {
    // Formula: C = (5.0/9.0)*(F - 32)
    return (5.0f / 9.0f) * (f - 32.0f);
}

// converts C to K
float celsius_to_kelvin(float c) {
    // Formula: K = C + 273.15
    return c + 273.15f;
}

// converts Kelvin to Celsius
float kelvin_to_celsius(float k) {
    // Formula: C = K - 273.15
    return k - 273.15f;
}

// categorization function

// categorizes the temperature in celsius and prints the advisory message.
void categorize_temperature(float celsius) {
    printf("\n--- Temperature Category ---\n");

    if (celsius < 0.0f) {
        printf("Category: Freezing\n");
        printf("Advisory: Wear a heavy coat. Do not stay outside for more than 30 minutes.\n");
    } else if (celsius < 10.0f) {
        printf("Category: Cold\n");
        printf("Advisory: Wear a light or medium jacket and pants.\n");
    } else if (celsius < 25.0f) {
        printf("Category: Comfortable\n");
        printf("Advisory: Beautiful weather today. Enjoy!\n");
    } else if (celsius < 35.0f) {
        printf("Category: Hot\n");
        printf("Advisory: Stay hydrated.\n");
    } else {
        printf("Category: Extreme Heat\n");
        printf("Advisory: Stay hydrated and remain indoors.\n");
    }
}

