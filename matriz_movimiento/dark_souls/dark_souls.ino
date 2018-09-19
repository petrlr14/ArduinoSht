int posX=1, posY=1, posInFieldX=1, posInFieldY=1, joyStickX, joyStickY, speedConst=1;
bool pressed=true;
int deathConst=2000, currentTime=0, contKills=0;
bool won=false, first=true, sobre=false;
int field[6][6]={
    {1,0,0,0,0,0},
    {0,0,0,0,0,0},
    {0,0,0,0,0,0},
    {0,0,0,0,0,0},
    {0,0,0,0,0,0},
    {0,0,0,0,0,0}
};

int frames[6][6] = {

        {1,0,0,0,0,1},
        {0,1,1,1,1,0},
        {0,0,1,1,0,0},
        {0,0,1,1,0,0},
        {0,1,1,1,1,0},
        {1,0,0,0,0,1}
    
    };

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
    randomSeed(analogRead(A2));
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
        case 2: 
        case 3: posX+=speedConst;
                break;
    }
    switch(joyStickY){
        case 0: posY-=speedConst;
                break;
        case 2: 
        case 3:posY+=speedConst;
                break;
    }
    posX=constrain(posX, 0, 5000);
    posY=constrain(posY, 0, 5000);
    posInFieldX=posX/1000;
    posInFieldY=posY/1000;
    if(!(posInFieldX==0&&posInFieldY==0)){
        sobre=true;
    }
    digitalWrite(posInFieldX+6, LOW);
    digitalWrite(posInFieldY, HIGH);
    cleanScan();
}
    
void respawn(){
    if((posInFieldX==0&&posInFieldY==0)&&sobre){
        cleanMatrix();
        setEnemey();
        field[0][0]=1;
        sobre=!sobre;
    }
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
    first=false;
    currentTime=0;
    posX=0;
    posY=0;
    posInFieldX=1;
    posInFieldY=1;
    contKills=0;
    won=false;
    cleanMatrix();
    setEnemey();
    field[0][0]=1;
}

void death(){
    if(field[posInFieldY][posInFieldX]==1){
        if(posInFieldX==0 && posInFieldY==0){
            currentTime=0;
        }
        currentTime+=10;
    }else if(posInFieldX==0 && posInFieldY==0){
        if(won){
            runFrame(true);
        }
    }else{
        currentTime=0;
    }
    if(currentTime==deathConst){
        runFrame(true);
    } 
}

void runFrame(bool flag){
    
        for(int scan=0; scan<300; scan++){
            for(int row=0; row<6; row++){
                digitalWrite(row, HIGH);
                for(int col=6; col<12; col++){
                    if(frames[row][col-6]==1){
                        digitalWrite(col, LOW);
                    }
                }
                cleanScan();
            }
        }
    
    if(flag){
    startGame();
}
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
            }
            cleanScan();
            updateMatrix();
        }
        respawn();
        death(); 
    }
}
/* 
int posX=1, posY=1, posInFieldX=0, posInFieldY=0, joyX=0, joyY=0, speed=1, timeToDie=0;
bool won=false, position=false, pressed=true;

int field[6][6]={
    {1,0,0,0,0,0},
    {0,0,0,0,0,0},
    {0,0,0,0,0,0},
    {0,0,0,0,0,0},
    {0,0,0,0,0,0},
    {0,0,0,0,0,0}
};

int frame[6][6]={
    {1,0,0,0,0,1},
    {0,1,0,0,1,0},
    {0,0,1,1,0,0},
    {0,0,1,1,0,0},
    {0,1,0,0,1,0},
    {1,0,0,0,0,1}
};

void setEnemies(){
    randomSeed(analogRead(A2));
    int enemyX, enemyY;
    for(int i=0; i<3; i++){
        do{
            enemyX=random(0,6);
            enemyY=random(0,6);
        }while(field[enemyX][enemyY]==1);
        field[enemyX][enemyY]=1;
    }
}


void clean(){
    for(int i=0; i<6; i++){
        digitalWrite(i, LOW);
        for(int j=6; j<12; j++){
            digitalWrite(j, HIGH);
        }
    }
}

void cleanMatrix(){
    for(int i=0; i<6; i++){
        for(int j=1; j<6; j++){
            field[i][j]=0;
        }
    }
}

void move(){
    joyX=map(analogRead(A0), 0, 1023, 0,2);
    joyY=map(analogRead(A1), 0, 1023, 0,2);
    switch(joyX){
        case 0:posX-=speed;
                break;
        case 2: posX+=speed;
                break;
    }
    switch(joyY){
        case 0:posY-=speed;
                break;
        case 2:posY+=speed;
                break;
    }
    posX=constrain(posX, 0,5000);
    posY=constrain(posY, 0,5000);
    posInFieldX=posX/1000;
    posInFieldY=posY/1000;
    digitalWrite(posInFieldY, HIGH);
    digitalWrite(posInFieldX+6, LOW);
    clean();
}

void respawn(){
    if(posX==0&&posY==0&&position){
        position=false;
        cleanMatrix();
        setEnemies();
        field[0][0]=1;
    }
    if(!(posX==0&&posY==0)){
        position=true;
    }
}

void pressedButton(){
    bool signa=digitalRead(12);
    bool positionDude=(posInFieldX==0&&posInFieldY==0);
    if(signa&&pressed){
        pressed=!pressed;
        if(!positionDude){
            if(field[posInFieldY][posInFieldX]==1){
                field[posInFieldY][posInFieldX]=0;
                speed+=10;
            }
        }
    }
    if(!signa){
        pressed=!pressed;
    }
}

void setup(){
    for(int i=0; i<12; i++){
        pinMode(i, OUTPUT);
    }
    pinMode(12, INPUT);
    setEnemies();
}

void death(){
    if(field[posInFieldY][posInFieldX]==1){
        if(posInFieldY==0&&posInFieldX==0){
            timeToDie=0;
            return;
        }
        timeToDie+=10;
        if(timeToDie==200){
           runFrame();
        }
    }else{
        timeToDie=0;
    }
}

void runFrame(){
    for(int scan=0; scan<500; scan++){
        for(int row=0; row<6; row++){
            digitalWrite(row, HIGH);
            for(int col=6; col<12; col++){
                if(frame[row][col-6]==1){
                    digitalWrite(col, LOW);
                }
            }
        }
    }
}

void loop(){
    for(int scan=0; scan<200; scan++){
        pressedButton();
        for(int row=0; row<6; row++){
            digitalWrite(row, HIGH);
            for(int col=6; col<12; col++){
                if(field[row][col-6]==1){
                    digitalWrite(col, LOW);
                }
            }
            move();
            clean();
        }
                respawn();
    }
}
 */