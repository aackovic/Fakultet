const int N;

sem cars = N;
sem mutex = 1;

vector<pair<sem*, sem*>> freeCars;


void car(){
    sem carSem = 0;
    sem visSem = 0;
    while(1){
        wait(mutex);

        freeCars.push_back(make_pair(&carSem,&visSem));
        
        signal(mutex);
        signal(cars);

        wait(carSem);
        //vozikanje
        signal(visSem);
        //gotovo
        wait(carSem);
    }
}

void visitor(){
    wait(cars);
    wait(mutex);

    sem* carSem = freeCars[0].first;
    sem* visSem = freeCars[0].second;
    freeCars.erase(0);

    signal(*carSem);
    signal(mutex);
    //vozikanje
    wait(*visSem);
    //gotovo
    signal(*carSem);
    //cao zdravo
}