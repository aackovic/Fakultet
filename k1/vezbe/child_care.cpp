int cntD = 0; // deca
int cntV = 0; // vaspitacice
const int K = 3;

int waiting = 0; // broj vaspitacica koje cekaju

sem mutex = 1;
sem v = 0; // vaspitacice pobegulje

int bringChilden(int cnt){
    wait(mutex);
    if((cntD + cnt) <= cntV * K){
        cntD += cnt;
        signal(mutex);
        return 1;
    }
    else{
        signal(mutex);
        return 0;
    }
}

void takeChildren(int cnt){
    wait(mutex);
    if(cnt <= cntD){
        cntD -= cnt;
    }

    while(waiting && cntD <= (brV - 1) * K){
        cntV--;
        waiting--;
        signal(v);
    }

    signal(mutex);
}

void vaspitacicaArriving(){
    wait(mutex);

    cntV++;
    if(waiting){
        cntV--;
        waiting--;
        signal(v);
    }
    signal(mutex);
}

void vaspitacicaLeaving(){
    wait(mutex);

    if(cntD <= (brV - 1) * K){
        brV--;
        signal(mutex);
    }
    else{
        signal(mutex);
        wait(v);
    }
}