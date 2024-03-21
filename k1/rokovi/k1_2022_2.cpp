const int N;
const int M;

sem carSems[N];
sem peopleSems[M];

sem mutex = 1;

vector<int> freeCars;
vector<int> freePeople;

int mutexId;

void car(int carId){
    int personId;

    while(1){
        wait(mutex);
        if(freePeople.size()){
            personId = freePeople[0];
            freePeople.erase(0);
            mutexId = carId;
            signal(peopleSems[personId]);

            wait(carSems[carId]);
        }
        else{
            freeCars.push_back(carId);
            signal(mutex);
            wait(carSems[carId]);
            personId = mutexId;

            signal(mutex);

            signal(peopleSems[personId]);
        }

        wait(carSems[carId]);
    }
}

void person(int personId){
    int carId;

    while(1){
        wait(mutex);

        if(freeCars.size()){
            carId = freeCars[0];
            freeCars.erase(0);
            mutexId = personId;
            carSems[carId].signal();

            peopleSems[personId].wait();
        }
        else{
            freePeople.push_back(personId);
            signal(mutex);
            peopleSems[personId].wait();
            carId = mutexId;

            signal(mutex);

            carSems[carId].signal();
        }

        carSems[carId].signal();
    }
}