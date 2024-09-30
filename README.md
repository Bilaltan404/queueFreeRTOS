# FreeRTOS Queue Example

This project demonstrates how to use two FreeRTOS queues (`queueText` and `queueInt`) to pass data between two tasks (`sendTask` and `receiveTask`). The tasks exchange both text and integer values through these queues and manage the flow of messages effectively.

## Description

In this example:
- `sendTask` sends both text messages and integer values to two separate queues (`queueText` for strings and `queueInt` for integers).
- `receiveTask` reads data from these queues and prints the received values.

The program also demonstrates how to:
- Send data to the front or back of the queue.
- Check how many messages are waiting in the queue and how many spaces are still available.

## How It Works

1. **Queue Creation:**
   - Two queues are created: one for text data (`queueText`) and one for integer data (`queueInt`).
   - `queueText` holds up to 5 text messages, and `queueInt` holds up to 5 integer values.

2. **sendTask Behavior:**
   - The `sendTask` sends a series of predefined messages and integers into the respective queues.
   - Text messages are inserted at either the front or the back of the queue depending on whether `xQueueSend` or `xQueueSendToFront` is used.
   - It then continuously increments the integer value and sends it to the `queueInt`, while also printing the status of both queues (how many messages are waiting and how many spaces are available).

3. **receiveTask Behavior:**
   - The `receiveTask` attempts to receive messages from both queues every second.
   - If data is received from the `queueText`, it prints the string. 
   - If data is received from `queueInt`, it prints the integer value.

## Code Breakdown

- **sendTask:** Sends data to both `queueText` and `queueInt` and prints the status of each queue (messages waiting and available spaces).
- **receiveTask:** Receives data from both queues and prints the received values.
- **app_main:** Initializes and starts the `sendTask` and `receiveTask`.

## Prerequisites

- ESP-IDF installed on your machine.
- A supported ESP32 board.

## How to Run

1. Clone this repository and navigate to the project folder.
2. Run the following commands to configure and flash the code to your ESP32:
   ```bash
   idf.py set-target esp32
   idf.py menuconfig
   idf.py flash monitor

## Expected Output

queueText : data waiting to be read : 3  available spaces: 2 
queueInt : data waiting to be read : 2  available spaces: 3 
got a data from queue!  ===  Test Message 2
current =  25
queueText : data waiting to be read : 2  available spaces: 3 
queueInt : data waiting to be read : 1  available spaces: 4

