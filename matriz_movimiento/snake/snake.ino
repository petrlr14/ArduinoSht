int xEnemy;
int yEnemy;
bool pressedPlus=true, pressedMinus=true;
int speed=0;
int currentPosX=0, currentPosY=0;
unsigned long currentTime, startTime=0;
int matriz[6][6] = {
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0}
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

void limpiar()
{
    //Los pines de las filas se ponen en LOW.
    for (int i = 0; i < 6; i++)
    {
        digitalWrite(i, LOW);
    }
    //Los pines de columnas se ponen en HIGH.
    for (int i = 6; i < 12; i++)
    {
        digitalWrite(i, HIGH);
    }
}

void cleanMatrix(){
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            matriz[i][j]=0;
        }
    }
}

void updateMatrix(){
    cleanMatrix();
    int x=map(analogRead(A0), 0, 1023, 0, 5);
    int y=map(analogRead(A1), 0, 1023, 0, 5);
    switch(x){
        case 0: currentPosX-=5;
                break;
        case 1: currentPosX-=1;
                break;
        case 4: currentPosX+=1;
                break;
        case 5: currentPosX+=5;
                break;
    }
    switch(y){
        case 0: currentPosY-=5;
                break;
        case 1: currentPosY-=1;
                break;
        case 4: currentPosY+=1;
                break;
        case 5: currentPosY+=5;
                break;
    }
    currentPosX=constrain(currentPosX, 0, 5000);
    currentPosY=constrain(currentPosY, 0, 5000);
    matriz[currentPosY/1000][currentPosX/1000]=1;
}

void resetGame(){
    cleanMatrix();
    matriz[0][0]=1;
    xEnemy=random(0, 5);
    yEnemy=random(0, 5);
    startTime=currentTime;
    speed=0;
  }
void runFrame(){
    for (int h = 0; h < 5; h++){
        for (int i = 0; i <500; i++){
            for (int j = 0; j < 6; j++){
                digitalWrite(j, HIGH);
                for (int k = 6; k < 12; k++){
                    if (frames[h][j][k - 6] == 1){
                        digitalWrite(k, LOW);
                    }
                }
                limpiar();
            }
        }
    }
    resetGame();
}

void increaseSpeed(){
    if(digitalRead(12)==HIGH && pressedPlus){
        speed+=1000;
        speed=constrain(speed, -4000, 4000);
        pressedPlus=!pressedPlus;
    }
    if(digitalRead(12)==LOW){
        pressedPlus=!pressedPlus;
    }
    if(digitalRead(13)==HIGH && pressedMinus){
        speed-=1000;
        speed=constrain(speed, -4000, 4000);
        pressedMinus=!pressedMinus;
    }
    if(digitalRead(13)==LOW){
        pressedMinus=!pressedMinus;
    }
}

void setup(){
    for (int i = 0; i < 12; i++){
        pinMode(i, OUTPUT);
    }
}

void loop(){
    currentTime=millis();
    if(currentTime>=startTime+(6000+speed)){
        xEnemy=random(0, 5);
        yEnemy=random(0, 5);
        startTime=currentTime;
    }
    for(int i=0; i<500; i++){
        digitalWrite(xEnemy, HIGH);
        digitalWrite(yEnemy+6, LOW);
        increaseSpeed();
        limpiar();
        for(int j=0; j<6; j++){
            digitalWrite(j, HIGH);
            for(int k=6; k<12; k++){
                if(matriz[j][k-6]==1 && matriz[xEnemy][yEnemy]!=1){
                    digitalWrite(k, LOW);
                }else if(matriz[j][k-6]==1 && matriz[xEnemy][yEnemy]==1){
                    runFrame();
                }
            }
            limpiar();
            updateMatrix();
        }
    }
        
}
