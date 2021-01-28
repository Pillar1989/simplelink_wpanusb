/*
 * ieee802154_radio.c
 *
 *  Created on: Jan 28, 2021
 *      Author: baozhu
 */
#include <stdbool.h>
#include "ieee802154_radio.h"


static void ieee802154_cc13xx_cc26xx_iface_init(const struct cc1352_device *dev)
{

}

static enum ieee802154_hw_caps
ieee802154_cc13xx_cc26xx_get_capabilities(const struct cc1352_device *dev)
{
	/* TODO: enable IEEE802154_HW_FILTER */
	return IEEE802154_HW_FCS | IEEE802154_HW_CSMA
	       | IEEE802154_HW_SUB_GHZ;
}

/** Clear Channel Assesment - Check channel's activity */
int ieee802154_cc13xx_cc26xx_cca(const struct cc1352_device *dev){
	return 0;
}

/** Set current channel */
int ieee802154_cc13xx_cc26xx_set_channel(const struct cc1352_device *dev, uint16_t channel){
	return 0;
}

/** Set/Unset filters (for IEEE802154_HW_FILTER ) */
int ieee802154_cc13xx_cc26xx_filter(const struct cc1352_device *dev,
	      bool set,
	      enum ieee802154_filter_type type,
	      const struct ieee802154_filter *filter){
	return 0;
}

/** Set TX power level in dbm */
int ieee802154_cc13xx_cc26xx_set_txpower(const struct cc1352_device *dev, int16_t dbm){
	return 0;
}

/** Transmit a packet fragment */
int ieee802154_cc13xx_cc26xx_tx(const struct cc1352_device *dev, enum ieee802154_tx_mode mode){
	return 0;
}

/** Start the device */
int ieee802154_cc13xx_cc26xx_start(const struct cc1352_device *dev){
	return 0;
}

/** Stop the device */
int ieee802154_cc13xx_cc26xx_stop(const struct cc1352_device *dev){
	return 0;
}

/** Set specific radio driver configuration. */
int ieee802154_cc13xx_cc26xx_configure(const struct cc1352_device *dev,
		 enum ieee802154_config_type type,
		 const struct ieee802154_config *config){
	return 0;
}

/** Get the available amount of Sub-GHz channels */




struct ieee802154_radio_api ieee802154_cc13xx_cc26xx_radio_api = {
	 .init = ieee802154_cc13xx_cc26xx_iface_init,

	.get_capabilities = ieee802154_cc13xx_cc26xx_get_capabilities,
	.cca = ieee802154_cc13xx_cc26xx_cca,
	.set_channel = ieee802154_cc13xx_cc26xx_set_channel,
	.filter = ieee802154_cc13xx_cc26xx_filter,
	.set_txpower = ieee802154_cc13xx_cc26xx_set_txpower,
	.tx = ieee802154_cc13xx_cc26xx_tx,
	.start = ieee802154_cc13xx_cc26xx_start,
	.stop = ieee802154_cc13xx_cc26xx_stop,
	.configure = ieee802154_cc13xx_cc26xx_configure,
};
