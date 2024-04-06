/* Project 6 - Project 6 - Parallel Numerical Integration Program on 2-D Mesh - Simple Messaage Pass Version*/


ARCHITECTURE MESH2(5);
#include <stdlib.h>
#include <math.h>

#define numproc 25
#define numpoints 30

float a,b,w,globalsum,answer;
int i;

float stream inchan[numproc+1];/* Input channel for communication between processors h_shah */

float integral[numproc]; /* Array to store local integrals for each processor h_shah */

/* calculated the function value for given input h_shah */
float f(float t) {
    return( sqrt(4 - t*t) );
}

void Integrate(int myindex, float *sum){
    float localsum = 0;
    float t;
    int j;
    float start, end, space;
/* Receive and send the start, end, and space from the processor h_shah */
    recv(inchan[myindex], start);
    recv(inchan[myindex], end);
    recv(inchan[myindex], space);
    send(inchan[myindex+1], start);
    send(inchan[myindex+1], end);
    send(inchan[myindex+1], space);

    t = start + myindex*(end-start)/numproc;
/* Performed numerical integratio h_shah */
    for (j = 1; j <= numpoints; j++) {
        localsum = localsum + f(t);
        t = t + space;
    }

    localsum = space * localsum;
    *sum = localsum;

}

main( ){
    a = 0;
    b = 2;
    w = (b-a)/(numproc*numpoints);
    /* Send initial values of a, b, and w to the first processor h_shah */
    send(inchan[0], a);
    send(inchan[0], b);
    send(inchan[0], w);
    /* Performed integration on each processor h_shah */
    forall i = 0 to numproc-1 do{
        Integrate(i, &integral[i]);
    }
     /* Aggregate the results for all the processors h_shah */
    for(i=0;i<numproc;i++){
        globalsum = globalsum + integral[i];
    }
    /* Calculated the final answer by adding the global sum and 
    the contribution from the endpoints h_shah */
    answer = globalsum + w/2*(f(b)-f(a));

    cout<< "Project 6 - Parallel Numerical Integration Program on 2-D Mesh" << ENDL
    << "Simple Message Pass: " <<"Professor's Version "<< ENDL
    <<"Submitted With Comments By Hrishikesh Shah"<< ENDL
    << "Answer is: ";
    cout<<answer<<ENDL;
}
