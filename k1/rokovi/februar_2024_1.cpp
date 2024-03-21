// coarse grain

bool lock = false;

void process(){
    while(1){
        <await(!lock); lock = true;>
        //critical
        lock = false;
        //non-critical
    }
}

//fine grain

bool TS(bool lock){
    <bool inital = lock;
    lock = true;
    return initial;>
}

bool lock = false;

void process(){
    while(1){
        while(TS(lock)) skip();
        //critical
        lock = false;
        //non-critical
    }
}

//konstantan upis u lcok izaziva invalidaciju kesa

void process(){
    while(1){
        while(lock) skip();
        while(TS(lock)){
            while(lock) skip();
        }
        //critical
        lock = false;
        //non-critical
    }
}