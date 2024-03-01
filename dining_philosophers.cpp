sem fork[n] = {1};

void Philosopher(int i){
    while (true){
        if (i != n - 1){
            wait(fork[i]);
            wait(fork[i + 1]);
        }
        else{
            wait(fork[0]);
            wait(fork[i]);
        }

        eat();

        if (i != n - 1){
            signal(fork[i]);
            signal(fork[i + 1]);
        }
        else{
            signal(fork[0]);
            signal(fork[i]);
        }
    }
}