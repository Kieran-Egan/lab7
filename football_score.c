/*
File Name: football_score.c

Description:
    This program asks the user to enter an NFL score, then prints all possible ways to achieve that score using:
        - TD + 2-pt (8 points)
        - TD + 1-pt (7 points)
        - TD only   (6 points)
        - Field Goal (3 points)
        - Safety     (2 points)

    Entering 0 or 1 stops the program.
*/

#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    int score;  // holds the user-input NFL score

    // loop that runs indefinitely until the user enters 0 or 1, when loop breaks.
    while (true)
    {
        // prompts the user for the NFL score
        printf("Enter the NFL score (enter 0 or 1 to STOP): ");
        scanf("%d", &score);

        // if the user enters 0 or 1, we stop immediately.
        if (score == 0 || score == 1) {
            printf("Program stopped.\n");
            break;  // Exit the while(true) loop
        }

        // checks if the user entered a negative number. If yes, prints an error and prompt again (continue the loop).
        if (score < 0) {
            printf("Invalid score. Score cannot be negative.\n\n");
            continue;  // skips the rest of this iteration
        }

        // prints a heading before listing the possible scoring combinations.
        printf("\nPossible combinations of scoring plays if a team’s score is %d:\n\n", score);

        // tracks how many valid scoring combinations we find.
        int combinationCount = 0;

        // brute-force tp find all combinations of the scoring plays:

        // each loop increments the number of a particular scoring play from 0 up to a limit so that we never exceed the user-entered score.
        for (int eight = 0; 8 * eight <= score; eight++) {
            for (int seven = 0; 8 * eight + 7 * seven <= score; seven++) {
                for (int six = 0; 8 * eight + 7 * seven + 6 * six <= score; six++) {
                    for (int three = 0; 8 * eight + 7 * seven + 6 * six + 3 * three <= score; three++) {
                        for (int two = 0; 8 * eight + 7 * seven + 6 * six + 3 * three + 2 * two <= score; two++) {
                            
                            // calculates the total score for the current combination
                            int total = 8*eight + 7*seven + 6*six + 3*three + 2*two;

                            // if this combination matches the user’s score exactly, we print it out in the desired format.
                            if (total == score) {
                                combinationCount++;
                                printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n",
                                       eight, seven, six, three, two);
                            }
                        }
                    }
                }
            }
        }

        // if no combination was found that summed to the user’s score (which shouldn’t happen if the score ≥ 2), we let the user know.
        if (combinationCount == 0) {
            printf("No combinations found for %d (unexpected if score >= 2).\n", score);
        }

        // prints a blank line before prompting for another score
        printf("\n");
    }

    return 0;  // indicates successful program termination
}
