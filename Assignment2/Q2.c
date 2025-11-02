#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void get_customer_info(char name[], char cnic[]) {
    printf("Enter customer name: ");
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Enter customer CNIC number: ");
    fgets(cnic, 20, stdin);
    cnic[strcspn(cnic, "\n")] = '\0';
}

int is_number(const char *str) {
    if (*str == '\0') return 0;
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}

void display_inventory(int inventory[][3]) {
    printf("Product Code|Quantity in Stock|Price Per Product|\n");
    for (int row = 0; row <4; row++) {
        for (int col = 0; col < 3; col++) {
            printf("\t%d\t\t|", inventory[row][col]);
        }
        printf("\n");
    }
}

void add_item(int cart[][2], int t_products) {
    char input[20];
    int product, quantity;
    for (int row = 0; row < t_products; row++) {
        while (1) {
            printf("Enter the product code: ");
            if (!fgets(input, sizeof(input), stdin)) {
                printf("Error reading input. Please try again.\n");
                continue;
            }
            input[strcspn(input, "\n")] = '\0';
            if (is_number(input)) {
                product = atoi(input);
                break;
            } else {
                printf("Invalid input. Please enter a numeric product code.\n");
            }
        }
        while (1) {
            printf("Enter the quantity: ");
            if (!fgets(input, sizeof(input), stdin)) {
                printf("Error reading input. Please try again.\n");
                continue;
            }
            input[strcspn(input, "\n")] = '\0';
            if (is_number(input)) {
                quantity = atoi(input);
                break;
            } else {
                printf("Invalid input. Please enter a numeric quantity.\n");
            }
        }
        cart[row][0] = product;
        cart[row][1] = quantity;
    }
}

int order_confirmed(int cart[][2], int t_products, int inventory[][3]) {
    int bill=0;
    for (int row = 0; row < t_products; row++) {
        for (int row_i =0; row_i < 4; row_i++) {
            if (cart[row][0] == inventory[row_i][0]) {
                inventory[row_i][1] -= cart[row][1];
                bill += cart[row][1]*inventory[row_i][2];
            }
        }
    }
    return bill;
}

float display_bill(int bill) {
    char reply[10];
    float disc =0;
    const char promo_code[] = "eid2025";

    printf("\nWe have a special Eid 2025 offer! Do you have the promo code? (yes/no): ");
    if (fgets(reply, sizeof(reply), stdin) == NULL) {
        printf("Error reading input.\n");
        return 0;
    }
    reply[strcspn(reply, "\n")] = '\0';

    if (strcasecmp(reply, "yes") == 0) {
        char user_code[20];

        printf("Please enter the promo code: ");
        if (fgets(user_code, sizeof(user_code), stdin) == NULL) {
            printf("Error reading input.\n");
            return 0;
        }
        user_code[strcspn(user_code, "\n")] = '\0';

        if (strcmp(user_code, promo_code) == 0) {
            printf("Promo code applied! You get a special discount.\n");
            disc = bill*0.75;
        } else {
            printf("Invalid promo code.\n");
        }
    } else if (strcasecmp(reply, "no") == 0) {
        printf("No worries! You can still enjoy our regular offer.\n");
    } else {
        printf("Invalid response. Please answer 'yes' or 'no'.\n");
    }
    return disc;
}

void show_invoice(int cart[][2], float disc, int bill) {
    printf("Your items\n Product code\t|Quantity\t|\n");
    for (int row = 0; row < 3; row++) {
        printf("%d\t\t|%d\t|\n", cart[row][0], cart[row][1]);
    }
    if (disc != 0) {
        printf("Your bill without discount is: %d\nYour bill after discount is %.2f", bill, disc);
    }
    else {
        printf("Your bill is:%d", bill);
    }
}

int main() {
    char name[50];
    char cnic[20];
    int products, bill ;
    float disc;
    char input[20];
    int inventory[4][3] = {
        {1, 50, 100},
        {2, 10, 200},
        {3, 20, 300},
        {4, 8, 150}
    };
    get_customer_info(name, cnic);
    display_inventory(inventory);

    while (1) {
        printf("Enter the amount of unique products you would like to buy (maximum 4): ");
        if (!fgets(input, sizeof(input), stdin)) {
            printf("Error reading input. Please try again.\n");
            continue;
        }
        input[strcspn(input, "\n")] = '\0';
        if (is_number(input)) {
            products = atoi(input);
            if (products <= 0) {
                printf("Please enter a positive number.\n");
            } else if (products > 4) {
                printf("You can buy at most 4 unique products. Please enter a number between 1 and 4.\n");
            } else {
                break;
            }
        } else {
            printf("Invalid input. Please enter a numeric value.\n");
        }
    }

    int cart[products][2];
    add_item(cart, products);

    char reply[10];
    printf("\nIs your order confirmed? ");
    if (!fgets(reply, sizeof(reply), stdin)) {
        printf("Error reading input.\n");
        return 1;
    }
    reply[strcspn(reply, "\n")] = '\0';

    if (strcasecmp(reply, "yes") == 0) {
        bill = order_confirmed(cart, products, inventory);
        disc = display_bill(bill);
        show_invoice(cart, disc, bill);
    }
    else if (strcasecmp(reply, "no") == 0) {
        printf("No worries! Enjoy.\n");
    } else {
        printf("Invalid response.\n");
    }
    printf("Inventory after the order.");
    display_inventory(inventory);
}