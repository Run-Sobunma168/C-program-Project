#include "function.h"
int main()
{
    char key;
    bool cd = true;
    int choice = 1;
    while (cd)
    {
        system("cls");
        printf(choice == 1 ? " ==> " : "     ");
        printf("Order\n");
        printf(choice == 2 ? " ==> " : "     ");
        printf("Admin\n");
        printf(choice == 3 ? " ==> " : "     ");
        printf("Close\n");
        key = getch();
        system("cls");
        switch (key)
        {
        case 72:
            if (choice > 1)
                choice--;
            break;
        case 80:
            if (choice < 3)
                choice++;
            break;
        case 13:
        {
            switch (choice)
            {
            case 1:
            {
                showOder();
            }
            break;
            case 2:
            {
                admin();
            }
            break;
            case 3:
            {
                cd = false;
            }
            break;
            }
        }
        }
    }

    return 0;
}