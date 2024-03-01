// coarse grain
// 1-indeksiranje
int slot = 0;
int flag [1:n] = {false};
flag[1] = true;

void process(int i){
    int myslot;

    while (true){
        < myslot = slot % (n + 1);
        slot = slot + 1;>
            <await(flag[myslot])>
            // kriticna sekcija
            < flag[myslot] = false;
        flag[myslot % (n + 1)] = true;>
        // nije kriticna sekcija
    }
}

// fine grain
// 0-indeksiranje
int slot = 0;
int flag[n] = {false};
flag[1] = true;

void process(int i) {
    int myslot;

    while (true) {
        myslot = FA(slot, 1) % n;
        while (!flag[myslot])
            skip();
        // kriticna sekcija
        flag[myslot] = false;
        flag[myslot % n] = true;
        // nije kriticna sekcija
    }
}