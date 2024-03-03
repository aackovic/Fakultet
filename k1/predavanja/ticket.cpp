//coarse grain

int number = 1, next = 1;
int turn[n] = {0};

void process(int i){

    while(true){
        <turn[i] = number; number = number + 1;> // moze <turn[i]=number++;>
        <await(turn[i] == next);>
        //kriticna sekcija
        <next = next + 1;> // next++;
        //nije kriticna sekcija
    }

}

//fine grain
// FA(var, incr)
// <int tmp = var; var = var + incr; return (tmp);>

//upotreba
// turn[i] = number; number = number + 1;>

int number = 1, next = 1;
int turn[n] = {0};

void process(int i){

    while(true){
        turn[i] = FA(number, 1);
        while(turn[i] != next) skip();
        //kriticna sekcija
        next++;
        //nije kriticna sekcija
    }

}