/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include "hal_gpio.h"
#include "log.h"
#include "hal_os.h"
#include "hal_os_delay.h"

static const char *TAG = "example";

/* Use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
#define BLINK_GPIO 2
#define BLINK_PERIOD_MS 500

static uint8_t g_led_state = 0;
static hal_gpio_t g_led_hal_gpio = {0};

static void blink_led(void)
{
    return_status_t rs = RETURN_STATUS_OK;
    /* Set the GPIO level according to the state (LOW or HIGH)*/
    rs = hal_gpio_set_pin(&g_led_hal_gpio, g_led_state);
    log_info(TAG, "Set pin: %s", return_status_get_string(rs));
}

static void configure_led(void)
{
    return_status_t rs = RETURN_STATUS_OK;

    g_led_hal_gpio.interrupt.b_enable = false;
    g_led_hal_gpio.pin_number = BLINK_GPIO;
    g_led_hal_gpio.port_number = -1;
    g_led_hal_gpio.pin.direction_mode = HAL_GPIO_DIRECTION_MODE_OUTPUT;
    g_led_hal_gpio.pin.output_mode = HAL_GPIO_MODE_OUTPUT_PUSH_PULL;
    
    rs = hal_gpio_init(&g_led_hal_gpio);

    log_info(TAG, "Example configured to blink GPIO LED: %s", return_status_get_string(rs));
}

void app_main(void)
{
    hal_os_t hal_os = {0};
    hal_os_delay_t hal_delay = {0};
    return_status_t rs = RETURN_STATUS_OK;
    hal_log_t hal_log = {0};

    rs = log_init(&hal_log);
    rs = log_set_level(LOG_LEVEL_DEBUG);

    rs = hal_os_init(&hal_os);
    log_info(TAG, "Os init: %s", return_status_get_string(rs));
    rs = hal_os_delay_init(&hal_delay);
    log_info(TAG, "Delay init: %s", return_status_get_string(rs));

    configure_led();

    while (1)
    {
        log_info(TAG, "Turning the LED %s!", g_led_state == true ? "ON" : "OFF");
        blink_led();
        /* Toggle the LED state */
        g_led_state = !g_led_state;

        hal_os_delay_ms(&hal_delay, BLINK_PERIOD_MS, false);
    }

    rs = hal_os_deinit(&hal_os);
    rs = hal_os_delay_deinit(&hal_delay);

}
