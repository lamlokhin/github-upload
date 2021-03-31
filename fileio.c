/*
* file i/o
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int nmain(){
    FILE *fp = fopen("supermarket.dat", "r");
    if (!fp){
        printf("Fail to open file!\n");
        exit(0);
    }

    char line[100];
    int lineNo = 0;
    while (fgets(line, sizeof(line), fp) != NULL){
        if (line[0] != '\n'){
            char *checkoutTime = strtok(line, " ");
            int checkouttime = atoi(checkoutTime);
            //newCustomer->checkoutTime = atoi(checkoutTime);
            printf("%d ", checkouttime);

            char *nItems = strtok(NULL, " ");
            int nitems = atoi(nItems);
            //newCustomer->nItems = atoi(nItems);
            printf("%d ", nitems);

            char *payment = strtok(NULL, " ");
            float payMent = atof(payment);
            //newCustomer->payment = atof(payment);
            printf("%.2f ", payMent);
            /*if (token != NULL){
                printf("A: %d ", atoi(token));
                //newCustomer->checkoutTime = atoi(token);
                token = strtok(NULL, " ");
            }
            if (token != NULL){
                printf("B: %d ", atoi(token));
                //newCustomer->nItems = atoi(token);
                token = strtok(NULL, " ");
            }
            if (token != NULL){
                printf("C: %.2f ", atof(token));
                //newCustomer->payment = atof(token);
                token = strtok(NULL, " ");
            }*/
        }
        printf("Line %d read.\n", lineNo);
        lineNo++;
    }
    printf("All lines read.\n");
    return 0;
}

