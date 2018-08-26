int arreglo[]={9, 11, 12, 13};

void setup(){
    for(int i = 0; i < 4; i++){
        pinMode(arreglo[i], OUTPUT);/* aqui se define si el pin es entrada o salida, en este caso es salida*/
    }
}
void loop(){
    for(int i = 0; i < 4; i++){
        digitalWrite(arreglo[i], HIGH);
        delay(100);
        digitalWrite(arreglo[i], LOW);
    }
    for(int i=3; i>0; i--){
        digitalWrite(arreglo[i], HIGH);
        delay(100);
        digitalWrite(arreglo[i], LOW);
    }
}
