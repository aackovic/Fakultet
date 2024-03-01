//coarse grain

bool free = true;

request(time, id):
    <await(free); free = false;>

release(): 
    <free = true;>


//fine grain sa raspodeljenim semaforima
typedef vector<int>(3) Time; // h:m:s
bool free = true;

//delay i signal definisu se slicno kao za stafetu

void request(Time time, int id){
    wait(e);
    if(!free)
        delay();
    free = false;
    signal();
}

void release(){
    wait(e);
    free = true;
    signal();
}

//fine grain sa privatnim semaforima
typedef vector<int>(3) Time; // h:m:s
bool free = true;
sem e = 1, b[n] = {0};
priority_queue<pair<Time,int>> pq = new priority_queue<pair<Time,int>>();

void request(Time time,int id){
    wait(e);
    if(!free){
        pq.push(time, id);
        signal(e);
        wait(b[id]);
    }
    free = false;
    signal(e);
}

void release(){
    wait(e);
    free = true;
    if(!pq.empty()){
        pq.pop();
        signal(b[id]);
    }
    else
        signal(e);
}