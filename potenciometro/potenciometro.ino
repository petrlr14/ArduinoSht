void setup()
{
    pinMode(3, OUTPUT);
}
void loop()
{
    int x = analogRead(A0); /* entre cero y 1023 */
    int y = (x * 255) / 1023;
    analogWrite(3, y);
}