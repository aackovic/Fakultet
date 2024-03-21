const int N = 3;

//fine grain

int turn[N] ={0};

void process(int i){
    while(1){
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

/*
Сви процеси су распоредом извршавања
иницијално добили вредности 1 за сопствене променљиве за
редослед (turn[i]) и сви су прочитали све вредности turn[i] из осталих
процеса у покушају да одреде нову сопствену вредност turn[i] и
свугде прочитали вредности 1, али нису још одредили нову вредност
turn[i]. Опишите разрешење и редослед уласка процеса у критичну
секцију под условом да је од тог тренутка распоред извршавања
процес 2, процес 1, процес 3, процес 2, процес 1, процес 3, …, а сваки
од њих добије довољно времена да изврши бар неколико итерација
програмске петље и кôд у критичној секцији.
*/

// resenje

/*
redom
proces 2 postavlja turn[2] na 2
ulazi u for petlju
pokusava da prodje pored procesa 1 koji u tom trenutku ima turn[1]=1 i ne uspeva (2,2)>(1,1)

proces 1 dobija izvrsavanje
postavlja turn[1] na 2
ulazi u for petlju
pokusava da prodje pored procesa 2
kako je (2,1) < (2,2) prolazi pored procesa 2
kako je (2,1) > (1,3) ne prolazi pored procesa 3

proces 3 dobija izvrsavanje
postavlja turn[3] na 2
ulazi u for petlju
pokusava da prodje pored procesa 1
kako je (2,3) > (2, 1) proces 3 ne prolazi

proces 2 dobija izvrsavanje
pokusava da prodje pored procesa 1
(2,2) > (2,1) tako da proces 2 ne prolazi pored procesa 1

proces 1 dobija izvrsavanje
pokusava da prodje pored proesa 3
kako je (2,1) < (2,3) proces 1 prolazi i ulazi u kriticnu sekciju
postavlja turn[1] na 0 i vraca se na pocetak
tu postavlja turn[1] na 1 pa zatim kao max+1 postavlja na 3
u for petlji je (3,1) > (2,2) pa ne prolazi proces 2

proces 3 dobija izvrsavanje
(2,3) < (3,1) pa proces 3 prolazi pored procesa 1
(2,3) > (2,2) pa proces 3 ne prolazi pored procesa 2

proces 2 dobija izvrsavnaje
(2,2) < (3,1) prolazi pored procesa 1
(2,2) < (2,3) prolazi pored procesa 3 i ulazi u kriticnu sekciju
turn[2] = 0
ulazi opet u petlju
turn[2] = 1 turn[2] = 4
ne prolazi pored procesa 1 (4,2) > (3,1)

proces 1 dobija izvrsavanje
(3,1) < (4,2) prolazi proces 2
(3,1) > (2,3) ne prolazi proces 3

proces 3 dobija izvrsavanje
(2,3) < (4,2) proces 3 prolazi i ulazi u kriticnu sekciju
turn[3]=0
ulazi opet u petlju
turn[3] = 1 turn[3] = 5
ne prolazi pored procesa 1 (5,3) > (3,1)
...
*/