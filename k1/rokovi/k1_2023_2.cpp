const int N;

int cnt = 0;

sem mutex = 1;
sem table = N; //mesta za stolom
sem together = 0; // ceka da dodje drugi da dodju/idu zajedno
sem togetherAck = 0;


void togetherAtTable(){
    wait(table);
    wait(mutex);

    cnt++;

    if(cnt >= 2 && cnt <= N)
        signal(mutex);
    else if(cnt == 1){
        signal(mutex);
        wait(together);
        signal(togetherAck);
    }
    else{
        signal(together);
        wait(togetherAck);
        signal(mutex);
    }
}

void leaveTable(){
    wait(mutex);

    cnt--;
    signal(table);

    if(cnt>=2){
        signal(mutex);
    }
    else if(cnt == 1){
        signal(mutex); 
        wait(together);
        signal(togetherAck);
    }
    else{
        signal(together);
        wait(togetherAck);
        signal(mutex);
    }
}