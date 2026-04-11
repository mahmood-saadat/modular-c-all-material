/** -----------------------------------------------------------------------------
 * @file        template.c
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
#include "../inc/template.h"
#include "return_status.h"
#include "log.h"

#include "hal_os_task.h"
#include "hal_os_delay.h"

#include <stdbool.h>

/**  ===========================================================================
 * ================================== Macro ====================================
 * ========================================================================== */
#define TEMPLATE_TASK_STACK_SIZE                4*1024
#define TEMPLATE_TASK_PRIORITY                  5
#define TEMPLATE_TASK_NAME                      "Template"
#define TEMPLATE_TASK_IS_IN_INTERNAL_RAM        false
#define TEMPLATE_TASK_LOOP_DELAY_MS             1000

/**  ===========================================================================
 * ================================= Data types ================================
 * ========================================================================== */


/**  ===========================================================================
 * ================================ Constants ==================================
 * ========================================================================== */
static const char * const DBG_ID = "template";

/**  ===========================================================================
 * ============================== Static private variables ====================#
 * ========================================================================== */
static volatile bool        g_b_is_running      = false;
static hal_os_task_handle_t g_os_task_handle    = {0};

/**  ===========================================================================
 * ========================= Private static function prototypes ================
 * ========================================================================== */
static void template_task(void * t_p_arg);

/**  ===========================================================================
 * =============================== Public functions body ======================#
 * ========================================================================== */
return_status_t template_start(template_t * t_p_handle)
{
    return_status_t rc = RETURN_STATUS_OK;

    rc = hal_os_task_create(
        &g_os_task_handle,
        template_task,
        TEMPLATE_TASK_NAME,
        TEMPLATE_TASK_STACK_SIZE,
        (void*)t_p_handle,
        TEMPLATE_TASK_PRIORITY,
        TEMPLATE_TASK_IS_IN_INTERNAL_RAM);

   return rc;
}

return_status_t template_stop(template_t * t_p_handle)
{
    return_status_t rc = RETURN_STATUS_OK;

    return rc;
}

/**  ===========================================================================
 * =============================== Private functions body ======================
 * ========================================================================== */

static void template_task(void * t_p_arg)
{
    hal_os_delay_t os_delay = {0};
    return_status_t rc = RETURN_STATUS_OK;
    // template_t * const p_handle = (template_t*)t_p_arg;

    g_b_is_running = true;
    rc = hal_os_delay_init(&os_delay);
    if(RETURN_STATUS_OK != rc)
    {
        g_b_is_running = false;
        log_err(
            DBG_ID,
            "Error on initialising the delay function: %s",
            return_code_get_string(rc));
    }

    for(;;)
    {
        if(!g_b_is_running)
        {
            break;
        }

        hal_os_delay_ms(&os_delay, TEMPLATE_TASK_LOOP_DELAY_MS, false);
    }

    rc = hal_os_task_delete(&g_os_task_handle);
}

// End of file
