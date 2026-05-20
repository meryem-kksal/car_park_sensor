const int trigPin = 7;
const int echoPin = 6;
const int buzzerPin = 11;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //bilgisayarla haberleşme
  
  pinMode(trigPin, OUTPUT); // sesi biz gönderiyoruz (Çıkış)
  pinMode(echoPin, INPUT);  // yankıyı biz dinliyoruz (Giriş)
  pinMode(buzzerPin, OUTPUT);
  pinMode(13,OUTPUT);//LED
}

void loop() {
  // 1. ADIM: Sensörü Temizle ve Sesi Fırlat
  digitalWrite(13,LOW);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // sesi gönder
  delayMicroseconds(10);       // 10 mikrosaniye boyunca bağır
  digitalWrite(trigPin, LOW);  // Sus ve dinlemeye geç

  //sesin gidip gelme süresini ölç (mikrosaniye cinsinden)
  long sure = pulseIn(echoPin, HIGH);

  // 3. ADIM: süreyi cme Çevir (fizik devrede)
  long mesafe = (sure / 2) * 0.0343;

  // ekranda görelim
  Serial.print("Mesafe: ");
  Serial.print(mesafe);
  Serial.println(" cm");
  // park Sensörü uyarı mantığı
  if (mesafe <= 10) {
    // 10 cm'den yakınsa SÜREKLİ ÖT (çarptın)
    digitalWrite(buzzerPin, HIGH); 
    digitalWrite(13,HIGH);

  }
  else if (mesafe <= 40) {
    // 10 ile 40 cm arasındaysa KESİKLİ ÖT
    // Mesafe kısaldıkça daha hızlı öter
    digitalWrite(buzzerPin, HIGH);
    delay(50); // 50ms öt
    digitalWrite(buzzerPin, LOW);
    delay(mesafe * 10); // mesafe formülü ile dinamik bekleme
  }
  else {
    // 40 cmden uzaksa güvendeyiz SUS
    digitalWrite(buzzerPin, LOW); 
  }

  delay(50); //  minik bir boşluk

    
}
