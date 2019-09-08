#include <stdio.h>
#include <thread> 
using namespace std;

thread tid[2];
 int x = 0;
bool wantp = false;
bool wantq = false;
int turn = 1;


void p() {
  wantp = true;
for(int jj=0;jj<10;jj++){	
  while(wantq) {
    if(turn == 2) {
      wantp = false;
      while(turn != 1) {
			
      }
      wantp = true;
    }
  }
  printf("Entry Thread 1 in critical section\n");
  x++;
  printf("Exit Thread 1 in critical section -- %d\n", x);

  turn = 2;
  wantp = false;}
}

void q() {
  wantq = true;
for(int jj=0;jj<10;jj++){
  while(wantp) {
    if(turn == 1) {
      wantq = false;
      pthread_yield();
      while(turn != 2) {

      }
      wantq = true;
    }
  }
  printf("Entry Thread 2 in critical section\n");
  x++;
  printf("Exit Thread 2 in critical section -- %d\n", x);
  turn = 1;
  wantq = false;
}}




int main() {
  tid[0]=thread(p);
  tid[1]=thread(q);

  tid[0].join();
  tid[1].join();

}
