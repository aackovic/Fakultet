int buf; // bilo koji tip
sem empty = 1, full = 0;

void Producer(int i){
    while(true){
        //proizvodnja podatka
        wait(empty);
        buf = data;
        signal(full);
    }
}

void Consumer(int i){
    while(true){
        //uzimanje podatka
        wait(full);
        result = buf;
        signal(empty);
    }
}