#include "tim3.h"

void tim3_init(uint16_t time3)  
{  
    TIM_TimeBaseInitTypeDef timer_init_structure;  
    NVIC_InitTypeDef nvic_init_structure;  
  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);            //使能TIM3时钟
	
    nvic_init_structure.NVIC_IRQChannel = TIM3_IRQn;                //选择TIM3中断通道
    nvic_init_structure.NVIC_IRQChannelCmd = ENABLE;                //TIM3中断使能
    nvic_init_structure.NVIC_IRQChannelPriority = 1;                //优先级为1
    NVIC_Init(&nvic_init_structure);  
  
    TIM_DeInit(TIM3);                                               //复位TIM3
    TIM_TimeBaseStructInit(&timer_init_structure);                  //初始化TIMBASE结构体
    
		timer_init_structure.TIM_Prescaler = 80-1;                      
    timer_init_structure.TIM_CounterMode = TIM_CounterMode_Up;      //向上计数
	  timer_init_structure.TIM_Period = time3-1;                      //定时周期
		timer_init_structure.TIM_ClockDivision = TIM_CKD_DIV1;          //系统时钟，不分频
    timer_init_structure.TIM_RepetitionCounter = 0x00;              //发生0+1次Update
    TIM_TimeBaseInit(TIM3, &timer_init_structure);  
  
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);                      //使能TIM3中断 
    TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_Update);           //运行TIM3的update时间更新触发源
		
		TIM_Cmd(TIM3, ENABLE);                                          //使能TIM3
}  

/***************************   TIM3 ÖÐ¶Ï·þÎñ³ÌÐò   *************************/  
void TIM3_IRQHandler()  
{  
    if(TIM_GetITStatus(TIM3, TIM_IT_Update))            //判断发生update事件
    {
			timeok++;			
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update);     //清除update事件更新标志
		}  
}  
