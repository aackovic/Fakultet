// coarse grain

<count = count + 1;>
<await(count == n);>

// fine grain

FA(count, 1);
while (count != n)
    skip;

// ima probleme
// reset brojaca posle svih i mora se proveriti pre pocetka inkr.
// up/down counter kao resenje
// problem azuriranja kes memorija

// sinhronizacija na barijeri sa procesom koordinatorom

int arrive[n] = {0}, cont[n] = {0};

void Worker(int i){
    while (true){
        // kod
        arrive[i] = 1;
        < await(cont[i] == 1); >
            cont[i] = 0;
    }
}

void Coordinator(){
    while (true){
        for (int i = 0; i < n; i++){
            < await(arrive[i] == 1); >
                arrive[i] = 0;
        }
        for (int i = 0; i < n; i++)
            cont[i] = 1;
    }
}