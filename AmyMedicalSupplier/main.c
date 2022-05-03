//Amy Waldron
//G00395091
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//all The Structs
//Details Of The Company
typedef struct
{
    //ints
    int regisNum;
    int yearF;
    int numOfEmployees;

    //questions
    int vatRegist;
    int averageT;
    int sector;
    int numStaff;

    //chars
    char name[30];
    char country[30];
    char email[30];
    char contactName[30];

    //floats
    float lastOrder;

}company;

//functions
bool SignIn();
void initArray(company* client);
void Menu(company* client);
void AddUser(company* client);
void UpdateUser(company* client);
void DeleteUser(company* client);
void DisplayAllUsers(company* client);
void DisplayUser(company* client);
void MakeData(company* client);
void ListUserLastAverTurnOver(company* client);
void PrintDetsFile(company* client);

//main
void main()
{
    bool signIn;

    //Declaring The Struct
    company* client;

    //Display
    printf("\n\t\tXYX Medical Supplier Ltd\n\n");

    //SignIn
    do {
        signIn = SignIn();

        if (signIn == true)
        {
            printf("\n\nCorrect Information entered!! \n");
        }

        else
        {
            printf("\n\nDENIED !!!\n");
            printf("Wrong UserName or Password\n\n");
        }
    } while (signIn == false);

    //Setting Up The Array
    client = (company*)malloc(50 * sizeof(company));
    //Unsure how to ask user for size when also reading in old companies from file
    //So i hardcoded it

    //Initalise  The Struct Array
    initArray(client);

    //Menu
    Menu(client);
}

//initialize array 
void initArray(company* client)
{
    FILE* clientDetails;

    //Set reg to -1
    for (int i = 0; i < 50; i++)
    {
        (*(client + i)).regisNum = -1;
    }

    //Read into Array from file
    clientDetails = fopen("Clients.txt", "r");

    if (clientDetails == NULL)
    {
        printf("\nError reading file");
    }
    else
    {
        for (int clRead = 0; clRead < 50; clRead++)
        {
            if ((*(client + clRead)).regisNum == -1)
            {
                fscanf(clientDetails, "%d ", &(*(client + clRead)).regisNum);
                fscanf(clientDetails, "%s ", &(*(client + clRead)).name);
                fscanf(clientDetails, "%s ", &(*(client + clRead)).country);
                fscanf(clientDetails, "%d ", &(*(client + clRead)).yearF);
                fscanf(clientDetails, "%s ", &(*(client + clRead)).email);
                fscanf(clientDetails, "%s ", &(*(client + clRead)).contactName);
                fscanf(clientDetails, "%f ", &(*(client + clRead)).lastOrder);
                fscanf(clientDetails, "%d ", &(*(client + clRead)).numOfEmployees);
                fscanf(clientDetails, "%d ", &(*(client + clRead)).vatRegist);
                fscanf(clientDetails, "%d ", &(*(client + clRead)).numStaff);
                fscanf(clientDetails, "%d ", &(*(client + clRead)).averageT);
                fscanf(clientDetails, "%d\n", &(*(client + clRead)).sector);
            }
        }
    }
}

//signIn
bool SignIn()
{
    char signInName[30];
    char pass[30];
    char userName[30];
    char userPass[30];

    int correctInfo = 0;
    int passwordLen = 0;

    //Askking the user for info
    printf("Please Enter Your Username: ");
    scanf("%s", &signInName);

    //Password
    printf("Please Enter Your Password: ");

    //This is cool prints * so pass is hidden
    do {
        pass[passwordLen] = getch();
        if (pass[passwordLen] != '\r') {
            printf("*");
        }
        passwordLen++;
    } while (pass[passwordLen - 1] != '\r');
    pass[passwordLen - 1] = '\0';
    getch();

    //File
    FILE* log;

    //Opening the file to read
    log = fopen("signIn.txt", "r");

    //Check if File Opened
    if (NULL == log) {
        printf("\n 101 ERROR!\n");
        printf("!THE FILE CANNOT BE OPENED! \n");
    }

    else
    {
        //Checking Entered info with file info
        while (correctInfo < 3)
        {
            //Read in & Assign info
            fscanf(log, "%s %s", userName, userPass);

            //If Entered details are same as file
            if (strcmp(userName, signInName) == 0)
            {
                if (strcmp(userPass, pass) == 0)
                {
                    correctInfo = 5;
                }
            }

            correctInfo++;
        }

        if (correctInfo > 4)
        {
            return true;
        }
    }
    return false;
}

//Menu
void Menu(company* client)
{
    int options;

    //Display Menu
    printf("\n\n\t----- Main Menu -----");
    printf("\n1: Add Client\n2: Display All Client Details\n3: Display Client Details\n4: Update A Client Details\n5: Delete Client\n6: Generate Statics\n7. Print All Clients Details To File\n8. List Clients In Order of Average Turnover \n");
    printf("Other to Exit\n");
    printf("Chosen Option: ");
    scanf("%d", &options);

    //depending on what option chosen

    //Option Choice
    switch (options)
    {
    case 1:
        AddUser(client);
        break;
    case 2:
        DisplayAllUsers(client);
        break;
    case 3:
        DisplayUser(client);
        break;
    case 4:
        UpdateUser(client);
        break;
    case 5:
        DeleteUser(client);
        break;
    case 6:
        MakeData(client);
        break;
    case 7:
        PrintDetsFile(client);
        break;
    case 8:
        ListUserLastAverTurnOver(client);
        break;
    default:
        PrintDetsFile(client);
        exit(0);
        break;
    }
}

//Option 1
//Add User
void AddUser(company* client)
{
    int currentUser;
    int unique;
    int check;

    char email[30];

    //Look For Next Free Array Entry
    for (int i = 0; i < 50; i++)
    {
        if ((*(client + i)).regisNum == -1)
        {
            do
            {
                //set to 0
                unique = 0;

                printf("\nEnter Users Register Number: ");
                scanf("%d", &currentUser);


                //Checking that number is unique
                for (int j = 0; j < 50; j++)
                {
                    if (currentUser == (*(client + j)).regisNum)
                    {
                        //Set Unique to -1 if reg already taken
                        unique = -1;
                    }
                }

                //not unique
                if (unique == -1)
                {
                    printf("\n\n101 !!ERROR!!");
                    printf("\nClient Register Is Not Unique!!\n");
                }

                else
                {
                    //when it is unique
                    (*(client + i)).regisNum = currentUser;
                }



            } while (unique == -1);

            //name
            printf("Company name: ");
            scanf("%s", (*(client + i)).name);

            //country
            printf("Companys country of origin: ");
            scanf("%s", (*(client + i)).country);

            //year founded
            printf("Year company was founded: ");
            scanf("%d", &(*(client + i)).yearF);

            //email
            do
            {
                check = 0;
                printf("\n (Insure to include @ + .com)\nCompany Email: ");
                scanf("%s", email);

                //is email in correct format
                if (strstr(email, "@") == NULL || strstr(email, ".com") == NULL)
                {
                    printf("\n 101 !!ERROR!!");
                    printf("\nMake sure email is entered correctly");
                    check = -1;
                }
            } while (check == -1);

            strncpy((*(client + i)).email, email, 30);

            //contact name
            printf("Company contact name: ");
            scanf("%s", &(*(client + i)).contactName);

            //last order
            printf("Last order: ");
            scanf("%f", &(*(client + i)).lastOrder);

            //employed
            printf("Amount of employees: ");
            scanf("%d", &(*(client + i)).numOfEmployees);

            //vat
            printf("Are they vat registed? (1: Yes 2 : No)\nPlease Select : ");
            scanf("%d", &(*(client + i)).vatRegist);

            //turnover
            printf("What is the average turnover? (1: Less than 1 Million 2: Less than 10 Million 3: Over 10 Million)\nPlease Select: ");
            scanf("%d", &(*(client + i)).averageT);

            //employed
            printf("How many are employed? (1: Less than 10 2: Less than 100 3: Over 100)\nPlease Select: ");
            scanf("%d", &(*(client + i)).numStaff);

            //sector
            printf("What sector is the company? (1: ICT 2: Medical Devices 3: Other)\nPlease Select: ");
            scanf("%d", &(*(client + i)).sector);

            //Print to Screen
            printf("Success!");
            printf("Taking you back to Menu");

            //Back to main menu
            Menu(client);
        }
    }

}

//Option 2 
//Display All User To SCreen
void DisplayAllUsers(company* client)
{
    char vat[20], averageTurn[20], sector[20], numStaff[20];
    int success = 0;

    for (int i = 0; i < 50; i++)
    {
        if ((*(client + i)).regisNum != -1)
        {
            success = 1;

            //print
            printf("\nRegister number: %d", (*(client + i)).regisNum);
            printf("\nCompany name: %s", (*(client + i)).name);
            printf("\nCountry based in: %s", (*(client + i)).country);
            printf("\nLast order amount: %.2f", (*(client + i)).lastOrder);
            printf("\nStaff employed: %d", (*(client + i)).numOfEmployees);
            printf("\nYear company founded: %d", (*(client + i)).yearF);
            printf("\nCompany contact email: %s", (*(client + i)).email);
            printf("\nCompany contact Name: %s", (*(client + i)).contactName);

            //vat
            printf("\nIs company vat registered: ");
            if ((*(client + i)).vatRegist == 1)
            {
                printf("Yes");
            }
            else
            {
                printf("No");
            }

            //turnover
            printf("\nAverage turnover: ");
            if ((*(client + i)).averageT == 1)
            {
                printf("Less than 1 Mil");
            }
            else if ((*(client + i)).averageT == 2)
            {
                printf("Less than 10 Million");
            }
            else
            {
                printf("Over 10 Million");
            }

            //employees
            printf("\nStaff employed: ");
            if ((*(client + i)).numStaff == 1)
            {
                printf("Less than 10");
            }
            else if ((*(client + i)).numStaff == 2)
            {
                printf("Less than 100");
            }
            else
            {
                printf("Over 100");
            }

            //sector
            printf("\nCompany sector: ");
            if ((*(client + i)).sector == 1)
            {
                printf("ICT");
            }
            else if ((*(client + i)).sector == 2)
            {
                printf("Medical Devices");
            }
            else
            {
                printf("Other");
            }
            printf("\n");
        }
    }

    if (success > 0)
    {
        printf("\n\nSuccess!");
    }
    else
    {
        printf("\n\n!Error, no clients to display");
    }

    printf("\nTaking you back to Menu");

    Menu(client);
}

//Option 3
//Display User
void DisplayUser(company* client)
{
    //Declare Variables
    int reg, success = 0;
    char vat[20], averageTurn[20], sector[20], numStaff[20];

    //Asking user what company to display
    printf("To display a company, enter its register number: ");
    scanf("%d", &reg);

    //find the one that matches
    for (int i = 0; i < 50; i++)
    {
        if ((*(client + i)).regisNum == reg)
        {
            success = 1;

            //print
            printf("\nRegister number: %d", (*(client + i)).regisNum);
            printf("\nCompany name: %s", (*(client + i)).name);
            printf("\nCountry based in: %s", (*(client + i)).country);
            printf("\nLast order amount: %.2f", (*(client + i)).lastOrder);
            printf("\nStaff employed: %d", (*(client + i)).numOfEmployees);
            printf("\nYear company founded: %d", (*(client + i)).yearF);
            printf("\nCompany contact email: %s", (*(client + i)).email);
            printf("\nCompany contact Name: %s", (*(client + i)).contactName);

            //vat
            printf("\nIs company vat registered: ");
            if ((*(client + i)).vatRegist == 1)
            {
                printf("Yes");
            }
            else
            {
                printf("No");
            }

            //turnover
            printf("\nAverage turnover: ");
            if ((*(client + i)).averageT == 1)
            {
                printf("Less than 1 Mil");
            }
            else if ((*(client + i)).averageT == 2)
            {
                printf("Less than 10 Million");
            }
            else
            {
                printf("Over 10 Million");
            }

            //employees
            printf("\nStaff employed: ");
            if ((*(client + i)).numStaff == 1)
            {
                printf("Less than 10");
            }
            else if ((*(client + i)).numStaff == 2)
            {
                printf("Less than 100");
            }
            else
            {
                printf("Over 100");
            }

            //sector
            printf("\nCompany sector: ");
            if ((*(client + i)).sector == 1)
            {
                printf("ICT");
            }
            else if ((*(client + i)).sector == 2)
            {
                printf("Medical Devices");
            }
            else
            {
                printf("Other");
            }
            printf("\n");
        }
    }


    if (success > 0)
    {
        printf("\n\nSuccess!");
    }
    else
    {
        printf("\n\n!Error, no clients to display");
    }

    printf("\nTaking you back to Menu");

    Menu(client);
}

//Option 4
// getting confused with adding User
//Update User
void UpdateUser(company* client)
{
    //Declare Variables
    int reg, check;
    char email[30];

    //Ask User which Company to Update
    printf("To update a company, enter its register number: ");
    scanf("%d", &reg);

    //Check for matching Reg
    for (int i = 0; i < 100; i++)
    {
        if ((*(client + i)).regisNum == reg)
        {
            ///name
            printf("Company name: ");
            scanf("%s", (*(client + i)).name);

            //country
            printf("Companys country of origin: ");
            scanf("%s", (*(client + i)).country);

            //year founded
            printf("Year company was founded: ");
            scanf("%d", &(*(client + i)).yearF);

            //email
            do
            {
                check = 0;
                printf("\n (Insure to include @ + .com)\nCompany Email: ");
                scanf("%s", email);

                //is email in correct format
                if (strstr(email, "@") == NULL || strstr(email, ".com") == NULL)
                {
                    printf("\n 101 !!ERROR!!");
                    printf("\nMake sure email is entered correctly");
                    check = -1;
                }
            } while (check == -1);

            strncpy((*(client + i)).email, email, 30);

            //contact name
            printf("Company contact name: ");
            scanf("%s", &(*(client + i)).contactName);

            //last order
            printf("Last order: ");
            scanf("%f", &(*(client + i)).lastOrder);

            //employed
            printf("Amount of employees: ");
            scanf("%d", &(*(client + i)).numOfEmployees);

            //vat
            printf("Are they vat registed? (1: Yes 2 : No)\nPlease Select : ");
            scanf("%d", &(*(client + i)).vatRegist);

            //turnover
            printf("What is the average turnover? (1: Less than 1 Million 2: Less than 10 Million 3: Over 10 Million)\nPlease Select: ");
            scanf("%d", &(*(client + i)).averageT);

            //employed
            printf("How many are employed? (1: Less than 10 2: Less than 100 3: Over 100)\nPlease Select: ");
            scanf("%d", &(*(client + i)).numStaff);

            //sector
            printf("What sector is the company? (1: ICT 2: Medical Devices 3: Other)\nPlease Select: ");
            scanf("%d", &(*(client + i)).sector);

            //////////////////////////////////////////////////////
            //basically same as adding user

            printf("\nSucess!");
            printf("\nTaking you back to menu");

            Menu(client);
        }
    }
}

// Option 5
//Delete User
void DeleteUser(company* client)
{
    int reg;
    int check;

    printf("To delete a company, enter its register number: ");
    scanf("%d", &reg);

    printf("Are you sure you wish to delete company %d? (1 for yes, 0 for no)", reg);
    //printf("");
    scanf("%d", &check);

    //look for matching register
    for (int i = 0; i < 50; i++)
    {
        if ((*(client + i)).regisNum == reg && check == 1)
        {
            //reg number
            (*(client + i)).regisNum = -1;
            //Only resetting this as this will tell the computer that its ready to be used and overwrite
            //the existing data saved


            printf("\nSuccess!");
            printf("\nUser Has Been Deleted!");

            Menu(client);
        }
    }

    printf("!Error, client not found");

    Menu(client);
}

// Option 6
//Generate Statistics 
void MakeData(company* client)
{
    int choice;
    int employ;
    int sector;
    int count = 0;
    int oneMil = 0;
    int tenMil = 0;
    int overTenMil = 0;
    int perc1Mil;
    int perc10Mil;
    int percOver;

    //choose an option
    printf("Display data by 1 for Sector or 2 for amount of employees");
    scanf("%d", &choice);

    //area
    if (choice == 1)
    {
        printf("Choose 1 for ICT 2 for medical devices 3 for other");
        scanf("%d", &sector);

        for (int i = 0; i < 50; i++)
        {
            if ((*(client + i)).regisNum != -1)
            {
                //printf("%d", (*(client + i)).sector);
                if ((*(client + i)).sector == sector)
                {
                    //update counter
                    count++;

                    if ((*(client + i)).averageT == 1)
                    {
                        oneMil++;
                    }
                    else if ((*(client + i)).averageT == 2)
                    {
                        tenMil++;
                    }
                    else if ((*(client + i)).averageT == 3)
                    {
                        overTenMil++;
                    }
                }
            }
        }
    }

    //employees
    if (choice == 2)
    {
        printf("Choose 1 for Less than 10 2 for Less than 100 3 for More than 100");
        scanf("%d", &employ);

        for (int i = 0; i < 50; i++)
        {
            if ((*(client + i)).regisNum != -1)
            {
                if ((*(client + i)).numStaff == employ)
                {
                    count++;
                    if ((*(client + i)).averageT == 1)
                    {
                        oneMil++;
                    }
                    else if ((*(client + i)).averageT == 2)
                    {
                        tenMil++;
                    }
                    else if ((*(client + i)).averageT == 3)
                    {
                        overTenMil++;
                    }
                }
            }
        }
    }

    //The maths behind the stats
    perc1Mil = (oneMil / count);
    perc10Mil = (tenMil / count);
    overTenMil = (overTenMil / count);

    printf("\nThe Data:");
    printf("\nLess than 1 Million: %d ", perc1Mil);
    printf("\nLess than 10 Million: 100%", perc10Mil);
    printf("\nMore than 10 Million: %d", overTenMil);

    printf("\nSucess!!");
    printf("\n\nStats Printed");


    Menu(client);
}

//Option 7
//Print User deatials to File
void PrintDetsFile(company* client)
{
    int test = 3;

    //File
    FILE* newFile;

    newFile = fopen("clients.txt", "w");

    //Writing to File
    for (int j = 0; j < 50; j++)
    {
        if ((*(client + j)).regisNum != -1)
        {

            fprintf(newFile, "%d ", (*(client + j)).regisNum);
            fprintf(newFile, "%s ", (*(client + j)).name);
            fprintf(newFile, "%s ", (*(client + j)).country);
            fprintf(newFile, "%d ", (*(client + j)).yearF);
            fprintf(newFile, "%s ", (*(client + j)).email);
            fprintf(newFile, "%s ", (*(client + j)).contactName);
            fprintf(newFile, "%.2f ", (*(client + j)).lastOrder);
            fprintf(newFile, "%d ", (*(client + j)).numOfEmployees);
            fprintf(newFile, "%d ", (*(client + j)).vatRegist);
            fprintf(newFile, "%d ", (*(client + j)).numStaff);
            fprintf(newFile, "%d ", (*(client + j)).averageT);
            fprintf(newFile, "%d\n", (*(client + j)).sector);
        }
    }

    fclose(newFile);

    Menu(client);
}

//option 8
//List by Average Turnover
void ListUserLastAverTurnOver(company* client)
{
    int oldest;
    int oldestNum = 0;
    int right = 0;
    int first = 0;

    //set first one as oldest to compare 
    //this way it isnt 0
    oldest = (*(client)).yearF;

    for (int j = 0; j < 50; j++)
    {
        right = 0;
        for (int i = 0; i < 50; i++)
        {
            if (oldest < (*(client + i)).yearF && (*(client + i)).regisNum != -1)
            {
                oldest = (*(client + i)).yearF;
                i = i;
                right = 1;
            }
        }
        if (right == 1 || first == 0)
        {
            first = 1;

            //print
            printf("\nRegister number: %d", (*(client + oldestNum)).regisNum);
            printf("\nCompany name: %s", (*(client + oldestNum)).name);
            printf("\nCountry based in: %s", (*(client + oldestNum)).country);
            printf("\nLast order amount: %.2f", (*(client + oldestNum)).lastOrder);
            printf("\nStaff employed: %d", (*(client + oldestNum)).numOfEmployees);
            printf("\nYear company founded: %d", (*(client + oldestNum)).yearF);
            printf("\nCompany contact email: %s", (*(client + oldestNum)).email);
            printf("\nCompany contact Name: %s", (*(client + oldestNum)).contactName);

            //vat
            printf("\nIs company vat registered: ");
            if ((*(client + oldestNum)).vatRegist == 1)
            {
                printf("Yes");
            }
            else
            {
                printf("No");
            }

            //turnover
            printf("\nAverage turnover: ");
            if ((*(client + oldestNum)).averageT == 1)
            {
                printf("Less than 1 Million");
            }
            else if ((*(client + oldestNum)).averageT == 2)
            {
                printf("Less than 10 Million");
            }
            else
            {
                printf("Over 10 Million");
            }

            //employees
            printf("\nStaff employed: ");
            if ((*(client + oldestNum)).numStaff == 1)
            {
                printf("Less than 10");
            }
            else if ((*(client + oldestNum)).numStaff == 2)
            {
                printf("Less than 100");
            }
            else
            {
                printf("Over 100");
            }

            //sector
            printf("\nCompany sector: ");
            if ((*(client + oldestNum)).sector == 1)
            {
                printf("ICT");
            }
            else if ((*(client + oldestNum)).sector == 2)
            {
                printf("Medical Devices");
            }
            else
            {
                printf("Other");
            }
            printf("\n");
        }

    }
}