void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}
int speed = 0;    // 速度格納
int position(int val);                             // RSW位置検出の

void loop() {
  int cnt = 0;                                        // 指定回数格納
  int pos = 0;                                       // RSWの位置格納
  while(1) {
    int val = analogRead(0);                // AD変換で抵抗値読み取り
    int s = position(val);                       // RSWの位置を検出
    if ( s != pos ) {                                // RSWの位置に変化がある場合
      pos = s;                                       // 位置を初期化
      cnt = 0;                                        // cntを初期化。
    } else {
      cnt++;                                         // RSWの位置に変化が無ければcntに加算
    }
    if ( cnt == 10 ) {
      break;                                         // cntの値が指定回数(10)になったら無限ループを抜ける
    }
    delay(5);                                       // 5ミリ秒待つ
  }

  speed += pos;                                // 速度を更新
  speed = constrain(speed, 0, 200); // 値の整合
  analogWrite(3, speed);                  // PWMの出力
  digitalWrite(4, LOW);                     // 4番ピンを入力にセット
  delay(300);                                    // 0.3秒待つ 
}

int position(int val) {
  if (val < 70) {          // 力行3
    return 3;
  } else if (val < 200) {  // 力行2
    return 2;
  } else if (val < 410) {  // 力行1
    return 1;
  } else if (val < 500) {  // 惰性走行
    return 0;
  } else if (val < 630) {  // ブレーキ1
    return -2;
  } else if (val < 800) {  // ブレーキ2
    return -4;
  } else if (val < 920) {  // ブレーキ3
    return -6;
  } else {                 // 非常ブレーキ(緊急時、即座に停止)
    return -20;
  }
}

