/** -----------------------------------------------------------------------------
 * @file        initialise.c
 *
 * @brief       The module description
 *
 * @details
 *
 * @date        Created on: Jan 2026
 * @date        Modified on: 
 * @author      M.Saadat (m.saadat@mail.com)
 * @version     V1.0.0
 *
 * @copyright   Copyright (c) 2026 M.Saadat 
 * All rights reserved.
 * This source code is licensed under the Apache 2.0 license found in the
 * LICENSE file in the root directory of this source tree.
 -----------------------------------------------------------------------------*/

/** ============================================================================
 * ====================================== Includes =============================
 * ========================================================================== */
#include "../inc/initialise.h"
#include "return_status.h"
#include "log.h"
#include "hal_os.h"
#include "hal_os_delay.h"

#include "if_analog_input.h"
#include "if_analog_output.h"

#include "../../globals/inc/globals.h"
#include "../inc/app_config.h"

/** ============================================================================
 * ================================ Macro ======================================
 * ========================================================================== */

/** ============================================================================
 * =============================== Data types ==================================
 * ========================================================================== */

/** ============================================================================
 * ================================ Constants ==================================
 * ========================================================================== */
static const char * const DBG_ID = "initialise";

/** ============================================================================
 * ============================== Static private variables =====================
 * ========================================================================== */


/** ============================================================================
 * ========================= Private static function prototypes ================
 * ========================================================================== */


/** ============================================================================
 * =============================== Public functions body =======================
 * ========================================================================== */

/** ----------------------------------------------------------------------------
 * @fn return_status_t initialise_init(initialise_t * const)
 * @brief The module initialiser
 * @param t_p_handle The pointer to the configuration structure
 *
 * @return RETURN_STATUS_OK on success
 ---------------------------------------------------------------------------- */
return_status_t initialise_init(initialise_t * const t_p_handle)
{
    hal_os_t hal_os = {0};
    hal_os_delay_t hal_delay = {0};
    return_status_t rs = RETURN_STATUS_OK;
    hal_log_t hal_log = {0};

    rs = log_init(&hal_log);
    rs = log_set_level(LOG_LEVEL_DEBUG);

    rs = hal_os_init(&hal_os);
    log_info(DBG_ID, "Os init: %s", return_status_get_string(rs));
    rs = hal_os_delay_init(&hal_delay);
    log_info(DBG_ID, "Delay init: %s", return_status_get_string(rs));

    /* g_analog_input_potentiometer is initialised here (rather than a local
     * variable) because app_task() reads this same global handle for every
     * sample; the handle's _p_config must remain valid for the module's
     * lifetime, not just for the duration of this function. */
    g_analog_input_potentiometer.native.adc_channel = APP_CONFIG_ADC_NATIVE_CHANNEL;
    g_analog_input_potentiometer.native.adc_number = 0;
    g_analog_input_potentiometer.native.pin_number = APP_CONFIG_ADC_NATIVE_PIN;
    g_analog_input_potentiometer.max_adc_value = APP_CONFIG_ADC_NATIVE_MAX;
    g_analog_input_potentiometer.type = IF_ANALOG_INPUT_TYPE_NATIVE;

    // g_analog_input_potentiometer.ads1115.b_scl_pullup_en = true;
    // g_analog_input_potentiometer.ads1115.b_sda_pullup_en = true;
    // g_analog_input_potentiometer.ads1115.clk_speed = I2C_CLOCK_HZ;
    // g_analog_input_potentiometer.ads1115.i2c_number = 0;
    // g_analog_input_potentiometer.ads1115.interrupt_level = 0;
    // g_analog_input_potentiometer.ads1115.scl_pin_number = SCL_PIN;
    // g_analog_input_potentiometer.ads1115.sda_pin_number = SDA_PIN;
    // g_analog_input_potentiometer.ads1115.channel = 0;
    // g_analog_input_potentiometer.ads1115.i2c_address = I2C_ADDRESS;
    // g_analog_input_potentiometer.type = IF_ANALOG_INPUT_TYPE_ADS1115;
    // g_analog_input_potentiometer.max_adc_value = ADC_EXTERNAL_MAX;

    g_analog_input_potentiometer.reference_voltage_mv = APP_CONFIG_ADC_REFERENCE_VOLTAGE_MV;
    rs = if_analog_input_init(&g_analog_input_potentiometer);
    log_info(DBG_ID, "Analog input init: %s", return_status_get_string(rs));

    /* g_analog_output_led is initialised here (rather than a local variable)
     * because app_task() drives this same global handle on every loop
     * iteration; the handle's _p_config must remain valid for the module's
     * lifetime, not just for the duration of this function. */
    g_analog_output_led.type = IF_ANALOG_OUTPUT_TYPE_NATIVE_PWM;
    g_analog_output_led.max_pwm_value = APP_CONFIG_PWM_MAX_VALUE;
    g_analog_output_led.native_pwm.pwm_number = APP_CONFIG_PWM_NUMBER;
    g_analog_output_led.native_pwm.channel_number = APP_CONFIG_PWM_CHANNEL_NUMBER;
    g_analog_output_led.native_pwm.pin_number = APP_CONFIG_PWM_PIN;
    g_analog_output_led.native_pwm.port_number = APP_CONFIG_PWM_PORT_NUMBER;
    g_analog_output_led.native_pwm.frequency_hz = APP_CONFIG_PWM_FREQUENCY_HZ;
    g_analog_output_led.native_pwm.b_inverted = APP_CONFIG_PWM_INVERTED;

    rs = if_analog_output_init(&g_analog_output_led);
    log_info(DBG_ID, "Analog output init: %s", return_status_get_string(rs));

    return rs;
}

/** ----------------------------------------------------------------------------
 * @fn return_status_t initialise_deinit(initialise_t * const)
 * @brief The module de-initialiser
 * @param t_p_handle The pointer to the configuration structure
 *
 * @return RETURN_STATUS_OK on success
 ---------------------------------------------------------------------------- */
return_status_t initialise_deinit(initialise_t * const t_p_handle)
{
    return_status_t rc = RETURN_STATUS_OK;

    return rc;
}

/** ============================================================================
 * =============================== Private functions declaration ===============
 * ========================================================================== */

// End of file
