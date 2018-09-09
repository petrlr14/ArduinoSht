int frames = 5;
int matriz[6][6] = {
    {1, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0  },
     {0, 0, 0, 0, 0, 0}};

void limpiar()
{
    //Los pines de las filas se ponen en LOW.
    for (int i = 0; i < 6; i++)
    {
        digitalWrite(i, LOW);
    }
    //Los pines de columnas se ponen en HIGH.
    for (int i = 8; i < 13; i++)
    {
        digitalWrite(i, HIGH);
    }
}

void setup()
{
    for (int i = 0; i < 6; i++){
        pinMode(i, OUTPUT);
    }
    for(int i=8; i<14; i++){
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

void loop()
{
    int x=map(analogRead(A0), 0, 1023, 0, 5);
    int y=map(analogRead(A1), 0, 1023, 0, 5);
        for (int i = 0; i < 50; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                digitalWrite(j, HIGH);
                for (int k = 8; k < 14; k++)
                {
                    cleanMatrix();
                    matriz[x][y]=1;
                    if (matriz[j][k - 8] == 1)
                    {
                        digitalWrite(k, LOW);
                    }
                }
                limpiar();
            }
        }
}
