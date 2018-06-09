int main(void)
{ 
	 u32 value;
	float temp;
	u8 buffer[7];
	int t;
	delay_init(168);
	Adcurm06_Init();	
#if 1
	//***********基本功能初始化***********//
	delay_init(168);		  //初始化延时函数
	uart_init(115200);	
	usart2_init(72,115200);

	USPrintf("Booting......\r\n");//启动中
	USPrintf("SysInformation Show  Start......\r\n");//系统信息开始展示
	USPrintf("SystemName: Grounging Res\r\n");//系统名称 接地电阻
	Sim800_Init();
	USPrintf("SysCommunication is ok\r\n");//通讯系统就位
	if(SD_Init())//检测不到 SD 卡,返回的是错误
	{
		USPrintf("SDCard was not found\r\n");//sd卡未就位
	}
	else
	{
		USPrintf("SDCard is OK!\r\n");//sd卡就位
	}
	USPrintf("SysInit Parameter List:\r\n");//系统初始化参数如下
	STMFLASH_Read(FlashSave_StartAddr,(u32*)StartCfg,17);
	memcpy(DHSyscfg.DH_CMD_ID,StartCfg,17);
	USPrintf("CMD_ID:");//设备ID号码
	Console(DHSyscfg.DH_CMD_ID,17);
	USPrintf("\r\n");
	USPrintf("StartTime:");//开始时间记录点
	Console((u8*)tmitoa(TimeStart),12);
	USPrintf("\r\n");

	
	//**************外设硬件初始化***************//
	LED_Init();		  		//初始化与LED连接的硬件接口  
	LEDFUNC_Init(500);
	delay_ms(5);
	for(;;)
	{	
		USPrintf("SysInit Parameter List:\r\n");
	  URM06_Func_Init(60,40);
		value = Get_Adcurm06(ADC_Channel_5);
 		temp=(float)value*2500/4096;
 		value =(u32)(temp/0.33f);
		buffer[0]=(unsigned char)(value/10000);
		buffer[0]+=0x30;
		buffer[1]=(unsigned char)(value%10000/1000);
		buffer[1]+=0x30;
		buffer[2]=(unsigned char)(value%1000/100);
		buffer[2]+=0x30;
		buffer[3]=(unsigned char)(value%100/10);
		buffer[3]+=0x30;
 		buffer[4]=(unsigned char)(value%10);
 		buffer[4]+=0x30;
    buffer[5]='m';
		buffer[6]='m';

	  USPrintf("sb sbsbsbsbsbsbsb");
    USPrintf((char *)buffer);
		delay_ms(1000);
		Sim800_Init();
		USPrintf("sim800c init ok ");
		USPrintf("\r\n");
		Sim_Rst();
		USPrintf("Sim_Rst ok \r\n");
		delay_ms(1000);
		t=Sim800_check();
		if (t == 1)
		{
			USPrintf("通讯模块回复信息，启动正常\r\n");
		}
		else
		{
			USPrintf("error \r\n");
		}
		NETmode();
	//	USPrintf("sim800c NETmode ok ");
	//	USPrintf("\r\n");
		NET1mode();
	//	USPrintf("sim800c NET1mode ok ");
		UDPconnect("ip","port");	
   // USPrintf("sim800c UDPconnect ok ");		
	//	MessageSend_Len((char *)buffer,7);
		USPrintf("hhhhhh");
//		USPrintf(buffer);
	
		//printf("%d ",value);
		//USART_SendData(USART1,value);
	}
	
		
//	TIM3_Int_Init(10000-1,8400-1);//10Khz
	//*****************************//
	
	//**************外设硬件初始化***************//
 
	LEDFUNC_Init(500);
	URM06_analog_Init();
 //	ADS1256_Init();
	delay_ms(5);
//	while(OV2640_Init())//初始化2640
//	{
//		LED3=1;
//	}
//	LED3=0;//硬件设备 初始化成功

	//***************硬件初始化**************//

	OSInit();  	 			//初始化UCOSII		 			  
 	OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );//创建起始任务
	OSStart();	
#endif
 #if 1
	URM06_analog_Init();
	uart_init(115200);	
	usart2_init(72,115200);
	
#endif
}
