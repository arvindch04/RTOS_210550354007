
//2. Create 3 realtime tasks each with the periodcity T1=1000ms, T2=2000ms, T3=5000ms. Also create use oneshot software timer to trigger a callback function from T3 after 10000ms.
//AUTHOR:CHINTALA ARAVIND KUMAR : 210550354007

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

//HANDLERS
TaskHandle_t T3_handle;
TimerHandle_t t_handle;
void *const pt_timerid; 

//TIMER CALL BACK FUNCTION
void pt_timer_handler(TimerHandle_t xTimer)
{
    printf("\nTimer fired\n");
}

//tasks with the periodcity T1=1000ms
void task_T1(void *data)
{
            while(1)
           {
               printf("\ntask_T1 with the periodcity T1=1000ms implemented\n");
               
               vTaskDelay(1000 / portTICK_PERIOD_MS);
           }
}

//tasks with the periodcity T2=2000ms
void task_T2(void *data)
{
            while(1)
           {
               printf("\ntask_T2 with the periodcity T2=2000ms implemented\n");
               
               vTaskDelay(2000 / portTICK_PERIOD_MS);
           }
}





//tasks with the periodcity T3=5000ms
void task_T3(void *data)
{
  
//oneshot software timer to trigger a callback function from T3 after 10000ms

   t_handle = xTimerCreate( "pt_timer", pdMS_TO_TICKS(10000) ,pdFALSE, pt_timerid,pt_timer_handler);
//If we use pdFALSE in the above api it means it will run only once
 
    xTimerStart(t_handle,0);
    while(1)
           {
               printf("\ntask_T3 with the periodcity T3=5000ms implemented\n");
               

               
               vTaskDelay(5000 / portTICK_PERIOD_MS);
           }
}

void app_main(void)
{
    
    xTaskCreate(task_T1, "task_T1", 2048, NULL, 3, NULL); //APIs for task creation
    xTaskCreate(task_T2, "task_T2", 2048, NULL, 2, NULL);
    xTaskCreate(task_T3, "task_T3", 2048, NULL, 5, &T3_handle);

  
}
