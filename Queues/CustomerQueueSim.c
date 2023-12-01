#include <stdio.h>
#include <stdlib.h>

typedef struct Passenger {
    int type; // 0 for regular, 1 for frequent flyer
    int timestamp; // Arrival time
    struct Passenger* next;
} Passenger;

typedef struct {
    Passenger* front;
    Passenger* rear;
} Queue;

void initializeQueue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

int isQueueEmpty(Queue* queue) {
    return (queue->front == queue->rear);
}

void enqueue(Queue* queue, int type, int timestamp) {
    Passenger* newPassenger = (Passenger*)malloc(sizeof(Passenger));
    newPassenger->type = type;
    newPassenger->timestamp = timestamp;
    newPassenger->next = NULL;

    if (isQueueEmpty(queue)) {
        queue->front = newPassenger;
        queue->rear = newPassenger;
    } else {
        queue->rear->next = newPassenger;
        queue->rear = newPassenger;
    }
}

Passenger* dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        return NULL;
    }

    Passenger* dequeuedPassenger = queue->front;

    if (queue->front == queue->rear) {
        queue->front = NULL;
        queue->rear = NULL;
    } else {
        queue->front = queue->front->next;
    }

    return dequeuedPassenger;
}

void simulateTicketCounter(int numRegular, int numFrequentFlyer, int strategy) {
    Queue regularQueue, frequentFlyerQueue;
    initializeQueue(&regularQueue);
    initializeQueue(&frequentFlyerQueue);

    for (int i = 0; i < numRegular; ++i) {
        enqueue(&regularQueue, 0, i);
    }

    for (int i = 0; i < numFrequentFlyer; ++i) {
        enqueue(&frequentFlyerQueue, 1, i);
    }

    int currentTime = 0;
    int totalTimeRegular = 0, totalTimeFrequentFlyer = 0;

    while (!isQueueEmpty(&regularQueue) && !isQueueEmpty(&frequentFlyerQueue)) {
        Passenger* currentPassenger = NULL;
        if (strategy == 0) {
            // Alternating Service
            if (!isQueueEmpty(&regularQueue)) {
                currentPassenger = dequeue(&regularQueue);
            }
            if (!isQueueEmpty(&frequentFlyerQueue)) {
                currentPassenger = dequeue(&frequentFlyerQueue);
            }
        } else if (strategy == 1) {
            // Serve All Regular Customers First
            currentPassenger = dequeue(&regularQueue);
        } else if (strategy == 2) {
            // Serve All Frequent Flyers First
            currentPassenger = dequeue(&frequentFlyerQueue);
        }

        if (currentPassenger != NULL) {
            int waitingTime = currentTime - currentPassenger->timestamp;

            if (currentPassenger->type == 0) {
                totalTimeRegular += waitingTime;
            } else {
                totalTimeFrequentFlyer += waitingTime;
            }

            free(currentPassenger);
        }

        currentTime++;
    }

    double avgTimeRegular = (numRegular == 0) ? 0 : totalTimeRegular / (double)numRegular;
    double avgTimeFrequentFlyer = (numFrequentFlyer == 0) ? 0 : totalTimeFrequentFlyer / (double)numFrequentFlyer;

    printf("Average Waiting Time for Regular Customers: %.2lf\n", avgTimeRegular);
    printf("Average Waiting Time for Frequent Flyers: %.2lf\n", avgTimeFrequentFlyer);
}

int main() {
    int numRegular, numFrequentFlyer, strategy;

    printf("Enter the number of regular customers: ");
    scanf("%d", &numRegular);

    printf("Enter the number of frequent flyers: ");
    scanf("%d", &numFrequentFlyer);

    printf("Select a serving strategy:\n");
    printf("0 - Alternating Service\n");
    printf("1 - Serve All Regular Customers First\n");
    printf("2 - Serve All Frequent Flyers First\n");
    printf("Enter your choice: ");
    scanf("%d", &strategy);

    simulateTicketCounter(numRegular, numFrequentFlyer, strategy);

    return 0;
}
