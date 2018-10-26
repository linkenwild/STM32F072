#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"
#include "tim13.h"
#include "tim14.h"
//ALIENTEK Ì½Ë÷ÕßSTM32F407¿ª·¢°å ÊµÑé8
//PWMÊä³öÊµÑé-¿âº¯Êý°æ±¾
int main(void)
{ 
	uint16_t led0pwmval = 0;
	uint16_t led1pwmval = 0;
	uint8_t dir0 = 1;
	uint8_t dir1 = 1;	
/*  TIM14±íÊ¾-Í¨¹ýLED0ÏÔÊ¾Ð§¹û
		TIM13±íÊ¾-Í¨¹ýLED1ÏÔÊ¾Ð§¹û£¨²éÑ¯Êý¾ÝÊÖ²áTIM13_CH1Í¨¹ýPA6Êä³ö£¬Í¨¹ý¶Å°îÏßÁ¬½ÓPF10,PF10ÊÇºÍLED1Á¬½ÓµÄ£©   */

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//ÉèÖÃÏµÍ³ÖÐ¶ÏÓÅÏÈ¼¶·Ö×é2
	delay_init(168);  //³õÊ¼»¯ÑÓÊ±º¯Êý
	uart_init(115200);
	//LED_Init();				//³õÊ¼»¯LED¶Ë¿Ú
	TIM14_Init(500-1,84-1);//ÖØÔØÖµ499£¬·ÖÆµÖµ83
	TIM13_Init(500-1,84-1);//ÖØÔØÖµ499£¬·ÖÆµÖµ83
	while(1)
	{
		delay_ms(10);//ÑÓÊ±200ms
		//TIM14µÄÔ¤ÖØÔØÖµ
		if(dir0 == 1)
		{
			led0pwmval++;		
		}
		else
		{
			led0pwmval--;		
		}
		if(led0pwmval > 300)
		{
			dir0 = 0;
		}			
		if (led0pwmval == 0)
		{
			dir0 = 1;
		}
		//TIM13µÄÔ¤ÖØÔØÖµ
		if(dir1 == 1)
		{
			led1pwmval++;			
		}
		else
		{
			led1pwmval--;			
		}

		if(led1pwmval > 100)
		{
			dir1 = 0;		
		}

		if(led1pwmval == 0)
		{
			dir1 = 1;		
		}
  		TIM_SetCompare1(TIM14, led0pwmval);//½«Ô¤ÖØÔØÖµled0pwmvalÐ´ÈëTIM14_CCR1¼Ä´æÆ÷
			TIM_SetCompare1(TIM13, led1pwmval);//½«Ô¤ÖØÔØÖµled1pwmvalÐ´ÈëTIM13_CCR1¼Ä´æÆ÷
	}
}
