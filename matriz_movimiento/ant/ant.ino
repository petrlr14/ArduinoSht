int matriz[6][6] = {
    {0, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1}};

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
    for (int i = 0; i < 12; i++)
    {
        pinMode(i, OUTPUT);
    }
}

void cleanMatrix()
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            matriz[i][j] = 0;
        }
    }
}

void loop()
{
    int x = map(analogRead(A0), 0, 1023, 0, 5);
    int y = map(analogRead(A1), 0, 1023, 0, 5);
    for(int i=0; i<300; i++){
        digitalWrite(y, HIGH);
        digitalWrite(x+6, LOW);
    }
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            digitalWrite(j, HIGH);
            for (int k = 6; k < 12; k++)
            {
                if (matriz[j][k - 6] == 1)
                {
                    digitalWrite(k, LOW);
                }
            }
            limpiar();
        }
    }
}
