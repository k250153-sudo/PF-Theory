#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Employee {
    int ID;
    char name[50];
    char designation[50];
    int salary;
};
void displayEmployees(struct Employee e[],int n) {
    printf("---------------------------------------------------------------\n");
    printf("| %-10s | %-15s | %-15s | %-10s |\n", "ID", "Name", "Designation", "Salary");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("| %-10d | %-15s | %-15s | %-10d |\n",
               e[i].ID,
               e[i].name,
               e[i].designation,
               e[i].salary);
    }
    printf("---------------------------------------------------------------\n");
    return;
}
void findHighestSalary(struct Employee e[],int n) {
    int max=e[0].salary;
    int index=0;
    for (int i = 1; i < n; i++) {
        if (e[i].salary>max) {
            max = e[i].salary;
            index = i;
        }
    }
    printf("Highest Salary is of: ");
    printf("| %-10s | %-15s | %-15s | %-10s |\n", "ID", "Name", "Designation", "Salary");
    printf("| %-10d | %-15s | %-15s | %-10d |\n",
               e[index].ID,
               e[index].name,
               e[index].designation,
               e[index].salary);


}
void searchbyid(struct Employee e[],int n,int id) {
    for (int i = 0; i < n; i++) {
        if (e[i].ID == id) {
            printf("| %-10s | %-15s | %-15s | %-10s |\n", "ID", "Name", "Designation", "Salary");
            printf("---------------------------------------------------------------\n");
            printf("| %-10d | %-15s | %-15s | %-10d |\n",
              e[i].ID,
              e[i].name,
              e[i].designation,
              e[i].salary);
            break;
        }
    }
}void searchbyname(struct Employee e[],int n,char name[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(e[i].name, name) == 0) {
            printf("| %-10s | %-15s | %-15s | %-10s |\n", "ID", "Name", "Designation", "Salary");
            printf("---------------------------------------------------------------\n");
            printf("| %-10d | %-15s | %-15s | %-10d |\n",
              e[i].ID,
              e[i].name,
              e[i].designation,
              e[i].salary);
            break;
        }
    }
}

int main() {
    int n;
    printf("Enter Number of Employees: ");
    scanf("%d",&n);
    while (getchar() != '\n');
    struct Employee employees[n];
    for (int i = 0; i < n; i++) {
        printf("Enter Employee %d ID: ",i+1);
        scanf("%d",&employees[i].ID);
        while (getchar() != '\n');
        printf("Enter Employee %d Name: ",i+1);
        fgets(employees[i].name, 50, stdin);
        employees[i].name[strcspn(employees[i].name, "\n")] = '\0';
        printf("Enter Employee %d Designation: ",i+1);
        fgets(employees[i].designation, 50, stdin);
        employees[i].designation[strcspn(employees[i].designation, "\n")] = '\0';
        printf("Enter Employee %d Salary: ",i+1);
        scanf("%d",&employees[i].salary);
        while (getchar() != '\n');
    }
    displayEmployees(employees,n);
    findHighestSalary(employees,n);
}
/*
To modify the existing program to give a 10% salary bonus to employees whose salary is below a certain threshold,
we can create a separate function, for example `giveBonus`, which takes the array of employee structures,
the number of employees, and the threshold salary as parameters.

Since arrays are passed by reference in C, any changes made to the employee salaries inside this function
will directly update the original array. Inside the function, we can loop through all the employees and
check each employee’s salary. If the salary is less than the threshold, we increase it by 10%.

After calling this function in the main program, the salaries of all eligible employees would be updated
automatically, and the updated salaries can then be displayed using the existing display function.
*/

