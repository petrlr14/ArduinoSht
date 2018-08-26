int len=14;
int step=(1024)/(len-1);
void setup()
{
  for(int i=2; i<len; i++){
  	pinMode(i, OUTPUT);
  }
  Serial.begin(9600);
}

void loop()
{
  int x=analogRead(A0);
  Serial.println(x);
  for(int i=2; i<len; i++){
    if(x>=step*i){
    	digitalWrite(i, HIGH);
    }else{
    	digitalWrite(i, LOW);
    }
  }
}