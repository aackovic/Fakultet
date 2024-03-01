//coarse grain

int cntR = 0;
sem rw = 1;

void Reader(int i){
    while(true){
        <cntR = cntR + 1; if(cntR == 1) wait(rw); >
        //read
        <cntR = cntR - 1; if(cntR == 0) signal(rw); >
    }
}

void Writer(int i){
    while(true){
        wait(rw);
        //write
        signal(rw);
    }
}

//fine grain

int cntR = 0;
sem rw = 1;
sem mutexR = 1;

void Reader(int i){
    while(true){
        wait(mutexR);
        cntR++;
        if(cntR == 1)
            wait(rw);
        signal(mutexR);
        //read
        wait(mutexR);
        cntR--;
        if(cntR == 0)
            signal(rw);
        signal(mutexR);
    }
}

void Writer(int i){
    while(true){
        wait(rw);
        //write
        signal(rw);
    }
}

//resenje favorizuje citaoce!!

//bolje resenje ogranicava nove citaoce da udju, ne i stare da izadju

int cntR = 0;
sem rw = 1;
sem mutexR = 1, enter = 1;

void Reader(int i){
    while(true){
        wait(enter);//!!
        wait(mutexR);
        cntR++;
        if(cntR == 1)
            wait(rw);
        signal(mutexR);
        signal(enter);//!!
        //read
        wait(mutexR);
        cntR--;
        if(cntR == 0)
            signal(rw);
        signal(mutexR);
    }
}

void Writer(int i){
    while(true){
        wait(enter);
        wait(rw);
        signal(enter);
        //write
        signal(rw);
    }
}

//coarse grain - predicate based

int cntR = 0, cntW = 0;

void Reader(int i){
    while(true){
        <await(cntW == 0) cntR = cntR + 1; >
        //read
        <cntR = cntR - 1>
    }
}

void Writer(int i){
    while(true){
        <await(cntR == 0 && cntW == 0) cntW = cntW + 1; >
        //write
        <cntW = cntW - 1;>
    }
}