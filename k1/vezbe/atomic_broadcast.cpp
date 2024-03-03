// buffer size = 1

const int N;
const int B=1;

int cnt = 0;
int buffer[B] = {};

sem mutex = 1;
sem empty = B;
sem full[N] = {0};

void producer(){
    while(1){
        int item = produce();

        wait(empty);
        buffer[0] = item;

        for(int i=0;i<N;i++)
            signal(full[id]);
    }
}

void consumer(int id){
    while(1){
        wait(full[id]);

        int item = buffer[0];
        wait(mutex);
        cnt++;
        if(cnt == N){
            cnt = 0;
            signal(empty);
        }
        signal(mutex);

        consume(item);
    }
}


// buffer size > 1

const int N;
const int B;

int cnt[B] = {0};
int buffer[B] = {};

int wi = 0;
//int ri[N] = {0};

sem mutex[B] = {1};
sem empty = B;
sem full[N] = {0};

void producer(){
    //int wi = 0; //moze svoj wi
    while(1){
        int item = produce();

        wait(empty);
        buffer[wi++] = item;
        wi %= B;

        for(int i=0;i<N;i++)
            signal(full[id]);
    }
}

void consumer(int id){
    int ri = 0; //moze svako svoj ri
    while(1){
        wait(full[id]);

        int item = buffer[ri];
        wait(mutex[ri]);
        cnt[ri]++;
        if(cnt[ri] == N){
            cnt = 0;
            signal(empty);
        }
        signal(mutex[ri]);

        consume(item);
        ri = (ri + 1) % B;
    }
}