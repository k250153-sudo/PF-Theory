#include <stdio.h>
#include <string.h>

void encodeMessage(char arr[]) {
    int counter = 0;
    char ch;
    printf("Enter a message to encode: ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    while (counter < 100)
    {
        ch = getchar();
        if (ch == '\n')
        {
            break;
        }
        else{
            arr[counter] = ch;
            counter++;
        }
    }
    arr[counter] = '\0';
    int length = counter;

    // Reverse the string
    for (int i = 0; i < length/2; i++)
    {
        char temp = arr[i];
        arr[i] = arr[length - i - 1];
        arr[length - i - 1] = temp;
    }
    for (int i = 0; i < length; i++) {
        unsigned char c = arr[i];
        c = c ^ (1 << 1);
        c = c ^ (1 << 4);
        arr[i] = c;
    }
    printf("\nEncoded string: ");
    for (int i = 0; i < length; i++) {
        printf("%c", arr[i]);
    }
    printf("\n");

    printf("Encoded (HEX) for safe copy-paste: ");
    for (int i = 0; i < length; i++) {
        printf("%02X ", (unsigned char)arr[i]);
    }
    printf("\n");
}

void decodeMessage(char arr[]) {
    int counter = 0;
    char ch;
    int choice_input;

    printf("Enter 1 for normal text or 2 for HEX input: ");
    scanf("%d", &choice_input);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    if (choice_input == 2) {
        printf("Enter the HEX encoded message (space-separated): ");
        char hex_line[500];
        fgets(hex_line, sizeof(hex_line), stdin);
        char *ptr = hex_line;
        unsigned int hex_val;
        while (sscanf(ptr, "%X", &hex_val) == 1 && counter < 100) {
            arr[counter] = (char)hex_val;
            counter++;
            while (*ptr == ' ') ptr++;
            while (*ptr != ' ' && *ptr != '\n' && *ptr != '\0') ptr++;
        }
    } else {
        printf("Enter a message to decode: ");
        while (counter < 100)
        {
            ch = getchar();
            if (ch == '\n')
            {
                break;
            }
            else{
                arr[counter] = ch;
                counter++;
            }
        }
    }

    arr[counter] = '\0';
    int length = counter;
    for (int i = 0; i < length; i++) {
        unsigned char c = arr[i];
        c = c ^ (1 << 1);
        c = c ^ (1 << 4);
        arr[i] = c;
    }
    for (int i = 0; i < length/2; i++)
    {
        char temp = arr[i];
        arr[i] = arr[length - i - 1];
        arr[length - i - 1] = temp;
    }
    printf("\nDecoded string: %s\n", arr);
}

int main() {
    char arr[100];
    int choice;
    do {
        printf("\nWhat would you like to do:\n 1.Encode a message\n 2.Decode a message\n 3.Exit\nPlease enter the option number: ");
        scanf("%d",&choice);

        switch (choice) {
            case 1:
                encodeMessage(arr);
                break;
            case 2:
                decodeMessage(arr);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
                while (getchar() != '\n');
        }
    }
    while (choice!=3);

    return 0;
}
// Use the HEX only code for decoding.