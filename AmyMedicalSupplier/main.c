//Amy Waldron
//G00395091
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//All The Structs

//Details Of The Company
typedef struct
{
    //ints
    int regisNum;
    int yearFounded;
    int numOfEmployees;
    int data;//The Struct
    int choiceOne, optionTwo;

    //chars
    char name[30];
    char country[30];
    char email[30];
    char contactName[30];

    //for questions
    char regVat[5];
    char averTurnOver[30];
    char areaOfSales[30];
    char numStaff[30];

    //floats
    float lastOrder;
    float averAnnualOrder;

}company;

//Data 
typedef struct
{
    int lessOneMil; 
    int lessTenMil;
    int overTenMil;
    int choiceOne;
    int options;
}data;

//Sign in
typedef struct
{
    char signInName[20];
    char password[20];
}signIn;

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
//Functions
bool SignIn();
void initArray(company* client, data statsGen);
void Menu(company* client, data statsGen);
void AddUser(company* client, data statsGen);
void UpdateUser(company* client, data statsGen);
void DeleteUser(company* client, data statsGen);
void DisplayAllUsers(company* client, data statsGen);
void DisplayUser(company* client, data statsGen);
void MakeData(company* client, data statsGen);
void ListUserLastAverTurnOver(company* client, data statsGen);
void PrintDetsFile(company* client, data statsGen);


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

//Main Method
void main()
{
    //Declaring The Struct
    company* client;
    data statsGen;

    //Setting Up The Array
    client = (company*)malloc(100 * sizeof(company));

    //Display
    printf("\n\t\t*\t      XYX Medical Supplier Ltd       \t  *");
    printf("\n \n");
    //Variables
    bool signIn;

    //Ask User to SignIn
    do {
        signIn = SignIn();

        if (signIn == true)
        {
            printf("\n\n\n--------------------------------------");
            printf("\n\t Correct Information entered!! \n");
            printf("\n--------------------------------------");
        }

        else
        {
            printf("\n\n\n--------------------------------------");
            printf("\n\t DENIED !!!\n");
            printf("\n\t Wrong Inormation Enetered \n");
            printf("\n\t Wrong UserName or Password \n");
            printf("\n--------------------------------------\n\n");
        }
    } while (signIn == false);

    statsGen.options = 0;

    //Initalise  The Struct Array
    initArray(client, statsGen);

    //Menu
    Menu(client, statsGen);
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

//Initialize The Array And Print Data To File
void initArray(company* client, data statsGen)
{
    FILE* StoredInfo;

    //Set Array to -1
    for (int i = 0; i < 100; i++)
    {
        (*(client + i)).regisNum = -1;
    }

    //Read into Array from file
    StoredInfo = fopen("Clients.txt", "r");

    if (StoredInfo != NULL)
    {
        for (int j = 0; j < 100; j++)
        {
            if ((*(client + j)).regisNum == -1)
            { 
                fscanf(StoredInfo, "%d %s %s %d %s ", &(*(client + j)).regisNum, &(*(client + j)).name, &(*(client + j)).country, &(*(client + j)).yearFounded, &(*(client + j)).email);
                fscanf(StoredInfo, "%s %.2f %d %.2f ", &(*(client + j)).contactName, &(*(client + j)).lastOrder, &(*(client + j)).numOfEmployees, &(*(client + j)).averAnnualOrder);
                fscanf(StoredInfo, "%s %s %s %s ", &(*(client + j)).regVat, &(*(client + j)).averTurnOver, &(*(client + j)).numStaff, &(*(client + j)).areaOfSales);
                fscanf(StoredInfo, "%d %d %d\n", &(*(client + j)).data, &(*(client + j)).choiceOne, &(*(client + j)).optionTwo);
          
            
                //when im reading in from file to set the struct at the start its only reading in one company and i have 3 in the text file 
                
                //I cant get this to work 
                //this is how you do it though

               /* create previous node = NULL
                    create head node = NULL

                    while (still have lines) {
                        assign values to a new node
                            new node->next = NULL

                            if (head node == NULL) head node = new node
                            else previous node->next = new node

                                previous node = new node
                    }*/
            
            }
        }
    }

}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

//signIn
bool SignIn()
{
    //Struct Varible
    struct signIn* login1;

    //Variables
    char signInName[30];
    char pass[30];
    char UserNam[30];
    char UserPass[30];
   
    int correctInfo = 0;
    int passwordLen = 0;
    int endFile;

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

    //Getting the file
    FILE* log;

    //Opening the file
    log = fopen("signIn.txt", "r");

    //Check if File Opened
    if (NULL == log) {
        printf("\n 101 ERROR!\n");
        printf("!THE FILE CANNOT BE OPENED! \n");
    }
    
    else
    {
        endFile = getc(log);
        
        //printing out file info
        while (correctInfo < 4)
        {
            fscanf(log, "%s %s", UserNam, UserPass);

            printf("hello");
            if (strcmp(UserNam, signInName) == 0)
            {
                printf("hello");
                if (strcmp(UserPass, pass) == 0)
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

        else
        {
            return false;
        }
    }
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

//Menu
void Menu(company* client, data statsGen)
{
    //Variables
    int options;

    //Display Menu
    printf("\n\n\t----- Main Menu -----");
    printf("\nChoose an option");
    printf("\n1: Add Client\n2: Display All Client Details\n3: Display Client Details\n4: Update A Client Details\n5: Delete Client\n6: Generate Statics\n7. Print All Clients Details To File\n8. List Clients In Order of Average Turnover \n");
    printf("Other to Exit\n");
    printf("Chosen Option: ");
    scanf("%d", &options);

    //depending on what option chosen

    //Option Choice
    switch (options)
    {
    case 1:
        AddUser(client, statsGen);
        break;
    case 2:
        DisplayAllUsers(client, statsGen);
        break;
    case 3:
        DisplayUser(client, statsGen);
        break;
    case 4:
        UpdateUser(client, statsGen);
        break;
    case 5:
        DeleteUser(client, statsGen);
        break;
    case 6:
        MakeData(client, statsGen);
        break;
    case 7:
        PrintDetsFile(client, statsGen);
        break;
    case 8:
        ListUserLastAverTurnOver(client, statsGen);
        break;
    default:
        PrintDetsFile(client, statsGen);
        exit(0);
        break;
    }
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

//Option 1
//Add User
void AddUser(company* client, data statsGen)
{
    //Variables
    int currentUser;
    int unique; 
    int check;
    int vat;
    int averTurnover;
    int numOfStaff;
    int areaOfSales;
    
    char email[30];

    //Look For Next Free Array Entry
    for (int i = 0; i < 100; i++)
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
                for (int j = 0; j < 100; j++)
                {
                    if (currentUser == (*(client + j)).regisNum)
                    {
                        unique = -1;
                    }
                }

               //not unique
                if (unique == -1)
                {
                    printf("\n\n101 !!ERROR!!");
                    printf("\nClient Reisgter Is Not Unique!!\n");
                }

                else
                {
                   //when it is unique
                    (*(client + i)).regisNum = currentUser;
                }



            } while (unique == -1);

            //The Company Name
            printf("Please Enter Company Name: ");
            scanf("%s", (*(client + i)).name);

            //The Company Country
            printf("Please Enter Companys Country: ");
            scanf("%s", (*(client + i)).country);

            //The Year Founded
            printf("Please Enter Year Company was founded: ");
            scanf("%d", &(*(client + i)).yearFounded);

            //The Company Email Address
            do
            {
                check = 0;
                printf("Please Enter Company Email: ");
                printf("\n (Insure to include @ + .com)\nEmail: ");
                scanf("%s", email);

                //is email unique and has correct format
                if (strstr(email, "@") == NULL || strstr(email, ".com") == NULL)
                {
                    printf("\n 101 !!ERROR!!");
                    printf("\nPlease enter a @ and .com");
                    check = -1;
                }
            } while (check == -1);

            strncpy((*(client + i)).email, email, 30);

            //Company Contact Name
            printf("Please Enter Company Contact Name: ");
            scanf("%s", &(*(client + i)).contactName);

            //Last Order
            printf("Please Enter Last Order Amount: ");
            scanf("%f", &(*(client + i)).lastOrder);

            //Number of Employees
            printf("Please Enter Number of Employees: ");
            scanf("%d", &(*(client + i)).numOfEmployees);

            //Average Annual Order
            printf("Please Enter Average Annual Order: ");
            scanf("%f", &(*(client + i)).averAnnualOrder);

            //Vat Registered
            printf("Is the Client Vat Registered (1: Yes 2:No)\nPlease Select: ");
            scanf("%d", &vat);

            //Client Average Turnover
            printf("What are the Clients Average Turnover (1: Less than 1 Million 2: Less than 10 Million 3: Over 10 Million)\nPlease Select: ");
            scanf("%d", &(*(client + i)).data);
            averTurnover = (*(client + i)).data;

            //Staff Employed
            printf("How many numOfStaff are employed (1: Less than 10 2: Less than 100 3: Over 100)\nPlease Select: ");
            scanf("%d", &(*(client + i)).optionTwo);
            numOfStaff = (*(client + i)).optionTwo;

            //Which Area of Sales is the company
            printf("Which Area of Sales is the Company (1: ICT 2: Medical Devices 3: Other)\nPlease Select: ");
            scanf("%d", &(*(client + i)).choiceOne);
            areaOfSales = (*(client + i)).choiceOne;


            //is The Vat Registered
            if (vat == 1)
            {
                strncpy((*(client + i)).regVat, "Yes", 5);
            }
            else
            {
                strcpy((*(client + i)).regVat, "No", 5);
            }

            //Average Turnover
            if (averTurnover == 1)
            {
                strncpy((*(client + i)).averTurnOver, "Less than 1 Mil", 30);
            }
            else if (averTurnover == 2)
            {
                strncpy((*(client + i)).averTurnOver, "Less than 10 Million", 30);
            }
            else
            {
                strncpy((*(client + i)).averTurnOver, "Over 10 Million", 30);
            }

            //Number Of Staff
            if (numOfStaff == 1)
            {
                strncpy((*(client + i)).numStaff, "Less than 10", 30);
            }
            else if (numOfStaff == 2)
            {
                strncpy((*(client + i)).numStaff, "Less than 100", 30);
            }
            else
            {
                strncpy((*(client + i)).numStaff, "Over 100", 30);
            }

            //Area Of sales
            if (areaOfSales == 1)
            {
                strncpy((*(client + i)).areaOfSales, "ICT", 30);
            }
            else if (areaOfSales == 2)
            {
                strncpy((*(client + i)).areaOfSales, "Medical Devices", 30);
            }
            else
            {
                strncpy((*(client + i)).areaOfSales, "Other ", 30);
            }

            //Print to Screen
            printf("Success!");
            printf("A New User has Added!");

            //Back to main menu
            Menu(client, statsGen);
        }
    }

}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////


// Option 2 
//Display All User To SCreen
void DisplayAllUsers(company* client, data statsGen)
{
    for (int i = 0; i < 100; i++)
    {
        if ((*(client + i)).regisNum != -1)
        {
            //Print to screen
            printf("\nClient Reg Number: %d\nName: %s\nCountry: %s", (*(client + i)).regisNum, (*(client + i)).name, (*(client + i)).country);
            printf("\nLast Order: %.2f\nNumber of Employees: %d\nAverage Annual Order: %.2f", (*(client + i)).lastOrder, (*(client + i)).numOfEmployees, (*(client + i)).averAnnualOrder);
            printf("\nYear Founded: %d\nEmail: %s\nContact Name: %s", (*(client + i)).yearFounded, (*(client + i)).email, (*(client + i)).contactName);
            printf("\nVat Registered: %s\nAverage Turnover: %s\nStaff: %s\nArea: %s", (*(client + i)).regVat, (*(client + i)).averTurnOver, (*(client + i)).numStaff, (*(client + i)).areaOfSales);
        }
    }

    printf("\n Success!");
    printf("\n All Users Have Been Displayed");

    Menu(client, statsGen);
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////


// Option 3
//Display User
void DisplayUser(company* client, data statsGen)
{
    //Declare Variables
    int reg;

    //Asking user what company to display
    printf("Please Enter The Reguster Number of Company you wish to Display: ");
    scanf("%d", &reg);

    //find the one that matches
    for (int i = 0; i < 100; i++)
    {
        if ((*(client + i)).regisNum == reg)
        {
            //print to screen
            printf("\nClient Reg Number: %d\nName: %s\nCountry: %s", (*(client + i)).regisNum, (*(client + i)).name, (*(client + i)).country);
            printf("\nYear Founded: %d\nEmail: %s\nContact Name: %s", (*(client + i)).yearFounded, (*(client + i)).email, (*(client + i)).contactName);
            printf("\nLast Order: %,.2f\nNumber of Employees: %d\nAverage Annual Order: %,.2f", (*(client + i)).lastOrder, (*(client + i)).numOfEmployees, (*(client + i)).averAnnualOrder);
            printf("\nVat Registered: %s\nAverage Turnover: %s\nStaff: %s\nArea: %s", (*(client + i)).regVat, (*(client + i)).averTurnOver, (*(client + i)).numStaff, (*(client + i)).areaOfSales);
        }
    }

    printf("\n Success!");
    printf("\nUser is Displayed");


    Menu(client, statsGen);
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

// Option 4
// getting confused with adding User
//Update User
void UpdateUser(company* client, data statsGen)
{
    //Declare Variables
    int reg, check, vat, avTurn, numStaff, areaOfSales;
    char email[30];

    //Ask User which Company to Update
    printf("Please Enter Reg Number of Company you wish to Update: ");
    scanf("%d", &reg);

    //Check for matching Reg
    for (int i = 0; i < 100; i++)
    {
        if ((*(client + i)).regisNum == reg)
        {
            //The Company Name
            printf("Please Enter Company Name: ");
            scanf("%s", (*(client + i)).name);

            //The Company Country
            printf("Please Enter Companys Country: ");
            scanf("%s", (*(client + i)).country);

            //The Year Company Founded
            printf("Please Enter Year Company was founded: ");
            scanf("%d", &(*(client + i)).yearFounded);

           

            do
            {
                check = 0;
                printf("Please Enter Company Email: ");
                printf("\n (Insure to include @ + .com)\nEmail: ");
                scanf("%s", email);

                //is email unique and has correct format
                if (strstr(email, "@") == NULL || strstr(email, ".com") == NULL)
                {
                    printf("\n 101 !!ERROR!!");
                    printf("\nPlease enter a @ and .com");
                    check = -1;
                }
            } while (check == -1);

            strncpy((*(client + i)).email, email, 30);

            //Company Contact Name
            printf("Please Enter Company Contact Name: ");
            scanf("%s", &(*(client + i)).contactName);

            //Number Staff Employed
            printf("How many Staff are employed (1: Less than 10 2: Less than 100 3: Over 100)\nPlease Pick An Option: ");
            scanf("%d", &(*(client + i)).optionTwo);
            numStaff = (*(client + i)).optionTwo;

            //Last Order
            printf("Please Enter Last Order Amount: ");
            scanf("%f", &(*(client + i)).lastOrder);

            //Number of Employees
            printf("Please Enter Number of Employees: ");
            scanf("%d", &(*(client + i)).numOfEmployees);

            //Client Average Turnover
            printf("What are the Clients Average Turnover (1: Less than 1 Million 2: Less than 10 Million 3: Over 10 Million)\nPlease Pick An Option: ");
            scanf("%d", &(*(client + i)).data);
            avTurn = (*(client + i)).data;

            //Average Annual Order
            printf("Please Enter Average Annual Order: ");
            scanf("%f", &(*(client + i)).averAnnualOrder);

            //Which Area of Sales is the company
            printf("Which Area of Sales is the Company (1: ICT 2: Medical Devices 3: Other)\nPlease Pick An Option: ");
            scanf("%d", &(*(client + i)).choiceOne);
            areaOfSales = (*(client + i)).choiceOne;

            //Vat Registered
            printf("Is the Client Vat Registered (1: Yes 2:No)\nPlease Pick An Option: ");
            scanf("%d", &vat);
   

            //////////////////////////////////////////////////////
            //basically same as adding user

            //Is Vat Regitered
            if (vat == 1)
            {
                strncpy((*(client + i)).regVat, "Yes", 5);
            }
            else
            {
                strcpy((*(client + i)).regVat, "No", 5);
            }


            //Number OF Staff
            if (numStaff == 1)
            {
                strncpy((*(client + i)).numStaff, "Less than 10", 25);
            }
            else if (numStaff == 2)
            {
                strncpy((*(client + i)).numStaff, "Less than 100", 25);
            }
            else
            {
                strncpy((*(client + i)).numStaff, "Over 100", 25);
            }

            //Area Of Sales
            if (areaOfSales == 1)
            {
                strncpy((*(client + i)).areaOfSales, "ICT", 25);
            }
            else if (areaOfSales == 2)
            {
                strncpy((*(client + i)).areaOfSales, "Medical Devices", 25);
            }
            else
            {
                strncpy((*(client + i)).areaOfSales, "Other ", 25);
            }

            //Average Turnover
            if (avTurn == 1)
            {
                strncpy((*(client + i)).averTurnOver, "Less than 1 Million", 25);
            }
            else if (avTurn == 2)
            {
                strncpy((*(client + i)).averTurnOver, "Less than 10 Million", 25);
            }
            else
            {
                strncpy((*(client + i)).averTurnOver, "Over 10 Million", 25);
            }

            printf("\nSucess!");
            printf("\nUser has been updated!");

           
            Menu(client, statsGen);
        }
    }
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////


// Option 5
//Delete User
void DeleteUser(company* client, data statsGen)
{
    //Declare Variables
    int reg;

    printf("Please Enter Reg Number of Company you wish to Delete: ");
    scanf("%d", &reg);

    //look for matching register
    for (int i = 0; i < 100; i++)
    {
        if ((*(client + i)).regisNum == reg)
        {
            //Register Number
            (*(client + i)).regisNum = -1;

            //Resetting them all back All
            strncpy((*(client + i)).name, "", 30);
            strncpy((*(client + i)).country, "", 30);
            (*(client + i)).yearFounded = 0;
            strncpy((*(client + i)).email, "", 30);
            strncpy((*(client + i)).contactName, "", 30);
            strncpy((*(client + i)).averTurnOver, "", 30);
            strncpy((*(client + i)).areaOfSales, "", 30);
            strncpy((*(client + i)).numStaff, "", 30);
            strncpy((*(client + i)).regVat, "", 5);
            (*(client + i)).lastOrder = 0.0;
            (*(client + i)).numOfEmployees = 0;
            (*(client + i)).averAnnualOrder = 0.0;
            (*(client + i)).data = 0;
            (*(client + i)).choiceOne = 0;
            (*(client + i)).optionTwo = 0;
        
            printf("\nSuccess!");
            printf("\nUser Has Been Deleted!");

            Menu(client, statsGen);
        }
    }
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////


// Option 6
//Generate Statistics 
void MakeData(company* client, data statsGen)
{
    //Variables
    int choice;
    int numE;
    int areaOfSales;
    int count = 0;
    
    int a = 0, b = 0, c = 0;

    int lessOneMil, lessTenMil, overTenMil;

    //choose an option
    printf("Would you like data done by 1: Area of Company or 2: Number of Employees");
    scanf("%d", &choice);
    statsGen.choiceOne = choice;


    if (choice == 1)
    {
        //setting to 0
        a = 0;
        b = 0;
        c = 0;
        count = 0;

        printf("Choose 1: ICT 2: Medical Devices 3: Other");
        scanf("%d", &areaOfSales);
        statsGen.options = areaOfSales;

        for (int i = 0; i < 100; i++)
        {
            if ((*(client + i)).regisNum != -1)
            {
                if ((*(client + i)).choiceOne == areaOfSales)
                {
                    count++;

                    switch ((*(client + i)).data)
                    {
                    case 1:
                        a++;
                        break;
                    case 2:
                        b++;
                        break;
                    case 3:
                        c++;
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }

    //Number Of Employees
    if (choice == 2)
    {
        //Setting to 0
        a = 0;
        b = 0;
        c = 0;
        count = 0;

        printf("Choose 1: Less than 10 Million 2: Less than 100 Million 3: More than 100 Million");
        scanf("%d", &numE);
        statsGen.options = numE;

        for (int i = 0; i < 100; i++)
        {
            if ((*(client + i)).regisNum != -1)
            {
                if ((*(client + i)).optionTwo == numE)
                {
                    count++;

                    switch ((*(client + i)).data)
                    {
                    case 1:
                        a++;
                        break;
                    case 2:
                        b++;
                        break;
                    case 3:
                        c++;
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }

    //The maths behind the stats
    lessOneMil = (a / count) * 100;
    lessTenMil = (b / count) * 100;
    overTenMil = (c / count) * 100;

    statsGen.lessOneMil = lessOneMil;
    statsGen.lessTenMil = lessTenMil;
    statsGen.overTenMil = overTenMil;

    printf("\nThe Data:");
    printf("\nLess than 1 Million: %d %", lessOneMil);
    printf("\nLess than 10 Million: %d %", lessTenMil);
    printf("\nMore than 10 Million: %d %", overTenMil);

    printf("\nSucess!!");
    printf("\n\nStats Printed");

    
    Menu(client, statsGen);
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

//Option 7
//Print User deatials to File
void PrintDetsFile(company* client, data statsGen)
{
    //varibles
    int test = 3;
    
    //Creating Object of File
    FILE* newFile;
    FILE* data;

    //File open
    newFile = fopen("Clients.txt", "a");

    //Writing to File
    for (int j = 0; j < 100; j++)
    {
        if ((*(client + j)).regisNum != -1)
        {
            
            fprintf(newFile, "%d %s %s %d %s ", (*(client + j)).regisNum, (*(client + j)).name, (*(client + j)).country, (*(client + j)).yearFounded, (*(client + j)).email);
            fprintf(newFile, "%s %.2f %d %.2f ", (*(client + j)).contactName, (*(client + j)).lastOrder, (*(client + j)).numOfEmployees, (*(client + j)).averAnnualOrder);
            fprintf(newFile, "%s %s %s %s ", (*(client + j)).regVat, (*(client + j)).averTurnOver, (*(client + j)).numStaff, (*(client + j)).areaOfSales);
            fprintf(newFile, "%d %d %d\n", (*(client + j)).data, (*(client + j)).choiceOne, (*(client + j)).optionTwo);
        }
    }

    fclose(newFile);

    //Stats File
    //Data
    data = fopen("Stats.txt", "a");

    for (int j = 0; j < 100; j++)
    {
        if ((*(client + j)).regisNum != -1)
        {
            //pritning
            fprintf(data, "%d %d %d %d %d\n", statsGen.options, statsGen.choiceOne, statsGen.lessOneMil, statsGen.lessTenMil, statsGen.overTenMil);
        }
    }

    //closing file
    fclose(data);

  
    Menu(client, statsGen);
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////








//List by Average Turnover
void ListUserLastAverTurnOver(company* client, data statsGen)
{


}