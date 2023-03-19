#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>
#include"struct.h"

void append(char* fileName, Country country){
    int fd = open(fileName, O_WRONLY | O_CREAT);
    lseek(fd, 0, SEEK_END);
    write(fd, &country, sizeof(Country)); 
    close(fd);
}

void printAll(char* fileName){
    printf("eeee");
    int fd = open(fileName, O_RDONLY);
    printf("%d", fd);
    size_t bytesRead;
    Country newCountry;
    do
    {
        printf("eeee");
        bytesRead = read(fd, &newCountry, sizeof(newCountry));
        if(bytesRead == sizeof(newCountry)){
            printf("Country: %s - ", newCountry.name);
            printf("population: %ld people, area: %ld units\n", newCountry.population, newCountry.area);
        }
    }while (bytesRead == sizeof(newCountry));
    close(fd);
}

void changeRecord(char* fileName){
    int fd = open(fileName, O_RDONLY);
    Country newCountry;
    size_t bytesRead;
    int isFound = 0;
    do
    {
        bytesRead = read(fd, &newCountry, sizeof(newCountry));
        if(strcmp(newCountry.name, "England") == 0){
            isFound = 1;
            break;
        }
    }while (bytesRead == sizeof(newCountry));
    close(fd);
    fd = open(fileName, O_WRONLY | O_CREAT);
    if(isFound){
        lseek(fd, sizeof(Country), SEEK_CUR);
        newCountry.area = 10;
        write(fd, &newCountry, sizeof(Country));
    }
    close(fd);
}

void openFile(char* fileName){
    int fd = open(fileName, O_WRONLY | O_CREAT);
    Country country;
    country.name = "Russia";
    country.area = 100000;
    country.population = 2000000;
    write(fd, &country, sizeof(Country));
    country.name = "England";
    write(fd, &country, sizeof(Country));
    fd = open(fileName, O_RDONLY);
    Country newCountry;
    size_t bytesRead;
    int isFound = 0;
    do
    {
        bytesRead = read(fd, &newCountry, sizeof(newCountry));
        if(strcmp(newCountry.name, "England") == 0){
            isFound = 1;
            break;
        }
    }while (bytesRead == sizeof(newCountry));
    close(fd);
    fd = open(fileName, O_WRONLY | O_CREAT);
    if(isFound){
        //printf("Country: %s - ", newCountry.name);
        //printf("population: %ld people, area: %ld units\n", newCountry.population, newCountry.area);
        lseek(fd, sizeof(Country), SEEK_CUR);
        newCountry.area = 10;
        write(fd, &newCountry, sizeof(Country));
    }
    close(fd);
}