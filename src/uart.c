#include "uart.h"


#define UART_BUF_SIZE 64
volatile char uart_received_buffer[UART_BUF_SIZE];
volatile uint8_t uart_msg_ready = 0;
volatile uint8_t msg_index = 0;

void uart_enable_rx_interrupt() {
    UCSR0B |= (1 << RXCIE0);
    sei();
}

void uart_init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0A = 0;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    uart_enable_rx_interrupt();
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}


// handler de commande, appelé dans l'interruption à chaque fois que la commande est complête. 
void handle_message(char *uart_received_buffer){
    // on renvoie le message pour vérifier que ca fonctionne bien (à commenter plus tard)
    uart_putstring("Message recu : ");
    uart_putstring((char*)uart_received_buffer);
   
    switch (uart_received_buffer[0])
    {
        //si la commande commence par h, alors c'est celle pour règler l'heure et on la règle en fonction
        case 'h':
        {
            int hour = 0, minute = 0;
            // Format attendu : hHH:MM
            if (sscanf(uart_received_buffer + 1, "%2d:%2d", &hour, &minute) == 2) {
                set_clock_time(hour, minute);
                uart_putstring("Heure reglee\n");
            } else {
                uart_putstring("Format invalide\n");
            }
            break;
        }

        case 'a':
        {
            current_clock_style = ANALOG; 
            uart_putstring("Affichage de l'horloge ANALOG\n"); 
            break; 
        }
        
        case 'r':
        {
            current_clock_style = ROUNDED_D; 
            uart_putstring("Affichage de l'horloge ROUNDED_DIGITAL"); 
            break; 
        }

        default:
            // si aucune commande n'est reconnue on affiche l'usage
            uart_putstring("Commande non recconue, usage : \n- Pour regler l'h : hHH:MM\n- Pour changer de cadran a (analog), r (rounded-digital), d (digital)\n");
            break;
    }
}

/// Interruption liée au chgt du registre RX de l'uart
ISR(USART_RX_vect) {
    // recup le msg recu caractère par caractère
    char c = UDR0;
    if (c == '\n' || msg_index >= UART_BUF_SIZE - 1) {
        uart_received_buffer[msg_index] = '\0';
        // si on arrive à a fin de la string, on met le flag msg ready à 1
        uart_msg_ready = 1;
        msg_index = 0;
        handle_message((char *)uart_received_buffer); 
    } else {
        // sinon on met le char recu 
        uart_received_buffer[msg_index++] = c;
    }
}


// fonctions de bouchra mais on se sert pkus de uart_receive
void uart_transmit(char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void uart_putstring(char *str) {
    while (*str) {
        uart_transmit(*str++);
    }
}

char uart_receive() {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}
