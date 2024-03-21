//coarse grain

Node* tail = nullptr;

void worker(){
    while(1){
        Node* node = new Node();
        node->locked = 1;
        <prev = tail; tail = node; >
        <await (!prev || !prev->locked); >
        //critical
        node->locked = 0;
        //non-critical
    }
}

//fine grain

Node* tail = nullptr;

void worker(){
    while(1){
        Node* node = new Node();
        node->locked = 1;
        Node* prev = node;
        SWAP(prev, tail);
        while(prev && prev->locked) skip();
        //critical
        node->locked = 0;
        //non-critical
    }
}