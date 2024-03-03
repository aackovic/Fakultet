int cnt = 0;
const int N;

sem mutex = 1;
sem b = 0;
sem ok = 0;


//neoptimalno ali malo semafora

void barrier(){
    wait(mutex);
    cnt++;
    if(cnt == N){
        cnt = 0;
        for(int i = 0; i < N - 1; i++){
            signal(b);
            wait(ok);
        }
    }
    else{
        signal(mutex);
        wait(b);
        signal(ok);
    }
}

//sa n semafora za procese

int cnt = 0;
const int N;

sem mutex = 1;
sem b[N] = 0;

void barrier(int id){
    wait(mutex);
    cnt++;
    if(cnt == N){
        for(int i = 0 ; i < N; i++){
            if(i!=id)
                signal(b[i]);
        }
        cnt=0;
        signal(mutex);
    }
    else{
        signal(mutex);
        wait(b[id]);
    }
}

// 2-phase barrier

int cnt = 0;
const int N;

sem barrier1 = 1;
sem barrier2 = 0;

void barrier(){
    wait(barrier1);
    cnt++;
    if(cnt == N)
        signal(barrier2);
    else
        signal(barrier1);
    
    wait(barrier2);
    cnt--;
    if(!cnt)
        signal(barrier1);
    else
        signal(barrier2);
}