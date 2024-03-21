const int N;

//n sems

int cnt = 0;
sem mutex = 1;
sem b[N] = {0};


void process(int id){
    wait(mutex);
    cnt++;
    if(cnt == N){
        for(int i = 0; i < N; i++){
            if(i != id)
                signal(b[i]);
        }
        cnt = 0;
        signal(mutex);
    }
    else{
        signal(mutex);
        wait(b[id]);
    }
}