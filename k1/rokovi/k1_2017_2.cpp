const int N  = 4;
sem sems[4] = {1};
sem cnts[4] = {2};
sem mutex = 1;

bool end = false;

typedef struct{
    int number;
    int color;
} Card;

vector<vector<Card>> stacks(4);

//i-ti stavlja na sledecu a uzima sa prethodne
void play(int i, vector<Card> cards){
    int indR = i == 0 ? 3 : (i - 1);
    int indL = i;

    wait(mutex);
    while(!end){
        signal(mutex);

        wait(sems[indL]);
        stacks[indL].push_back(getRandomCard(cards));
        signal(cnts[indL]);
        signal(sems[indL]);

        wait(cnts[indR]);

        wait(mutex);
        if(end){
            signal(mutex);
            break;
        }

        wait(sems[indR]);
        takeTopCard(cards, stacks[indR]);
        signal(sems[indR]);

        if(winning(cards)){
            wait(mutex);
            end = true;
            signal(mutex);
            /*wtf*/
            for(int i = 0; i < 4; i++)
                signal(cnts[i]);

        }
        wait(mutex);
    }
}