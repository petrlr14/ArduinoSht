#define DS 4
#define ST 5
#define SH 6

#define ZUP 7
#define ZDOWN 8
#define FIRE 9
#define XLEFT 10
#define YUP 11
#define XRIGHT 12
#define YDOWN 13

long offSet = 1000, timer = 0;
int field[4][4][4];
int array[16];
int bombCont = -1;
bool canPress[7] = {true, true, true, true, true, true, true};

class Hero {
 public:
  int posX, posY, posZ;
};

class Enemy {
 public:
  int posX, posY, posZ;
};

class Bomb {
 public:
  int posX, posY, posZ;
};

Hero hero;
Enemy enemy;
Bomb bomb[3];

void cleanSolid() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        field[i][j][k] = 0;
      }
    }
  }
}

void shiftHelper() {
  digitalWrite(ST, 0);
  for (int i = 15; i >= 0; i--) {
    digitalWrite(SH, 0);
    digitalWrite(DS, array[i]);
    digitalWrite(SH, 1);
  }
  digitalWrite(ST, 1);
}

void cleanShift() {
  digitalWrite(ST, 0);
  for (int i = 15; i >= 0; i--) {
    digitalWrite(SH, 0);
    digitalWrite(DS, 0);
    digitalWrite(SH, 1);
  }
  digitalWrite(ST, 1);
}

void cleanScan() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(i, HIGH);
  }
}

void matrixToArray(int level) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      array[j + (i * 4)] = field[level][i][j];
    }
  }
}

void buttonHelper(int pin, int* data, int mod) {
  bool isPressed = digitalRead(pin);
  if (canPress[pin - 7] && isPressed) {
    canPress[pin - 7] = false;
    if (pin != FIRE) {
      *data = constrain(*data + mod, 0, 3);
    } else {
      bombCont++;
      if (bombCont == 3) {
        bombCont = 0;
      }
      setBomb();
    }
  }
  if (!canPress[pin - 7] && !isPressed) {
    canPress[pin - 7] = true;
  }
}

void setBomb() {
  bomb[bombCont].posX = hero.posX;
  bomb[bombCont].posY = hero.posY;
  bomb[bombCont].posZ = hero.posZ;
}

void player() {
  buttonHelper(ZUP, &hero.posZ, -1);
  buttonHelper(ZDOWN, &hero.posZ, 1);
  buttonHelper(FIRE, &hero.posX, 1);
  buttonHelper(XLEFT, &hero.posX, -1);
  buttonHelper(YUP, &hero.posY, -1);
  buttonHelper(XRIGHT, &hero.posX, 1);
  buttonHelper(YDOWN, &hero.posY, 1);
  cleanSolid();
}

void enemyMove() {
  if (hero.posX > enemy.posX) {
    enemy.posX++;
  }
  if (hero.posX < enemy.posX) {
    enemy.posX--;
  }
  if (hero.posY > enemy.posY) {
    enemy.posY++;
  }
  if (hero.posY < enemy.posY) {
    enemy.posY--;
  }
  if (hero.posZ > enemy.posZ) {
    enemy.posZ++;
  }
  if (hero.posZ < enemy.posZ) {
    enemy.posZ--;
  }
}

void drawBomb() {
  for (int i = 0; i < 3; i++) {
    if (bomb[i].posX != 1) {
      field[bomb[i].posZ][bomb[i].posY][bomb[i].posX] = 1;
    }
  }
}

void drawAll() {
  field[hero.posZ][hero.posY][hero.posX] = 1;
  drawBomb();
  field[enemy.posZ][enemy.posY][enemy.posX] = 1;
}

void resetGame() {
  hero.posX = 0;
  hero.posY = 0;
  hero.posZ = 0;
  for (int i = 0; i < 3; i++) {
    bomb[i].posX = -1;
    bomb[i].posY = -1;
    bomb[i].posZ = -1;
  }
  enemy.posX = 3;
  enemy.posY = 3;
  enemy.posZ = 3;
}

bool isInCollision() {
  return enemy.posZ == hero.posZ && enemy.posY == hero.posY &&
         enemy.posX == hero.posX;
}

bool isInExplotion() {
  bool explotion = false;
  for (int i = 0; i < 3; i++) {
    if (bomb[i].posX == enemy.posX && bomb[i].posY == enemy.posY &&
        bomb[i].posZ == enemy.posZ) {
      explotion = true;
      break;
    }
  }
  return explotion;
}

void makeExplotion() {
  int offSetXL = constrain(enemy.posX - 1, 0, 3);
  int offSetXR = constrain(enemy.posX + 1, 0, 3);
  int offSetYU = constrain(enemy.posY - 1, 0, 3);
  int offSetYD = constrain(enemy.posY + 1, 0, 3);
  int offSetZU = constrain(enemy.posZ - 1, 0, 3);
  int offSetZD = constrain(enemy.posZ + 1, 0, 3);
  for (int i = offSetZU; i <= offSetZD; i++) {
    for (int j = offSetYU; j <= offSetYD; j++) {
      for (int k = offSetXL; k <= offSetXR; k++) {
        field[i][j][k] = 1;
      }
    }
  }
}

void makeCollision() {
  int offSetXL = constrain(hero.posX - 1, 0, 3);
  int offSetXR = constrain(hero.posX + 1, 0, 3);
  int offSetYU = constrain(hero.posY - 1, 0, 3);
  int offSetYD = constrain(hero.posY + 1, 0, 3);
  int offSetZU = constrain(hero.posZ - 1, 0, 3);
  int offSetZD = constrain(hero.posZ + 1, 0, 3);
  for (int i = offSetZU; i <= offSetZD; i++) {
    for (int j = offSetYU; j <= offSetYD; j++) {
      for (int k = offSetXL; k <= offSetXR; k++) {
        field[i][j][k] = 1;
      }
    }
  }
}

void setup() {
  for (int i = 0; i < 14; i++) {
    if (i > 6) {
      pinMode(i, INPUT);
    } else {
      pinMode(i, OUTPUT);
    }
  }
  cleanScan();
  resetGame();
  timer = millis();
}

void procedure(int j) {
  matrixToArray(j);
  shiftHelper();
  digitalWrite(j, LOW);
  cleanShift();
  digitalWrite(j, HIGH);
}

void loop() {
  for (int level = 0; level < 4; level++) {
    if (isInCollision()) {
      makeCollision();
      for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 4; j++) {
            procedure(j);
        }
      }
      resetGame();
      timer = millis();
    } else if (isInExplotion()) {
      makeExplotion();
      for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 4; j++) {
          procedure(j);
        }
      }
      resetGame();
      timer = millis();
    } else {
      procedure(level);
      cleanSolid();
      player();
      if (millis() >= (timer + offSet)) {
        timer = millis();
        enemyMove();
      } else {
        drawAll();
      }
    }
  }
}