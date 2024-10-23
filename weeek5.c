#include <stdio.h>
#include <stdlib.h>

// defining constants
#define coffeebeans 8
#define water 30
#define milkforespresso 0
#define milkforcappucino 70
#define milkformocha 160
#define chocformocha 30
#define waterformocha 39
#define adminpassword 00000
#define coffeethreshold 8
#define waterthreshold 30
#define milkthreshold 70
#define chocthreshold 30

// function declaration
int menu();
int askordertype();
int exitapplication();
int paymentmethod(double price);
int adminoperation();

int currentCoffeeBeans;
int currentWater;
int currentMilk;
int currentChocolate;
double espressoPrice = 3.5;
double cappuccinoPrice = 4.5;
double mochaPrice = 5.5;
double totalSales = 0.0;

int main() {
    int askuserchoice;
    
     srand(time(NULL)); //to randomize the seed

    // Initialize ingredients with random values within a range
    currentCoffeeBeans = rand() % 101; // Random value from 0 to 100
    currentWater = rand() % 201;       // Random value from 0 to 200
    currentMilk = rand() % 151;        // Random value from 0 to 150
    currentChocolate = rand() % 101;   // Random value from 0 to 100

    while (1) {
        printf("Hello! I'm Lily, your coffee server!\n");
        printf("Please select one: \n1. Admin Mode \n2. Order coffee customer \n3. Exit\n");
        scanf("%d", &askuserchoice);

        if (askuserchoice == 1) {
            adminoperation();
        } else if (askuserchoice == 2) {
            menu();
        } else if (askuserchoice == 3) {
            exitapplication();
            break;
        } else {
            printf("Incorrect input. Please try again.\n");
        }
    }
    return 0;
}

// function for the user to place order
int askordertype() {
    int order;
    int confirm;
    double price;

    printf("Please select your order: 1. Espresso 2. Cappuccino 3. Mocha\n");
    scanf("%d", &order);

    // Check ingredient availability based on the selected order
    if (order == 1) {
        // Espresso requires coffee beans and water
        if (currentCoffeeBeans < coffeethreshold || currentWater < waterthreshold) {
            printf("Sorry, Espresso is unavailable due to insufficient ingredients.\n");
            return 0;
        }
        price = espressoPrice;
        printf("You have ordered Espresso. Confirm? (1. Yes 2. No)\n");
    } else if (order == 2) {
        // Cappuccino requires coffee beans, water, and milk
        if (currentCoffeeBeans < coffeethreshold || currentWater < waterthreshold || currentMilk < milkthreshold) {
            printf("Sorry, Cappuccino is unavailable due to insufficient ingredients.\n");
            return 0;
        }
        price = cappuccinoPrice;
        printf("You have ordered Cappuccino. Confirm? (1. Yes 2. No)\n");
    } else if (order == 3) {
        // Mocha requires coffee beans, water, milk, and chocolate
        if (currentCoffeeBeans < coffeethreshold || currentWater < waterformocha || currentMilk < milkformocha || currentChocolate < chocthreshold) {
            printf("Sorry, Mocha is unavailable due to insufficient ingredients.\n");
            return 0;
        }
        price = mochaPrice;
        printf("You have ordered Mocha. Confirm? (1. Yes 2. No)\n");
    } else {
        printf("Invalid order. Please try again.\n");
        return 0;  // Return 0 for invalid input
    }

    scanf("%d", &confirm);
    if (confirm == 1) {
        printf("Order confirmed!\n");
        totalSales += price;  // Update total sales
        paymentmethod(price);
    } else {
        printf("Order canceled.\n");
    }
    return 0;
}

// function to display menu to the user
int menu() {
    printf("The items are Espresso, Cappuccino, Mocha\n");
    printf("The price for Espresso is %.2f\n", espressoPrice);
    printf("The price for Cappuccino is %.2f\n", cappuccinoPrice);
    printf("The price for Mocha is %.2f\n", mochaPrice);
    askordertype();
    return 0;
}

// function for payment specifications
int paymentmethod(double price) {
    double amountPaid = 0.0;
    double coin;

    printf("Please pay %.2f Dirham by inserting coins (1 or 0.5 Dirham).\n", price);

    while (amountPaid < price) {
        printf("Insert coin: ");
        scanf("%lf", &coin);

        if (coin == 1.0 || coin == 0.5) {
            amountPaid += coin;
            printf("You have inserted %.2f. Total paid: %.2f\n", coin, amountPaid);
        } else {
            printf("Invalid coin. Please collect your coin and insert a valid one (1 or 0.5 Dirham).\n");
        }

        if (amountPaid >= price) {
            printf("Payment complete. Thank you! Have a good day!\n");
            break;
        }
    }
    return 0;
}

int adminoperation() {
    int password;
    int choice;
    while (1) {
        printf("Enter admin password: ");
        scanf("%d", &password);
        if (password == adminpassword) {
            printf("Admin access granted.\n");

            while (1) {
                printf("\nAdmin Menu:\n");
                printf("1: Display the quantity of each ingredient in the machine and the total sale amount\n");
                printf("2: Replenish ingredients in the machine\n");
                printf("3: Change coffee price\n");
                printf("0: Exit Admin Mode\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                if (choice == 1) {
                    // Display ingredient levels and total sales
                    printf("Current ingredient levels:\n");
                    printf("Coffee Beans: %d g\n", currentCoffeeBeans);
                    printf("Water: %d ml\n", currentWater);
                    printf("Milk: %d ml\n", currentMilk);
                    printf("Chocolate: %d g\n", currentChocolate);
                    printf("Total sales amount: %.2f Dirham\n", totalSales);
                } else if (choice == 2) {
                    // Replenish ingredients
                    printf("Replenishing ingredients...\n");
                    currentCoffeeBeans = 100;  // Reset to full levels
                    currentWater = 200;
                    currentMilk = 150;
                    currentChocolate = 100;
                    printf("Ingredients have been replenished.\n");
                } else if (choice == 3) {
                    // Change coffee prices
                    printf("Enter new price for Espresso: ");
                    scanf("%lf", &espressoPrice);
                    printf("Enter new price for Cappuccino: ");
                    scanf("%lf", &cappuccinoPrice);
                    printf("Enter new price for Mocha: ");
                    scanf("%lf", &mochaPrice);
                    printf("Prices updated successfully.\n");
                } else if (choice == 0) {
                    // Exit Admin Mode
                    printf("Exiting Admin Mode.\n");
                    break;
                } else {
                    printf("Invalid choice. Please try again.\n");
                }
            }
            break;
        } else {
            printf("Sorry, password is incorrect.\n");
            return 0;
        }
    }
    return 0;
}

int exitapplication() {
    int exit;
    printf("Do you wish to exit? 1. Yes 2. No\n");
    scanf("%d", &exit);
    if (exit == 1) {
        printf("You are now out of the system.\n");
        return 1;
    } else {
        askordertype();
    }
    return 0;
}
