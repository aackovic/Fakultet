const int N;
const int K;

bool priority = 1;

sem sems[2 * N + 1];

int cap = N; //broj slob mesta

int entering = 0; //cekaju na ulaz
int exiting = 0; //cekaju na izlaz

int consecutive = 0;

int enterHead = 0, enterTail = 0;
int exitHead = 0, exitTail = 0;

sem mutex = 1;

bool enterReq(){
    wait(mutex);

    if(cap - entering <= 0){
        signal(mutex);
        return false;
    }
    entering++;
    if(entering == 1 && !exiting){
        signal(mutex);
        return true;
    }
    int index = enterTail++;
    enterTail %= N;
    signal(mutex);
    wait(sems[index]);
    return true;
}

bool exitReq(){
    wait(mutex);
    cap++;
    exiting++;
    if(!entering && exiting == 1){
        signal(mutex);
        return;
    }
    int index = N + exitTail++;
    exitTail %= N;
    signal(mutex);
    wait(sems[index]);
}

void entered(){
    wait(mutex);
    entering--;
    cap--;
    signal();
    signal(mutex);
}

void exited(){
    wait(mutex);
    exiting--;
    signal();
    signal(mutex);
}

void signal(){
    int index = -1;
    bool hasCap = (cap - exiting) < N; //ovo nema smisla
    //valjda cap + exitiing > 0
    bool signalExit = (exiting) && (priority || !hasCap || !entering);
    bool signalEnter = (entering && hasCap) && (!priority || !exiting);

    if(signalExit){
        index = N + exitHead++;
        exitHead %= N;
    }
    else if(signalEnter){
        index = enterHead++;
        enterHead %= N;
    }
    if(index >= 0){
        if(priority != signalExit)
            consecutive = 0;
        else
            consecutive++;
        if(consecutive == K){
            consecutive = 0;
            priority = !priority;
        }
        signal(sem[index]);
    }
}

void car(){
    while(1){
        if(enterReq()){
            entered();
            //...
            exitReq();
            //...
            exited();
        }
    }
}