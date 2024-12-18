# MNIST-MSP430-Implementation

This project implements a Deep Neural Network (DNN) on the MSP430 microcontroller to classify handwritten digits (0-9) from the MNIST dataset.  

## Overview  
1. **Train the DNN**: A Multi-Layer Perceptron (MLP) is trained on the MNIST dataset with at least 95% accuracy. The model's weights and biases are exported to a `.txt` file.  
2. **Port to MSP430**: The DNN forward pass logic is implemented in C/C++ for the MSP430, optimized for its 4 KB RAM.  
3. **UART Communication**: Image data is sent to the MSP430 via UART, and predictions are received in return.  

## Features  
- Efficient DNN inference on a microcontroller.  
- UART-based data transfer for input and output.  
- Optimized memory usage for embedded systems.  

## Requirements  
- **Hardware**: MSP430 microcontroller  
- **Software**: Code Composer Studio, a UART tool (e.g., Tera Term), MNIST dataset  

## Usage  
1. Train the DNN locally and export the weights.  
2. Flash the MSP430 with the provided code.  
3. Use UART to send MNIST images and receive predictions.  

## Acknowledgments  
Thanks to [AndrewCarterUK’s MNIST Neural Network in C](https://github.com/AndrewCarterUK/mnist-neural-network-plain-c) for inspiration and resources.  

