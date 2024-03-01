//coarse grain
//2 process

bool in1= false, in2 = false;
int last = 1;

void process1(){
    while(true){
        in1 = true, last = 1;
        <await(!in2 || last==2);>
        //kriticna sekcija
        in1 = false;
        //nije kriticna sekcija
    }
}

void process2(){
    while(true){
        in2 = true, last = 2;
        <await(!in1 || last==1);>
        //kriticna sekcija
        in1 = false;
        //nije kriticna sekcija
    }
}

//fine grain

bool in1= false, in2 = false;
int last = 1;

void process1(){
    while(true){
        in1 = true, last = 1;
        while(in2 && last == 1) skip();
        //kriticna sekcija
        in1 = false;
        //nije kriticna sekcija
    }
}


void process2(){
    while(true){
        in2 = true, last = 2;
        while(in1 && last == 2) skip();
        //kriticna sekcija
        in2 = false;
        //nije kriticna sekcija
    }
}