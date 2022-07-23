#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>
#include "utf8.h"
#include "stack.h"

/* Hand instructions codepoints */
#define INCREMENT 0x1f446
#define DECREMENT 0x1f447
#define MOVEFORWARD 0x1f449
#define MOVEBACKWARDS 0x1f448
#define LOOPSTART 0x1f91c
#define LOOPEND 0x1f91b
#define PRINT 0x1f44a

void print_hand_instruction(char *);
int get_number_of_instructions(char *);
bool get_instructions(char *, char [][5]);

int main(void)
{
    int number_of_instructions, counter = 0, pointer = 0, loop_start;
    unsigned char memory[400];
    Node *stack = NULL;
    uint32_t codepoint;

    number_of_instructions = get_number_of_instructions("input.hand");

    /* Declaring the array of instructions */
    char instructions[number_of_instructions][5];

    /* Array of loops */
    int loops[number_of_instructions];

    /* Filling the array of instructions */
    get_instructions("input.hand", instructions);

    /* Indexing loops */
    for (counter = 0; counter < number_of_instructions; counter++) {
        codepoint = to_cp(instructions[counter]);

        switch (codepoint) {
            case LOOPSTART:
                stack = push(stack, counter);
                break;
            case LOOPEND:
                loop_start = pop(&stack);
                loops[loop_start] = counter;
                loops[counter] = loop_start;
                break;
        }
    }

    /* Start of execution */
    for (counter = 0; counter < number_of_instructions; counter++) {
        codepoint = to_cp(instructions[counter]);

        switch (codepoint) {
            case INCREMENT:
                memory[pointer] += 1;
                break;
            case DECREMENT:
                memory[pointer] -= 1;
                break;
            case MOVEFORWARD:
                pointer += 1;
                break;
            case MOVEBACKWARDS:
                pointer -= 1;
                break;
            case LOOPSTART:
                if (memory[pointer] == 0) {
                    counter = loops[counter];
                }
                break;
            case LOOPEND:
                if (memory[pointer] != 0) {
                    counter = loops[counter];
                }
                break;
            case PRINT:
                printf("%c", memory[pointer]);
                break;
        }
    }

    free_stack(&stack);

    return 0;
}

void print_hand_instruction(char *hand_instruction)
{
    int index;

    for (index = 0; index < 5; index++) {
        printf("%c", hand_instruction[index]);
    }
}

int get_number_of_instructions(char *source)
{
    FILE *hand = NULL;
    int number_of_instructions = 0;

    /* Opening the source file in read-only mode */
    hand = fopen(source, "r");

    if (hand == NULL) {
        return -1;
    }

    /* Computing the number of instructions */
    while (fgetc(hand) != EOF) {
        number_of_instructions += 1;
    }

    number_of_instructions /= 4;

    if (fclose(hand) != 0) {
        return -1;
    }

    return number_of_instructions;
}

bool get_instructions(char *source, char instructions[][5])
{
    int counter = 0, index = 0;
    char character;

    FILE *hand = fopen(source, "r");

    if (hand == NULL) {
        return false;
    }

    /* Filling the array of instructions */
    while ((character = fgetc(hand)) != EOF) {
        instructions[counter][index % 4] = character;

        if ((index % 4) == 3) {
            instructions[counter][4] = '\0';
            counter += 1;
        }

        index += 1;
    }

    /* Closing the .hand file */
    if (fclose(hand) != 0) {
        return false;
    }

    return true;
}
