int o = 0;
int h = 0;

sem mutex = 1;
sem oSem = 0;
sem hSem = 0;


void oxygen(int id){
    wait(mutex);
    if(h >= 2){
        h -= 2;
        signal(hSem);
        signal(hSem);
        bond(id);
        signal(mutex);
    }
    else{
        o++;
        signal(mutex);
        wait(oSem);
        bond(id);
    }
}

void hydrogen(int id){
    wait(mutex);
    if(h && o){
        h--;
        o--;
        signal(oSem);
        signal(hSem);
        bond(id);
        signal(mutex);
    }
    else{
        h++;
        signal(mutex);
        wait(hSem);
        bond(id);
    }
}

// resenje sa ok kao za barijeru

int o = 0;
int h = 0;

sem mutex = 1;
sem oSem = 0;
sem hSem = 0;

sem oOk = 0;
sem hOk = 0;


void oxygen(int id){
    wait(mutex);
    if(h >= 2){
        h -= 2;
        signal(hSem);
        wait(hOk);
        signal(hSem);
        wait(hOk);
        bond(id);
        signal(mutex);
    }
    else{
        o++;
        signal(mutex);
        wait(oSem);
        bond(id);
        signal(oOk);
    }
}

void hydrogen(int id){
    wait(mutex);
    if(h && o){
        h--;
        o--;
        signal(oSem);
        wait(oOk);
        signal(hSem);
        wait(hOk);
        bond(id);
        signal(mutex);
    }
    else{
        h++;
        signal(mutex);
        wait(hSem);
        bond(id);
        signal(hOk);
    }
}

// 2-phase barrier
// malo je drugaciji bond u odnosu na gornja resenja nebitno je

int cnt = 0;

sem mutex = 1;
sem oSem = 1;
sem hSem = 2;
sem door1 = 1;
sem door2 = 0;
typedef struct{
    vector<int> ids(3);
} Molecule;

Molecule mol = new Molecule();

void oxygen(int id){
    wait(oSem);
    mol = barrier(id);
    bond(mol);
}

void hydrogen(int id){
    wait(hSem);
    mol = barrier(id);
    bond(mol);
}

Molecule barrier(int id){
    wait(door1);
    mol.ids[cnt++] = id;
    if(cnt == 3){
        signal(door2);
    }
    else
        signal(door1);
    wait(door2);
    cnt--;
    if(!cnt){
        signal(oSem);
        signal(hSem);
        signal(hSem);
        signal(door1);
    }
    else
        signal(door2);
    return mol;
}