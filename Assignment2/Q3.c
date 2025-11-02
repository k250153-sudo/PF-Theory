#include <stdio.h>
void update(int grid[3][3]) {
    int row,column,bit;
    printf("Enter Row Number: ");
    scanf("%d", &row);
    printf("Enter Column Number: ");
    scanf("%d", &column);
    printf("Do you want to set or clear ");
    switch (getchar()) {
        case 'c':
            case 'C':
            printf("Which bit do you want to clear(0--> Power Status 1--> Overload Warning 2--> Maintenance Required): ");
            scanf("%d",&bit);
            grid[row][column] &= ~(1 << bit);

        case 's':
            case 'S':
            printf("Which bit do you want to set(0--> Power Status 1--> Overload Warning 2--> Maintenance Required): ");
            scanf("%d",&bit);
            grid[row][column] |= (1 << bit);
    }
}
void query(int grid[3][3]) {
    int row,column,bit;
    printf("Enter Row Number: ");
    scanf("%d", &row);
    printf("Enter Column Number: ");
    scanf("%d", &column);
    int bit0 = (grid[row][column] >> 0) & 1;
    int bit1 = (grid[row][column] >> 1) & 1;
    int bit2 = (grid[row][column] >> 2) & 1;
    if (bit0 == 1) {
        printf("Power is ON\n");
    } else {
        printf("Power is OFF\n");
    }

    if (bit1 == 1) {
        printf("Overload Warning\n");
    }

    if (bit2 == 1) {
        printf("Maintenance Required \n");
    }
}
void diagnostics(int grid[3][3]) {
    int count=0;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            int bit1 = (grid[row][column] >> 1) & 1;
            int bit2 = (grid[row][column] >> 2) & 1;
            if (bit1==1 || bit2==1) {
                count++;
            }
        }
    }
    printf("The total number of sectors that that are currently overloaded or require maintenance are %d \n",count);
}
int main() {
    int grid[3][3] = {
        {1, 3, 5},
        {2, 4, 7},
        {0, 6, 1}
    };
    int function;
    do {
        printf("\n\nWhich of the following function do you want to perform:\n 1.Update a specific sector\n 2.Query about a specific sector\n 3.Diagnostic Report of the whole grid\n 4.Exit\nPlease enter the option number:");
        scanf("%d",&function);
        switch (function) {
            case 1:
                update(grid);
                break;
            case 2:
                query(grid);
                break;
            case 3:
                diagnostics(grid);
                break;
                case 4:
                printf("Exiting...\n");

        }
    } while (function != 4);
    return 0;
}
