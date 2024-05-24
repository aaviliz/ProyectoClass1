//librerias
#include <stdio.h>


#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


//declarición de constantes
#define ledRojo 25
#define ledAmarillo 33
#define ledVerde 32


#define baseRetraso 100


//declaración de variables
struct leds
{
    int pinLed;
    int valorLed;
};


struct pulsadores
{
    int pinPulsador;
    int valorPulsador;
};




//declaración de funciones
esp_err_t initLed(struct leds *);
esp_err_t ledAUno(struct leds *);
esp_err_t ledACero(struct leds *);
esp_err_t initPulsador(struct pulsadores *);
esp_err_t retrasoSincrono(int);
esp_err_t parpadeo(struct leds *, int);
int estadoPulsador(struct pulsadores *);
int flancoSubida(struct pulsadores *);
esp_err_t cambiarEstadoLed(struct leds *);


void app_main(void)
{
    //inicialización de variables
    struct leds led1 = {ledRojo,0};
    struct pulsadores pul1 = {18,0};
    //int multiplo = 1;
    initLed(&led1);
    initPulsador(&pul1);


    while(true)
    {
        if (flancoSubida(&pul1))
        {
            printf("flanco subida\n");
            cambiarEstadoLed(&led1);
        }
    }
}


//definición de la función
esp_err_t initLed(struct leds * led)
{
    gpio_set_direction(led->pinLed, GPIO_MODE_OUTPUT);
    return ESP_OK;
}
esp_err_t ledAUno(struct leds * led)
{
    led->valorLed = 1;
    gpio_set_level(led->pinLed, led->valorLed);
    return ESP_OK;
}
esp_err_t ledACero(struct leds * led)
{
    led->valorLed = 0;
    gpio_set_level(led->pinLed, led->valorLed);
    return ESP_OK;
}
esp_err_t initPulsador(struct pulsadores * pulsador)
{
    gpio_set_direction(pulsador->pinPulsador, GPIO_MODE_INPUT);
    gpio_set_pull_mode(pulsador->pinPulsador, GPIO_PULLUP_ONLY);
    return ESP_OK;
}
esp_err_t retrasoSincrono(int multiplo)
{
    vTaskDelay(pdMS_TO_TICKS(baseRetraso*multiplo));
    return ESP_OK;
}
esp_err_t parpadeo(struct leds * led, int multiplo)
{
    ledAUno(led);
    printf("valor led %d\n",led->valorLed);
    retrasoSincrono(multiplo);
    ledACero(led);
    printf("valor led %d\n",led->valorLed);
    retrasoSincrono(multiplo);
    return ESP_OK;
}
int estadoPulsador(struct pulsadores *pul)
{
    pul->valorPulsador = gpio_get_level(pul->pinPulsador);
    return pul->valorPulsador;
}
int flancoSubida(struct pulsadores *pul)
{
    int estado = 0;
    if (estadoPulsador(pul))
    {
        retrasoSincrono(1);
        if (!estadoPulsador(pul))
            estado = 1;
    }
    return estado;


}
esp_err_t cambiarEstadoLed(struct leds *led)
{
    if (led->valorLed)
        ledACero(led);
    else
        ledAUno(led);
    return ESP_OK;
}
