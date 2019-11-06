#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <string>

using namespace std;

class A{
    public:

    int a;
    string b;
    
    void add_op(){
        a++;
    }

    void sub_op(){
        a--;
    }
};

static A obj;

void th_add(void *arg){

    while(1)
    {
        if (obj.a > 400)
            break;
        usleep(100);
        obj.add_op();
        obj.b = "add";
    }
    //pthread_cancel( pthread_self());
}

    
void th_sub(void *arg){


    while(1)
    {
        if (obj.a < 0)
           break; 
        
        usleep(410);
        obj.sub_op();
        obj.b = "sub";
    }
    //pthread_cancel( pthread_self() );
}


     
    

int main(void)
{
    pthread_t tid1;
    pthread_t tid2;
    int n = 101;
    while ( n--)
        if ( fork() ==0 ){
             sleep(3); 
             th_add(NULL);
             exit(0);
        }

    n = 101;
    while ( n--)
        if ( fork() ==0 ){
             sleep(3);
             th_sub(NULL);
             exit(0);
        }

    while(1)
    {
        cout<< "a = " << obj.a << "   b = "<< obj.b<<endl;
        usleep(500); 
    }
    return 0;
}

   
