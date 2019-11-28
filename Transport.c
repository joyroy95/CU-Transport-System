#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>

COORD coord = {0, 0};
/* Global variables */

double diesel_p =68.00, cng_p =30.00, distance_p_diesel = 2.56, distance_p_cng = 2.25, sum , sum1;  // variables to store fuel prices
FILE *f1;           // for existing System;
FILE *f2;           // for proposed System;
FILE *f3;

struct record
{
    int no;
    char source[30];
    char terminal[30];
    double length;
    int n;
};
struct record route;

/*  all the functions */

int Home(void);     // display the home menu
void cursorToxy(int x,int y);   // to move the cursor in (x,y) position
void Existing(void);    // function for existing system
void Proposed(void);    // function for proposed system
void Compare(void);     // function to compare
void help(void);    // help menu
void about(void);   // about menu
void addEx(void);   // add in existing system
void addProp(void); // add in proposed system
void delteEx(void); // delete from existing system
void delteProp(void);   // delete from proposed system
void editEx(void);  // edits in existing
void editProp(void); // edit in proposed
void showEx(void); // show existing
void showProp(void); // show proposed
void fuel(void);

/* cursorToxy function*/
void cursorToxy(int x, int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

int main()
{
    system("color 3f"); // background and foreground color
    Home(); // call the home function to print home menu
    //  system("pause");
    return 0;
}
/* Home function*/
int Home(void)
{
    system("cls"); // clears the screen
    cursorToxy(15,1);
    printf("*************** Transport System ***************"); // heading
    puts("");
    /* menu options */
    int x= 29,y=4;
    cursorToxy(x,y);
    puts("1. Existing System");
    y+=2;
    cursorToxy(x,y);
    puts("2. Proposed System");
    y+=2;
    cursorToxy(x,y);
    puts("3. Fuel Price");
    y+=2;
    cursorToxy(x,y);
    puts("4. Compare");
    y+=2;
    cursorToxy(x,y);
    puts("5. About");
    y+=2;
    cursorToxy(x,y);
    puts("0. Exit");
    y+=2;
    x=25;
    y+=2;
    cursorToxy(x,y);
    printf("Enter menu choice: ");
    char choice = getche();
    switch(choice)
    {
    case '1' :
        Existing();
        break;
    case '2':
        Proposed();
        break;
    case '3':
        fuel();
        break;
    case '4':
        Compare();
        break;
    case '5':
        about();
        break;
    case '0':
        return 0;
        break;
    default:
        cursorToxy(x, y+2);
        puts("Enter The Right Choice: ");
        Home();
    }
}

/* function for existing system */
void Existing(void)
{
    system("cls");
    int x=34, y=4;
    cursorToxy(15,1);
    printf("*************** Transport System ***************"); // heading
    cursorToxy(15,3);
    printf("     ********** Existing System  **********   ");
    cursorToxy(x,y+=2);
    printf("1. View");
    cursorToxy(x,y+=2);
    printf("2. Add");
    cursorToxy(x,y+=2);
    printf("3. Delete");
    cursorToxy(x,y+=2);
    printf("4. Edit");
    cursorToxy(x,y+=2);
    printf("5. Back");
    cursorToxy(x,y+=2);
    printf("0. Exit");
    cursorToxy(25,y+=4);
    printf("Enter menu choice: ");
    char choice = getche();
    switch(choice)
    {
    case '1':
        showEx();
        break;
    case '2':
        addEx();
        break;
    case '3':
        delteEx();
        break;
    case '4':
        editEx();
        break;
    case '5':
        Home();
        break;
    case '0':
        exit(0);
    default:
        Existing();
    }
    cursorToxy(5,20);
}

/* function for Adding in Existing system */
void addEx(void)
{
    system("cls");

    cursorToxy(15,1);
    printf("***************  Existing System ***************"); // heading
    cursorToxy(15,3);
    printf("     **********   Add a Route    **********");
    f1 = fopen("existingSys.txt", "a+");
    int x = 23, y=6;
    cursorToxy(x,y);
    printf("Enter Route No  : ");
    scanf("%d", &route.no);
    getchar();
    y+=2;
    cursorToxy(x,y);
    printf("Enter Source    : ");
    gets(route.source);
    y+=2;
    cursorToxy(x,y);
    printf("Enter Terminal  : ");
    gets(route.terminal);
    y+=2;
    cursorToxy(x,y);
    printf("Road Length [km]: ");
    scanf("%lf", &route.length);
    y+=2;
    cursorToxy(x,y);
    printf("How Many Times ");
    y+=1;
    cursorToxy(x,y);
    printf("The Route is Traveled/day?: ");
    scanf("%d", &route.n);
    getchar();
    fseek(f1,0,SEEK_END);
    fwrite(&route, sizeof(route), 1, f1);
    fclose(f1);
    x+=3;
    y+=5;
    cursorToxy(x,y);
    printf("Successfully Added.!");
    y+=2;
    cursorToxy(x,y);
    printf("1. Add Another");
    y+=2;
    cursorToxy(x,y);
    printf("2. Back");
    y+=2;
    cursorToxy(x,y);
    printf("3. View List");
    y+=2;
    cursorToxy(x,y);
    printf("0. Exit");
    y+=3;
    cursorToxy(x,y);
    printf("Enter Menu Choice: ");
    char choice = getche();
    switch(choice)
    {
    case '1':
        addEx();
        break;
    case '2':
        Existing();
        break;
    case '3':
        showEx();
        break;
    case '0':
        exit(0);
    default:
        Existing();
    }
}
/* function for Showing Existing system */
void showEx(void)
{
    double  Rqdiesel, Rqcng, diesel_cost, cng_cost;
    int n;
    sum = 0;
    system("cls");
    cursorToxy(15,1);
    printf("*************** Existing System ****************"); // heading
    cursorToxy(15,3);
    printf("     ********** Existing Routes ***********");
    f1 = fopen("existingSys.txt", "rb");
    int j;
    int x = 22, y=4, flag = 0;;
    while(fread(&route,sizeof(route),1,f1)  == 1)
    {
        flag = 1;
        Rqdiesel = route.n * (route.length/distance_p_diesel);      // required diesel
        Rqcng    = route.n * (route.length/distance_p_cng);         // required CNG
        diesel_cost = diesel_p * Rqdiesel;
        cng_cost    = cng_p * Rqcng;
        cursorToxy(15,y+=2);
        printf("Route %d.", route.no);
        cursorToxy(15,y+=2);
        printf("\xB2\xB2\xB2");
        printf(" %s - %s",route.source, route.terminal);
        cursorToxy(x, y+=2);
        printf("[ Length         : %.2lf km", route.length);
        cursorToxy(58, y);
        printf("]");
        cursorToxy(x, y+=2);
        printf("[ Travels/Day    : %d", route.n);
        cursorToxy(58, y);
        printf("]");
        cursorToxy(x, y+=2);
        printf("[ Required Diesel: %.2lf L", Rqdiesel);
        cursorToxy(58, y);
        printf("]");
        cursorToxy(x, y+=2);
        printf("[ Cost of Diesel : %.2lf Tk", diesel_cost);
        cursorToxy(58, y);
        printf("]");
        cursorToxy(x, y+=2);
        printf("[ Required CNG   : %.2lf L", Rqcng);
        cursorToxy(58, y);
        printf("]");
        cursorToxy(x, y+=2);
        printf("[ Cost of CNG    : %.2lf Tk", cng_cost);
        cursorToxy(58, y);
        printf("]");
        sum+=cng_cost;
        cursorToxy(x, y+=2);
    }
    if(flag == 0)
    {
        cursorToxy(x, y+=4);
        printf("File Is Empty...");
        cursorToxy(x, y+=2);
    }
    fclose(f1);
    cursorToxy(15,y);
    printf("***********************************************");
    x = 30;
    y+=3;
    cursorToxy(x,y);
    printf("1. Add");
    y+=2;
    cursorToxy(x,y);
    printf("2. Delete");
    y+=2;
    cursorToxy(x,y);
    printf("3. Edit");
    y+=2;
    cursorToxy(x,y);
    printf("4. Back");
    y+=2;
    cursorToxy(x,y);
    printf("0. Exit");
    y+=3;
    cursorToxy(20,y);
    printf("Enter Menu Choice: ");
    char choice = getche();
    switch(choice)
    {
    case '1':
        addEx();
        break;
    case '2':
        delteEx();
        break;
    case '3':
        editEx();
        break;
    case '4':
        Existing();
        break;
    case '0':
        exit(0);
    default:
        showEx();
    }
}

/* function for proposed system */
void Proposed(void)
{
    system("cls");
    cursorToxy(15,1);
    printf("*************** Transport System ***************"); // heading
    cursorToxy(15,3);
    printf("     ********** Proposed System *********   ");
    cursorToxy(35,5);
    printf("1. View");
    cursorToxy(35,7);
    printf("2. Add");
    cursorToxy(35,9);
    printf("3. Delete");
    cursorToxy(35,11);
    printf("4. Edit");
    cursorToxy(35,13);
    printf("5. Back");
    cursorToxy(35,15);
    printf("0. Exit");
    cursorToxy(25,17);
    printf("Enter menu choice:");
    char choice = getche();

    switch(choice)
    {
    case '1':
        showProp();
        break;
    case '2':
        addProp();
        break;
    case '3':
        delteProp();
        break;
    case '4':
        editProp();
        break;
    case '5':
        Home();
        break;
    case '0':
        // cursorToxy(5,20);
        exit(0);
    default:
        Proposed();
    }

    cursorToxy(5,20);
}

/* about */
void about(void)
{
    system("cls");
    cursorToxy(15,1);
    printf("*************** Transport System ***************"); // heading
    cursorToxy(15,3);
    printf("           ********** About *********   ");
    cursorToxy(5,20);

    /* this coordinates might need to be changed when more stuffs are added */
    cursorToxy(35,20);
    printf("1. Back");
    cursorToxy(35,22);
    printf("0. Exit");
    cursorToxy(25,24);
    printf("Enter menu choice:");
    char choice = getche();
    switch(choice)
    {
    case '1':
        Home();
        break;
    case '0':
        exit(0);
    default:
        about();
    }
}

void editEx(void)
{
    system("cls");
    cursorToxy(15, 1);
    printf("*************** Existing System ****************");
    cursorToxy(15, 3);
    printf("     **********   Edit a Route   **********");
    int x = 23, y=6;
    cursorToxy(x, y);
    printf("Enter Route No To Edit : ");
    int r1, found = 0;
    scanf("%d", &r1);
    f1 = fopen("existingSys.txt", "rb+");
    while(fread(&route, sizeof(route), 1, f1)==1)
    {
        if(r1==route.no)
        {
            getchar();

            cursorToxy(x,y+=2);
            printf("Enter Source    : ");
            gets(route.source);
            y+=2;
            cursorToxy(x,y);
            printf("Enter Terminal  : ");
            gets(route.terminal);
            y+=2;
            cursorToxy(x,y);
            printf("Road Length [km]: ");
            scanf("%lf", &route.length);
            y+=2;
            cursorToxy(x,y);
            printf("How Many Times ");
            y+=1;
            cursorToxy(x,y);
            printf("The Route is Traveled/day?: ");
            scanf("%d", &route.n);
            getchar();

            fseek(f1,-sizeof(route), SEEK_CUR);
            fwrite(&route, sizeof(route), 1, f1);

            found = 1;
            cursorToxy(x, y+=2);
            printf("The route is successfully edited.");
            break;
        }
    }

    if(found==0)
    {
        cursorToxy(x, y+=2);
        printf("No Route Found.");
    }
    fclose(f1);
    cursorToxy(x, y+=2);
    printf("1. Home");
    cursorToxy(x, y+=2);
    printf("2. View");
    cursorToxy(x, y+=2);
    printf("3. Existing System");
    cursorToxy(x, y+=2);
    printf("0. Exit");
    cursorToxy(22, y+=4);
    printf("Enter Menu Choice: ");
    char choice = getche();
    switch(choice)
    {
    case '1':
        Home();
        break;
    case '2':
        showEx();
        break;
    case '3':
        Existing();
        break;
    case '0':
        exit(0);
    default:
        Existing();
    }
}

void delteEx(void)
{
    system("cls");
    cursorToxy(15, 1);
    printf("*************** Existing System ****************");
    cursorToxy(15, 3);
    printf("     **********   Delete a Route    **********");
    int x = 23, y=6;
    cursorToxy(x, y);
    printf("Enter Route No To Delete : ");
    int r1, flag = 0;
    scanf("%d", &r1);
    f1 = fopen("existingSys.txt", "rb");
    f2 = fopen("new.txt", "wb");
    while(fread(&route, sizeof(route), 1, f1)==1)
    {
        if(r1!=route.no)
        {

            fwrite(&route, sizeof(route), 1, f2);
        }
    }
    fclose(f1);
    fclose(f2);
    remove("existingSys.txt");
    rename("new.txt", "existingSys.txt");
    cursorToxy(x, y+=2);
    printf("The route is successfully deleted.");
    cursorToxy(x, y+=2);
    printf("1. Home");
    cursorToxy(x, y+=2);
    printf("2. View");
    cursorToxy(x, y+=2);
    printf("3. Existing System");
    cursorToxy(x, y+=2);
    printf("0. Exit");
    cursorToxy(22, y+=4);
    printf("Enter Menu Choice: ");
    char choice = getche();
    switch(choice)
    {
    case '1':
        Home();
        break;
    case '2':
        showEx();
        break;
    case '3':
        Existing();
    case '0':
        exit(0);
    default:
        Existing();
    }
}

void addProp(void)
{
     system("cls");
    cursorToxy(15,1);
    printf("***************  Proposed System ***************"); // heading
    cursorToxy(15,3);
    printf("     **********   Add a Route    **********");
    f2 = fopen("proposedsystem.txt", "a+");
    int x = 23, y=6;
    cursorToxy(x,y);
    printf("Enter Route No  : ");
    scanf("%d", &route.no);
    getchar();
    y+=2;
    cursorToxy(x,y);
    printf("Enter Source    : ");
    gets(route.source);
    y+=2;
    cursorToxy(x,y);
    printf("Road Length [km]: ");
    scanf("%lf", &route.length);
    y+=2;
    cursorToxy(x,y);
    printf("How Many Times ");
    y+=1;
    cursorToxy(x,y);
    printf("The Route is Traveled/day?: ");
    scanf("%d", &route.n);
    getchar();
    fseek(f1,0,SEEK_END);
    fwrite(&route, sizeof(route), 1, f1);
    fclose(f1);
    x+=3;
    y+=5;
    cursorToxy(x,y);
    printf("Successfully Added.!");
    y+=2;
    cursorToxy(x,y);
    printf("1. Add Another");
    y+=2;
    cursorToxy(x,y);
    printf("2. Back");
    y+=2;
    cursorToxy(x,y);
    printf("3. View List");
    y+=2;
    cursorToxy(x,y);
    printf("0. Exit");
    y+=3;
    cursorToxy(x,y);
    printf("Enter Menu Choice: ");
    char choice = getche();
    switch(choice)
    {
    case '1':
        addProp();
        break;
    case '2':
        Proposed();
        break;
    case '3':
        showProp();
        break;
    case '0':
        exit(0);
    default:
        Proposed();
    }
}
void showProp(void)
{
    double  Rqdiesel, Rqcng, diesel_cost, cng_cost;
    int n;
    system("cls");
    cursorToxy(15,1);
    printf("*************** Proposed System ****************"); // heading
    cursorToxy(15,3);
    printf("     ********** Proposing Routes ***********");
    f2 = fopen("proposedsystem.txt", "rb");
    int j;
    int x = 22, y=4, flag = 0;;
    while(fread(&route,sizeof(route),1,f2)  == 1)
    {
        flag = 1;
        Rqdiesel = route.n * (route.length/distance_p_diesel);      // required diesel
        Rqcng    = route.n * (route.length/distance_p_cng);         // required CNG
        diesel_cost = diesel_p * Rqdiesel;
        cng_cost    = cng_p * Rqcng;
        cursorToxy(15,y+=2);
        printf("Route %d.", route.no);
        cursorToxy(15,y+=2);
        printf("\xB2\xB2\xB2");
        printf(" %s - %s",route.source, "Sholoshahar By Bus");
        cursorToxy(x, y+=2);
        printf("[ Length         : %.2lf km", route.length);
        cursorToxy(58, y);
        printf("]");
        cursorToxy(x, y+=2);
        printf("[ Travels/Day    : %d", route.n);
        cursorToxy(58, y);
        printf("]");
        cursorToxy(x, y+=2);
        printf("[ Required Diesel: %.2lf L", Rqdiesel);
        cursorToxy(58, y);
        printf("]");
        cursorToxy(x, y+=2);
        printf("[ Cost of Diesel : %.2lf Tk", diesel_cost);
        cursorToxy(58, y);
        printf("]");
        cursorToxy(x, y+=2);
        printf("[ Required CNG   : %.2lf L", Rqcng);
        cursorToxy(58, y);
        printf("]");
        cursorToxy(x, y+=2);
        printf("[ Cost of CNG    : %.2lf Tk", cng_cost);
        cursorToxy(58, y);
        printf("]");
        cursorToxy(15, y+=2);
        printf("\xB2\xB2\xB2");
        printf(" %s - %s", "Sholoshahar", "Campus By Train");

        double rqfuel, fuel_cost;

        rqfuel = 8.24;

        fuel_cost = rqfuel*8;

        cursorToxy(x, y+=2);
        printf("[ Length         : %.2lf km", 15.5);
        cursorToxy(58, y);
        printf("]");
        cursorToxy(x, y+=2);
        printf("[ Travels/Day    : %d", 10);
        cursorToxy(58, y);
        printf("]");
        cursorToxy(x, y+=2);
        printf("[ Required Fuel  : %.2lf L", rqfuel);
        cursorToxy(58, y);
        printf("]");
        cursorToxy(x, y+=2);
        printf("[ Cost of Fuel   : %.2lf Tk", fuel_cost);
        cursorToxy(58, y);
        printf("]");
        cursorToxy(15, y+=2);

        printf("\xB2\xB2\xB2");

        double total_cost;

        total_cost = cng_cost + fuel_cost;
        sum1 += total_cost;

        printf(" Total Cost = %.2lf Tk", total_cost);

        cursorToxy(x, y+=2);

    }
    if(flag == 0)
    {
        cursorToxy(x, y+=4);
        printf("File Is Empty...");
        cursorToxy(x, y+=2);
    }
    fclose(f1);
    cursorToxy(15,y);
    printf("***********************************************");
    x = 30;
    y+=3;
    cursorToxy(x,y);
    printf("1. Add");
    y+=2;
    cursorToxy(x,y);
    printf("2. Delete");
    y+=2;
    cursorToxy(x,y);
    printf("3. Edit");
    y+=2;
    cursorToxy(x,y);
    printf("4. Back");
    y+=2;
    cursorToxy(x,y);
    printf("0. Exit");
    y+=3;
    cursorToxy(20,y);
    printf("Enter Menu Choice: ");
    char choice = getche();
    switch(choice)
    {
    case '1':
        addProp();
        break;
    case '2':
        delteProp();
        break;
    case '3':
        editProp();
        break;
    case '4':
        Proposed();
        break;
    case '0':
        exit(0);
    default:
        showProp();
    }
}
void delteProp(void)
{
    system("cls");
    cursorToxy(15, 1);
    printf("*************** Proposed System ****************");
    cursorToxy(15, 3);
    printf("     **********   Delete a Route    **********");
    int x = 23, y=6;
    cursorToxy(x, y);
    printf("Enter Route No To Delete : ");
    int r1;
    scanf("%d", &r1);
    f1 = fopen("proposedsystem.txt", "rb");
    f3 = fopen("new1.txt", "wb");
    while(fread(&route, sizeof(route), 1, f2)==1)
    {
        if(r1!=route.no)
        {
            fwrite(&route, sizeof(route), 1, f3);
        }
    }
    fclose(f2);
    fclose(f3);
    remove("proposedsystem.txt");
    rename("new1.txt", "proposedsystem.txt");
    cursorToxy(x, y+=2);
    printf("The route is successfully deleted.");
    cursorToxy(x, y+=2);
    printf("1. Home");
    cursorToxy(x, y+=2);
    printf("2. View");
    cursorToxy(x, y+=2);
    printf("3. Proposed System");
    cursorToxy(x, y+=2);
    printf("0. Exit");
    cursorToxy(22, y+=4);
    printf("Enter Menu Choice: ");
    char choice = getche();
    switch(choice)
    {
    case '1':
        Home();
        break;
    case '2':
        showProp();
        break;
    case '3':
        Proposed();
        break;
    case '0':
        exit(0);
    default:
        Proposed();
    }
}
void editProp(void)
{
    system("cls");
    cursorToxy(15, 1);
    printf("*************** Proposed System ****************");
    cursorToxy(15, 3);
    printf("     **********   Edit a Route   **********");
    int x = 23, y=6;
    cursorToxy(x, y);
    printf("Enter Route No To Edit : ");
    int r1, found = 0;
    scanf("%d", &r1);
    f2 = fopen("proposedsystem.txt", "rb+");
    while(fread(&route, sizeof(route), 1, f2)==1)
    {
        if(r1==route.no)
        {
            getchar();
            cursorToxy(x,y+=2);
            printf("Enter Source    : ");
            gets(route.source);
            y+=2;
            cursorToxy(x,y);
            printf("Road Length [km]: ");
            scanf("%lf", &route.length);
            y+=2;
            cursorToxy(x,y);
            printf("How Many Times ");
            y+=1;
            cursorToxy(x,y);
            printf("The Route is Traveled/day?: ");
            scanf("%d", &route.n);
            getchar();

            fseek(f1,-sizeof(route), SEEK_CUR);
            fwrite(&route, sizeof(route), 1, f1);

            found = 1;
            cursorToxy(x, y+=2);
            printf("The route is successfully edited.");
            break;
        }
    }

    if(found==0)
    {
        cursorToxy(x, y+=2);
        printf("No Route Found.");
    }
    fclose(f1);
    cursorToxy(x, y+=2);
    printf("1. Home");
    cursorToxy(x, y+=2);
    printf("2. View");
    cursorToxy(x, y+=2);
    printf("3. Proposed System");
    cursorToxy(x, y+=2);
    printf("0. Exit");
    cursorToxy(22, y+=4);
    printf("Enter Menu Choice: ");
    char choice = getche();
    switch(choice)
    {
    case '1':
        Home();
        break;
    case '2':
        showProp();
    case '3':
        Proposed();
        break;
    case '0':
        exit(0);
    default:
        Proposed();
    }
}
void fuel(void)
{
    system("cls");
    int x=15, y=4;
    cursorToxy(15, 1);
    printf("*************** Transport System ***************"); // heading
    cursorToxy(15,3);
    printf("     **********    Fuel Price    **********  ");
    cursorToxy(x, y+=2);
    printf("             Diesel : %.2lf BDT/Liter",diesel_p);
    cursorToxy(x, y+=2);
    printf("              CNG   : %.2lf BDT/Liter",cng_p);
    cursorToxy(x, y+=3);
    printf("                   1. Edit");
    cursorToxy(x, y+=2);
    printf("                   2. Back");
    cursorToxy(x, y+=2);
    printf("                   0. Exit");
    cursorToxy(x+6, y+=3);
    printf("Enter Menu Choice:");
    char choice = getche();
    switch(choice)
    {
    case '1':
        system("cls");
        cursorToxy(15,1);
        printf("*************** Transport System ***************"); // heading
        cursorToxy(15,3);
        printf("     **********    Fuel Price    **********  ");
        y=4;
        cursorToxy(x, y+=2);
        printf("       Enter Diesel price(BDT/Liter): ");
        scanf("%lf",&diesel_p);
        cursorToxy(x, y+=2);
        printf("       Enter CNG price(BDT/Liter): ");
        scanf("%lf",&cng_p);
        cursorToxy(x, y+=3);
        printf("                   1. Back");
        cursorToxy(x, y+=2);
        printf("                   0. Exit");
        cursorToxy(x, y+=2);
        printf("Enter menu choice:");
        char ch = getche();
        switch(ch)
        {
        case '1':
            fuel();
            break;
        case '0':
            exit(0);
        }
        break;
    case '2':
        Home();
        break;
    case '0':
        exit(0);
    default:
        fuel();
    }
}

void compare1(void)
{
    double  Rqdiesel, Rqcng, diesel_cost, cng_cost;
    int n;
    sum = 0;
    f1 = fopen("existingSys.txt", "rb");
    int j;
    int x = 22, y=4, flag = 0;;
    while(fread(&route,sizeof(route),1,f1)  == 1)
    {
        flag = 1;
        Rqdiesel = route.n * (route.length/distance_p_diesel);      // required diesel
        Rqcng    = route.n * (route.length/distance_p_cng);         // required CNG
        diesel_cost = diesel_p * Rqdiesel;
        cng_cost    = cng_p * Rqcng;
        sum+=cng_cost;
    }
}

void compare2(void)
{
     double  Rqdiesel, Rqcng, diesel_cost, cng_cost;
    int n;
    sum1 = 0.0;
    f1 = fopen("proposedsystem.txt", "rb");
    while(fread(&route,sizeof(route),1,f1)  == 1)
    {
        Rqdiesel = route.n * (route.length/distance_p_diesel);      // required diesel
        Rqcng    = route.n * (route.length/distance_p_cng);         // required CNG
        diesel_cost = diesel_p * Rqdiesel;
        cng_cost    = cng_p * Rqcng;
        double rqfuel, fuel_cost;
        rqfuel = 8.24;
        fuel_cost = rqfuel*8;
        double total_cost;
        total_cost = cng_cost + fuel_cost;
        sum1 += total_cost;
    }
}
/* function to compare between the systems*/
void Compare(void)
{
    system("cls");
    cursorToxy(15,1);
    printf("*************** Transport System ***************"); // heading
    cursorToxy(15,3);
    printf("        ********** Comparison *********   ");
    compare1();
    compare2();
    cursorToxy(15,6);
    printf("Cost of Existing System %.2lf Tk", sum);
    cursorToxy(15,8);
    printf("Cost of Proposed System %.2lf Tk", sum1);
    /* this coordinates might need to be changed when more stuffs are added */
    cursorToxy(35,20);
    printf("1. Back");
    cursorToxy(35,22);
    printf("0. Exit");
    cursorToxy(25,24);
    printf("Enter menu choice:");
    char choice = getche();
    switch(choice)
    {
    case '1':
        Home();
        break;
    case '0':
        exit(0);
    default:
        about();
    }
}

