#include <thread>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define THREAD_COUNT 8
using namespace  std;

int tickets[THREAD_COUNT];
int choosing[THREAD_COUNT];

volatile int x=0;



void thread_body(void *arg) {
    long thread = (long)arg;
    for(int i=0;i<50;i++){
    choosing[thread] = 1;

    int max_ticket = 0;
    for (int i = 0; i < THREAD_COUNT; ++i) {
        int ticket = tickets[i];
        max_ticket = ticket > max_ticket ? ticket : max_ticket;
    }
    tickets[thread] = max_ticket + 1;
    choosing[thread] = 0;
    for (int other = 0; other < THREAD_COUNT; ++other) {
        while (choosing[other]) { }
        while (tickets[other] != 0 &&
               (tickets[other] < tickets[thread] ||
                (tickets[other] == tickets[thread] && other < thread))) { }
    }
    printf("Entry Thread %d in critical section\n",thread);
    x++;
    printf("Exit Thread %d in critical section -- %d\n", thread,x);

    
    
    tickets[thread] = 0;
    }
    return;
}

int main(int argc, char **argv) {
    memset((void*)tickets, 0, sizeof(tickets));
    memset((void*)choosing, 0, sizeof(choosing));

    thread threads[THREAD_COUNT];

    for (int i = 0; i < THREAD_COUNT; ++i) {
        threads[i]=thread(thread_body, (void*)((long)i));
    }

    for (int i = 0; i < THREAD_COUNT; ++i) {
        threads[i].join();
    }

    return 0;
}
