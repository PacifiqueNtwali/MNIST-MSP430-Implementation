# MNIST-MSP430-Implementation

This project is all about running a deep neural network (DNN) on the MSP430 microcontroller to recognize handwritten digits (0-9) from the MNIST dataset. It’s a fun mix of machine learning and embedded systems, where we take a trained DNN model and make it work on a resource-constrained microcontroller like the MSP430.

What’s in This Project?
The project has three main parts:

Training the DNN model: We train a neural network on the MNIST dataset and export the weights and biases.
Porting it to the MSP430: The trained model’s logic is implemented in C/C++ to run directly on the microcontroller.
Setting up UART communication: We use UART to send image data to the MSP430 and get the prediction results back.
How It Works
1. Training the DNN
We start by training a simple neural network (an MLP) to classify MNIST digits. Instead of building everything from scratch, we use an existing implementation (like this one). The model is trained locally on a computer using a tool like Visual Studio Code, and we ensure it gets at least 95% accuracy.

Once the training is done, the weights and biases are exported to a .txt file. This file will be used by the MSP430 to perform the predictions.

2. Running the DNN on the MSP430
The MSP430 microcontroller has limited resources, so we carefully implement the forward pass logic of the trained model in C/C++.

Input data: Sample MNIST images are prepared and sent to the MSP430.
Memory management: Since the MSP430 has only 4 KB of RAM, we optimize memory usage to handle the image and calculations.
3. UART Communication
UART (Universal Asynchronous Receiver-Transmitter) is used to communicate with the MSP430. Here’s what happens:

The computer sends an image (as pixel data) to the MSP430 over UART.
The MSP430 processes the image using the DNN logic and predicts the digit.
The predicted digit is sent back to the computer via UART.
We test the setup with at least 10 images to make sure it works reliably.

What You’ll Get
By the end of this project, you’ll have:

A trained DNN model with its weights and biases exported to a .txt file.
C/C++ code for the MSP430 that includes:
DNN forward pass logic
UART communication for sending and receiving data
A working demo where the MSP430 predicts digits from the MNIST dataset.
How to Use This
Clone this repository.
Train the DNN model on your computer using the included code or your own implementation. Export the weights and biases to a .txt file.
Flash the MSP430 with the provided code.
Use a UART tool (like Tera Term or PuTTY) to send an MNIST image to the MSP430 and receive the prediction.
Tools and Requirements
Hardware: MSP430 microcontroller
Software:
Google Colab (or equivalent) for training the DNN
Code Composer Studio for MSP430 development
A UART communication tool (e.g., Tera Term, PuTTY)
Dataset: MNIST (handwritten digit dataset)
Acknowledgments
Big thanks to the open-source community for tools and code, especially AndrewCarterUK’s MNIST Neural Network in C. This project wouldn’t be possible without their work.
