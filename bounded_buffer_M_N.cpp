int buf[n];
int front = 0, rear = 0;
sem empty = n, full = 0;
sem mutexP = 1, mutext C = 1;


void Producer(){
    while(true){
        wait(empty);
        wait(mutexP);
        buf[rear] = data;
        rear = (rear + 1) % n;
        // moze i kao buf[rear++] = data; rear = rear % n;
        signal(mutexP);
        signal(full);
    }
}

void Consumer(){
    while(true){
        wait(full);
        wait(mutexC);
        result = buf[front];
        front = (front + 1) % n;
        // result = buf[front++]; front = front % n;
        signal(mutexC);
        signal(empty);
    }
}