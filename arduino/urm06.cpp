#define  TRIGGER   2  // 触发超声波

void setup() 
{ 
  Serial.begin(9600);
  pinMode(TRIGGER, OUTPUT);
}
void loop()
{
  digitalWrite(TRIGGER, LOW); // 使超声波信号使能接口低电平,100ms/time

  unsigned int distance = analogRead(A0);  // 读取URM06输出的模量
  
  distance = (unsigned int)(((unsigned long)distance * 5000)/1024);  //设置参考电压为5V，计算出单位为毫伏的采集到的模拟电压

  distance = (unsigned int)((float)distance / 0.33f); //输出距离值,单位毫米,每0.33毫伏代表1毫米

  Serial.print(distance);     
  Serial.println("mm");
  delay(1000);  //延迟100ms，进行第二次测量
}
