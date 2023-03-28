#include <stdio.h>
#include<stdlib.h>
#include"fileProc.c"
#include"main.h"


void printMenu()
{
    printf("_____________________MENU________________________\n");
    printf("1 - to add a new record\n");
    printf("2 - to modify a record\n");
    printf("3 - to delete a record\n");
    printf("4 - to read a record\n");
    printf("5 - to show records\n");
    printf("6 - to get a list of the most populous countries\n");
    printf("7 - to sort countries by their population\n");
    printf("8 - to exit\n");
    printf("_________________________________________________\n");
}

int main(){
    Node* head = NULL;
    int end = 0;
    while(end == 0)
    {
        printMenu();
        int command = 0;
        int res = 0;
        while(res == 0)
        {
            printf("Your command: ");
            res = InputInt(&command);
        }
        if(command == 1)
        {
            addRecord();
        }
        else if(command == 2)
        {
        }
        else if(command == 3)
        {
            deleteCountry(&head);
        }
        else if(command == 4)
        {

        }
        else if(command == 5)
        {
            findCountry(head);
        }
        else if(command == 6)
        {
            getTheMostPopulous(head);
        }
        else if(command == 7)
        {
            getHightPopulate(head);
        }
        else if(command == 8)
        {
            freeCountries(head);
            end = 1;
        }
    }
    return 0;
}
