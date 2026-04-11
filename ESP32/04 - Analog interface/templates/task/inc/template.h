/** -----------------------------------------------------------------------------
 * @file        template.h
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

#ifndef TEMPLATES_TASK_INC_TEMPLATE_H_
#define TEMPLATES_TASK_INC_TEMPLATE_H_

/** ============================================================================
 * ======================================= Includes ============================
 * ========================================================================== */
#include "return_status.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/** ============================================================================
 * ============================== Macro and Constants ==========================
 * ========================================================================== */

/** ============================================================================
 * ================================ Data types ================================#
 * ========================================================================== */

typedef struct
{

}template_t;

/** ============================================================================
 * ============================= Public functions prototype ====================
 * ========================================================================== */

/** ----------------------------------------------------------------------------
 * @brief Start the task
 * @param t_p_handle The pointer to the configuration structure that must be valid until
 *        the task has been finished
 *
 * @return RETURN_STATUS_OK on success
 ---------------------------------------------------------------------------- */
return_status_t template_start(template_t * t_p_handle);
/** ----------------------------------------------------------------------------
 * @brief Stop the task
 * @param t_p_handle The pointer to the configuration structure
 *
 * @return RETURN_STATUS_OK on success
 ---------------------------------------------------------------------------- */
return_status_t template_stop(template_t * t_p_handle);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // TEMPLATES_TASK_INC_TEMPLATE_H_
// End of file
