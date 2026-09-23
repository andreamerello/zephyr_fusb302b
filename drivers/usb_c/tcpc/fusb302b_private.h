/*
 * Copyright 2023 Jonas Otto
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_DRIVERS_USBC_DEVICE_FUSB302B_PRIVATE_H_
#define ZEPHYR_DRIVERS_USBC_DEVICE_FUSB302B_PRIVATE_H_

#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/usb_c/usbc_tcpc.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

#define FUSB302_RX_BUFFER_SIZE 80
#define FUSB302_TX_BUFFER_SIZE 48

struct alert_info {
	void *data;
	tcpc_alert_handler_cb_t handler;
};

struct fusb302b_data {
	const struct device *dev;
	struct alert_info alert_info;
	struct gpio_callback gpio_cb;
	struct k_work irq_work;
	/* Serializes multi-register measurement and CC configuration. */
	struct k_mutex lock;
	uint8_t switches0_cache;
	bool switches0_cache_valid;
	int cc;
	atomic_t data_avail;
};

struct fusb302b_cfg {
	struct i2c_dt_spec i2c;
	struct gpio_dt_spec gpio_irq;
};

int fusb302b_init(const struct device *dev);

#endif /* ZEPHYR_DRIVERS_USBC_DEVICE_FUSB302B_PRIVATE_H_ */
