/*
 * drivers/base/power/clock_ops.c - Generic clock manipulation PM callbacks
 *
 * Copyright (c) 2011 Rafael J. Wysocki <rjw@sisk.pl>, Renesas Electronics Corp.
 *
 * This file is released under the GPLv2.
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/io.h>
#include <linux/pm.h>
#include <linux/pm_runtime.h>
#include <linux/clk.h>
#include <linux/slab.h>
#include <linux/err.h>

#ifdef CONFIG_PM_RUNTIME

struct pm_runtime_clk_data {
	struct list_head clock_list;
	struct mutex lock;
};

enum pce_status {
	PCE_STATUS_NONE = 0,
	PCE_STATUS_ACQUIRED,
	PCE_STATUS_ENABLED,
	PCE_STATUS_ERROR,
};

struct pm_clock_entry {
	struct list_head node;
	char *con_id;
	struct clk *clk;
	enum pce_status status;
};

static struct pm_runtime_clk_data *__to_prd(struct device *dev)
{
	return dev ? dev->power.subsys_data : NULL;
}

/**
 * pm_runtime_clk_acquire - Acquire a device clock.
 * @dev: Device whose clock is to be acquired.
 * @con_id: Connection ID of the clock.
 */
static void pm_runtime_clk_acquire(struct device *dev,
				    struct pm_clock_entry *ce)
{
	ce->clk = clk_get(dev, ce->con_id);
	if (IS_ERR(ce->clk)) {
		ce->status = PCE_STATUS_ERROR;
	} else {
		ce->status = PCE_STATUS_ACQUIRED;
		dev_dbg(dev, "Clock %s managed by runtime PM.\n", ce->con_id);
	}
}

/**
 * pm_runtime_clk_suspend - Disable clocks in a device's runtime PM clock list.
 * @dev: Device to disable the clocks for.
 */
int pm_runtime_clk_suspend(struct device *dev)
{
	struct pm_runtime_clk_data *prd = __to_prd(dev);
	struct pm_clock_entry *ce;

	dev_dbg(dev, "%s()\n", __func__);

	if (!prd)
		return 0;

	mutex_lock(&prd->lock);

	list_for_each_entry_reverse(ce, &prd->clock_list, node) {
		if (ce->status == PCE_STATUS_NONE)
			pm_runtime_clk_acquire(dev, ce);

		if (ce->status < PCE_STATUS_ERROR) {
			clk_disable(ce->clk);
			ce->status = PCE_STATUS_ACQUIRED;
		}
	}

	mutex_unlock(&prd->lock);

	return 0;
}

/**
 * pm_runtime_clk_resume - Enable clocks in a device's runtime PM clock list.
 * @dev: Device to enable the clocks for.
 */
int pm_runtime_clk_resume(struct device *dev)
{
	struct pm_runtime_clk_data *prd = __to_prd(dev);
	struct pm_clock_entry *ce;

	dev_dbg(dev, "%s()\n", __func__);

	if (!prd)
		return 0;

	mutex_lock(&prd->lock);

	list_for_each_entry(ce, &prd->clock_list, node) {
		if (ce->status == PCE_STATUS_NONE)
			pm_runtime_clk_acquire(dev, ce);

		if (ce->status < PCE_STATUS_ERROR) {
			clk_enable(ce->clk);
			ce->status = PCE_STATUS_ENABLED;
		}
	}

	mutex_unlock(&prd->lock);

	return 0;
}

/**
 * pm_runtime_clk_notify - Notify routine for device addition and removal.
 * @nb: Notifier block object this function is a member of.
 * @action: Operation being carried out by the caller.
 * @data: Device the routine is being run for.
 *
 * For this function to work, @nb must be a member of an object of type
 * struct pm_clk_notifier_block containing all of the requisite data.
 * Specifically, the pwr_domain member of that object is copied to the device's
 * pwr_domain field and its con_ids member is used to populate the device's list
 * of runtime PM clocks, depending on @action.
 *
 * If the device's pwr_domain field is already populated with a value different
 * from the one stored in the struct pm_clk_notifier_block object, the function
 * does nothing.
 */
static int pm_runtime_clk_notify(struct notifier_block *nb,
				 unsigned long action, void *data)
{
	struct pm_clk_notifier_block *clknb;
	struct device *dev = data;
	char **con_id;
	int error;

	dev_dbg(dev, "%s() %ld\n", __func__, action);

	clknb = container_of(nb, struct pm_clk_notifier_block, nb);

	switch (action) {
	case BUS_NOTIFY_ADD_DEVICE:
		if (dev->pwr_domain)
			break;

		error = pm_runtime_clk_init(dev);
		if (error)
			break;

		dev->pwr_domain = clknb->pwr_domain;
		if (clknb->con_ids[0]) {
			for (con_id = clknb->con_ids; *con_id; con_id++)
				pm_runtime_clk_add(dev, *con_id);
		} else {
			pm_runtime_clk_add(dev, NULL);
		}

		break;
	case BUS_NOTIFY_DEL_DEVICE:
		if (dev->pwr_domain != clknb->pwr_domain)
			break;

		dev->pwr_domain = NULL;
		pm_runtime_clk_destroy(dev);
		break;
	}

	return 0;
}

#else /* !CONFIG_PM_RUNTIME */

/**
 * enable_clock - Enable a device clock.
 * @dev: Device whose clock is to be enabled.
 * @con_id: Connection ID of the clock.
 */
static void enable_clock(struct device *dev, const char *con_id)
{
	struct clk *clk;

	clk = clk_get(dev, con_id);
	if (!IS_ERR(clk)) {
		clk_enable(clk);
		clk_put(clk);
		dev_info(dev, "Runtime PM disabled, clock forced on.\n");
	}
}

/**
 * disable_clock - Disable a device clock.
 * @dev: Device whose clock is to be disabled.
 * @con_id: Connection ID of the clock.
 */
static void disable_clock(struct device *dev, const char *con_id)
{
	struct clk *clk;

	clk = clk_get(dev, con_id);
	if (!IS_ERR(clk)) {
		clk_disable(clk);
		clk_put(clk);
		dev_info(dev, "Runtime PM disabled, clock forced off.\n");
	}
}

/**
 * pm_runtime_clk_notify - Notify routine for device addition and removal.
 * @nb: Notifier block object this function is a member of.
 * @action: Operation being carried out by the caller.
 * @data: Device the routine is being run for.
 *
 * For this function to work, @nb must be a member of an object of type
 * struct pm_clk_notifier_block containing all of the requisite data.
 * Specifically, the con_ids member of that object is used to enable or disable
 * the device's clocks, depending on @action.
 */
static int pm_runtime_clk_notify(struct notifier_block *nb,
				 unsigned long action, void *data)
{
	struct pm_clk_notifier_block *clknb;
	struct device *dev = data;
	char **con_id;

	dev_dbg(dev, "%s() %ld\n", __func__, action);

	clknb = container_of(nb, struct pm_clk_notifier_block, nb);

	switch (action) {
	case BUS_NOTIFY_BIND_DRIVER:
		if (clknb->con_ids[0]) {
			for (con_id = clknb->con_ids; *con_id; con_id++)
				enable_clock(dev, *con_id);
		} else {
			enable_clock(dev, NULL);
		}
		break;
	case BUS_NOTIFY_UNBOUND_DRIVER:
		if (clknb->con_ids[0]) {
			for (con_id = clknb->con_ids; *con_id; con_id++)
				disable_clock(dev, *con_id);
		} else {
			disable_clock(dev, NULL);
		}
		break;
	}

	return 0;
}

#endif /* !CONFIG_PM_RUNTIME */

/**
 * pm_runtime_clk_add_notifier - Add bus type notifier for runtime PM clocks.
 * @bus: Bus type to add the notifier to.
 * @clknb: Notifier to be added to the given bus type.
 *
 * The nb member of @clknb is not expected to be initialized and its
 * notifier_call member will be replaced with pm_runtime_clk_notify().  However,
 * the remaining members of @clknb should be populated prior to calling this
 * routine.
 */
void pm_runtime_clk_add_notifier(struct bus_type *bus,
				 struct pm_clk_notifier_block *clknb)
{
	if (!bus || !clknb)
		return;

	clknb->nb.notifier_call = pm_runtime_clk_notify;
	bus_register_notifier(bus, &clknb->nb);
}
