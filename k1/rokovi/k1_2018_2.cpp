const int N = 5;
int baboons = 0;
int currSide = 0;
sem waiting[2] = {0};
vector<int> vec;
sem mutex = 1;

// side 0/1
void baboon(int side){
    wait(mutex);

    if(!baboons || (currSide == side && baboons < n && !list.size())){
        currSide=side;
        baboons++;
        signal(mutex);
    }
    else{
        vec.push_back(side);
        signal(mutex);
        wait(waiting[side]);
    }

    cross();

    wait(mutex);
    baboons--;
    if(vec.size()){
        if(vec[0] == side){
            vec.erase(side);
            baboons++;
            signal(waiting[side]);
        }
        else if(!baboons){
            currSide = !side;
            while(vec[0] == currSide && baboons < N){
                vec.erase(side);
                baboons++;
                signal(waiting[currSide]);
            }
        }
    }
    signal(mutex);
}