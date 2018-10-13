#define DS 4
#define ST 5
#define SH 6

int array[16]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

void clean(){
  for(int i=0; i<16; i++){
  	array[i]=0;
  }
}

void cleanScan(){
  for(int i=5; i<9; i++){
  	digitalWrite(i, HIGH);
  }
}

void setup()
{
  for(int i=2; i<9; i++){
  	pinMode(i, OUTPUT);
  }
}

void loop()
{
  for(int level=0; level<4; level++){
  	cleanScan();
  	digitalWrite(level, LOW);
  	for(int i=0; i<16; i++){
      
      
      digitalWrite(ST, 0);
      for(int x=15; x>=0; x--){
        digitalWrite(DS, array[x]);
        digitalWrite(SH, 0);
       	digitalWrite(SH, 1);
      }
      digitalWrite(ST, 1);
      delay(100);
  }
  }
}