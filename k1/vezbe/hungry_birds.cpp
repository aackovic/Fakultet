const int F; //worms
const int N; //birds

sem babyMutex = 0;
sem parent = 1;
sem leave = 1;
int food = 0;

void babyBird(){
    while(1){
        wait(babyMutex);
        food--;
        if(!food)
            signal(parent);
        else
            signal(babyMutex);
        eat();
    }
}

void parentBird(){
    while(1){
        //...
        parentEat();
        //...
        guard();
        //...
    }
}

void parentEat(){
    wait(leave);
    eat();
    signal(leave);
}

void guard(){
    wait(parent);
    wait(leave);
    hunt();
    food = F;
    signal(leave);
    signal(babyMutex);
}