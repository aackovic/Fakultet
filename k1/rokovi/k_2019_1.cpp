const int N;

sem sems[N + 1];
bool reader[N + 1];
int head = 0, tail = 0;

sem mutex = 1;

int cnt = 0;

void reader(){
    wait(mutex);

    if(head == tail && count >= 0){
        cnt++;
        signal(mutex);
    }
    else{
        int index = tail++;
        tail %= N + 1;
        reader[index] = 1;
        signal(mutex);
        wait(sems[index]);
    }

    read();

    wait(mutex);
    if(--cnt == 0 && head != tail){
        cnt--;
        signal(sems[head++]);
        head %= N+1;
    }
    signal(mutex);
}

void writer(){
    wait(mutex);
    if(head == tail && !cnt){
        cnt--;
        signal(mutex);
    }
    else{
        int index = tail++;
        tail %= N + 1;
        reader[index] = 0;
        signal(mutex);
        wait(sems[index]);
    }

    write();

    wait(mutex);

    if(head == tail){
        cnt = 0;
    }
    else if(reader[head]){
        cnt = 0;
        while(read[head] && head!= tail){
            cnt++;
            signal(sems[head++]);
            head %= N + 1;
        }
    }
    else{
        signal(sems[head++]);
        head %= N + 1;
    }
    signal(mutex);
}