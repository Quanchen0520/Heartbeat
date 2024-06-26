const byte sn[3] = { 46, 47, 48 };                          //資料選擇線
const byte xred[8] = { 22, 23, 24, 25, 26, 27, 28, 29 };    //紅燈腳位
const byte xgreen[8] = { 30, 31, 32, 33, 34, 35, 36, 37 };  //綠燈腳位
const byte xblue[8] = { 38, 39, 40, 41, 42, 43, 44, 45 };   //藍燈腳位
const byte row[8][3] = {
  //從左到右,選擇讓第N列亮
  { 0, 0, 0 },  //第一列
  { 1, 0, 0 },  //第二列
  { 0, 1, 0 },  //第三列
  { 1, 1, 0 },  //第四列
  { 0, 0, 1 },  //第五列
  { 1, 0, 1 },  //第六列
  { 0, 1, 1 },  //第七列
  { 1, 1, 1 }   //第八列
};
int speed = 10;  //速度
void setup() {
  for (int i = 22; i <= 49; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);  //致能腳EN 要是高電位才能亮喔,其他顏色燈高電位 = 不亮
  }
  for (int i = 0; i <= 7; i++) {  //這裡是為了方便調顏色
    digitalWrite(xred[i], HIGH);
    digitalWrite(xblue[i], HIGH);
    digitalWrite(xgreen[i], HIGH);
  }
}
void loop() {
  walk();
  speed = map(analogRead(A0), 0, 1023, 1, 15);  //調整速度
}
byte wk[8][8][8] = {
  //這裡就是放圖片的地方
  {
    { 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 0, 1, 1, 0, 0, 1 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 1, 0, 0, 1, 1, 1 } },
  { { 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 0, 1, 1, 0, 0, 1 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 1, 0, 0, 1, 1, 1 } },
  { { 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1 } },
  { { 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 1, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 1, 0, 0, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1 } },
  { { 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1 } },
  { { 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1 } },
  { { 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 0, 1, 1, 0, 0, 1 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 1, 0, 0, 1, 1, 1 } },
  { { 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 0, 1, 1, 0, 0, 1 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 1, 0, 0, 1, 1, 1 } },
};
void walk() {
  for (int a = 0; a <= 7; a++) {        // 此迴圈負責切換圖片
    for (int l = 1; l <= speed; l++) {  // 這個負責速度及防閃爍
      for (int i = 0; i <= 7; i++) {    // 這裡開始每一列的控制
        if (i == 0) {                   // 下面的if都是 控制每一列要亮的燈
          for (int k = 0; k <= 7; k++) {
            digitalWrite(xred[k], wk[a][k][i]);
          }
        } else if (i == 1) {
          for (int k = 0; k <= 7; k++) {
            digitalWrite(xred[k], wk[a][k][i]);
          }
        } else if (i == 2) {
          for (int k = 0; k <= 7; k++) {
            digitalWrite(xred[k], wk[a][k][i]);
          }
        } else if (i == 3) {
          for (int k = 0; k <= 7; k++) {
            digitalWrite(xred[k], wk[a][k][i]);
          }
        } else if (i == 4) {
          for (int k = 0; k <= 7; k++) {
            digitalWrite(xred[k], wk[a][k][i]);
          }
        } else if (i == 5) {
          for (int k = 0; k <= 7; k++) {
            digitalWrite(xred[k], wk[a][k][i]);
          }
        } else if (i == 6) {
          for (int k = 0; k <= 7; k++) {
            digitalWrite(xred[k], wk[a][k][i]);
          }
        } else if (i == 7) {
          for (int k = 0; k <= 7; k++) {
            digitalWrite(xred[k], wk[a][k][i]);
          }
        }
        for (int j = 0; j <= 2; j++) {
          digitalWrite(sn[j], row[i][j]);
        }
        delay(1);  //這裡是為了要讓不該亮的燈不亮
      }
    }
  }
}