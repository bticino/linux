/*
 * Chip specific defines for DM646x SoC
 *
 * Author: Kevin Hilman, Deep Root Systems, LLC
 *
 * 2007 (c) Deep Root Systems, LLC. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */
#ifndef __ASM_ARCH_DM646X_H
#define __ASM_ARCH_DM646X_H

#include <mach/hardware.h>
#include <mach/emac.h>
#include <mach/asp.h>
#include <linux/i2c.h>
#include <linux/videodev2.h>

#define DM646X_EMAC_BASE		(0x01C80000)
#define DM646X_EMAC_CNTRL_OFFSET	(0x0000)
#define DM646X_EMAC_CNTRL_MOD_OFFSET	(0x1000)
#define DM646X_EMAC_CNTRL_RAM_OFFSET	(0x2000)
#define DM646X_EMAC_MDIO_OFFSET		(0x4000)
#define DM646X_EMAC_CNTRL_RAM_SIZE	(0x2000)

#define DM646X_ATA_REG_BASE		(0x01C66000)

/* System module register offsets */
#define PINMUX0				0x00
#define PINMUX1				0x04
#define BOOTCFG				0x14

void __init dm646x_init(void);
void __init dm646x_init_ide(void);
void __init dm646x_init_mcasp0(struct snd_platform_data *pdata);
void __init dm646x_init_mcasp1(struct snd_platform_data *pdata);
void __init dm646x_init_cir_device(void);


struct spi_board_info;
void dm646x_init_spi0(struct spi_board_info *info, unsigned len);

void dm646x_video_init(void);

enum vpif_if_type {
	VPIF_IF_BT656,
	VPIF_IF_BT1120,
	VPIF_IF_RAW_BAYER
};

struct vpif_interface {
	enum vpif_if_type if_type;
	unsigned hd_pol:1;
	unsigned vd_pol:1;
	unsigned fid_pol:1;
};

struct vpif_subdev_info {
	const char *name;
	struct i2c_board_info board_info;
	u32 input;
	u32 output;
	unsigned can_route:1;
	struct vpif_interface vpif_if;
};

struct vpif_display_config {
	int (*set_clock)(int, int);
	struct vpif_subdev_info *subdevinfo;
	int subdev_count;
	const char **output;
	int output_count;
	const char *card_name;
	bool ch2_clip_en;
	bool ch3_clip_en;
};

struct vpif_input {
	struct v4l2_input input;
	const char *subdev_name;
};

#define VPIF_CAPTURE_MAX_CHANNELS	2

struct vpif_capture_chan_config {
	const struct vpif_input *inputs;
	int input_count;
};

struct vpif_capture_config {
	int (*setup_input_channel_mode)(int);
	int (*setup_input_path)(int, const char *);
	struct vpif_capture_chan_config chan_config[VPIF_CAPTURE_MAX_CHANNELS];
	struct vpif_subdev_info *subdev_info;
	int subdev_count;
	const char *card_name;
};

void dm646x_setup_vpif(struct vpif_display_config *,
		       struct vpif_capture_config *);

void dm646x_video_init(void);

struct vpif_output {
	u16 id;
	const char *name;
};

#endif /* __ASM_ARCH_DM646X_H */
