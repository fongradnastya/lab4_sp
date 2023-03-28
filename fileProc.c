#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include<fcntl.h>
#include <string.h>
#include"countries.c"


char* inputFileName(){
    char* fileName;
    int res = 0;
    while(res != 1)
    {
        printf("Please, enter a file name: ");
        fileName = GetString();
        int len = strlen(fileName); // Получаем длину имени файла
        char *ext = fileName + len - 4; // Получаем расширение файла
        if (strcmp(ext, ".txt") == 0 || strcmp(ext, ".bin") == 0)
        {
            res = 1;
        }
        else{
            printf("Wrong file extension. Pleade, try again\n");
        }
    }
    return fileName;
}

int openFile(int mode, char* fileName){
    int fileDescriptor;
    if(mode == 1)
    {
        fileDescriptor = open(fileName, O_WRONLY | O_APPEND | O_CREAT, 0666); 
    }
    else if(mode == 2)
    {
        fileDescriptor = open(fileName, O_RDWR, 0666); 
    }
    return fileDescriptor;
}

void addRecord()
{
    Country country = getCountry();
    struct iovec iov[3]; // Массив структур iovec для векторной записи

    iov[0].iov_base = country.name;
    iov[0].iov_len = 100; 
    iov[1].iov_base = &country.area; 
    iov[1].iov_len = sizeof(long); 
    iov[2].iov_base = &country.population;
    iov[2].iov_len = sizeof(long); 
    
    char* fileName = inputFileName();
    int fileDescriptor = open(fileName, O_WRONLY | O_APPEND | O_CREAT, 0666);

    if (writev(fileDescriptor, iov, 3) == -1)
    {
        // Выполняем векторную запись из массива структур iovec в файл и
        // проверяем успешность операции
        perror("File write error");
        exit(1);
    }
    close(fileDescriptor); // Закрываем файл
    printf("The record has been added successfully.\n");
}


long countRecords(char* fileName)
{
    long count;
    int fileDescriptor = open(fileName, O_RDONLY);
    int recordLen = 100 + sizeof(long) * 2; 
    count = lseek(fileDescriptor, 0, SEEK_END) / recordLen;
    close(fileDescriptor);
    return count;
}

long inputPopulation(){
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
    return population;
}

long inputCountryArea(){
    long area;
    int res = 0;
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
    return area;
}

int inputCountryNumber(int counter){
    int number;
    printf("There are %d countries in the file\n", counter);
    int res = 0;
    while(res != 1){
        printf("Please, enter a country number: ");
        res = InputInt(&number);
        if(number > counter){
            printf("This number is too big. Please, try again\n");
            res = 0;
        }
        else if ( res == -1){
            printf("This value should be positive\n");
        }
    }
    printf("%d\n", number);
    return number;
}

void modifyRecord()
{
    // Country country;
    struct iovec iov[3]; // Массив структур iovec для векторной записи
    iov[0].iov_base = NULL;
    iov[0].iov_len = 100; 
    iov[1].iov_len = sizeof(long); 
    iov[2].iov_len = sizeof(long); 
    char* fileName = inputFileName();
    int fileDescriptor = openFile(2, fileName);
    int counter = countRecords(fileName);
    if(counter == 0)
    {
        printf("This file is empty. Nothing to modify");
    }
    else
    {
        int number = inputCountryNumber(counter);
        int pos = (number - 1) * (100 + sizeof(long) * 2);
        if (lseek(fileDescriptor, pos, SEEK_SET) == -1)
        {
            // Перемещаем указатель позиции в файле на начало нужной записи
            perror("Seaking file error");
            exit(1);
        }
        if (readv(fileDescriptor, iov, 3) == -1)
        {
            // Выполняем векторное чтение из файла в массив структур iovec
            // и проверяем успешность операции
            perror("Reading file error");
            exit(1);
        }
        close(fileDescriptor); // Закрываем файл
        printChangeMenu();
        int command;
        int res = 0;
        while(res == 0)
        {
            printf("Your command: ");
            res = InputInt(&command);
        }
        if(command == 1){
            printf("Please, enter the country name: ");
            char* name = GetString();
            iov[0].iov_base = name; 
            iov[0].iov_len = 100;
        }
        else if(command == 2){
            long area = inputCountryArea();
            iov[1].iov_base = &area; 
            iov[1].iov_len = sizeof(long);
        }
        else if(command == 3){
            long population = inputPopulation();
                iov[2].iov_base = &population;
                iov[2].iov_len = sizeof(long);
        }
        else{
            printf("Wrong command\n");
        }
        fileDescriptor = open(fileName, O_WRONLY); // Открываем файл для записи
        if (fileDescriptor == -1)
        {
            perror("Ошибка открытия файла");
            exit(1);
        }
        if (lseek(fileDescriptor, pos, SEEK_SET) == -1)
        {
            perror("Ошибка перемещения в файле");
            exit(1);
        }
        if (writev(fileDescriptor, iov, 3) == -1)
        {
            perror("Ошибка записи в файл");
            exit(1);
        }
        close(fileDescriptor); // Закрываем файл
        printf("Предприятие успешно изменено.\n");
    }
}

void ReadRecord()
{
    Country country;
    struct iovec iov[3];
    char* fileName = inputFileName();
    int fileDescriptor = open(fileName, O_RDONLY);
    if (fileDescriptor == -1)
    {
        printf("No file with such name\n");
    }
    else
    {
        int count = countRecords(fileName);
        int number = inputCountryNumber(count);
        int pos = (100 + sizeof(long) * 2) * (number - 1);
        if (lseek(fileDescriptor, pos, SEEK_SET) == -1)
        {
            perror("Ошибка перемещения в файле");
            exit(1);
        }
        iov[0].iov_base = country.name;
        iov[0].iov_len = 100; 
        iov[1].iov_base = &country.area; 
        iov[1].iov_len = sizeof(long); 
        iov[2].iov_base = &country.population;
        iov[2].iov_len = sizeof(long); 
        if (readv(fileDescriptor, iov, 4) == -1)
        {
            perror("Ошибка чтения из файла");
            exit(1);
        }
        close(fileDescriptor);
        printCountry(country); 
    }
}

void readAllRecords() {
    Country country;
    struct iovec iov[3]; 
    int count = 0; // счетчик записей
    char* fileName = inputFileName();
    int fileDescriptor = open(fileName, O_RDONLY);
    if (fileDescriptor == -1)
    {
        printf("No file with such name\n");
    }
    else
    {
        while (1)
        { 
            iov[0].iov_base = country.name;
            iov[0].iov_len = 100; 
            iov[1].iov_base = &country.area; 
            iov[1].iov_len = sizeof(long); 
            iov[2].iov_base = &country.population;
            iov[2].iov_len = sizeof(long); 

            // Выполняем векторное чтение из файла в массив структур iovec и
            // сохраняем количество прочитанных байтов
            ssize_t bytesRead = readv(fileDescriptor, iov, 3);
            if (bytesRead == -1)
            { // Проверяем успешность операции чтения
                perror("Ошибка чтения из файла");
                exit(1);
            }
            if (bytesRead == 0)
            { 
                break;
            }
            count++; // Увеличиваем счетчик записей
            printCountry(country);
        }
        close(fileDescriptor);
        if (count == 0)
        {
            printf("Файл пуст.\n");
        }
    }
}