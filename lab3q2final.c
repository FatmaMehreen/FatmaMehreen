#include <stdio.h>  

int main() {
    int initialbalance = 1000; //initialize the balance with 1000
    int transactions[] = {200, -150, -500, -400, -50, -200, 300}; // Array of transaction values 

    // Calculate the number of elements in the transactions array :divide total size/ size of any element
    int numoftransactions = sizeof(transactions) / sizeof(transactions[0]);

    int tobeprocessed[numoftransactions]; //array to store unprocessed transactions
    int tbpCount = 0; // Counter for number of unprocessed transactions

    // Loop through each transaction 
    for (int i = 0; i < numoftransactions; i++) {
        // Check if the transaction is negative and if its greater the available balance
        if (transactions[i] < 0 && -transactions[i] > initialbalance) {
            printf("Transaction %d  invalid: %d\n", i + 1, transactions[i]);
            // Add invalid transaction to the toBeProcessed array
            tobeprocessed[tbpCount++] = transactions[i];
        } else {
            // Update the balance 
            initialbalance += transactions[i];
            
            // Check if  balance has reached zero 
            if (initialbalance == 0) {
                printf("Balance has reached 0. No further transactions will be processed.\n");
                // Add remaining unprocessed transactions to the tobeprorocessed array
                for (int j = i + 1; j < numoftransactions; j++) {
                    tobeprocessed[tbpCount++] = transactions[j];
                }
                break;
            }
        }
    }

    // Print the final balance 
    printf("Final balance: %d\n", initialbalance);

    // Print the unprocessed transactions
    printf("Unprocessed transactions: ");
    if (tbpCount == 0) { // Check if there are no unprocessed transactions
        printf("no unprocessed transation\n"); 
    } else {
        // Loop through and print each unprocessed transaction
        for (int i = 0; i < tbpCount; i++) {
            printf("%d ", tobeprocessed[i]);
        }
        printf("\n"); 
    }

    return 0;
}
