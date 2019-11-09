# (Pthreads) Found minimum element in vector with mutex

## pthreadmin.c:<br/>
Found the min of vector with size N in parallel. The search will split in nt threads. <br/>
Each thread will search in N/nt elements of vector.<br/>
The code receive from prompt command the number of threads will be create (nt),
the number of elements of vector and the seed of rand() of each element that will be generated.<br/>


## To compile the code:
gcc pthreadmin.c -o pthreadmin -pthread<br/>

## To run the code:
./pthreadmin nt N seed <br/>
  
### run example:<br/>
```
$./pthreadmin 4 100 1000
```
<br/>

### Performance:<br/>
For better load balancing, the numbers of threads (nt) selected in define must be higher or equal than number of processors:<br/> nt>= number of processors.<br/>
This improve lowest idleness of processors<br/>
