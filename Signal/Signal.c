#define _XOPEN_SOURCE 700


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <time.h>

pid_t PID;
pid_t userPID;

char userPIDChar[500];

static void signalFunction(int signum){

    if (signum == SIGUSR1){
        
       
        
    } else if(signum == SIGINT){
        exit(0);
       
    
    }else{
        fprintf(stdout,"%d\n",signum);
        fputs("This signal is not bieng handled\n",stdout);
        fflush(stdout);
    }
}
static void handler(int signum){
    kill(userPID,SIGUSR1);
 
}
long long nsecs() {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec*1000000000 + t.tv_nsec;
}
void emptyfunction(){
    return;
}


int main(int argc, char **argv){
    
    struct sigaction sa;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    if(atoi(argv[1]) == -1){
        sa.sa_handler = handler;
    }else{
        sa.sa_handler = signalFunction;
    }

    sigaction(SIGUSR1, &sa, NULL);

    if(atoi(argv[1])==-1){
        PID = getpid();
        printf("%d\n",PID);
        fgets(userPIDChar, 4096, stdin);
        userPID = atoi(userPIDChar);
        int flag =1;
        while(flag){
            pause();
        }
        
        
        
    }
    if(atoi(argv[1])==1){
        long long start = nsecs();
        emptyfunction();
        long long end =  nsecs();
        printf("%llu\n", end - start); 
    }
     if(atoi(argv[1])==2){
        long long start = nsecs();
        PID = getpid();
        long long end = nsecs();
        long long total = end - start;
        printf("%llu\n", total); 
    }
    if(atoi(argv[1])==3){
        long long start = nsecs();
        system("/bin/true");
        long long end = nsecs();
        long long total = end - start;
        printf("%llu\n", total); 
    }
    if(atoi(argv[1])==4){
        PID = getpid();
        long long start = nsecs();
        kill(PID, SIGUSR1);
        long long end = nsecs();
        long long total = end - start;
        printf("%llu\n", total); 
    }
    if(atoi(argv[1])==5){
        PID = getpid();
        printf("%d\n",PID);
        fgets(userPIDChar, 4096, stdin);
        userPID = atoi(userPIDChar);
        long long start = nsecs();

        sigset_t sigset;
        int sig;
        sigemptyset(&sigset);
        sigaddset(&sigset, SIGUSR1);
        sigprocmask(SIG_BLOCK, &sigset ,NULL);
        
        kill(userPID, SIGUSR1);
        
        sigwait(&sigset,&sig);
        
        long long end = nsecs();
        long long total = end - start;
        printf("%llu\n", total);
        
    }
}


