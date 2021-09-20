//QUESTION1:1. 1. Create 3 realtime tasks each with the periodcity T1=1000ms, T2=2000ms, T3=5000ms. Also create two additional task T4 and T5 where T4 sends integer data to T5 using Messsage Queues.
//AUTHOR:CHINTALA ARAVIND KUMAR : 210550354007
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"  



//HANDLERS
TaskHandle_t T4_handle;
TaskHandle_t T5_handle;
QueueHandle_t locmq;

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
            while(1)
           {
               printf("\ntask_T3 with the periodcity T3=5000ms implemented\n");
              
               vTaskDelay(5000 / portTICK_PERIOD_MS);
           }
}

void task_T4(void *data)
{
    int DATA = 0;
    while(1)
           {
              printf("\ntask_T4  started:sending data\n");

               DATA++; 
               
               xQueueSend(locmq,&DATA, 0);
              
               vTaskDelay(1000 / portTICK_PERIOD_MS);
           }
}


void task_T5(void *data)
{
    int buff;
    while(1)
           {
            printf("\ntask_T5  started:recieving data\n");
               
            xQueueReceive(locmq, &buff, 0);

            printf("\nBuff(data) sent from task_T4 to task_T5: %d\n", buff);
               
            vTaskDelay(1000 / portTICK_PERIOD_MS);
           }
}


void app_main(void)
{
   


    locmq =  xQueueCreate(5, sizeof(int)); //API for queue creation

    xTaskCreate(task_T1, "task_T1", 2048, NULL, 3, NULL); //APIs for task creation
    xTaskCreate(task_T2, "task_T2", 2048, NULL, 2, NULL);
    xTaskCreate(task_T3, "task_T3", 2048, NULL, 1, NULL);

    xTaskCreate(task_T4, "task_T4", 2048, NULL, 5, &T4_handle);
    xTaskCreate(task_T5, "task_T5", 2048, NULL, 7, &T5_handle);

}
