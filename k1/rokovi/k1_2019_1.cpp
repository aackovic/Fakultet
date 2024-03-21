//coarse grain

bool lock = false;

void process(int i){
    while(1){
        <await(!lock); lock=true;>
        //critical section
        lock = false;
        //non-critical section
    }
}

//fine grain

//SWAP(var1, var2) : < temp = var1; var1 = var2; var2 = temp; >

bool lock = false;

void process(int i){
    bool initLock = true;

    while(1){
        while(lock) skip;

        SWAP(lock, initLock);
        while(initLock){
            while(lock) skip;
        }

        //critical
        lock = false;
        //non - critical
    }
}