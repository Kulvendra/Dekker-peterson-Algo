#include <stdio.h> 
#include <thread>
using namespace std;  

int flag[2]; 
int turn; 
const int MAX = 1e9; 
int ans = 0; 

void lock_init() 
{ 
	
	flag[0] = flag[1] = 0; 
	turn = 0; 
} 

 
void lock(int self) 
{ 
	 
	flag[self] = 1; 

	 
	 
	turn = 1-self; 

	 
	while (flag[1-self]==1 && turn==1-self) ; 
} 

 
void unlock(int self) 
{ 
	 
	flag[self] = 0; 
} 

 
void func(int self) 
{ 
	int i = 0; 

	printf("Thread Entered: %d\n", self); 
	for(i=0;i<50;i++){
	lock(self); 
	printf("Entry Thread %d in critical section\n",self);
    	ans++;
	printf("Exit Thread %d in critical section -- %d\n", self,ans);
	unlock(self); }
} 

 
int main() 
{ 
	 

	lock_init(); 

	 
	thread t1( func, 0); 
	thread t2( func, 1); 

	 
	t1.join(); 
	t2.join(); 

	
	return 0; 
} 

