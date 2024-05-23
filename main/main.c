#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//Declaracion constantes
#define ledRojo 25
#define ledVerde 32
#define ledAmarillo 33

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
esp_err_t ledAZero(struct leds *);
esp_err_t initPuls(struct puls *);
esp_err_t retrasoSincrono(int);
esp_err_t parpadeo(struct leds *, int);

void app_main(void)
{
    //inicializacion variables
  struct leds led1 = {ledRojo,0};
  struct puls pul1 = {18,0};
  int multiplo = 1;
  initLed(&led1);
  initPuls(&pul1);

  while (true)
  {
    parpadeo(&led1, multiplo);
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
    led->valorLed=1;
    gpio_set_level(led->pinLed, led->valorLed);
    return ESP_OK;
}
esp_err_t ledAZero(struct leds *led)
{
     led->valorLed=0;
    gpio_set_level(led->pinLed,  led->valorLed);
    return ESP_OK;
}
esp_err_t initPuls(struct puls * pulsador)
{
    gpio_set_direction(pulsador->pinPuls, GPIO_MODE_INPUT);
    gpio_set_pull_mode(pulsador->valorPuls, GPIO_PULLUP_ONLY);
    return ESP_OK;
}
esp_err_t retrasoSincrono(int multiplo)
{
    vTaskDelay(multiplo*1000/portTICK_PERIOD_MS);
    return ESP_OK;
}
esp_err_t parpadeo(struct leds * led, int multiplo)
{
    ledAUno(led);
    printf("valor Led %d\n",led->valorLed);
    retrasoSincrono(multiplo);
    ledAZero(led);
    printf("valor Led %d\n", led->valorLed);
    retrasoSincrono(multiplo);
    return ESP_OK;
}
