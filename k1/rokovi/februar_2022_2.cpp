const int N; // broj racuna
const int M; // broj korisnika


typedef struct
{
    int balance;
    int waitingFor = 0;
    int maxTicket = 0;
    sem mutex = 1;
    sem balSem = 0;
    sem users[M] = {1, 0, 0, ...};
} Account;

Account accounts[N];

void deposit(int amount, int id){
    Account& acc = accounts[id];

    wait(acc.mutex);

    acc.balance += amount;

    if(waitingFor && acc.balance >= acc.waitingFor){
        acc.balance -= acc.waitingFor;
        acc.waitingFor = 0;
        signal(acc.balSem);
    }
    
    signal(acc.mutex);
}

void withdraw(int amount, int id){
    Account& acc = accounts[id];

    wait(acc.mutex);

    int ticket = (acc.maxTicket++) % M;

    signal(acc.mutex);

    wait(acc.users[ticket]);

    wait(acc.mutex);

    if(acc.balance >= amount){
        acc.balance -= amount;
        signal(acc.mutex);
    }
    else{
        acc.waitingFor = amount;
        signal(acc.mutex);
        wait(acc.balSem);
    }

    signal(acc.users[ticket + 1] % M);
}