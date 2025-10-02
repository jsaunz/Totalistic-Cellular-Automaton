//Totalistic Cellular Automaton

/*-------------------------------------------
Project 1: Totalistic Cellular Automaton
	Simulates a one-dimensional cellular automaton 
    that evolves cells based on user-specified rules, 
    displaying the world evolution and accumulated 
    cell counts across generations.
Course: CS 211, Fall 2025, UIC
Author: Jamila Saunders
------------------------------------------- */

#include <stdio.h>
#include <stdbool.h>

const int WORLD_SIZE = 65;

typedef struct cell_struct{
    int localSum; // total sum of local cells, [left] + [me] + [right]: possible values are 0-6
    int status;   // this cell's current status: 0, 1, or 2
    int count;    // running accumulated count of this cell's active status for all generations
} cell;

// converts rule into base-3 representation, stores into valArray[], true if valid, false if not

bool setValArray(int valArray[7], int rule) {
    if (rule < 0 || rule > 2186) {
        return false;
    }
    for (int i = 0; i < 7; i++) {
        valArray[i]  = rule % 3;
        rule = rule / 3;
    }
    return true;
}

void task3(int valArray[7]) {
    for (int i = 6; i >= 0; i--) {
        if (valArray[i] == 0) {
            printf("| |     ");
        }
        else if (valArray[i] == 1) {
            printf("|-|     ");
        }
        else if (valArray[i] == 2) {
            printf("|+|     ");
        }
    }
    printf("\n\n");
}

// updates the subitems for each cell in world based on local statuses

void setSums(cell world[WORLD_SIZE]) {
    for (int i = 0; i < 65; i++) {
        world[i].localSum = world[i - 1].status + world[i].status + world[i + 1].status;
    }
    world[64].localSum = world[63].status + world[64].status + world[0].status;
    world[0].localSum = world[64].status + world[0].status + world[1].status;

    return;
}

// evolves the world to next gen by updating cell status and using its localSum
// updated count for all cells
// returns total sum for all status values after evolution step

int evolveWorld(cell world[WORLD_SIZE], int ruleValArray[7]) {
    int newStatusArray[WORLD_SIZE];
    int totalSum = 0;

    for (int i = 0; i < WORLD_SIZE; i++) {
        int sum = world[i].localSum; // finding local sum of all cells in gen
        int newStatus = ruleValArray[sum]; // next status = valArray[sum] (locates status at the index = sum)
        newStatusArray[i] = newStatus;
    }
    for (int i = 0; i < WORLD_SIZE; i++) {
        world[i].status = newStatusArray[i];
        world[i].count += world[i].status;
        totalSum += world[i].status;
    }
    return totalSum;
}


int main() {
    cell world[WORLD_SIZE];

    printf("Welcome to the Totalistic Cellular Automaton!\n");

    printf("Enter the rule # (0-2186): \n");

    // task 2

    int userRule;

    scanf("%d", &userRule);

    while (userRule < 0 || userRule > 2186) {
        printf("Enter the rule # (0-2186): \n");
        scanf("%d", &userRule);
    }
    
    int valArray[7];

    setValArray(valArray, userRule);
    
    printf("\nThe value array for rule #%d is ", userRule);

    for (int i = 6; i >= 0; i--) {
        printf("%d", valArray[i]);
    }
    printf("\n\n");



    printf("The evolution of all possible states are as follows:\n");
    printf("Local Sum:   6       5       4       3       2       1       0      \n");
    printf("States:    |+++|   |++-|   |++ |   |+- |   |-- |   |-  |   |   |    \n");
    printf("                   |+-+|   |+ +|   |+ -|   |- -|   | - |            \n");
    printf("                   |-++|   | ++|   |-+ |   | --|   |  -|            \n");
    printf("                           |+--|   | +-|   |+  |                    \n");
    printf("                           |-+-|   |- +|   | + |                    \n");
    printf("                           |--+|   | -+|   |  +|                    \n");
    printf("                                   |---|                            \n");
    printf("New Status: ");      

    // task 3
    
    task3(valArray);

    printf("Enter the number of generations (1-49): ");     
    
    // task 5a

    int numGenerations;
    scanf("%d", &numGenerations);
    printf("\n");
    while (numGenerations < 1 || numGenerations > 49) {
        printf("Enter the number of generations (1-49): ");
        scanf("%d", &numGenerations);
        printf("\n");
    }

    // task 5b

    printf("Enter the value (1 or 2) for the initial active cell: ");
    printf("\n");

    int middleStatus;
    scanf("%d", &middleStatus);
    while (middleStatus < 1 || middleStatus > 2) {
        printf("Enter the value (1 or 2) for the initial active cell: ");
        printf("\n");
        scanf("%d", &middleStatus);
    }

    // initialize the world

    for (int i = 0; i < 65; i++) {
        world[i].status = 0;
        world[i].count = 0;
    }

    world[32].status = middleStatus;
    world[32].count = middleStatus;

    printf("Initializing world & evolving...\n");
    // task 5c

    char midCell;

    if (middleStatus == 1) {
        midCell = '-';
    }
    else if (middleStatus == 2) {
        midCell = '+';
    }
    printf("%33c", midCell);
    for (int i = 0; i < 33; i++) {
        printf(" ");
    }

    setSums(world);

    // adding up total sum of statuses for a generation

    int genTotal = 0;
    for (int i = 0; i < WORLD_SIZE; i++) {
        genTotal += world[i].status;
    }

    printf("%-2d", genTotal);

    // task 7

    for (int i = 0; i < (numGenerations - 1); i++) {
        int sum = evolveWorld(world, valArray);
        setSums(world); // getting local sums for use in next gen
        for (int j = 0; j < WORLD_SIZE; j++) {
            if (world[j].status == 0) {
                printf(" ");
            }
            else if (world[j].status == 1) {
                printf("-");
            }
            else if (world[j].status == 2) {
                printf("+");
            }
        }
        printf(" ");
        printf("%2d \n", sum);
    }

    for (int i = 0; i < WORLD_SIZE; i++) {
        printf("_");
    }
    printf("\n");

    // task 8

    for (int i = 0; i < WORLD_SIZE; i++) {
        if (world[i].count == 0) {
            printf(" ");
        }
        else if (world[i].count < 10) {
            printf(" ");
        }
        else {
            printf("%d", world[i].count / 10);
        }
    }
    printf("\n");

    for (int i = 0; i < WORLD_SIZE; i++) {
        if (world[i].count == 0) {
            printf(" ");
        }
        else {
            printf("%d", world[i].count % 10);
        }
    }
    
    printf("\n");

    return 0;
}
