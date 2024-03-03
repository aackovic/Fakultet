const int N; // bees
const int H; // honey

int food = 0;

sem mutex = 1;
sem bear = 0;

void bear(){
    while(1){
        wait(bear);
        eat();
        food = 0;
        signal(mutex);
    }
}

void bee(){
    buzzz();
    wait(mutex);
    food++;
    if(food == N)
        signal(bear);
    else
        signal(mutex);
}