int main(void)
{ 

	u32 value_adc;
	float temp;
	u8 buffer[6];
	//***********基本功能初始化***********//
	delay_init(168);		  //初始化延时函数
	 #if 1
	uart_init(115200);	
	//**************外设硬件初始化***************//
	LED_Init();		  		//初始化与LED连接的硬件接口  
	LEDFUNC_Init(500);
	USPrintf("Booting......\r\n");//启动中
	USPrintf("SysInformation Show  Start......\r\n");//系统信息开始展示
	USPrintf("SystemName: Grounging Res\r\n");//系统名称 接地电阻
	USPrintf("SysCommunication is ok\r\n");//通讯系统就位

	Sim800_Init();	
	
	NET1mode();
	USPrintf("NetMode is Config OK ......\r\n");//系统初始化参数如下
	while(UDPconnect("ip","port")<1)
	{
		LED1=1;
		LED0=1;
		NET1mode();
	}
	USPrintf("UDPConnect ip port is OK!\r\n");//系统初始化参数如下
	delay_ms(2000);
	USPrintf("SysInit Parameter List:\r\n");//系统初始化参数如下
	
	USPrintf("StartTime:");//开始时间记录点
	Console((u8*)tmitoa(TimeStart),12);
	USPrintf("\r\n");

	My_RTC_Init();//发送基本信息之前，通信应该就位

	delay_ms(5);
	Adcurm06_Init();
	GetWorkingTemp_Init();
	delay_ms(5);
	URM06_analog_In();
	#endif 
	TIM3_Int_Init(4999,16799);//分频168M/16800=10K

	delay_ms(5);
	for(;;)
	{
	  URM06_Func();
		value_adc=Get_Adcurm06(5);
		temp=(float)value_adc*2500/4096;
		value_adc =(u32)(temp/0.33f);
		buffer[0]=(unsigned char)(value_adc/1000);
		buffer[0]+=0x30;
		buffer[1]=(unsigned char)(value_adc%1000/100);
		buffer[1]+=0x30;
		buffer[2]=(unsigned char)(value_adc%100/10);
		buffer[2]+=0x30;
		buffer[3]=(unsigned char)(value_adc%10);
		buffer[3]+=0x30;
		buffer[4]='m';
		buffer[5]='m';
		USPrintf((char *)buffer);
		delay_ms(1000);
		NVIC_SetVectorTable(NVIC_VectTab_FLASH,0);  
		Uart2_Send(buffer,7);
		delay_ms(1000);
	}

}
