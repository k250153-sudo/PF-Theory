#include <stdio.h>

void add_books(int isbns[100],char titles[100][50],float prices[100],int quantities[100],int *top);
void process_sale(int isbns[], char titles[][50], float prices[], int quantities[], int *top);
void display_books(int top,int quantities[],int isbns[], char titles[][50], float prices[]);

int main() {
    int isbns[100];
    char titles[100][50];
    float prices[100];
    int quantities[100];
    int top=0;
    int input;

    do{
        printf("Please enter:\n 1--> Add a new book. \n 2--> Process a sale.\n 3-->Low Stock Report.\n 4--> Exit \n Enter option number only");
        scanf("%d",&input);
    switch (input) {
        case 1:
            add_books(isbns,titles,prices,quantities,&top);
            break;
        case 2:
            process_sale(isbns,titles,prices,quantities,&top);
            break;
        case 3:
            display_books(top,quantities,isbns,titles,prices);
            break;
        case 4:
            printf("Exiting...\n");
            break;
    }


    }while(input!=4);
    return 0;
}

void add_books(int isbns[100],char titles[100][50],float prices[100],int quantities[100],int *top) {
    if (*top >= 100) {
        printf("Inventory full. Cannot add more books.\n");
        return;
    }
    long long check;
    int valid = 0;
    while (!valid) {
        printf("Enter ISBN: ");
        if (scanf("%lld", &check) != 1) {
            while(getchar() != '\n');
            printf("Invalid input. Please enter numeric ISBN.\n");
            continue;
        }
        long long temp = check;
        int length = 0;
        if (temp == 0) length = 1;
        else {
            while (temp != 0) {
                temp /= 10;
                length++;
            }
        }
        if (length != 13) {
            printf("ISBN length is not 13\n");
            continue;
        }
        int duplicate = 0;
        for (int n = 0; n < *top; n++) {
            if (isbns[n] == check) {
                printf("The same ISBN exists\n");
                duplicate = 1;
                break;
            }
        }
        if (duplicate) continue;

        valid = 1;
    }
    isbns[*top] = (int)check;
    while(getchar() != '\n');

    printf("Enter book title: ");
    scanf(" %[^\n]", titles[*top]);
    printf("Enter price and quantity: ");
    scanf("%f %d",&prices[*top],&quantities[*top]);

    (*top)++;
}

void process_sale(int isbns[], char titles[][50], float prices[], int quantities[], int *top) {
    printf("Enter the ISBN and number of copies sold\n");
    int t_isbn, t_num;
    scanf("%d %d",&t_isbn,&t_num);
    for (int n =0; n<*top; n++) {
        if (isbns[n]==t_isbn) {
            if (quantities[n]==0) {
                printf("Book is out of stock\n");
                return;
            }
            if (quantities[n]<t_num) {
                printf("Only %d copies are available. Sale cannot be processed.\n", quantities[n]);
                return;
            }
            quantities[n] -= t_num;
            printf("Sale processed successfully. %d copies remaining.\n", quantities[n]);
            return;
        }
    }
    printf("The book is not available in our store.\n");

}

void display_books(int top,int quantities[],int isbns[], char titles[][50], float prices[]) {
    printf("Low Stock Report:\n");
    int found = 0;
    for (int n = 0; n<top; n++) {
        if (quantities[n] < 5) {
            printf("%d. ISBN: %d \nName:%s \n Quantity Available:%d\n Price:%.2f\n",n+1,isbns[n],titles[n],quantities[n],prices[n]);
            found = 1;
        }

    }
    if (!found) {
        printf("No books are currently low in stock.\n");
    }
}
