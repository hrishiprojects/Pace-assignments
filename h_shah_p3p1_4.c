#define n 4
float A[n + 1][n + 1] = {
    {0, 0, 0, 0, 0},
    {0, 4, 0, 0, 0},
    {0, 5, 1, 0, 0},
    {0, 7, 75, 1, 0},
    {0, 8, 9, 10, 1}
};

float B[n + 1] = {0, 1, 2, 3, 3};
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
