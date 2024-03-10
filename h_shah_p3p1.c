#define n 10
float A[n + 1][n + 1] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 4, 9, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 6, 13, 1, 5, 0, 0, 0, 0, 0, 0},
    {0, 7, 67, 52, 1, 11, 0, 0, 0, 0, 0},
    {0, 2, 45, 25, 26, 1, 8, 0, 0, 0, 0},
    {0, 3, 1, 32, 14, 34, 1, 63, 0, 0, 0},
    {0, 18, 3, 0, 21, 28, 44, 1, 5, 0, 0},
    {0, 90, 4, 4, 5, 5, 52, 3, 1, 55, 0},
    {0, 12, 8, 9, 6, 17, 6, 63, 64, 1, 1}
};

float B[n + 1] = {0, 1, 2, 3, 4};
float x[n + 1];
float stream pipechan[n + 2];
int i;

void PipeProcess(int i) {
    
    int q;
    float sum, xvalue;
    sum = 0;
    for (q = 1; q < i; q++) {
        recv(pipechan[i], xvalue); 
        send(pipechan[i + 1], xvalue); 
        sum = sum + A[i][q] * xvalue;
    }
    x[i] = (B[i] - sum) / A[i][i]; 
    send(pipechan[i + 1], x[i]); 
}

int main() {
    int k;
    forall i = 1 to n do {
        
        PipeProcess(i);
        
    }
    for (k = 1; k <= n ; k++) {
        cout<<"x["<<k<<"] = "<<x[k]<<endl;
    }
    
    return 0;
}
