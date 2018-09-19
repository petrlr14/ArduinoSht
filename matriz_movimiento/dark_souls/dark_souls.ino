int posX=1, posY=1, posInFieldX=1, posInFieldY=1, joyStickX, joyStickY, speedConst=10;
bool pressed=true;
int deathConst=4000, currentTime=0, contKills=0;
bool won=false;
int field[6][6]={
    {1,0,0,0,0,0},
    {0,0,0,0,0,0},
    {0,0,0,0,0,0},
    {0,0,0,0,0,0},
    {0,0,0,0,0,0},
    {0,0,0,0,0,0}
};

int frames[5][6][6] = {
    {{1, 1, 1, 1, 1, 1},
     {1, 0, 0, 0, 0, 1},
     {1, 0, 0, 0, 0, 1},
     {1, 0, 0, 0, 0, 1},
     {1, 0, 0, 0, 0, 1},
     {1, 1, 1, 1, 1, 1}},
    {{0, 0, 0, 0, 0, 0},
     {0, 1, 1, 1, 1, 0},
     {0, 1, 0, 0, 1, 0},
     {0, 1, 0, 0, 1, 0},
     {0, 1, 1, 1, 1, 0},
     {0, 0, 0, 0, 0, 0}},
    {{0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0},
     {0, 0, 1, 1, 0, 0},
     {0, 0, 1, 1, 0, 0},
     {0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0}},
    {{0, 0, 0, 0, 0, 0},
     {0, 1, 1, 1, 1, 0},
     {0, 1, 0, 0, 1, 0},
     {0, 1, 0, 0, 1, 0},
     {0, 1, 1, 1, 1, 0},
     {0, 0, 0, 0, 0, 0}},
    {{1, 1, 1, 1, 1, 1},
     {1, 0, 0, 0, 0, 1},
     {1, 0, 0, 0, 0, 1},
     {1, 0, 0, 0, 0, 1},
     {1, 0, 0, 0, 0, 1},
     {1, 1, 1, 1, 1, 1}}};

void cleanScan(){
    for(int row=0; row<6; row++){
        digitalWrite(row, LOW);
        for(int col=6; col<12; col++){
            digitalWrite(col, HIGH);
        }
    }
}

void cleanMatrix(){
    for(int row=0; row<6; row++){
        for(int col=0; col<6; col++){
            field[row][col]=0;
        }
    }
}

void setEnemey(){
    randomSeed(millis());
    int enemyX=0, enemyY=0;
    for(int i=0; i<3; i++){
        enemyX=random(1,6);
        enemyY=random(1,6);
        field[enemyX][enemyY]=1;
    }
}

void updateMatrix(){
    joyStickX=map(analogRead(A0), 0, 1023, 0, 3);
    joyStickY=map(analogRead(A1), 0, 1023, 0, 3);
    switch(joyStickX){
        case 0: posX-=speedConst;
                break;
        case 2: posX+=speedConst;
                break;
    }
    switch(joyStickY){
        case 0: posY-=speedConst;
                break;
        case 2: posY+=speedConst;
                break;
    }
    posX=constrain(posX, 0, 5000);
    posY=constrain(posY, 0, 5000);
    posInFieldX=posX/1000;
    posInFieldY=posY/1000;
    if(posInFieldX==1 && posInFieldY==1){
        runFrame();
    }
    digitalWrite(posInFieldX+6, LOW);
    digitalWrite(posInFieldY, HIGH);
    
    cleanScan();
}

void buttonPress(){
    bool sig=digitalRead(12);
    bool pos=true;
    if(posInFieldX==0 && posInFieldY==0){
        pos=false;
    }
    if(pressed && sig && pos){
        if(field[posInFieldY][posInFieldX]==1){
            pressed=!pressed;
            field[posInFieldY][posInFieldX]=0;
            speedConst+=3;
            contKills++;
            if(contKills==3){
                won=true;
            }
        }
    }
    if(sig){
        pressed=!pressed;
    }
}

void startGame(){
    currentTime=0;
    posX=0;
    posY=0;
    posInFieldX=0;
    posInFieldY=0;
    contKills=0;
    won=false;
    cleanMatrix();
    setEnemey();
    field[0][0]=1;
}

void death(){
    bool pos=(posInFieldX==0 && posInFieldY==0);
    if(field[posInFieldY][posInFieldX]==1 && !pos){
        currentTime+=10;
    }else{
        currentTime=0;
    }
    if(currentTime==deathConst){
        runFrame();
    } 
}

void runFrame(){
    for(int frame=0; frame<5; frame++){
        for(int scan=0; scan<100; scan++){
            for(int row=0; row<6; row++){
                digitalWrite(row, HIGH);
                for(int col=6; col<12; col++){
                    if(frames[frame][row][col-6]==1){
                        digitalWrite(col, LOW);
                    }
                }
                cleanScan();
            }
        }
    }
    startGame();
}


void setup(){
    for(int i=0; i<12; i++){
        pinMode(i, OUTPUT);
    }
    startGame();
}

void loop(){
    for(int scan=0; scan=200; scan++){
        buttonPress();
       for(int row=0; row<6; row++){
            digitalWrite(row, HIGH);
            for(int col=6; col<12; col++){
                if(field[row][col-6]==1){
                    digitalWrite(col, LOW);
                }
                if(won){
                    runFrame();
                }
            }
            cleanScan();
            updateMatrix();
        }
        death(); 
    }
}