/** -----------------------------------------------------------------------------
 * @file        app_config.h
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

#ifndef APP_CONFIGS_SIMPLE_INC_APP_CONFIG_H_
#define APP_CONFIGS_SIMPLE_INC_APP_CONFIG_H_

/** ============================================================================
 * ======================================= Includes ============================
 * ========================================================================== */
#include "return_status.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/** ============================================================================
 * ============================== Macro ========================================
 * ========================================================================== */
#define APP_CONFIG_SDA_PIN             21
#define APP_CONFIG_SCL_PIN             22
#define APP_CONFIG_I2C_CLOCK_HZ        100000
#define APP_CONFIG_LOOP_DELAY_MS       100
#define APP_CONFIG_I2C_ADDRESS         0x48 //Add pin to GND
#define APP_CONFIG_ADC_REFERENCE_VOLTAGE_MV    3300
#define APP_CONFIG_ADC_NATIVE_TYPE     IF_ANALOG_INPUT_TYPE_NATIVE
#define APP_CONFIG_ADC_NATIVE_MAX      3100
#define APP_CONFIG_ADC_NATIVE_CHANNEL  6
#define APP_CONFIG_ADC_NATIVE_PIN      34
#define APP_CONFIG_ADC_EXTERNAL_TYPE   IF_ANALOG_INPUT_TYPE_ADS1115
#define APP_CONFIG_ADC_EXTERNAL_MAX    16383
// #define APP_CONFIG_PWM_PIN             2
// #define APP_CONFIG_PWM_FREQUENCY_HZ    1000

/** ============================================================================
 * ============================== Constants ====================================
 * ========================================================================== */


/** ============================================================================
 * ================================ Data types ================================#
 * ========================================================================== */

typedef struct
{

}app_config_t;

/** ============================================================================
 * ============================= Public functions prototype ====================
 * ========================================================================== */

/** ----------------------------------------------------------------------------
 * @brief The module initialiser
 * @param t_p_handle The pointer to the configuration structure
 *
 * @return RETURN_CODE_OK on success
 -----------------------------------------------------------------------------*/
return_status_t app_config_init(app_config_t * const t_p_handle);

/** ----------------------------------------------------------------------------
 * @brief The module de-initialiser
 * @param t_p_handle The pointer to the configuration structure
 *
 * @return RETURN_CODE_OK on success
 -----------------------------------------------------------------------------*/
return_status_t app_config_deinit(app_config_t * const t_p_handle);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // APP_CONFIGS_SIMPLE_INC_APP_CONFIG_H_
// End of file
