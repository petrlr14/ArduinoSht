int len=3;
int step=(1023)/(len);
void setup()
{
  for(int i=2; i<5; i++){
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600);
  }

void loop()
{
  float x=analogRead(A0);
  Serial.println(x);
  x=5*(x/1023);
  for(int i=2; i<5; i++){
    if(i<=x){
      digitalWrite(i, HIGH);
    }else{
      digitalWrite(i, LOW);
    }
  }
}
