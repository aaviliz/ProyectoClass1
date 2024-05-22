#include <stdio.h>
#include "driver/gpio.h"

//Declaracion Variables
struct leds
{
    int pinLed;
    int valorLed;
};
struct puls
{
    int pinPuls;
    int valorPuls;
};

//Declaracion funciones
esp_err_t initLed(struct leds *);
esp_err_t ledAUno(struct leds *);
esp_err_t initPuls(struct puls *);

void app_main(void)
{
    //inicializacion variables
  struct leds led1 = {2,0};
  struct puls pul1 = {18,0};

  initLed(&led1);
  initPuls(&pul1);

  while (true)
  {
    ledAUno(&led1);
  }
}

//Definicion funcion
esp_err_t initLed(struct leds * led)
{
    gpio_set_direction(led->pinLed, GPIO_MODE_OUTPUT);
    return ESP_OK;
}
esp_err_t ledAUno(struct leds * led)
{
    gpio_set_level(led->pinLed, 1);
    return ESP_OK;
}
esp_err_t initPuls(struct puls * pulsador)
{
    gpio_set_direction(pulsador->pinPuls, GPIO_MODE_INPUT);
    gpio_set_pull_mode(pulsador->valorPuls, GPIO_PULLUP_ONLY);
    return ESP_OK;
}