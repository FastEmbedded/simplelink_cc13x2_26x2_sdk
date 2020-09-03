/*
 * Copyright (c) 2019 Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*
 *  ======== easylink_adv_config.syscfg.js ========
 */

"use strict";

// Get common utility functions
const Common = system.getScript("/ti/easylink/easylink_common.js");

// Get Adv Setting long descriptions
const docs = system.getScript("/ti/easylink/adv_config/"
    + "easylink_adv_config_docs.js");

// Configurables for the EasyLink Advanced Configuration module
const config = {
    displayName: "Advanced",
    description: "Configure RF driver client settings",
    config: [
        {
            name: "enableMultiClientMode",
            displayName: "Enable Multi-Client Mode",
            description: "Set Multi-client mode for application that will use "
                + "multiple RF clients",
            longDescription: docs.enableMultiClientModeLongDesc,
            default: false
        },
        {
            name: "clientEventCb",
            displayName: "Client Event Callback Function",
            description: "Defines the callback function provided to the RF "
                + "driver",
            longDescription: docs.clientEventCbLongDescription,
            default: "NULL"
        },
        {
            name: "clientEventMask",
            displayName: "Client Event Mask",
            description: "Event mask used to subscribe certain client events",
            longDescription: docs.clientEventMaskLongDescription,
            options: [
                {
                    displayName: "RF_ClientEventNone",
                    name: "0"
                },
                {name: "RF_ClientEventPowerUpFinished"},
                {name: "RF_ClientEventRadioFree"},
                {name: "RF_ClientEventSwitchClientEntered"}
            ],
            default: ["0"]
        }
    ]
};

/*
 * ======== validate ========
 * Validate this inst's configuration
 *
 * @param inst       - EasyLink Advanced Configuration instance to be validated
 * @param validation - object to hold detected validation issues
 */
function validate(inst, validation)
{
    // Validate the callback function
    if(Common.isCName(inst.clientEventCb))
    {
        if(inst.clientEventCb === "")
        {
            validation.logError("Empty function name not allowed, use 'NULL' "
                + "instead", inst, "clientEventCb");
        }
    }
    else
    {
        validation.logError("'" + inst.clientEventCb + "' is not a valid a C "
            + "identifier", inst, "clientEventCb");
    }
}

// Exports to the top level EasyLink module
exports = {
    config: config,
    validate: validate
};
