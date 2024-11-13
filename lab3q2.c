#include <stdio.h>

int main() {
    int initialbalance = 1000; 
    int transactions[] = {-2000, -250, -300, -400, -505, -200, 200};
    //to get number of elements in the array: divide the total size of the array by the size of any element(here first element used)
    int numTransactions = sizeof(transactions) / sizeof(transactions[0]);
    
    
    int toBeProcessed[numTransactions];//to store the unprocessed transactions. declare new array
    int toBeProcessedCount = 0;

   
    for (int i = 0; i < numTransactions; i++) {
        if (transactions[i] < 0 && -transactions[i] > initialbalance) {
            
            printf("invalid");
            toBeProcessed[toBeProcessedCount++] = transactions[i];
        } else {
           
            initialbalance += transactions[i];
           
            if (initialbalance == 0) {
                printf("Balance has reached 0. No further transactions will be processed.\n");
               
                for (int j = i + 1; j < numTransactions; j++) {
                    toBeProcessed[toBeProcessedCount++] = transactions[j];
                }
                break;
            }
        }
    }

  
    printf("Final balance: %d\n", initialbalance);
    printf("Unprocessed transactions: ");
    for (int i = 0; i < toBeProcessedCount; i++) {
        printf("%d ", toBeProcessed[i]);
    }
    printf("\n");

    return 0;
}

    
