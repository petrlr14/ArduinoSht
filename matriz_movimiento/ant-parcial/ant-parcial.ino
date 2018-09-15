int xPos=0, yPos=0;
long xJoyStick=0, yJoyStick=0;
int field[6][6];
bool pressedPlus=true;

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

bool checkVictory(){
    bool win=true;
    for(int row=0; row<6; row++){
        for(int col=0; col<6; col++){
            if((field[row][col])==0)
                win=false;
        }
    }
    return win;
}

void clean(){
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

void updatePos(){
    xJoyStick=map(analogRead(A0), 0, 1023, 0, 5000);
    yJoyStick=map(analogRead(A1), 0, 1023, 0, 5000);
    switch(xJoyStick){
        case 0: xPos-=10;
                break;
        case 1000: xPos-=1;
                break;
        case 2000:
        case 3000: xPos+=0;
                break;
        case 4000: xPos+=1;
                break;
        case 5000: xPos+=10;
                break;
    }
    switch(yJoyStick){
        case 0: yPos-=10;
                break;
        case 1000: yPos-=1;
                break;
        case 2000:
        case 3000: yPos+=0;
                break;
        case 4000: yPos+=1;
                break;
        case 5000: yPos+=10;
                break;
    }
    xPos=constrain(xPos, 0, 5000);
    yPos=constrain(yPos, 0, 5000);
    int xPosFinal=(xPos/1000)+6;
    int yPosFinal=yPos/1000;
    digitalWrite(yPosFinal, HIGH);
    digitalWrite(xPosFinal, LOW);
    field[yPosFinal][xPosFinal-6]=1;
    clean();
}

void resetGame(){
    cleanMatrix();
    xPos=0;
    yPos=0;
    digitalWrite(yPos, HIGH);
    digitalWrite(xPos, LOW);
    clean();
}

void runFrame(){
    cleanMatrix();
    for (int h = 0; h < 5; h++){
        for (int i = 0; i <500; i++){
            for (int j = 0; j < 6; j++){
                digitalWrite(j, HIGH);
                for (int k = 6; k < 12; k++){
                    if (frames[h][j][k - 6] == 1){
                        digitalWrite(k, LOW);
                    }
                }
                clean();
            }
        }
    }
    resetGame();
}

void reset(){
    if(digitalRead(12)==HIGH && pressedPlus){
        runFrame();
    }
    if(digitalRead(12)==LOW){
        pressedPlus=!pressedPlus;
    }
}

void setup(){
    for(int i=0; i<12; i++){
        pinMode(i, OUTPUT);
    }
    pinMode(12, INPUT);
    cleanMatrix();
}

void loop(){
    
    for(int scan=0; scan<250; scan++){
        reset();
        for(int row=0; row<6; row++){
            digitalWrite(row, HIGH);
            for(int col=6; col<12; col++){
                if(field[row][col-6]==1){
                    digitalWrite(col, LOW);
                }
                if(checkVictory()){
                    runFrame();
                }
            }
            clean();
            updatePos();
        }
    }
}