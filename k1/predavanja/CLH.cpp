// coarse grain

Node tail = (false);

void process(int i){
    while(true){
        Node prev, node = (true);
        <prev = tail; tail = node;>
        <await(!prev.locked);>
        //kriticna sekcija
        <node.locked=false;>
        //nije kriticna sekcija
    }
}


//get and set

//GS(var, new)

//<int tmp = var; var = new; return (tmp);>
//koristi se za <prev = tail; tail = node;>

//fine grain

Node tail = (false);

void process(int i){
    while(true){
        Node prev, node = (true);
        prev = GS(tail, node);
        while(prev.locked) skip;
        //kriticna sekcija
        node.locked=false;
        //nije kriticna sekcija
    }
}