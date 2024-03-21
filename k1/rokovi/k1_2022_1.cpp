//coarse grain anderson


const int N;
int slot;
bool slots[N];

void worker(int id){
    while(1){
        <int myslot = slot; slot = slot % N + 1;>
        <await (slots[myslot]);>
        //critical
        <slots[myslot] = false; slots[myslot % N + 1] = true;>
        //non-critical
    }
}

//fine grain CAS
//(CAS(a, b, c) : < if (a == c) { c = b; return true; } else { a = c; return false; } >)

const int N;
int slot;
bool slots[N];

void worker(int id){
    while(1){
        myslot = slot;
        while(!CAS(myslot, myslot % N + 1, slot)) skip();
        while(!slots[myslot]) skip();
        //critical
        slots[myslot] = false;
        slots[myslot % N + 1] = true;
        //non-critical
    }
}