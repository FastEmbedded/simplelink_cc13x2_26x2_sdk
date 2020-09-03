/******************************************************************************

 Group: WCS, BTS
 Target Device: cc13x2_26x2

 ******************************************************************************
 
 Copyright (c) 2010-2020, Texas Instruments Incorporated
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

 *  Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

 *  Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

 *  Neither the name of Texas Instruments Incorporated nor the names of
    its contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 ******************************************************************************
 
 
 *****************************************************************************/

/**
 *  @defgroup RTLSSrv RTLSSrv Internal
 *  This module describes internal API's that RTLS Services will use
 *  @{
 *  @file  rtls_srv_internal.h
 *       RTLS Services Internal header file
 */

#ifndef RTLSSRVINTERNAL_H
#define RTLSSRVINTERNAL_H

#ifdef __cplusplus
extern "C"
{
#endif

/*-------------------------------------------------------------------
 * INCLUDES
 */

#include "map_direct.h"

/*********************************************************************
 * MACROS
 */
#define RTLSSrv_malloc ICall_malloc
#define RTLSSrv_free   ICall_free

#define BUILD_UINT16(loByte, hiByte) \
          ((uint16)(((loByte) & 0x00FF) + (((hiByte) & 0x00FF) << 8)))

/*-------------------------------------------------------------------
 * CONSTANTS
 */

#define BIT_x(x)          (1 << (x))

#define HCI_CTE_MAX_SAMPLES_PER_EVENT            (96)  //!< Max samples data length in one HCI event

/*-------------------------------------------------------------------
 * TYPEDEFS
 */

/// @brief Structure holding the state of an ongoing Extented I/Q Report
typedef struct
{
  uint8_t                      evtStarted;         //!< I/Q event is ongoing
  uint8_t                      evtIndex;           //!< Index chunk number
  uint16_t                     remainingDataSize;  //!< Remaining size until we have all data
  rtlsSrv_connectionIQReport_t *pTmpExtIqEvt;      //!< This will temporarily hold the event that will eventually be sent to the user
} rtlsSrv_extIqEvtState_t;

/*-------------------------------------------------------------------
 * API's
 */

/*********************************************************************
 * @fn          RTLSSrv_handleError
 *
 * @brief       Handles errors by translating from HCI format to RTLS Services format
 *              Errors may result from incorrect user usage of API's
 *
 * @param       errSrc - which command/opcode caused the error
 * @param       errCause - what was the actual error
 * @param       connHandle - connection handle on which the error happened
 *
 * @return      TRUE = success, FALSE = failure
 */
bStatus_t RTLSSrv_handleError(uint16_t errSrc, uint16_t errCause, uint16_t connHandle);

/*********************************************************************
 * @fn          RTLSSrv_callAppCb
 *
 * @brief       Allocate and send a message to the application
 *
 * @param       evtType - opcode of the event
 * @param       evtSize - size of evtData
 * @param       pEvtData - actual information to pass
 *
 * @return      TRUE = success, FALSE = failure
 */
bStatus_t RTLSSrv_callAppCb(uint8_t evtType, uint16_t evtSize, uint8_t *pEvtData);

/*********************************************************************
 * @fn          RTLSSrv_handleConnIqEvent
 *
 * @brief       Handle a Connection IQ Event sent by HCI
 *
 * @param       pEvtData - actual information to pass
 *
 * @return      TRUE = success, FALSE = failure
 */
bStatus_t RTLSSrv_handleConnIqEvent(uint8_t *pEvtData);

/*********************************************************************
 * @fn          RTLSSrv_handleExtConnIqEvent
 *
 * @brief       Handle an Extended Connection IQ Event sent by HCI
 *
 * @param       evtData - actual information to pass
 *
 * @return      TRUE = success, FALSE = failure
 */
bStatus_t RTLSSrv_handleExtConnIqEvent(uint8_t *pEvtData);

/*********************************************************************
 * @fn          RTLSSrv_handleCteReqFail
 *
 * @brief       Handle a failed CTE request
 *
 * @param       pEvtData - actual information to pass
 *
 * @return      TRUE = success, FALSE = failure
 */
bStatus_t RTLSSrv_handleCteReqFail(uint8_t *pEvtData);

/*********************************************************************
 * @fn          RTLSSrv_handReadAntInfo
 *
 * @brief       Handle read antenna info event
 *
 * @param       pEvtData - actual information to pass
 *
 * @return      TRUE = success, FALSE = failure
 */
bStatus_t RTLSSrv_handleReadAntInfo(uint8_t *pEvtData);
#ifdef __cplusplus
}
#endif

#endif /* RTLSSRVINTERNAL_H */

/** @} End RTLSSrv */
