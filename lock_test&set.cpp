// coarse grain

bool lock = false;

void process(){
    while(true){
        <await(!lock) lock = true;>
        //kriticna sekcija
        lock = false;
        //nije kriticna sekciaj
    }
}

//fine grain

bool lock = false;

void proccess(){
    while(true){
        while(TS(lock)) skip();
        //kriticna sekcija
        lock = false;
        //nije kriticna sekcija
    }
}