int PIR_sensor = A5;    //指定PIR模拟端口 A5
int LED = 13;           //指定LED端口 13
int val = 0;            //存储获取到的PIR数值
 
void setup()
{
  pinMode(PIR_sensor, INPUT);   //设置PIR模拟端口为输入模式
  pinMode(LED, OUTPUT);         //设置端口2为输出模式
  Serial.begin(9600);          //设置串口波特率为9600
}
 
void loop()
{
  val = analogRead(PIR_sensor);    //读取A0口的电压值并赋值到val
  Serial.println(val);            //串口发送val值
  
  if (val > 150)//判断PIR数值是否大于150，
  {
    digitalWrite(LED,HIGH);  //大于表示感应到有人
  }
  else
  {
    digitalWrite(LED,LOW);   //小于表示无感应到有人
  }
  delay(1000);  //延迟100ms，进行第二次测量
}
