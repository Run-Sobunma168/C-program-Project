#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>
#include "gotoXY.h"
struct product
{
    char name[20];
    int code;
    float price, discount, amount;
    int qty;
};
void line() { puts("_________________________________________________________"); }

void inputPro(struct product *obj, int index, char message[])
{
    printf("\t%s[%d]\n", message, (index + 1));
    printf("\tCode      : ");
    scanf("%d", &obj->code);
    fflush(stdin);
    printf("\tName      : ");
    gets(obj->name);
    printf("\tPrice     : ");
    scanf("%f", &obj->price);
    printf("\tDiscount  : ");
    scanf("%f", &obj->discount);
    obj->qty = 0;
    obj->amount = 0;
}

void outputPro(struct product obj)
{
    printf("%5d %10s %15.2f$ %10.1f%% \n", obj.code, obj.name, obj.price, obj.discount);
}

FILE *file;
struct product obj;

int sizeOfFILE()
{
    file = fopen("Drinks", "rb");
    fseek(file, 0, SEEK_END);
    return ftell(file) / sizeof(obj);
    fclose(file);
}

void admin()
{
    int choice = 1;
    bool cd = 1;
    char key;
    file = fopen("Drinks", "rb");
    fseek(file, 0, SEEK_END);
    int n1 = ftell(file) / sizeof(obj);
    fclose(file);
    do
    {
        system("cls");
        printf("\t\tAdmin %d\n", n1);
        printf(choice == 1 ? "\t ==>  " : "\t     ");
        printf("Input Drink\n");
        printf(choice == 2 ? "\t ==>  " : "\t     ");
        printf("Output Drink\n");
        printf(choice == 3 ? "\t ==>  " : "\t     ");
        printf("Sort\n");
        printf(choice == 4 ? "\t ==>  " : "\t     ");
        printf("Update\n");
        printf(choice == 5 ? "\t ==>  " : "\t     ");
        printf("Delete\n");
        printf(choice == 6 ? "\t ==>  " : "\t     ");
        printf("Back\n");
        key = getch();
        system("cls");
        switch (key)
        {
        case 72:
            if (choice > 1)
                choice = choice - 1;
            break;
        case 80:
            if (choice < 6)
                choice = choice + 1;
            break;
        case 13:
        {
            switch (choice)
            {
            case 1:
            {
                file = fopen("Drinks", "ab");
                int num;
                printf("Enter number of product for Add : ");
                scanf("%d", &num);
                for (int i = n1; i < n1 + num; i++)
                {
                    inputPro(&obj, i, "Enter Infor of new Drink");
                    fwrite(&obj, sizeof(obj), 1, file);
                }
                fclose(file);
                n1 = n1 + num;
                getch();
            }
            break;
            case 2:
            {
                file = fopen("Drinks", "rb");
                printf("%5s %10s %15s %10s\n", "Code", "Name", "Price", "Discount");
                line();
                while (fread(&obj, sizeof(obj), 1, file))
                {
                    outputPro(obj);
                }
                fclose(file);
                getch();
            }
            break;
            case 3:
                puts(" cahe 3");
                break;
            case 4:
                puts(" cahe 4");
                break;
            case 5:
                puts(" cahe 5");
                break;
            case 6:
                cd = 0;
                break;
            }
            break;
        }
        }
    } while (cd);
}

void inputProOrder(struct product *obj, int index)
{
    printf("\tCode      : %d %s\n", index, (obj->qty == 0) ? "" : "(Edit)");
    printf("\tName      : %s\n", obj->name);
    printf("\tPrice($)  : %.2f\n", obj->price);
    printf("\tDiscount  : %.2f\n", obj->discount);
    printf("\tQTY       : ");
    scanf("%d", &obj->qty);
    obj->amount = (obj->price * obj->qty) - ((obj->price * obj->qty) * obj->discount / 100);
    printf("\tAmount    : %.2f$\n", obj->amount);
}

void outputProOrder(struct product obj, int i)
{
    printf("%5d %10s %15.2f$ %10.1f%% \n", i, obj.name, obj.price, obj.discount);
}

void showInvoid(struct product obj[], int n)
{
    float total = 0.0;
    int total_qty = 0;
    system("cls");
    printf("\n\t\t\t\t\tINVOID\n");
    printf("\t\t%-5s %-10s %-5s %-10s %-10s %-10s \n", "No", "Description", "QTY", "Price", "dis", "Amount");
    printf("\t     ");
    line();
    for (int i = 0; i < n; i++)
    {
        if (obj[i].qty != 0)
        {
            printf("\t\t%-5d %-10s %-5d $%-10.2f %-10.1f $%-10.1f \n", i + 1, obj[i].name, obj[i].qty, obj[i].price, obj[i].discount, obj[i].amount);
            total += obj[i].amount;
            total_qty += obj[i].qty;
        }
    }
    printf("\t     ");
    line();

    printf("\t\tTotal_Qty    Grade_Total_Dollar :%17.2f$\n", total);
    printf("\t\t  %d%25s   :%17.0fR\n", total_qty, "Grade_Total_Riel", total * 4100);
}

void showOder()
{
    int a = 0, scode;
    int n = sizeOfFILE();
    bool cd = true;
    file = fopen("Drinks", "rb");
    struct product drink[n];
    gotoXY(60, 0);
    printf("%d\n", n);
    while (fread(&obj, sizeof(obj), 1, file))
    {
        drink[a] = obj;
        gotoXY(60, a + 1);
        outputProOrder(drink[a], a + 1);
        a++;
    }
    gotoXY(0, 1);
    while (cd)
    {
        printf("\t\tEnter code : ");
        scanf("%d", &scode);
        if (scode > 0 && scode <= n)
        {
            inputProOrder(&drink[scode - 1], scode);
        }
        char end = getch();
        if (end == '=')
        {
            cd = false;
        }
    }
    showInvoid(drink, n);
    fclose(file);
    getch();
}