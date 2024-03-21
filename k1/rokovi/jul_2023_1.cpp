// coarse grain

int slot = 0;
int flag[n] = {0};
flag[0] = true;

void process(int id){
    int myslot;

    while(1){
        <myslot = slot % n; slot++;>
        <await(flag[myslot])>
        //critical
        <flag[myslot] = false;
        flag[(myslot + 1) % n] = true;>
        //non-critical
    }
}

// fine grain

//(SWAP(var1, var2) : 
//< temp = var1; var1 = var2; var2 = temp; >)


int slot = 0;
int flag[n] = {0};
flag[0] = true;

bool gflag = 1;

void process(int id){
    int myslot;

    while(1){
        bool lck = false;
        while(!lck){
            while(!gflag) skip();
            SWAP(lck, gflag);
        }

        myslot = curr % n;
        curr++;
        gflag true;

        while(!flag[myslot]) skip();
        //critical
        flag[myslot] = false;
        flag[(myslot + 1) % n] = true;
        //non-critical
    }
}