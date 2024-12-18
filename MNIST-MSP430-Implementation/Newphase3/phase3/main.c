#include "msp430.h"
#include <stdint.h>
#include <math.h>
#include "DNN_Parameters.h"

#define IMAGE_SIZE 784
#define NUM_OUTPUTS 10

// Global variables
unsigned char image_data[IMAGE_SIZE];
unsigned int index = 0;
volatile unsigned char processing_complete = 0;

void init_clock(void) {
    CSCTL0_H = CSKEY >> 8;
    CSCTL1 = DCOFSEL_3 | DCORSEL;
    CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK;
    CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;
    CSCTL0_H = 0;
}

void init_ports(void) {
    // Configure GPIO pins
    P1DIR |= BIT0;              // LED1 output
    P1OUT &= ~BIT0;             // LED1 off
}

void init_uart(void) {
    // Configure UART pins
    P2SEL1 |= BIT0 | BIT1;
    P2SEL0 &= ~(BIT0 | BIT1);

    // Configure UART
    UCA0CTLW0 = UCSWRST;
    UCA0CTLW0 |= UCSSEL__SMCLK;
    UCA0BR0 = 52;
    UCA0BR1 = 0x00;
    UCA0MCTLW |= UCOS16 | UCBRF_1;
    UCA0CTLW0 &= ~UCSWRST;
    UCA0IE |= UCRXIE;
}

void transmit_byte(unsigned char byte) {
    while (!(UCA0IFG & UCTXIFG));  // Wait for the TX buffer
    UCA0TXBUF = byte;
}

void transmit_string(const char* str) {
    while (*str) {
        transmit_byte(*str++);
    }
}

float apply_sigmoid(float x) {
    if (x < -3.0f) return 0.0f;
    if (x > 3.0f) return 1.0f;
    return 1.0f / (1.0f + exp(-x));
}

int perform_inference(void) {
    float max_output = -1000.0f;
    int predicted_class = 0;
    unsigned int i, j;

    for (i = NUM_OUTPUTS; i > 0; i--) {
        unsigned int idx = i - 1;
        float sum = biases[idx];

        for (j = IMAGE_SIZE; j > 0; j--) {
            sum += weights[idx * IMAGE_SIZE + (j - 1)] * (image_data[j - 1] / 255.0f);
        }

        float output = apply_sigmoid(sum);
        if (output > max_output) {
            max_output = output;
            predicted_class = idx;
        }
    }

    return predicted_class;
}

void send_result(int digit) {
    transmit_string("Result: ");
    transmit_byte('0' + digit);  // Send result as a character
    transmit_string("\r\n");
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    init_clock();               // Initialize system clock
    init_ports();
    PM5CTL0 &= ~LOCKLPM5;
    init_uart();

    transmit_string("MNIST Classifier Ready\r\n");

    __bis_SR_register(GIE);     // Enable global interrupts

    while (1) {
        if (processing_complete) {
            P1OUT |= BIT0;       // LED on during processing

            int result = perform_inference();
            send_result(result);

            processing_complete = 0;
            index = 0;
            P1OUT &= ~BIT0;      // turn LED off after processing
        }
        __no_operation();
    }
}

#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void) {
    switch (__even_in_range(UCA0IV, USCI_UART_UCTXCPTIFG)) {
        case USCI_NONE: break;
        case USCI_UART_UCRXIFG:
            if (index < IMAGE_SIZE) {
                image_data[index++] = UCA0RXBUF;
                if (index == IMAGE_SIZE) {
                    processing_complete = 1;
                }
            }
            break;
        default: break;
    }
}
