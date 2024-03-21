//coarse grain

Node* tail = nullptr;

void process(){
    while(1){
        Node* prev, next = new Node();
        next->locked = true;
        <prev = tail; tail = next;>
        <await(!prev->locked);>
        //critical
        <next->locked> = false;>
        //non-critical
    }
}

//fine grain

/*
(CAS(a, b, c):
< if (a == c) { c = b; return true;}
else { a = c; return false;}>)
*/

Node* tail = nullptr;

void process(){
    while(1){
        Node* prev, next = new Node();
        next->locked = true;
        prev = tail;
        while(!CAS(prev, next, tail)) skip();
        //

        while(prev->locked) skip();

        prev->locked = false;
    }
}