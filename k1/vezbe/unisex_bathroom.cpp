const int N;

sem toilet = 1;
sem entry = 1;
sem ticket = N;
sem mutexWomen = 1, mutexMen = 1;

int womenCount = 0, menCount = 0;

void Woman(int id){
    wait(entry);

    wait(mutexWomen);
    womenCount++;
    if(womenCount == 1)
        wait(toilet);
    signal(mutexWomen);

    signal(entry);
    wait(ticket);
    usingToilet();
    signal(ticket);

    wait(mutexWomen);
    womenCount--;
    if(!womenCount)
        signal(toilet);
    signal(mutexWomen);
}

void Man(int id){
    wait(entry);

    wait(mutexMan);
    menCount++;
    if(menCount == 1)
        wait(toilet);
    signal(mutexMen);

    signal(entry);
    wait(ticket);
    usingToilet();
    signal(ticket);

    wait(mutexMen);
    menCount--;
    if(!menCount)
        signal(toilet);
    signal(mutexMen);
}