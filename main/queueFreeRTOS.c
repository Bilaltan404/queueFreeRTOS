
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

TaskHandle_t sendTaskHandle = NULL;
TaskHandle_t receiveTaskHandle = NULL;

QueueHandle_t queueText;
QueueHandle_t queueInt;

void sendTask(void *arg)
{

    char txbuff[100];
    int value = 0;
    queueText = xQueueCreate(5, sizeof(txbuff));
    queueInt = xQueueCreate(5, sizeof(value));

    if (queueText == 0)
    {
        printf("failed to create queue1= %p \n", queueText); // Failed to create the queue.
    }

    if (queueInt == 0)
    {
        printf("failed to create queueInt= %p \n", queueInt); // Failed to create the queue.
    }

    value = 15;
    xQueueSend(queueInt, &value, (TickType_t)0);

    value += 10;
    xQueueSend(queueInt, &value, (TickType_t)0);

    value = 0;
    xQueueSend(queueInt, &value, (TickType_t)0);

    sprintf(txbuff, "Test Message 1");
    xQueueSend(queueText, (void *)txbuff, (TickType_t)0);

    sprintf(txbuff, "Test Message 2");
    xQueueSendToFront(queueText, (void *)txbuff, (TickType_t)0);

    sprintf(txbuff, "Test Message 3");
    xQueueSend(queueText, (void *)txbuff, (TickType_t)0);

    sprintf(txbuff, "Test Message 4");
    xQueueSend(queueText, (void *)txbuff, (TickType_t)0);

    while (1)
    {
        value++;
        xQueueSend(queueInt, &value, (TickType_t)0);

        printf("queueText : data waiting to be read : %d  available spaces: %d \n", uxQueueMessagesWaiting(queueText), uxQueueSpacesAvailable(queueText));
        printf("queueInt :data waiting to be read : %d  available spaces: %d \n", uxQueueMessagesWaiting(queueInt), uxQueueSpacesAvailable(queueInt));
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void receiveTask(void *arg)
{
    char rxbuff[100];
    while (1)

    {
       
        if (xQueueReceive(queueText, &(rxbuff), (TickType_t)5)) // see the data and remove it from the queue. If want to see the data but keep it in the queue.
        {                                                       // you can use  if(xQueuePeek(queue1, &(rxbuff) , (TickType_t)5 ))   
            printf("got a data from queue!  ===  %s \n", rxbuff);
        }

        if (xQueueReceive(queueInt, &(rxbuff), (TickType_t)5))
        {
            printf("current =  %d \n", *rxbuff);
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main()
{

    xTaskCreate(sendTask, "sendTask", 4096, NULL, 2, &sendTaskHandle);
    xTaskCreate(receiveTask, "receiveTask", 4096, NULL, 3, &receiveTaskHandle);
}