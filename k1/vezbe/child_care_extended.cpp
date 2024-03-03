// roditelj ceka da ostavi decu sve dok ne uspe da ostavi

// 1. resenje

const int K = 3;

int cntD = 0, cntV = 0;
int waitingD = 0, waitingV = 0;

sem mutex = 1;
sem entry = 1;
sem v = 0;

void bringChildren(int cnt){
    wait(entry);
    wait(mutex);

    if((cntD + cnt) > K * cnt){
        waitingD = cnt;
        signal(mutex);
        wait(v);
        waitingD = 0;
    }

    cntD += cnt;
    signal(mutex);
    signal(entry);
}

void takeChildren(int cnt){
    wait(mutex);

    cntD-=cnt;
    if(waitingD && cntD + waitingD <= K * cntV)
        signal(v);
    else if(waitingV && cntD <= K * (cntV - 1))
        signal(v);
    else
        signal(mutex);
}

void vaspitacicaArriving(){
    wait(mutex);

    cntV++;
    if(waitingD && cntD + waitingD <= K * cntV)
        signal(v);
    else if(waitingV && cntD <= K * (cntV - 1))
        signal(v);
    else
        signal(mutex);
}

void vaspitacicaLeaving(){
    wait(entry);
    wait(mutex);
    if(cntD > K * (cntV - 1)){
        waitingV++;
        signal(mutex);
        wait(v);
        waitingV--;
    }
    cntV--;
    signal(mutex);
    signal(entry);
}


// 2. resenje - queue


const int K = 3;

typedef struct{
    char type;
    int cnt;
    sem s;
} Person;

int cntD = 0, cntV = 0;
sem mutex = 1;
queue<int> q;

void bringChildren(int cnt){
    wait(mutex);

    if((cntD + cnt) > K * cnt){
        Person p = new Person();
        p.cnt=cnt;
        p.type = 'd';
        init(p.sem,0);
        q.push(p);
        signal(mutex);
        wait(p.sem);
    }

    cntD += cnt;
    if(q.size())
        signal_c();
    else
        signal(mutex);
}

void takeChildren(int cnt){
    wait(mutex);

    cntD-=cnt;
    if(q.size())
        signal_c();
    else
        signal(mutex);
}

void vaspitacicaArriving(){
    wait(mutex);

    cntV++;
    if(q.size())
        signal_c();
    else
        signal(mutex);
}

void vaspitacicaLeaving(){
    wait(mutex);
    if(cntD > K * (cntV - 1)){
        Person p = new Person();
        p.cnt=0; // nebitno je
        p.type='v';
        init(p.sem,0);
        q.push(p);
        signal(mutex);
        wait(p.sem);
    }
    cntV--;
    if(q.size())
        signal_c();
    else
        signal(mutex);
}

void signal_c(){
    Person p  = q.front();
    if(p.type == 'v' && cntD <= K * (cntV - 1)){
        q.pop();
        signal(p.sem);
    }
    else if(p.type == 'd' && (cntD + p.cnt) <= K *cntV){
        q.pop();
        signal(p.sem);
    }
    else
        signal(mutex);
}