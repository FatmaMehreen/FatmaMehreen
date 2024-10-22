#include <stdio.h>
#include <string.h>
 
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
#define chocthreshold 
#define milkthreshold

int askordertype();
int  exitapplication();
int adminoperation();
int pricelist();


int main(){
 
  printf("Hello! I'm Lily your coffee server! \n");
  printf("Please select one: \n1. Admin Mode \n2. Order coffee customer \n3. exit \n");
  scanf("%d", &askuserchoice);
 
return 0;
}


/*int askordertype(){
  int order;
  printf("Please select your order: 1. espresso 2. cappucino 3. mocha");
  scanf("%d", &order);
  if (order== 1){
    printf("You have ordered espresso. confirm?(1.yes 2. no)");}
    else if (order == 2){
      printf("You have ordered cappucino. confirm?(1. yes 2. no)");
    } else if (order == 3){
      printf("you have ordered mocha. confirm?1. yes 2 no");

    }
    }*/

int askordertype() {
    int order;
    int confirm;

    printf("Please select your order: 1. espresso 2. cappuccino 3. mocha\n");
    scanf("%d", &order);

    if (order == 1) {
        printf("You have ordered espresso. Confirm? (1. yes 2. no)\n");
    } else if (order == 2) {
        printf("You have ordered cappuccino. Confirm? (1. yes 2. no)\n");
    } else if (order == 3) {
        printf("You have ordered mocha. Confirm? (1. yes 2. no)\n");
    } else {
        printf("Invalid order. Please try again.\n");
        return 0;  // Return 0 for invalid input
    }

    scanf("%d", &confirm);
    if (confirm == 1) {
        printf("Order confirmed!\n");
        printf("Please proceed to pay");
        paymentmethod();
    } else {
        printf("Order canceled.\n");
        return 0;  // Return 0 for canceled order
    }
}



/*int pricelist(){
int priceespresso = 3.5;
printf("the price for espresso is %d\n", priceespresso);
int pricecappucino = 4.5;
printf("the price for cappucino is %d\n", pricecappucino);
int priceformocha = 5.5;
printf("the price for mocha is 5.5\n", priceformocha);
printf("Please proceed to pay\n");
paymentmethod();
}*/



int adminoperation(){
int password;
int totalamount;
printf("enter admin password:", password);
scanf("%d", &password);
if (strcmp (password, adminpassword)==0){
    printf("the total same amount is :\n", totalamount);
    printf("the quantity of ingredients left is: \n");
    printf("do you wish to replenish ingredients?(1. yes 2. no)");
    } else {
      printf("sorry, password is incorrect");
    }
    }

int exitapplication(){
int exit;
    printf("do you wish to exit? 1.yes 2.no");
    scanf("%d",&exit);
    if(exit == 1){
      printf("you are now out of the system");
    } else{
      askordertype();
    }

}
