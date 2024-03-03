// coarse grain
// 1-indeksiranje
int turn [1:n] = {0};

void process(int i){
    while (true){
        < turn[i] = max(turn [1:n]) + 1;>
            for (int j = 1; j <= n; j++){
            if (j != i)
                < await(turn[j] == 0 || turn[i] < turn[j]); >
        }
        // kriticna sekcija
        turn[i] = 0;
        // nije kriticna sekcija
    }
}

// asimetricno resenje
//  ok za inicijalne vr turn razlicite od 0
turn1 = 1;
turn1 = turn2 + 1;
while (turn2 != 0 && turn1 > turn2)
    skip();

turn2 = 1;
turn2 = turn1 + 1;
while (turn1 != 0 && turn2 >= turn1)
    skip();

// (a,b) > (c,d)

// (turn[i], i) > (turn[j], j)

// fine grain
// 0-indeksiranje
void process(int i){
    while (true){
        turn[i] = 1;
        turn[i] = (*max_element(turn, turn + n)) + 1;
        for (int j = 0; j < n; j++){
            if (j != i)
                while (turn[j] != 0 && (turn[i], i) > (turn[j], j))
                    skip();
        }
        // kriticna sekcija
        turn[i] = 0;
        // nije kriticna sekcija
    }
}
