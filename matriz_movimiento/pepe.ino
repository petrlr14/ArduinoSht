int matriz[6][56]={
  
  {1,0,0,0,0,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0},
  {1,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0},
  {1,0,1,1,0,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0},
  {1,0,0,0,0,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0},
  {1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0},
  {1,0,0,0,0,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0}   
 
};

void limpiar() 
{           
//Los pines de las filas se ponen en LOW.  
for (int i=0;i<6;i++)
 {  
  digitalWrite(i,LOW);
 }
//Los pines de columnas se ponen en HIGH.  
for (int i=6;i<12;i++)
 {  
  digitalWrite(i,HIGH);
 }   
}

void setup()
{
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop()
{
for(int h=0; h<56; h++){
    for(int i=0; i<1000; i++){
      for(int j=0; j<6; j++){
        digitalWrite(j, HIGH);
          for(int k=6; k<12; k++){
            
            if(matriz[j][k-6+h]==1){
              digitalWrite(k, LOW);
            }
          }
          limpiar();
      }
    }
    
  }
}
