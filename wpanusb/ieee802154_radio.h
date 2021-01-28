/*
 * ieee802154_radio.h
 *
 *  Created on: Jan 28, 2021
 *      Author: baozhu
 */

#ifndef WPANUSB_IEEE802154_RADIO_H_
#define WPANUSB_IEEE802154_RADIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <ti/drivers/rf/RF.h>
#include <stdlib.h>
#include "ti_easylink_config.h"
#include "ti_drivers_config.h"
#include "ti_radio_config.h"

#define BIT(n)  (1UL << (n))
/**
 * @brief IEEE 802.15.4 Channel assignments
 *
 * Channel numbering for 868 MHz, 915 MHz, and 2450 MHz bands.
 *
 * - Channel 0 is for 868.3 MHz.
 * - Channels 1-10 are for 906 to 924 MHz with 2 MHz channel spacing.
 * - Channels 11-26 are for 2405 to 2530 MHz with 5 MHz channel spacing.
 *
 * For more information, please refer to 802.15.4-2015 Section 10.1.2.2.
 */
enum ieee802154_channel {
	IEEE802154_SUB_GHZ_CHANNEL_MIN = 0,
	IEEE802154_SUB_GHZ_CHANNEL_MAX = 10,
	IEEE802154_2_4_GHZ_CHANNEL_MIN = 11,
	IEEE802154_2_4_GHZ_CHANNEL_MAX = 26,
};

enum ieee802154_hw_caps {
	IEEE802154_HW_FCS	  = BIT(0), /* Frame Check-Sum supported */
	IEEE802154_HW_PROMISC	  = BIT(1), /* Promiscuous mode supported */
	IEEE802154_HW_FILTER	  = BIT(2), /* Filter PAN ID, long/short addr */
	IEEE802154_HW_CSMA	  = BIT(3), /* CSMA-CA supported */
	IEEE802154_HW_2_4_GHZ	  = BIT(4), /* 2.4Ghz radio supported */
	IEEE802154_HW_TX_RX_ACK	  = BIT(5), /* Handles ACK request on TX */
	IEEE802154_HW_SUB_GHZ	  = BIT(6), /* Sub-GHz radio supported */
	IEEE802154_HW_ENERGY_SCAN = BIT(7), /* Energy scan supported */
	IEEE802154_HW_TXTIME	  = BIT(8), /* TX at specified time supported */
	IEEE802154_HW_SLEEP_TO_TX = BIT(9), /* TX directly from sleep supported */
};

enum ieee802154_filter_type {
	IEEE802154_FILTER_TYPE_IEEE_ADDR,
	IEEE802154_FILTER_TYPE_SHORT_ADDR,
	IEEE802154_FILTER_TYPE_PAN_ID,
	IEEE802154_FILTER_TYPE_SRC_IEEE_ADDR,
	IEEE802154_FILTER_TYPE_SRC_SHORT_ADDR,
};

enum ieee802154_event {
	IEEE802154_EVENT_TX_STARTED, /* Data transmission started */
	IEEE802154_EVENT_RX_FAILED   /* Data reception failed */
};

enum ieee802154_rx_fail_reason {
	IEEE802154_RX_FAIL_NOT_RECEIVED,  /* Nothing received */
	IEEE802154_RX_FAIL_INVALID_FCS,   /* Frame had invalid checksum */
	IEEE802154_RX_FAIL_ADDR_FILTERED, /* Address did not match */
	IEEE802154_RX_FAIL_OTHER	  /* General reason */
};

struct ieee802154_filter {
/** @cond ignore */
	union {
		uint8_t *ieee_addr;
		uint16_t short_addr;
		uint16_t pan_id;
	};
/* @endcond */
};

/** IEEE802.15.4 Transmission mode. */
enum ieee802154_tx_mode {
	/** Transmit packet immediately, no CCA. */
	IEEE802154_TX_MODE_DIRECT,

	/** Perform CCA before packet transmission. */
	IEEE802154_TX_MODE_CCA,

	/** Perform full CSMA CA procedure before packet transmission. */
	IEEE802154_TX_MODE_CSMA_CA,

	/** Transmit packet in the future, at specified time, no CCA. */
	IEEE802154_TX_MODE_TXTIME,

	/** Transmit packet in the future, perform CCA before transmission. */
	IEEE802154_TX_MODE_TXTIME_CCA,
};

/** IEEE802.15.4 Frame Pending Bit table address matching mode. */
enum ieee802154_fpb_mode {
	/** The pending bit shall be set only for addresses found in the list.
	 */
	IEEE802154_FPB_ADDR_MATCH_THREAD,

	/** The pending bit shall be cleared for short addresses found in
	 *  the list.
	 */
	IEEE802154_FPB_ADDR_MATCH_ZIGBEE,
};

/** IEEE802.15.4 driver configuration types. */
enum ieee802154_config_type {
	/** Indicates how radio driver should set Frame Pending bit in ACK
	 *  responses for Data Requests. If enabled, radio driver should
	 *  determine whether to set the bit or not based on the information
	 *  provided with ``IEEE802154_CONFIG_ACK_FPB`` config and FPB address
	 *  matching mode specified. Otherwise, Frame Pending bit should be set
	 *  to ``1``(see IEEE Std 802.15.4-2006, 7.2.2.3.1).
	 */
	IEEE802154_CONFIG_AUTO_ACK_FPB,

	/** Indicates whether to set ACK Frame Pending bit for specific address
	 *  or not. Disabling the Frame Pending bit with no address provided
	 *  (NULL pointer) should disable it for all enabled addresses.
	 */
	IEEE802154_CONFIG_ACK_FPB,

	/** Indicates whether the device is a PAN coordinator. */
	IEEE802154_CONFIG_PAN_COORDINATOR,

	/** Enable/disable promiscuous mode. */
	IEEE802154_CONFIG_PROMISCUOUS,

	/** Specifies new radio event handler. Specifying NULL as a handler
	 *  will disable radio events notification.
	 */
	IEEE802154_CONFIG_EVENT_HANDLER
};


/** IEEE802.15.4 driver configuration data. */
struct ieee802154_config {
	/** Configuration data. */
	union {
		/** ``IEEE802154_CONFIG_AUTO_ACK_FPB`` */
		struct {
			bool enabled;
			enum ieee802154_fpb_mode mode;
		} auto_ack_fpb;

		/** ``IEEE802154_CONFIG_ACK_FPB`` */
		struct {
			uint8_t *addr;
			bool extended;
			bool enabled;
		} ack_fpb;

		/** ``IEEE802154_CONFIG_PAN_COORDINATOR`` */
		bool pan_coordinator;

		/** ``IEEE802154_CONFIG_PROMISCUOUS`` */
		bool promiscuous;
	};
};



/* See IEEE 802.15.4-2015 20.2.2 */
#define IEEE802154_SUN_PHY_FSK_PHR_LEN 2

/* IEEE 802.15.4-2015 915 MHz 2FSK PHY symbol rate (20.6.3) */
#define IEEE802154_SUN_PHY_2FSK_200K_SYMBOLS_PER_SECOND 200000

/* IEEE 802.15.4-2006 PHY constants (6.4.1) */
#define IEEE802154_MAX_PHY_PACKET_SIZE 127
#define IEEE802154_TURNAROUND_TIME 12

/* IEEE 802.15.4-2006 PHY PIB attributes (6.4.2) */
#define IEEE802154_PHY_CCA_MODE 1
#define IEEE802154_PHY_SHR_DURATION 2
#define IEEE802154_PHY_SYMBOLS_PER_OCTET 8

/* IEEE 802.15.4-2006 MAC constants (7.4.1) */
#define IEEE802154_UNIT_BACKOFF_PERIOD 20

/* ACK is 2 bytes for PHY header + 2 bytes MAC header + 2 bytes MAC footer */
#define IEEE802154_ACK_FRAME_OCTETS 6

/* IEEE 802.15.4-2006 MAC PIB attributes (7.4.2)
 *
 * The macAckWaitDuration attribute does not include aUnitBackoffPeriod for
 * non-beacon enabled PANs (See IEEE 802.15.4-2006 7.5.6.4.2)
 */
#define IEEE802154_MAC_ACK_WAIT_DURATION			    \
	(IEEE802154_TURNAROUND_TIME + IEEE802154_PHY_SHR_DURATION + \
	 IEEE802154_ACK_FRAME_OCTETS * IEEE802154_PHY_SYMBOLS_PER_OCTET)

/* Reserve two bytes for 16-bit CRC */
#define IEEE802154_MTU (IEEE802154_MAX_PHY_PACKET_SIZE - 2)

#define CC13XX_CC26XX_RAT_CYCLES_PER_SECOND 4000000

#define CONFIG_IEEE802154_CC13XX_CC26XX_SUB_GHZ_NUM_RX_BUF 6

#define CC13XX_CC26XX_NUM_RX_BUF \
	CONFIG_IEEE802154_CC13XX_CC26XX_SUB_GHZ_NUM_RX_BUF

/* Three additional bytes for length, RSSI and status values from CPE */
#define CC13XX_CC26XX_RX_BUF_SIZE (IEEE802154_MAX_PHY_PACKET_SIZE + 3)

/*
 * Two additional bytes for the SUN FSK PHY HDR
 * (See IEEE 802.15.4-2015 20.2.2)
 */
#define CC13XX_CC26XX_TX_BUF_SIZE \
	(IEEE802154_MAX_PHY_PACKET_SIZE + IEEE802154_SUN_PHY_FSK_PHR_LEN)

#define CC13XX_CC26XX_RECEIVER_SENSITIVITY -100
#define CC13XX_CC26XX_RSSI_DYNAMIC_RANGE 95



struct cc1352_device {
	RF_Handle rf_handle;
	RF_Object rf_object;

//	struct net_if *iface;
//	uint8_t mac[8];
//
//	struct k_mutex tx_mutex;
//
//	dataQueue_t rx_queue;
//	rfc_dataEntryPointer_t rx_entry[CC13XX_CC26XX_NUM_RX_BUF];
	uint8_t rx_data[CC13XX_CC26XX_NUM_RX_BUF][CC13XX_CC26XX_RX_BUF_SIZE];
	uint8_t tx_data[CC13XX_CC26XX_TX_BUF_SIZE];

	/* Common Radio Commands */
	volatile rfc_CMD_CLEAR_RX_t cmd_clear_rx;
	volatile rfc_CMD_SET_TX_POWER_t cmd_set_tx_power;
	volatile rfc_CMD_FS_t cmd_fs;

	/* Sub-GHz Radio Commands */
	volatile rfc_CMD_PROP_RADIO_DIV_SETUP_PA_t cmd_prop_radio_div_setup;
	volatile rfc_CMD_PROP_RX_ADV_t cmd_prop_rx_adv;
	volatile rfc_CMD_PROP_TX_ADV_t cmd_prop_tx_adv;
	volatile rfc_propRxOutput_t cmd_prop_rx_adv_output;
	volatile rfc_CMD_PROP_CS_t cmd_prop_cs;
};

/**
 * @brief IEEE 802.15.4 radio interface API.
 *
 */
struct ieee802154_radio_api {
	void (*init)(const struct cc1352_device *dev);

	/** Get the device capabilities */
	enum ieee802154_hw_caps (*get_capabilities)(const struct cc1352_device *dev);

	/** Clear Channel Assesment - Check channel's activity */
	int (*cca)(const struct cc1352_device *dev);

	/** Set current channel */
	int (*set_channel)(const struct cc1352_device *dev, uint16_t channel);

	/** Set/Unset filters (for IEEE802154_HW_FILTER ) */
	int (*filter)(const struct cc1352_device *dev,
		      bool set,
		      enum ieee802154_filter_type type,
		      const struct ieee802154_filter *filter);

	/** Set TX power level in dbm */
	int (*set_txpower)(const struct cc1352_device *dev, int16_t dbm);

	/** Transmit a packet fragment */
	int (*tx)(const struct cc1352_device *dev, enum ieee802154_tx_mode mode);

	/** Start the device */
	int (*start)(const struct cc1352_device *dev);

	/** Stop the device */
	int (*stop)(const struct cc1352_device *dev);

	/** Set specific radio driver configuration. */
	int (*configure)(const struct cc1352_device *dev,
			 enum ieee802154_config_type type,
			 const struct ieee802154_config *config);

	/** Get the available amount of Sub-GHz channels */
	uint16_t (*get_subg_channel_count)(const struct cc1352_device *dev);
};


#ifdef __cplusplus
}
#endif

#endif /* WPANUSB_IEEE802154_RADIO_H_ */
