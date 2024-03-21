const int N;
sem arrive[N] = {0};
sem pass[N] = {0};
bool coordinator = 0;
sem coordSem = 0;
sem mutex = 1;

void coord1(){
    for(int i = 0; i < N/2; i++)
        wait(arrive[i]);
    wait(mutex);
    if(coordinator){
        coordinator = 0;
        signal(mutex);
        signal(coordSem);
    }
    else{
        coordinator = 1;
        signal(mutex);
        wait(coordSem);
    }
    for(int i = 0; i < N/2; i++)
        signal(pass[i]);
}

void coord2(){
    for(int i = N/2; i < N; i++)
        wait(arrive[i]);
    wait(mutex);
    if(coordinator){
        coordinator = 0;
        signal(mutex);
        signal(coordSem);
    }
    else{
        coordinator = 1;
        signal(mutex);
        wait(coordSem);
    }
    for(int i = N/2; i < N; i++)
        signal(pass[i]);
}


void process(int id){
    while(1){
        work();
        signal(arrive[i]);
        wait(pass[i]);
    }
}