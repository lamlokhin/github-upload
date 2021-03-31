/*
* supermarket.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

typedef struct customer *customerT;

struct customer {
    int checkoutTime;
    int nItems;
    float payment;
};

struct cashier {
    int numberOfCustomersServed; /* This should be initialized to 0 */
    int totalCustomerServiceTime; /* This should be initialized to 0 */
    float totalAmountReceived; /* This should be initialized to 0 */
    queueADT customerQ; /* This should be initialized to an empty queue */
    /* This is a Queue of customer structures*/
};

typedef struct cashier cashierT;
/* Note: this is not typedef struct cashier *cashierT; */
/* Therefore, a variable of type cashierT is a structure, not a pointer. */

int main(){
    FILE *fp = fopen("supermarket.dat", "r");
    if (!fp){
        printf("Fail to open file!\n");
        exit(0);
    } //else printf("Successful to open file!\n");
    // initialize cashiers
    cashierT cashier[4];
    for (int i = 0; i <= 3; i++){
        cashier[i].numberOfCustomersServed = 0;
        cashier[i].totalAmountReceived = 0.0;
        cashier[i].totalCustomerServiceTime = 0;
        cashier[i].customerQ = emptyQueue();
    }
    char line[100];
    int totalWaitingTime = 0;
    int time = 0, cashierCheckoutTimeRemaining[4] = {0, 0, 0, 0};
    /* Read supermarket.dat file and begin simulation */
    while (fgets(line, sizeof(line), fp) != NULL){


        /* read in lines with content, deal with the situation that customer come */
        if (line[0] != '\n'){

            // the first string
            char *token = strtok(line, " ");
            customerT newCustomer = (customerT)malloc(sizeof(customerT));

                //printf("A: %d ", atoi(token));
                newCustomer->checkoutTime = atoi(token);
                token = strtok(NULL, " ");

                //printf("B: %d ", atoi(token));
                newCustomer->nItems = atoi(token);
                token = strtok(NULL, " ");

                //printf("C: %.2f ", atof(token));
                newCustomer->payment = atof(token);
                token = strtok(NULL, " ");

            // choose the shortest cashier queue and enqueue
            int cashierChoice, i = 0;
            if (newCustomer->nItems <= 5)
                cashierChoice = 0;
            else cashierChoice = 1;

            while (i <= 3){
                for (i = cashierChoice + 1; i <= 3; ++i){
                    if (queueLength(cashier[cashierChoice].customerQ) > queueLength(cashier[i].customerQ)){
                        cashierChoice = i;

                        break;
                    }
                }
            }
            enqueue(cashier[cashierChoice].customerQ, newCustomer);
            //printf("Customer %d enqueued to cashier %d\n", time, cashierChoice);
        }

        // dequeue customers to empty cashiers, update cashier
        for (int i = 0; i <= 3; ++i){
            if (queueIsEmpty(cashier[i].customerQ) == 0 && cashierCheckoutTimeRemaining[i] == 0){

                customerT nextCustomer = dequeue(cashier[i].customerQ);

                cashierCheckoutTimeRemaining[i] = nextCustomer->checkoutTime;
                cashier[i].numberOfCustomersServed++;
                cashier[i].totalAmountReceived += nextCustomer->payment;
                cashier[i].totalCustomerServiceTime += nextCustomer->checkoutTime;
            }
        }
        // end of the minute
        for (int i = 0; i <= 3; ++i){
            if ((queueIsEmpty(cashier[i].customerQ) == 0) && (cashierCheckoutTimeRemaining[i] > 0)){
                totalWaitingTime += queueLength(cashier[i].customerQ);
            }
        }

        for (int i = 0; i <= 3; ++i){
            if (cashierCheckoutTimeRemaining[i] > 0){
                cashierCheckoutTimeRemaining[i]--;
            }
        }
        //printf("Line %d read\n", time);
        time++;

        //printf("%d minutes passed\n", time);
    }

    //printf("All lines read, processing remaining queues\n");

    /* No more customers and we need to deal with the customers in the queue
    TODO:
    Serve all the remaining customers in the queue
    Complete the counting and output required information */
    while (queueIsEmpty(cashier[0].customerQ) == 0 || queueIsEmpty(cashier[1].customerQ) == 0 || queueIsEmpty(cashier[2].customerQ) == 0 || queueIsEmpty(cashier[3].customerQ) == 0){
        // dequeue customers to empty cashiers, update cashier
        for (int i = 0; i <= 3; ++i){
            if (queueIsEmpty(cashier[i].customerQ) == 0 && cashierCheckoutTimeRemaining[i] == 0){
                customerT nextCustomer = dequeue(cashier[i].customerQ);

                cashierCheckoutTimeRemaining[i] = nextCustomer->checkoutTime;
                cashier[i].numberOfCustomersServed++;
                cashier[i].totalAmountReceived += nextCustomer->payment;
                cashier[i].totalCustomerServiceTime += nextCustomer->checkoutTime;
            }
        }
        // end of the minute
        for (int i = 0; i <= 3; ++i){
            if ((queueIsEmpty(cashier[i].customerQ) == 0) && (cashierCheckoutTimeRemaining[i] > 0)){
                totalWaitingTime += queueLength(cashier[i].customerQ);
            }
        }

        for (int i = 0; i <= 3; ++i){
            if (cashierCheckoutTimeRemaining[i] > 0){
                cashierCheckoutTimeRemaining[i]--;
            }
        }
        time++;
        //printf("%d minutes passed\n", time);
    }

    //printf("All queues processed, total time: %d minutes\n", time);
    //printf("\n");

    printf("The average time a customer needs to wait after he joins a queue until he starts to check out:\n");
    int totalNumberOfCustomersServed;
    for (int i = 0; i <= 3; ++i){
        totalNumberOfCustomersServed += cashier[i].numberOfCustomersServed;
    }
    //printf("Total number of customers served = %d\n", totalNumberOfCustomersServed);
    //printf("Total time of waiting = %d\n", totalWaitingTime);
    double averageWaitingTime = ((double)totalWaitingTime/totalNumberOfCustomersServed);
    printf("%.2f minutes\n", averageWaitingTime);
    printf("\n");

    printf("The total amount of money each of the cashier receives:\n");
    for (int i = 0; i <= 3; ++i){
        printf("Cashier %d: $%.2f\n", i, cashier[i].totalAmountReceived);
    }
    printf("\n");

    printf("The total number of customers each of the cashiers serves:\n");
    for (int i = 0; i <= 3; ++i){
        printf("Cashier %d: %d customers\n", i, cashier[i].numberOfCustomersServed);
    }

    fclose(fp);
    return (0);
}
