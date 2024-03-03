int cntR = 0, cntW = 0;
sem e = 1, r = 0, w = 0;
int delR = 0, delW = 0; //delayed

//delay i signal kao opste op.

void delay(){
    if(!request){
        delP++; // P - proces r/w
        signal(e);
        wait(rs); //request semafor r/w
    }
}

void signal(){
    if(req1){
        delR--;
        signal(r); //npr reader
    }
    else if(req2){
        delW--;
        signal(w); //npr writer
    }
    //...
    else
        signal(e);
}


void Reader(int i){
    while(true){
        //...
        wait(e);
        if(cntW > 0){
            delR++;
            signal(e);
            wait(r);
        }
        cntR++;
        if(delR > 0){
            delR--;
            signal(r);
        }
        else
            signal(e);
        //read
        wait(e);
        cntR--;
        if(cntR == 0 && delW > 0){
            delW--;
            signal(w);
        }
        else
            signal(e);
        //...
    }
}

void Writer(int i){
    while(true){
        //...
        wait(e);
        if(cntR > 0 || cntW > 0){
            delW++;
            signal(e);
            wait(w);
        }
        cntW++;
        signal(e);
        //write
        wait(e);
        cntW--;
        if(delR > 0){
            delR--;
            signal(r);
        }
        else if(delW > 0){
            delW--;
            signal(w);
        }
        else
            signal(e);
    }
}

//moze i univerzalni signal
//imamo neku listu za cekanje
vector<char> lst; 

void signal(){
    if(lst.size() && lst[0] == 'R' && cntW == 0){
        lst.erase(0);
        signal(r);
    }
    else if(lst.size() && lst[0] == 'W' && cntR == 0 && cntW == 0){
        lst.erase(0);
        signal(w);
    }
    else
        signal(e);
}