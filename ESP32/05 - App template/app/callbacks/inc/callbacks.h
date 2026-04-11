/** -----------------------------------------------------------------------------
 * @file        callbacks.h
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

#ifndef CALLBACKSS_SIMPLE_INC_CALLBACKS_H_
#define CALLBACKSS_SIMPLE_INC_CALLBACKS_H_

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


/** ============================================================================
 * ============================== Constants ====================================
 * ========================================================================== */


/** ============================================================================
 * ================================ Data types ================================#
 * ========================================================================== */

typedef struct
{

}callbacks_t;

/** ============================================================================
 * ============================= Public functions prototype ====================
 * ========================================================================== */

/** ----------------------------------------------------------------------------
 * @brief The module initialiser
 * @param t_p_handle The pointer to the configuration structure
 *
 * @return RETURN_CODE_OK on success
 -----------------------------------------------------------------------------*/
return_status_t callbacks_init(callbacks_t * const t_p_handle);

/** ----------------------------------------------------------------------------
 * @brief The module de-initialiser
 * @param t_p_handle The pointer to the configuration structure
 *
 * @return RETURN_CODE_OK on success
 -----------------------------------------------------------------------------*/
return_status_t callbacks_deinit(callbacks_t * const t_p_handle);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CALLBACKSS_SIMPLE_INC_CALLBACKS_H_
// End of file
