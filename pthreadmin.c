/*
    Developed by João Zanetti
    https://github.com/joao-zanetti
*/
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define params 3

//Struct for each thread
typedef struct
{
    int index; //index vector of the thread
    pthread_t id; //id of the thread
}pt;

//Lock for the variable min, in wich must be accessed for only one thread at the same time 
pthread_mutex_t lock;

int nt,N,seed,min,*v,range;

//found the min value of the vector v
void *foundmin(void *ptr){
    int i,minlocal,initrange,rangelocal;
    pt *pa = (pt*)ptr;
    long int aux;


    if((*pa).index==nt-1){ //if number(nt) of threads is odd  
        rangelocal=range+(N%nt); //the last thread 
    }
    else{
        rangelocal=range;
    }

    //initial position of each thread in vector
    initrange=(*pa).index*range;
    //initializes minlocal with first position of vector
    minlocal=v[initrange];

    //calculates the minlocal of rangelocal numbers of vector
	for(i=initrange;i<initrange+rangelocal; i++) {
         if (v[i]<minlocal){
             minlocal=v[i]; 
         } 
    }

    pthread_mutex_lock(&lock);
    if(minlocal<min){
        min=minlocal;
    }
    pthread_mutex_unlock(&lock);
}

//initializes vector
void initvet(){
    int i;

    for(i=0;i< N;i++){
          v[i]=rand()%seed;
          //printf("%d ",v[i]);
    }
    min=v[0];
}



int main(int argc, char *argv[ ]){

    int i;
    pt *p;

    //reading from prompt command
    if(argc==params+1){
        nt=atoi(argv[1]); //number of threads
        N=atoi(argv[2]); //vetor size
        seed=atoi(argv[3]); //seed of rand() for each element of the vector
        range=N/nt;
    }
    else{
        printf("numbers of parameters is incorrect\n");
        return 0;
    }

    //allocates the vector of threads (struct pt)
    p=malloc(nt*sizeof(pt));
    //allocates the vector of numbers
    v=malloc(N*sizeof(int));
    
    //initializes the vector with rand() with seed received from parameter
    initvet();
    
    //create nt threads
    for (i = 0; i < nt; i++){
        p[i].index=i;
        if(pthread_create(&p[i].id, NULL, foundmin,(void*)&p[i])) {
            fprintf(stderr, "Error creating thread\n");
            return -1;
        }
    }


    //wait nt threads to finish
    for (i = 0; i < nt; i++){
        if(pthread_join(p[i].id, NULL)){
            fprintf(stderr, "Error joining thread\n");
            return -i;
        }
    }

    printf("Minimum:%d\n",min);

    fflush(0);
    return 0;
}
