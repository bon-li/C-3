/*
* C Program creates a linked list that contains part number, part name, and on hand quantity.
*  User can insert new parts, search for a product, update a product, and display all products.
*/
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

const int NAME_LEN = 10;

//Node structure created
struct part {
    int number;
    char name[NAME_LEN+1]; 
    int on_hand;
    struct part *next;
};

typedef struct part *node;

//Function declarations
node i(node inventory);
node s(node inventory);
void u(node inventory);
void p(node inventory);
bool validateInput(char num[]);

//Main function for menu
int main() 
{
    //Variable declaration
    bool checkValid = true;
    char num[256];
    int choice = 0;
    node partPtr;
    node inventory = NULL;

    //User menu for inserting, searching, update, displaying product
    printf("Product menu\n");
    while(choice != 5){

        checkValid = false;

        do 
        {
            printf("1) Insert new product\n");
            printf("2) Search for a product\n");
            printf("3) Update a product\n");
            printf("4) Display all products\n");
            printf("5) Exit program\n");
            scanf("%s", num);
            checkValid = validateInput(num);

            //Checks for valid input
            if (checkValid == false) 
            {
                printf("\nEntered value was not a positive integer.\n");
            }

        }while(checkValid == false);

        choice = atoi(num);
        
        switch (choice) 
        {
            //Insert new product
            case 1:
                inventory = i(inventory);
                break;

            //Search for a product
            case 2:
                partPtr = s(inventory);
                if (partPtr != NULL) 
                {
                    printf("Product found:\nPart Number: %d Part Name: %s Quantity: %d\n", partPtr -> number, partPtr -> name, partPtr -> on_hand);
                } 
                else 
                {
                    printf("Unable to find part number.\n");
                }
                break;

            //Update a product
            case 3:
                u(inventory);
                break;

            //Display all products
            case 4:
                p(inventory);
                break;
            
            //Exits program
            case 5:
                printf("Program is terminating.\n");
                break;
            
            default:
                printf("\nInvalid option.\n");
                break;
        }
    }
}

//Inserts new product into list
node i(node inventory) 
{
    //Variable declaration
    char num[256];
    char q[256];
    char partName[NAME_LEN+1];
    int partNum;
    int quantity;
    int flag = 0;
    bool checkValid = true;
    node checkPtr;
    node temp;
    node ptr = inventory;

    do 
    {
        flag = 1;
        checkValid = true;

        //Asks user for new part number
        printf("Enter a new part number:\n");
        scanf("%s",num);
        checkValid = validateInput(num);
        //Validates part number
        if (checkValid == false) 
        {
            flag = 0;
        }
        else if (checkValid == true) 
        {
            partNum = atoi(num);
            if(ptr == NULL) {

            }
            else{
                //Searches for part number
                while(ptr -> number != partNum && ptr -> next != NULL) 
                {
                    ptr = ptr -> next;
                }

                if(ptr -> number == partNum) 
                {
                    flag = 0;
                } 
            }
        }

        printf("Enter part name:\n");
        scanf("%s", partName);
        //Checks for empty part name
        if(strlen(partName) == 0) 
        {
            checkValid = false;
            flag = 0;
        }

        printf("Enter initial quantity:\n");
        scanf("%s",q);
        checkValid = validateInput(q);

        //Validates quantity input
        if (checkValid == false) 
        {
            flag = 0;
        }
        else if (checkValid == true) 
        {
            quantity = atoi(q);
        }

        if (flag == 0) 
        {
            printf("Unable to input data. Please try again.\n");
        }

    }while(flag == 0);
    
    //Allocates memory for new node
    temp = (node)malloc(sizeof(struct part));
    if (temp == NULL) 
    {
        printf("Out of memory space.\n");
    } 
    else 
    {
        temp -> next = NULL;
    }
    
    //Saves user input into temp node
    temp -> number = partNum;
    strcpy(temp -> name, partName);
    temp -> on_hand = quantity;

    //Saves temp node in empty inventory
    if (inventory == NULL) 
    {
        inventory = temp;
        printf("New product has been added.\n");
        return inventory;
    }

    ptr = inventory;

    //Orders new product by part number
    if (inventory == NULL || inventory -> number >= temp -> number) 
    {
            //Temp node is saved
            temp -> next = inventory;
            inventory = temp;
            printf("New product has been added.\n");
    } 
    else 
    {
        //Orders new product by part number
        while (ptr -> next != NULL && ptr -> next -> number < temp -> number)
        {
            ptr = ptr -> next;
        }
            //Inserts new product
            temp -> next = ptr -> next;
            ptr -> next = temp;
            printf("New product has been added.\n");
    }

    return inventory;
}

//Searches for a product in list
node s(node inventory) 
{
    //Variable declaration
    char pnum[256];
    int partNum;
    bool checkValid = false;
    bool pValid = false;
    node ptr = inventory;

    //Checks for empty list
    if(inventory == NULL) 
    {
        printf("\nNo products found.\n");
        return NULL;
    }

    while (pValid == false) 
    {
        while (checkValid == false) 
        {
            //Gets user input for part number
            printf("Enter part number:\n");
            scanf("%s", pnum);
            checkValid = validateInput(pnum);

            //Validates user iput
            if(checkValid == false) 
            {
                printf("Input is invalid.\n");
            } 
        }
        partNum = atoi(pnum);

        //Searches for part number
        while(ptr -> number != partNum && ptr -> next != NULL) 
        {
            ptr = ptr -> next;
        }

        //Displays product found
        if(ptr -> number == partNum) 
        {
            pValid = true;
            return ptr;
        } 
        else 
        {
            //Product not found
            checkValid = false;
            pValid = false;
            ptr = inventory;
            return NULL;
        }
    }
    return NULL;
}

//Updates a product in list
void u(node inventory) 
{
    //Variable declaration
    char pnum[256];
    char qnum[256];
    int partNum;
    int quantity;
    bool checkValid = false;
    bool pValid = false;
    bool qValid = false;
    node ptr = inventory;

    //Checks for empty list
    if(inventory == NULL) 
    {
        printf("\nNo products found.\n");
        return;
    }

    while (pValid == false) 
    {
        while (checkValid == false) 
        {
            //Asks user for part number
            printf("Enter part number:\n");
            scanf("%s", pnum);
            checkValid = validateInput(pnum);

            //Validates user input
            if(checkValid == false) 
            {
                printf("Input is invalid.\n");
            } 
        }
        partNum = atoi(pnum);

        //Searches for product with part number
        while(ptr -> number != partNum && ptr -> next != NULL) 
        {
            ptr = ptr -> next;
        }

        if(ptr -> number == partNum) 
        {
            pValid = true;

            while(qValid == false) 
            {
                //Get user input for new quantity
                printf("Input new quantity:\n");
                scanf("%s", qnum);
                qValid = validateInput(qnum);

                //Validates user input
                if(qValid == false) 
                {
                    printf("Input is invalid.\n");
                } 
                else 
                {
                    //Updates quantity for product
                    quantity = atoi(qnum);
                    ptr -> on_hand = quantity;
                    printf("Quantity for product has been updated.\n");
                }
            }
            
        } 
        else 
        {
            printf("Unable to find part number.\n");
            checkValid = false;
            pValid = false;
            ptr = inventory;
        }
    }
}

//Prints out all products in list
void p(node inventory) 
{
    //Variable delcaration
    node ptr = inventory;

    //Checks for empty list
    if(ptr == NULL) 
    {
        printf("\nNo products found.\n");
        return;
    }

    //Lists all products in list
    printf("Products:\n");
    while(ptr != NULL) 
    {
        printf("Part Number: %d Part Name: %s Quantity: %d\n", ptr -> number, ptr ->name, ptr ->on_hand);
        ptr = ptr -> next;
    }
}

//Checks for valid user number input
bool validateInput(char num[]) 
{

    //Checks each character in array for digit
    for(int index = 0; index < strlen(num); index++)
    {
        if (!isdigit(num[index]))
        {
            return false;
            break;
        }
    }

    return true;
}
