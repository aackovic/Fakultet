//coarse grain TS

bool lock = false;

bool TS(bool lock){
    <bool initial = lock;
    lock = true;
    return inital;>
}

void process(int i){
    while(1){
        <await(!lock) lock = true;>
        //while(TS(lock)) skip;
        //critical
        lock = false;
        //non-critical
    }
}

//fine grain

//(CAS(a, b, c):
//< if (a == c) { c = b; return true;}
//else { a = c; return false;}>)



// if lock == false, lock = true, return true
// if lock == true, return false
bool c = true;
bool lock = false;

void process(int i){
    while(1){
        while(!CAS(lock,true,c)) skip;
        //critical
        lock = false;
        //non-critical
    }
}
