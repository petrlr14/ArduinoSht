#define DS 4
#define ST 5
#define SH 6

int fieldMap[1][16] = 
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

int posX = 0, posY = 0, posZ=0;

bool canPress[7] = {true, true, true, true, true, true};

void cleanPos(int index){
    for(int i=0; i<16; i++){
        fieldMap[index][i]=0;
    }
}

void cleanLayer(){
    for(int i=0; i<4; i++){
        digitalWrite(i, HIGH);
    }
}

void shiftHelper(int index){
    digitalWrite(ST, 0);
    for(int i=15; i>=0; i--){
        digitalWrite(DS, fieldMap[index][i]);
        digitalWrite(SH, 0);
        digitalWrite(SH, 1);
    }
    digitalWrite(ST, 1);
}

void bottonHelper(int pin)
{
    bool isPressed = digitalRead(pin);
    if (isPressed && canPress[pin - 7])
    {
        canPress[pin - 7] = false;

        switch (pin)
        {
        case 7:
            posZ--;
            posZ=constrain(posZ, 0, 3);
            break;
        case 8:
            posZ++;
            posZ=constrain(posZ, 0, 3);
            break;
        case 10:
            posX--;
            posX=constrain(posX, 0, 3);
            break;
        case 11:
            posY--;
            posY=constrain(posY, 0, 3);
            break;
        case 12:
            posX++;
            posX=constrain(posX, 0, 3);
            break;
        case 13:
            posY++;
            posY=constrain(posY, 0, 3);
            break;
        }
    }
    if (!isPressed && !canPress[pin-7])
    {
        canPress[pin - 7] = true;
    }
}

void move()
{
    bottonHelper(7);
    bottonHelper(8);
    bottonHelper(10);
    bottonHelper(11);
    bottonHelper(12);
    bottonHelper(13);
    cleanLayer();
    cleanPos(0);
    fieldMap[0][posX+(posY*4)]=1;
    digitalWrite(posZ, LOW);
    shiftHelper(0);
}



void setup(){
    for(int i=0; i<14; i++){
        if(i<7){
            pinMode(i, OUTPUT);
        }else{
            pinMode(i, INPUT);
        }
    }
}

void loop(){
    move();
    for(int i=0; i<500; i++){

    }
}