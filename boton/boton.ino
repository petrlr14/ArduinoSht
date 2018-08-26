void setup(){
    pinMode(13, INPUT);
    pinMode(0, OUTPUT);
}

void loop(){
    int x=digitalRead(13);/* TRUE===HIGH ; FALSE===LOW*/
    if(x==HIGH){
        digitalWrite(0, HIGH);
    }
}