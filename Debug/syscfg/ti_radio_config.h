/*
 *  ======== ti_radio_config.h ========
 *  Configured RadioConfig module definitions
 *
 *  DO NOT EDIT - This file is generated for the CC1352P1F3RGZ
 *  by the SysConfig tool.
 *
 *  Radio Config module version : 1.8
 *  SmartRF Studio data version : 2.20.0
 */
#ifndef _TI_RADIO_CONFIG_H_
#define _TI_RADIO_CONFIG_H_

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/rf_mailbox.h)
#include DeviceFamily_constructPath(driverlib/rf_common_cmd.h)
#include DeviceFamily_constructPath(driverlib/rf_ieee_cmd.h)
#include DeviceFamily_constructPath(driverlib/rf_prop_cmd.h)
#include <ti/drivers/rf/RF.h>

// *********************************************************************************
//   RF Frontend configuration
// *********************************************************************************
// RF design based on: LAUNCHXL-CC1352P-2 (CC1352PEM-XD4251-XD24-PA24_10dBm)
#define LAUNCHXL_CC1352P_2

// High-Power Amplifier supported
#define SUPPORT_HIGH_PA

// RF frontend configuration
#define FRONTEND_SUB1G_DIFF_RF
#define FRONTEND_SUB1G_EXT_BIAS
#define FRONTEND_24G_DIFF_RF
#define FRONTEND_24G_EXT_BIAS

// Supported frequency bands
#define SUPPORT_FREQBAND_868
#define SUPPORT_FREQBAND_2400

// TX power table size definitions
#define TXPOWERTABLE_868_PA13_SIZE 20 // 868 MHz, 13 dBm
#define TXPOWERTABLE_868_PA20_SIZE 8 // 868 MHz, 20 dBm
#define TXPOWERTABLE_868_PA13_20_SIZE 26 // 868 MHz, 13 + 20 dBm
#define TXPOWERTABLE_2400_PA5_SIZE 16 // 2400 MHz, 5 dBm

// TX power tables
extern RF_TxPowerTable_Entry txPowerTable_868_pa13[]; // 868 MHz, 13 dBm
extern RF_TxPowerTable_Entry txPowerTable_868_pa20[]; // 868 MHz, 20 dBm
extern RF_TxPowerTable_Entry txPowerTable_868_pa13_20[]; // 868 MHz, 13 + 20 dBm
extern RF_TxPowerTable_Entry txPowerTable_2400_pa5[]; // 2400 MHz, 5 dBm



//*********************************************************************************
//  RF Setting:   IEEE 802.15.4-2006, 250 kbps, OQPSK, DSSS = 1:8
//
//  PHY:          ieee154
//  Setting file: setting_ieee_802_15_4.json
//*********************************************************************************

// PA table usage
#define TX_POWER_TABLE_SIZE_ieee154_0 TXPOWERTABLE_2400_PA5_SIZE

#define txPowerTable_ieee154_0 txPowerTable_2400_pa5

// TI-RTOS RF Mode object
extern RF_Mode RF_prop_ieee154_0;

// RF Core API commands
extern rfc_CMD_RADIO_SETUP_PA_t RF_cmdRadioSetup_ieee154_0;
extern rfc_CMD_FS_t RF_cmdFs_ieee154_0;
extern rfc_CMD_IEEE_TX_t RF_cmdIeeeTx_ieee154_0;
extern rfc_CMD_IEEE_RX_t RF_cmdIeeeRx_ieee154_0;

// RF Core API overrides
extern uint32_t pOverrides_ieee154_0[];


//*********************************************************************************
//  RF Setting:   200 kbps, 50 kHz Deviation, 2-GFSK, 311 kHz RX Bandwidth
//
//  PHY:          2gfsk200kbps154g
//  Setting file: setting_tc746_154g.json
//*********************************************************************************

// PA table usage
#define TX_POWER_TABLE_SIZE TXPOWERTABLE_868_PA13_SIZE

#define txPowerTable txPowerTable_868_pa13

// TI-RTOS RF Mode object
extern RF_Mode RF_prop;

// RF Core API commands
extern rfc_CMD_PROP_RADIO_DIV_SETUP_PA_t RF_cmdPropRadioDivSetup;
extern rfc_CMD_FS_t RF_cmdFs;
extern rfc_CMD_PROP_TX_ADV_t RF_cmdPropTxAdv;
extern rfc_CMD_PROP_RX_ADV_t RF_cmdPropRxAdv;

// RF Core API overrides
extern uint32_t pOverrides[];

#endif // _TI_RADIO_CONFIG_H_
