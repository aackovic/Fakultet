int buf[n];
int front = 0, rear = 0;
sem empty = n, full = 0;

void Producer(){
    while(true){
        wait(empty);
        buf[rear] = data;
        rear = (rear + 1) % n;
        // moze i kao buf[rear++] = data; rear = rear % n;
        signal(full);
    }
}

void Consumer(){
    while(true){
        wait(full);
        result = buf[front];
        front = (front + 1) % n;
        // result = buf[front++]; front = front % n;
        signal(empty);
    }
}