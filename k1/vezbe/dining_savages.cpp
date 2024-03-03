const int N;
const int M;

sem mutex = 1;
sem cook = 0;
sem savage = 0;

int food;

void cook(){
    while(1){
        sleep(); //fus spavanje
        wait(cook);
        prepare();
        food = M;
        signal(savage);
    }
}

void savage(){
    do_something(); // radi nesto

    wait(mutex);
    if(food == 0){
        signal(cook);
        wait(savage);
    }
    food--;
    signal(mutex);
    eat();
}