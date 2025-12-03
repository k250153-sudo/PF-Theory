#include <stdio.h>
#include <string.h>


struct Book {
    int x,y,t; // t symbolizes last time a book is accessed.

};
 int findleastused(struct Book books[], int n) {
    int min=books[0].t,index=0;
    for(int i=1; i<n; i++) {
        if(books[i].t < min) {
            min = books[i].t;
            index = i;
        }
    }
     return index;
}
int findbook(struct Book books[], int n, int x) {
      int index=-1;
     for (int i = 0; i < n; i++) {
         if (books[i].x == x) {
             index = i;
             break;
         }
     }
     return index;
 }

int main() {
    int capacity,Q;
    char opr[10];
    int x,y,size=0,t=0;
     int j=0;
    scanf("%d %d",&capacity,&Q);
    struct Book books[capacity];
    for(int i=0;i<Q;i++) {
        scanf("%s",opr);
        if(strcmp(opr,"ADD")==0) {
            scanf("%d %d", &x, &y);
            j=findbook(books,size,x);
            if (j!=-1){
                books[j].y=y;
                books[j].t=t;
                t++;
            }
            else {
                if (size==capacity) {
                    j = findleastused(books, capacity);
                    books[j].x = x;
                    books[j].y = y;
                    books[j].t=t;
                    t++;
                } else {
                    books[size].x = x;
                    books[size].y = y;
                    books[size].t=t;
                    t++;
                    size++;
                }
            }

        }

        else if(strcmp(opr,"ACCESS")==0) {
            scanf("%d", &x);
            j=findbook(books,size,x);
            if (j!=-1) {
                printf("%d\n",books[j].y);
                books[j].t = t;
                t++;
            }
            else {
                printf("-1\n");
            }

        }
    }
     return 0;
}
// Input validations are not added assuming that input is correctly entered.