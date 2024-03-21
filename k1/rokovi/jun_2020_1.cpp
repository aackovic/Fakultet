//coarse grain anderson n

const int N;
int slot = 0;
bool slots[N];

void worker(int id){
    while(1){
        <int myslot = slot; slot = slot % N + 1;>
        <await (slots[myslot]);>
        //critical
        <slots[myslot] = false; 
        slots[myslot % N + 1] = true;>
        //non-critical
    }
}

//fine grain

//addAndGet(var, incr) : < var = var + incr; return(var); >

void worker(int id){
    while(1){
        int index = (addAndGet(slot,1) - 1) % N;
        while(!slots[index]) skip();
        //critical
        slots[index] = false;
        slots[(index + 1) % N] = true;
        //non-critical
    }
}