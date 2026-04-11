/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include "if_analog_input.h"
#include "hal_pwm.h"
#include "log.h"
#include "hal_os.h"
#include "hal_os_delay.h"

static const char * TAG = "example";

#define SDA_PIN             21
#define SCL_PIN             22
#define I2C_CLOCK_HZ        100000
#define LOOP_DELAY_MS       100
#define I2C_ADDRESS         0x48 //Add pin to GND
#define ADC_REFERENCE_VOLTAGE_MV    3300
#define ADC_NATIVE_TYPE     IF_ANALOG_INPUT_TYPE_NATIVE
#define ADC_NATIVE_MAX      3100
#define ADC_NATIVE_CHANNEL  6
#define ADC_NATIVE_PIN      34
#define ADC_EXTERNAL_TYPE   IF_ANALOG_INPUT_TYPE_ADS1115
#define ADC_EXTERNAL_MAX    16383
#define PWM_PIN             2
#define PWM_FREQUENCY_HZ    1000


void app_main(void)
{
    hal_os_t hal_os = {0};
    hal_os_delay_t hal_delay = {0};
    return_status_t rs = RETURN_STATUS_OK;
    hal_log_t hal_log = {0};
    if_analog_input_t analog_input = {0};
    int32_t voltage_mv = 0;
    hal_pwm_t led_pwm = {0};

    rs = log_init(&hal_log);
    rs = log_set_level(LOG_LEVEL_DEBUG);

    rs = hal_os_init(&hal_os);
    log_info(TAG, "Os init: %s", return_status_get_string(rs));
    rs = hal_os_delay_init(&hal_delay);
    log_info(TAG, "Delay init: %s", return_status_get_string(rs));

    // analog_input.native.adc_channel = ADC_NATIVE_CHANNEL;
    // analog_input.native.adc_number = 0;
    // analog_input.native.pin_number = ADC_NATIVE_PIN;
    // analog_input.max_adc_value = ADC_NATIVE_MAX;
    // analog_input.type = IF_ANALOG_INPUT_TYPE_NATIVE;

    analog_input.ads1115.b_scl_pullup_en = true;
    analog_input.ads1115.b_sda_pullup_en = true;
    analog_input.ads1115.clk_speed = I2C_CLOCK_HZ;
    analog_input.ads1115.i2c_number = 0;
    analog_input.ads1115.interrupt_level = 0;
    analog_input.ads1115.scl_pin_number = SCL_PIN;
    analog_input.ads1115.sda_pin_number = SDA_PIN;
    analog_input.ads1115.channel = 0;
    analog_input.ads1115.i2c_address = I2C_ADDRESS;
    analog_input.type = IF_ANALOG_INPUT_TYPE_ADS1115;
    analog_input.max_adc_value = ADC_EXTERNAL_MAX;

    analog_input.reference_voltage_mv = ADC_REFERENCE_VOLTAGE_MV;
    rs = if_analog_input_init(&analog_input);
    log_info(TAG, "Analog input init: %s", return_status_get_string(rs));

    led_pwm.channel_number = 0;
    led_pwm.frequency_hz = PWM_FREQUENCY_HZ;
    led_pwm.io_pin_number = PWM_PIN;
    led_pwm.max_pwm_value = 0x4000;
    rs = hal_pwm_init(&led_pwm);
    log_info(TAG, "LED PWM init: %s", return_status_get_string(rs));

    while (1)
    {
        rs = if_analog_input_get_voltage(&analog_input, &voltage_mv);
        log_info(
            TAG, 
            "Analog channel read: %s, Voltage: %d (mv)", 
            return_status_get_string(rs), 
            voltage_mv);
        
        rs = hal_pwm_set(&led_pwm, voltage_mv*5);
        log_info(TAG, "PWM set: %s", return_status_get_string(rs));

        hal_os_delay_ms(&hal_delay, LOOP_DELAY_MS, false);
    }

    rs = hal_os_deinit(&hal_os);
    rs = hal_os_delay_deinit(&hal_delay);
    rs = hal_pwm_deinit(&led_pwm);
    rs = if_analog_input_deinit(&analog_input);

}
