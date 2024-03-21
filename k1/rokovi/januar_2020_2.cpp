const int N;

typedef struct{
    vector<sem*> entering;
    vector<sem*> exiting;
    sem mutexEntering = 1;
    sem mutexExiting = 1;
} Floor;

sem liftSem = 0;
vector<Floor> floors(N);

void person(){
    sem personSem = 0;
    int currFloor = rand() % N;

    while(1){
        int nextFloor = rand() % N;

        Floor& current = floors[currFloor];
        Floor& next = floors[nextFloor];

        wait(current.mutexEntering);
        current.peopleEntering.push_back(&personSem);
        signal(current.mutexEntering);

        wait(personSem);

        wait(next.mutexExiting);
        next.peopleExiting.push_back(&personSem);
        signal(next.mutexExiting);

        signal(liftSem);

        wait(personSem);

        signal(liftSem);
    }
}


void lift(){
    int currFloor = 0;
    bool up = true;

    while(1){
        currFloor += up ? 1 : -1;
        up = currFloor != N - 1 ? up : !up;

        Floor& floor = floors[currFloor];

        int cntExiting = floor.peopleExiting.size();

        wait(floor.mutexEntering);

        int cntEntering = floor.peopleEntering.size();

        if(!cntExiting && !cntEntering){
            signal(floor.mutexEntering);
            continue();
        }

        for(int i = 0; i < cntExiting; i++){
            sem* personSem = floor.peopleExiting[0];
            signal(*personSem);
            floor.peopleExiting.erase(0);
        }

        for(int i = 0; i< cntExiting; i++)
            wait(liftSem);

        for(int i = 0; i < cntEntering; i++){
            sem* personSem = floor.peopleEntering[0];
            signal(*personSem);
            floor.peopleEntering.erase(0);
        }

        for(int i = 0; i< cntEntering; i++)
            wait(liftSem);

        signal(floor.mutexEntering);
    }
}