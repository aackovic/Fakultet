
int in[n] = {0}, last[n] = {0};

void process(int i){
    while(true){
        for(int j = 0; j < n; j++){
            in[i] = j;
            last[j] = i;
            for(int k = 1; k < n; k++){
                if(k!=i)
                    while(in[k] >= in[i] && last[j] == i) skip();
            }
        }
        //kriticna sekcija
        in[i] = 0;
        //nije kriticna sekcija
    }
}