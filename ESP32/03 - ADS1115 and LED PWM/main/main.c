/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include "hal_i2c.h"
#include "ads1115.h"
#include "hal_pwm.h"
#include "log.h"
#include "hal_os.h"
#include "hal_os_delay.h"

static const char * TAG = "example";

#define SDA_PIN             21
#define SCL_PIN             22
#define I2C_CLOCK_HZ        100000
#define LOOP_DELAY_MS       100
#define ADS1115_I2C_ADDRESS 0x48 //Add pin to GND
#define PWM_PIN             2
#define PWM_FREQUENCY_HZ    1000


void app_main(void)
{
    hal_os_t hal_os = {0};
    hal_os_delay_t hal_delay = {0};
    return_status_t rs = RETURN_STATUS_OK;
    hal_log_t hal_log = {0};
    hal_i2c_t hal_i2c = {0};
    ads1115_t potentiometer = {0};
    uint16_t adc_value = 0;
    hal_pwm_t led_pwm = {0};

    rs = log_init(&hal_log);
    rs = log_set_level(LOG_LEVEL_DEBUG);

    rs = hal_os_init(&hal_os);
    log_info(TAG, "Os init: %s", return_status_get_string(rs));
    rs = hal_os_delay_init(&hal_delay);
    log_info(TAG, "Delay init: %s", return_status_get_string(rs));

    hal_i2c.b_scl_pullup_en = true;
    hal_i2c.b_sda_pullup_en = true;
    hal_i2c.clk_speed = I2C_CLOCK_HZ;
    hal_i2c.i2c_number = 0;
    hal_i2c.interrupt_level = 0;
    hal_i2c.scl_pin_number = SCL_PIN;
    hal_i2c.sda_pin_number = SDA_PIN;
    rs = hal_i2c_init(&hal_i2c);
    log_info(TAG, "I2C init: %s", return_status_get_string(rs));

    potentiometer.p_hal_i2c = &hal_i2c;
    potentiometer.channel = 0;
    potentiometer.i2c_address = ADS1115_I2C_ADDRESS;
    rs = ads1115_init(&potentiometer);
    log_info(TAG, "ADS1115 init: %s", return_status_get_string(rs));

    led_pwm.channel_number = 0;
    led_pwm.frequency_hz = PWM_FREQUENCY_HZ;
    led_pwm.io_pin_number = PWM_PIN;
    led_pwm.max_pwm_value = 0x4000;
    rs = hal_pwm_init(&led_pwm);
    log_info(TAG, "LED PWM init: %s", return_status_get_string(rs));

    while (1)
    {
        rs = ads1115_read(&potentiometer, &adc_value);
        log_info(
            TAG, 
            "ADC channel read: %s, ADC value: %d", 
            return_status_get_string(rs), 
            adc_value);
        
        rs = hal_pwm_set(&led_pwm, adc_value);
        log_info(TAG, "PWM set: %s", return_status_get_string(rs));

        hal_os_delay_ms(&hal_delay, LOOP_DELAY_MS, false);
    }

    rs = hal_os_deinit(&hal_os);
    rs = hal_os_delay_deinit(&hal_delay);
    rs = hal_pwm_deinit(&led_pwm);
    rs = ads1115_deinit(&potentiometer);
    rs = hal_i2c_deinit(&hal_i2c);

}
