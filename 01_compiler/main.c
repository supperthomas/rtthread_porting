#include "rtthread.h"
#include "rthw.h"

#define GPIO_LED  

void main_thread_entry(void *parameter)
{

	//GPIO_INIT
	while(1)
	{
		//GPIO_ON
		rt_thread_mdelay(1000);
		//GPIO_OFF
		rt_thread_mdelay(1000);
	}
}

void rt_application_init(void)
{
    rt_thread_t tid;
	
#ifndef RT_MAIN_THREAD_STACK_SIZE
#define RT_MAIN_THREAD_STACK_SIZE     2048
#endif
#ifndef RT_MAIN_THREAD_PRIORITY
#define RT_MAIN_THREAD_PRIORITY       (RT_THREAD_PRIORITY_MAX / 3)
#endif
	
    tid = rt_thread_create("main", main_thread_entry, RT_NULL,
                           RT_MAIN_THREAD_STACK_SIZE, RT_MAIN_THREAD_PRIORITY, 20);
    RT_ASSERT(tid != RT_NULL);

    rt_thread_startup(tid);
}
uint8_t heap_size[10240*5];

void rt_hw_board_init(void)
{
#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)&heap_size[0], (void *)&heap_size[10240*5-1]);
#endif
	
}

void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    rt_tick_increase();
    /* leave interrupt */
    rt_interrupt_leave();
}

int rtthread_startup(void)
{
    rt_hw_interrupt_disable();
	
    /* board level initalization
     * NOTE: please initialize heap inside board initialization.
     */
    rt_hw_board_init();

    /* show RT-Thread version */
    rt_show_version();

    /* timer system initialization */
    rt_system_timer_init();

    /* scheduler system initialization */
    rt_system_scheduler_init();
	
    /* create init_thread */
    rt_application_init();

    /* timer thread initialization */
    rt_system_timer_thread_init();

    /* idle thread initialization */
    rt_thread_idle_init();

    /* start scheduler */
    rt_system_scheduler_start();

    /* never reach here */
    return 0;
}
int main ( void )
{
	//gpio clock init
	rtthread_startup();

	while(1)
	{
		
		if(i<10000000)
		{
			i++;
			continue;
		}
		else
		{
			if(flag == 0)
			{
			    //GPIO_ON
				flag = 1;
			}
			else
			{
				//GPIO_OFF
				flag = 0;
			}
			i = 0;
		}
	}
}
