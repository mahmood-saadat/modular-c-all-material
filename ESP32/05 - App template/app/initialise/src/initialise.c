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

    if_analog_input_t analog_input = {0};

    rs = log_init(&hal_log);
    rs = log_set_level(LOG_LEVEL_DEBUG);

    rs = hal_os_init(&hal_os);
    log_info(DBG_ID, "Os init: %s", return_status_get_string(rs));
    rs = hal_os_delay_init(&hal_delay);
    log_info(DBG_ID, "Delay init: %s", return_status_get_string(rs));

    analog_input.native.adc_channel = APP_CONFIG_ADC_NATIVE_CHANNEL;
    analog_input.native.adc_number = 0;
    analog_input.native.pin_number = APP_CONFIG_ADC_NATIVE_PIN;
    analog_input.max_adc_value = APP_CONFIG_ADC_NATIVE_MAX;
    analog_input.type = IF_ANALOG_INPUT_TYPE_NATIVE;

    // analog_input.ads1115.b_scl_pullup_en = true;
    // analog_input.ads1115.b_sda_pullup_en = true;
    // analog_input.ads1115.clk_speed = I2C_CLOCK_HZ;
    // analog_input.ads1115.i2c_number = 0;
    // analog_input.ads1115.interrupt_level = 0;
    // analog_input.ads1115.scl_pin_number = SCL_PIN;
    // analog_input.ads1115.sda_pin_number = SDA_PIN;
    // analog_input.ads1115.channel = 0;
    // analog_input.ads1115.i2c_address = I2C_ADDRESS;
    // analog_input.type = IF_ANALOG_INPUT_TYPE_ADS1115;
    // analog_input.max_adc_value = ADC_EXTERNAL_MAX;

    analog_input.reference_voltage_mv = APP_CONFIG_ADC_REFERENCE_VOLTAGE_MV;
    rs = if_analog_input_init(&analog_input);
    log_info(DBG_ID, "Analog input init: %s", return_status_get_string(rs));

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
