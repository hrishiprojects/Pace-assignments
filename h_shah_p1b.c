#include <stdlib.h>
int z;

float factorial_of_integer(int z) { 
    float factorial = 1.0, o;

    for (o = 1; o <=z; o++) 
        factorial = factorial * o;      

    return factorial;            
}
int main() {
    
    cout << "Enter a positive integer whose factorial you want to calculate: " << endl; 
    cin >> z; 

    if (z >= 0) {
        cout.precision(12);
        cout << "Factorial of positive integer is: " << factorial_of_integer(z) << endl; 
    } else {
        cout << "You have entered a negative integer" << endl;
    }

    return 0; 
    
}