#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

long int t = 0;

int main(void) 
{
    // Configuração de PB1 a PB5 como saída (LEDs), PB0 como entrada (botão)
    DDRB = 0b00111110;   // PB1 a PB5 saída, PB0 entrada
    PORTB = 0b00000001;  // Pull-up ativado no botão (PB0)

    while (1) 
    {
        _delay_ms(1); // Espera 1 segundo
        // Incrementa tempo e faz overflow a cada 60s
        t = ++t % 60000;

        // Leitura do botão (ativo em LOW)
        uint8_t botao = PINB & (1 << PB0);
		
		// Verifica se o botão foi pressionado E estamos no sinal verde do veículo
        if (!botao && t < 42000) 
		{
            if (t < 32000) 
			{
                t = 32000; // Antecipar mudança para amarelo
            }
            // Senão, faltam menos de 10s → não faz nada
        }
        // Controle dos LEDs do semáforo  
        if (t < 42000) 
        {
            PORTB |= (1 << 3); // Acende verde veículos (PB3)
            PORTB |= (1 << 5); // Acende vermelho pedestres (PB5)
            PORTB &= ~(1 << 4); // Apaga verde pedestres (PB4)
            PORTB &= ~(1 << 2); // Apaga amarelo veículos (PB2)
            PORTB &= ~(1 << 1); // Apaga vermelho veículos (PB1)
        }
        else if (t < 45000) 
        {
            PORTB |= (1 << 2); // Acende amarelo veículos (PB2)
            PORTB |= (1 << 5); // Acende vermelho pedestres (PB5)
            PORTB &= ~(1 << 3); // Apaga verde veículos (PB3)
            PORTB &= ~(1 << 4); // Apaga verde pedestres (PB4)
            PORTB &= ~(1 << 1); // Apaga vermelho veículos (PB1)
        }
        else if (t < 57000) 
        {
            PORTB |= (1 << 1); // Acende vermelho veículos (PB1)
            PORTB |= (1 << 4); // Acende verde pedestres (PB4)
            PORTB &= ~(1 << 3); // Apaga verde veículos (PB3)
            PORTB &= ~(1 << 2); // Apaga amarelo veículos (PB2)
            PORTB &= ~(1 << 5); // Apaga vermelho pedestres (PB5)
        }
            // Se estiver nos últimos 3 segundos, piscar o verde do pedestre
        else if (t <= 60000) 
        {
            PORTB |= (1 << 1); // Acende vermelho veículos (PB1)
            PORTB |= (1 << 5); // Acende vermelho pedestres (PB5)
            PORTB &= ~(1 << 4); // Apaga verde pedestres (PB4)
            PORTB &= ~(1 << 2); // Apaga amarelo veículos (PB2)
            PORTB &= ~(1 << 3); // Apaga verde veículos (PB3)
            _delay_ms(500);

            PORTB |= (1 << 1); // Acende vermelho veículos (PB1)
            PORTB &= ~(1 << 5); // Apaga vermelho pedestres (PB5)
            PORTB &= ~(1 << 4); // Apaga verde pedestres (PB4)
            PORTB &= ~(1 << 2); // Apaga amarelo veículos (PB2)
            PORTB &= ~(1 << 3); // Apaga verde veículos (PB3)
            _delay_ms(500);

            PORTB |= (1 << 1); // Acende vermelho veículos (PB1)
            PORTB |= (1 << 5); // Acende vermelho pedestres (PB5)
            PORTB &= ~(1 << 4); // Apaga verde pedestres (PB4)
            PORTB &= ~(1 << 2); // Apaga amarelo veículos (PB2)
            PORTB &= ~(1 << 3); // Apaga verde veículos (PB3)
            _delay_ms(500);

            PORTB |= (1 << 1); // Acende vermelho veículos (PB1)
            PORTB &= ~(1 << 5); // Apaga vermelho pedestres (PB5)
            PORTB &= ~(1 << 4); // Apaga verde pedestres (PB4)
            PORTB &= ~(1 << 2); // Apaga amarelo veículos (PB2)
            PORTB &= ~(1 << 3); // Apaga verde veículos (PB3)
            _delay_ms(500);

            PORTB |= (1 << 1); // Acende vermelho veículos (PB1)
            PORTB |= (1 << 5); // Acende vermelho pedestres (PB5)
            PORTB &= ~(1 << 4); // Apaga verde pedestres (PB4)
            PORTB &= ~(1 << 2); // Apaga amarelo veículos (PB2)
            PORTB &= ~(1 << 3); // Apaga verde veículos (PB3)
            _delay_ms(500);

            PORTB |= (1 << 1); // Acende vermelho veículos (PB1)
            PORTB &= ~(1 << 5); // Apaga vermelho pedestres (PB5)
            PORTB &= ~(1 << 4); // Apaga verde pedestres (PB4)
            PORTB &= ~(1 << 2); // Apaga amarelo veículos (PB2)
            PORTB &= ~(1 << 3); // Apaga verde veículos (PB3)
            _delay_ms(500);
        
            t = 0;
            continue; // volta ao início do while(1)
        }
    }
    
}
