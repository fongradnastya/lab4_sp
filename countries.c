#include<stdio.h>
#include<stdlib.h>
#include"struct.h"
#include"countries.h"
#include"input.c"

Country getCountry()
{
    printf("Please, enter the country name: ");
    char* name = GetString();
    long population;
    int res = 0;
    while(res != 1)
    {
        printf("Please, enter the country population: ");
        res = InputLong(&population);
        if(res == 0)
        {
            printf("This value should be digit!\n");
        }
        else if(res == -1)
        {
            printf("This value should be positive!\n");
        }
    }
    long area;
    res = 0;
    while(res != 1)
    {
        printf("Please, enter the country area: ");
        res = InputLong(&area);
        if(res == 0)
        {
            printf("This value should be digit!\n");
        }
        else if(res == -1)
        {
            printf("This value should be positive!\n");
        }
    }
    Country newCountry;
    newCountry.name = name;
    newCountry.area = area;
    newCountry.population = population;
    return newCountry;
}

Node* createNewNode(Country country)
{
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL)
    {
        printf("Unpossible to allocate memory\n");
        exit(1);
    }
    node->value = country;
    node->next = NULL;
    return node;
}

Node* getTail(Node* head)
{
    Node* temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    return temp;
}

int getCountriesQuantity(Node* head)
{
    if(head == NULL)
    {
        return 0;
    }
    int cnt = 1;
    Node* temp = head;
    while(temp->next != NULL)
    {
        cnt++;
        temp = temp->next;
    }
    return cnt;
}

void appendCountry(Node** head, Node* newNode)
{
    if(*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        Node* tail = getTail(*head);
        tail->next = newNode;
    }
}

void deleteCountry(Node** head)
{
    Node* temp = *head;
    Node* prevNode = NULL;
    printf("Please, enter the country name:");
    char* name = GetString();
    if (temp == NULL)
    {
        printf("Nothing to delete\n");
    }
    else if (strcmp(temp->value.name, name) == 0)
    {
        *head = (*head)->next;
        printf("The country was successfully deleted\n");
    }
    else
    {
        while(temp->next != NULL)
        {
            if(strcmp(temp->value.name, name) == 0)
            {
                prevNode = temp;
                break;
            }
            temp = temp->next;
        }
        if(prevNode == NULL)
        {
            printf("There are no countries with such name\n");
        }
        else
        {
            Node* currNode = prevNode->next;
            prevNode->next = currNode->next;
            printf("The country was successfully deleted\n");
        }
    }
}

void printCountry(Country country)
{
    printf("Country: %s - ", country.name);
    printf("population: %ld people, area: %ld units\n", country.population, country.area);
}


void printAllCountries(Node* head)
{
    if(head == NULL)
    {
        printf("There are no countries yet\n");
    }
    else
    {
        printf("__________________COUNTRIES______________________\n");
        while(head != NULL)
        {
            printCountry(head->value);
            head = head->next;
        }
        printf("_________________________________________________\n");
    }
}

Node* findCountry(Node* head)
{
    printf("Please, enter the country name:");
    char* name = GetString();
    while(head != NULL)
    {
        if(strcmp(head->value.name, name) == 0)
        {
            printCountry(head->value);
            return head;
        }
        head = head->next;
    }
    printf("Country %s wasn't found\n", name);
    return NULL;
}

void printChangeMenu()
{
    printf("___________________CHANGE_MENU___________________\n");
    printf("1 - to change a country name\n");
    printf("2 - to change a country population\n");
    printf("3 - to change a country area\n");
    printf("_________________________________________________\n");
}

void changeCountry(Node** head)
{
    Node* node = findCountry(*head);
    if(node != NULL)
    {
        printChangeMenu();
        int command;
        int res = 0;
        while(res == 0)
        {
            printf("Your command: ");
            res = InputInt(&command);
        }
        if(command == 1)
        {
            printf("Please, enter the country name: ");
            char* name = GetString();
            node->value.name = name;
        }
        else if(command == 2)
        {
            long population;
            int res = 0;
            while(res != 1)
            {
                printf("Please, enter the country population: ");
                res = InputLong(&population);
                if(res == 0)
                {
                    printf("This value should be digit!\n");
                }
                else if(res == -1)
                {
                    printf("This value should be positive!\n");
                }
            }
            node->value.population = population;
        }
        else if(command == 3)
        {
            long area;
            res = 0;
            while(res != 1)
            {
                printf("Please, enter the country area: ");
                res = InputLong(&area);
                if(res == 0)
                {
                    printf("This value should be digit!\n");
                }
                else if(res == -1)
                {
                    printf("This value should be positive!\n");
                }
            }
            node->value.area = area;
        }
        else
        {
            printf("Wrong command\n");
        }
    }
}

void freeCountries(Node* head)
{
    Node* current = head;
    Node* next;
    while (current != NULL)
    {
        next = current->next;
        free(current->value.name);
        free(current);
        current = next;
    }
}

Node* sort( Node* root )
{
    Node *new_root = NULL;
    while ( root != NULL )
    {
        Node *node = root;
        root = root->next;
        if ( new_root == NULL || node->value.population < new_root->value.population)
        {
            node->next = new_root;
            new_root = node;
        }
        else
        {
            Node *current = new_root;
            while ( current->next != NULL && !( node->value.population < current->next->value.population ) )
            {                   
                current = current->next;
            }                
            node->next = current->next;
            current->next = node;
        }
    }
    return new_root;
}

void getHightPopulate(Node* head)
{
    long minPopulation;
    int res = 0;
    while(res != 1)
    {
        printf("Please, enter min population: ");
        res = InputLong(&minPopulation);
        if(res == 0)
        {
            printf("This value should be digit!\n");
        }
        else if(res == -1)
        {
            printf("This value should be positive!\n");
        }  
    }
    Node* temp = head;
    Node* highest = NULL;
    while(temp != NULL)
    {
        if(temp->value.population >= minPopulation)
        {
            Node* newNode = createNewNode(temp->value);
            appendCountry(&highest, newNode);
        }
        temp = temp->next;
    }
    printAllCountries(highest);
    sort(highest);
    printAllCountries(highest);
}

void getTheMostPopulous(Node* head)
{
    long maxDensity = 0;
    Node* temp = head;
    while(temp != NULL)
    {
        long density = temp->value.population / temp->value.area;
        if(density > maxDensity)
        {
            maxDensity = density;
        }
        temp = temp->next;
    }
    printf("Max population density is %ld people per unit\n", maxDensity);
    printf("Countries:\n");
    temp = head;
    while(temp != NULL)
    {
        long density = temp->value.population / temp->value.area;
        if(density == maxDensity)
        {
            printCountry(temp->value);
        }
        temp = temp->next;
    }
}