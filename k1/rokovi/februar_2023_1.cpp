//coarse grain

int number = 0;
int next = 0;
int turn[n] = {0};

void process(){
    while(1){
        <turn[i] = number; number++;>
        <await(turn[i] == next);>
        //critical
        <next = next +1;>
        //non-critical
    }
}

//fine grain

//addAndGet(var, incr) : < var = var + incr; return(var);

int number = 0;
int next = 0;
int turn[n] = {0};

void process(){
    while(1){
        turn[i] = addAndGet(number, 1) - 1;
        while(turn[i] != next) skip();
        //critical
        next++;
        //non-critical
    }
}