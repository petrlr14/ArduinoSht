int frames = 5;
int matriz[5][6][6] = {
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
    for (int i = 0; i < 12; i++){
        pinMode(i, OUTPUT);
    }
}

void loop()
{
    int x=map(analogRead(A0), 0, 255, 1, 4);
    intyx=map(analogRead(A1), 0, 255, 1, 4);
    for (int h = 0; h < frames; h++)
    {
        for (int i = 0; i < 50*x; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                digitalWrite(j, HIGH);
                for (int k = 6; k < 12; k++)
                {
                    if (matriz[h][j][k - 6] == 1)
                    {
                        digitalWrite(k, LOW);
                    }
                }
                limpiar();
            }
        }
    }
}
