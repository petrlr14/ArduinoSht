int xEnemy=5;
int yEnemy=5;
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

void setup()
{
    for (int i = 0; i < 12; i++){
        pinMode(i, OUTPUT);
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

void loop()
{
    
    
    currentTime=millis();
    if(currentTime>=startTime+6000){
        xEnemy=random(0, 5);
        yEnemy=random(0, 5);
        startTime=currentTime;
    }
    for(int i=0; i<500; i++){
        for(int j=0; j<6; j++){
            digitalWrite(j, HIGH);
            for(int k=6; k<12; k++){
                if(matriz[j][k-6]==1){
                    digitalWrite(k, LOW);
                }
            }
            limpiar();
            
            updateMatrix();
        }
    }
        
}
