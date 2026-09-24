/** -----------------------------------------------------------------------------
 * @file        app.c
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

/**  ===========================================================================
 * ====================================== Includes =============================
 * ========================================================================== */
#include "../inc/app.h"
#include "return_status.h"
#include "log.h"

#include "../../initialise/inc/initialise.h"

#include "hal_os_task.h"
#include "hal_os_delay.h"

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

/**  ===========================================================================
 * ================================== Macro ====================================
 * ========================================================================== */
#define APP_TASK_STACK_SIZE                4*1024
#define APP_TASK_PRIORITY                  5
#define APP_TASK_NAME                      "App"
#define APP_TASK_IS_IN_INTERNAL_RAM        true
#define APP_TASK_LOOP_DELAY_MS             100
#define APP_TASK_ANALOG_OUTPUT_MULTIPLIER  5U

/**  ===========================================================================
 * ================================= Data types ================================
 * ========================================================================== */


/**  ===========================================================================
 * ================================ Constants ==================================
 * ========================================================================== */
static const char * const DBG_ID = "app";

/**  ===========================================================================
 * ============================== Static private variables ====================#
 * ========================================================================== */
static volatile bool        g_b_is_running      = false;
static hal_os_task_handle_t g_os_task_handle    = {0};

/**  ===========================================================================
 * ========================= Private static function prototypes ================
 * ========================================================================== */
static void app_task(void * t_p_arg);

/**  ===========================================================================
 * =============================== Public functions body ======================#
 * ========================================================================== */
return_status_t app_start(app_t * t_p_handle)
{
    return_status_t rc = RETURN_STATUS_OK;

    initialise_init(NULL);

    rc = hal_os_task_create(
        &g_os_task_handle,
        app_task,
        APP_TASK_NAME,
        APP_TASK_STACK_SIZE,
        (void*)t_p_handle,
        APP_TASK_PRIORITY,
        APP_TASK_IS_IN_INTERNAL_RAM);

   return rc;
}

return_status_t app_stop(app_t * t_p_handle)
{
    return_status_t rc = RETURN_STATUS_OK;

    return rc;
}

/**  ===========================================================================
 * =============================== Private functions body ======================
 * ========================================================================== */

static void app_task(void * t_p_arg)
{
    hal_os_delay_t os_delay = {0};
    return_status_t rc = RETURN_STATUS_OK;
    // app_t * const p_handle = (app_t*)t_p_arg;
    int32_t voltage_mv = 0;
    uint32_t scaled_output_value = 0;
    uint16_t pwm_output_value = 0;
    return_status_t rs = RETURN_STATUS_OK;
    return_status_t rs_output = RETURN_STATUS_OK;

    log_info(DBG_ID, "app_task started");

    g_b_is_running = true;
    rc = hal_os_delay_init(&os_delay);
    if(RETURN_STATUS_OK != rc)
    {
        g_b_is_running = false;
        log_err(
            DBG_ID,
            "Error on initialising the delay function: %s",
            return_status_get_string(rc));
    }

    for(;;)
    {
        if(!g_b_is_running)
        {
            break;
        }
        //App logic here
        rs = if_analog_input_get_voltage(&g_analog_input_potentiometer, &voltage_mv);
        log_info(
            DBG_ID, 
            "Analog channel read: %s, Voltage: %d (mv)", 
            return_status_get_string(rs), 
            voltage_mv);

        if ((RETURN_STATUS_OK == rs) && (0 <= voltage_mv))
        {
            /* Scale the input reading up for the PWM output, capping it to
             * the output's max_pwm_value so it never overflows the duty
             * cycle range accepted by if_analog_output_set_pwm_value(). */
            scaled_output_value = (uint32_t)voltage_mv * APP_TASK_ANALOG_OUTPUT_MULTIPLIER;
            if (scaled_output_value > g_analog_output_led.max_pwm_value)
            {
                scaled_output_value = g_analog_output_led.max_pwm_value;
            }
            pwm_output_value = (uint16_t)scaled_output_value;

            rs_output = if_analog_output_set_pwm_value(&g_analog_output_led, pwm_output_value);
            log_info(
                DBG_ID,
                "Analog output set: %s, PWM value: %u",
                return_status_get_string(rs_output),
                pwm_output_value);
        }

        hal_os_delay_ms(&os_delay, APP_TASK_LOOP_DELAY_MS, false);
    }

    rc = hal_os_task_delete(&g_os_task_handle);
}

// End of file
