/*
 * Copyright (c) [2020], MediaTek Inc. All rights reserved.
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws.
 * The information contained herein is confidential and proprietary to
 * MediaTek Inc. and/or its licensors.
 * Except as otherwise provided in the applicable licensing terms with
 * MediaTek Inc. and/or its licensors, any reproduction, modification, use or
 * disclosure of MediaTek Software, and information contained herein, in whole
 * or in part, shall be strictly prohibited.
*/
/***************************************************************************
***************************************************************************

*/

#include "rt_config.h"
#include "wlan_config/config_internal.h"

/*
*ht phy info related
*/
VOID ht_cfg_init(struct ht_cfg *obj)
{
	/*initial ht_phy_info value*/
	obj->ht_bw = HT_BW_20;
	obj->ext_cha = EXTCHA_NOASSIGN;
	obj->ht_ldpc = TRUE;
	obj->ht_stbc = STBC_USE;
	obj->ht_gi = GI_400;
	obj->ht_protect_en = TRUE;
	obj->min_mpdu_start_space = INTERVAL_NO_RESTRICTION;
	obj->amsdu_en = TRUE;
	obj->ht40_intolerant = FALSE;
	obj->mmps = MMPS_DISABLE;
	obj->frag_thld = DEFAULT_FRAG_THLD;
	obj->len_thld = DEFAULT_RTS_LEN_THLD;
	obj->pkt_thld = DEFAULT_RTS_PKT_THLD;
	obj->ba_cfg.ba_decline = 0;
	obj->ba_cfg.ba_enable = 1;
	obj->ba_cfg.ba_tx_wsize = BA_WIN_SZ_64;
	obj->ba_cfg.ba_rx_wsize = BA_WIN_SZ_64;
}

VOID ht_cfg_exit(struct ht_cfg *obj)
{
	os_zero_mem(obj, sizeof(struct ht_cfg));
}

/*
 *  export configure function
 */
/*
 *Set
 */
VOID wlan_config_set_ht_bw(struct wifi_dev *wdev, UCHAR ht_bw)
{
	struct wlan_config *cfg = (struct wlan_config *)wdev->wpf_cfg;

	if (cfg)
		cfg->ht_conf.ht_bw = ht_bw;
	wlan_operate_set_support_ch_width_set(wdev, ht_bw);
}

VOID wlan_config_set_ht_bw_all(struct wpf_ctrl *ctrl, UCHAR ht_bw)
{
	struct wlan_config *cfg;
	unsigned int i;

	for (i = 0; i < WDEV_NUM_MAX; i++) {
		cfg = (struct wlan_config *)ctrl->pf[i].conf;
		if (cfg)
			cfg->ht_conf.ht_bw = ht_bw;
	}
}

VOID wlan_config_set_ext_cha(struct wifi_dev *wdev, UCHAR ext_cha)
{
	struct wlan_config *cfg = (struct wlan_config *)wdev->wpf_cfg;

	if (cfg)
		cfg->ht_conf.ext_cha = ext_cha;
}

VOID wlan_config_set_ht_stbc(struct wifi_dev *wdev, UCHAR ht_stbc)
{
	struct wlan_config *cfg = NULL;

	cfg = (struct wlan_config *)wdev->wpf_cfg;
	if (cfg)
		cfg->ht_conf.ht_stbc = ht_stbc;
}

VOID wlan_config_set_ht_ldpc(struct wifi_dev *wdev, UCHAR ht_ldpc)
{
	struct wlan_config *cfg = NULL;

	cfg = (struct wlan_config *)wdev->wpf_cfg;
	if (cfg)
		cfg->ht_conf.ht_ldpc = ht_ldpc;
}

VOID wlan_config_set_ht_mode(struct wifi_dev *wdev, UCHAR ht_mode)
{
	struct wlan_config *cfg = NULL;
	UCHAR gf_support;

	cfg = (struct wlan_config *)wdev->wpf_cfg;
	if (cfg) {
		cfg->ht_conf.ht_mode = ht_mode;
		gf_support = (ht_mode == HTMODE_GF) ? 1 : 0;
		cfg->ht_conf.gf_support = gf_support;
	}
}

VOID wlan_config_set_40M_intolerant(struct wifi_dev *wdev, UCHAR val)
{
	struct wlan_config *cfg = NULL;

	cfg = (struct wlan_config *)wdev->wpf_cfg;
	if (cfg)
		cfg->ht_conf.ht40_intolerant = val;
}

VOID wlan_config_set_mmps(struct wifi_dev *wdev, UCHAR mmps)
{
	struct wlan_config *cfg = NULL;

	cfg = (struct wlan_config *)wdev->wpf_cfg;
	if (cfg)
		cfg->ht_conf.mmps = mmps;
}

VOID wlan_config_set_edca_valid(struct wifi_dev *wdev, BOOLEAN bValid)
{
	struct wlan_config *cfg = (struct wlan_config *)wdev->wpf_cfg;
	if (cfg)
		cfg->ht_conf.EdcaParm.bValid = bValid;
}

VOID wlan_config_set_edca_valid_all(struct wpf_ctrl *ctrl, BOOLEAN bValid)
{
	struct wlan_config *cfg;
	unsigned int i;
	for (i = 0; i < WDEV_NUM_MAX; i++) {
		cfg = (struct wlan_config*)ctrl->pf[i].conf;
		if (cfg)
			cfg->ht_conf.EdcaParm.bValid = bValid;
	}
}

VOID wlan_config_set_ht_gi(struct wifi_dev *wdev, UCHAR ht_gi)
{
	struct wlan_config *cfg = NULL;

	cfg = (struct wlan_config *)wdev->wpf_cfg;
	if (cfg)
		cfg->ht_conf.ht_gi = ht_gi;
}

VOID wlan_config_set_ht_protect_en(struct wifi_dev *wdev, UCHAR ht_protect_en)
{
	struct wlan_config *cfg = NULL;

	cfg = (struct wlan_config *)wdev->wpf_cfg;
	if (cfg)
		cfg->ht_conf.ht_protect_en = ht_protect_en;
}

VOID wlan_config_set_amsdu_en(struct wifi_dev *wdev, UCHAR enable)
{
	struct wlan_config *cfg = NULL;

	cfg = (struct wlan_config *)wdev->wpf_cfg;
	if (cfg)
		cfg->ht_conf.amsdu_en = enable;
}

VOID wlan_config_set_frag_thld(struct wifi_dev *wdev, UINT32 frag_thld)
{
	struct wlan_config *cfg = NULL;

	cfg = (struct wlan_config *)wdev->wpf_cfg;
	if (cfg)
		cfg->ht_conf.frag_thld = frag_thld;
}

VOID wlan_config_set_rts_len_thld(struct wifi_dev *wdev, UINT32 len_thld)
{
	struct wlan_config *cfg = NULL;

	cfg = (struct wlan_config *)wdev->wpf_cfg;
	if (cfg)
		cfg->ht_conf.len_thld = len_thld;
}

VOID wlan_config_set_rts_pkt_thld(struct wifi_dev *wdev, UCHAR pkt_num)
{
	struct wlan_config *cfg = NULL;

	cfg = (struct wlan_config *)wdev->wpf_cfg;
	if (cfg)
		cfg->ht_conf.pkt_thld = pkt_num;
}

VOID wlan_config_set_min_mpdu_start_space(struct wifi_dev *wdev, UCHAR mpdu_density)
{
	struct wlan_config *cfg = NULL;

	cfg = (struct wlan_config *)wdev->wpf_cfg;
	if (cfg)
		cfg->ht_conf.min_mpdu_start_space = mpdu_density;
}

VOID wlan_config_set_ba_decline(struct wifi_dev *wdev, UINT8 decline)
{
	struct wlan_config *cfg = NULL;

	cfg = (struct wlan_config *)wdev->wpf_cfg;
	if (cfg)
		cfg->ht_conf.ba_cfg.ba_decline = decline;
}

VOID wlan_config_set_ba_enable(struct wifi_dev *wdev, UINT8 en)
{
	struct wlan_config *cfg = NULL;

	cfg = (struct wlan_config *)wdev->wpf_cfg;
	if (cfg)
		cfg->ht_conf.ba_cfg.ba_enable = en;
}

VOID wlan_config_set_ba_txrx_wsize(struct wifi_dev *wdev,
		UINT16 tx_wsize, UINT16 rx_wsize)
{
	struct wlan_config *cfg = NULL;

	/* TX */
	if ((tx_wsize == 0) || (tx_wsize > BA_WIN_SZ_256))
		tx_wsize = BA_WIN_SZ_64;
	/* RX */
	if ((rx_wsize == 0) || (rx_wsize > BA_WIN_SZ_256))
		rx_wsize = BA_WIN_SZ_64;

	cfg = (struct wlan_config *)wdev->wpf_cfg;
	if (cfg) {
		cfg->ht_conf.ba_cfg.ba_tx_wsize = tx_wsize;
		cfg->ht_conf.ba_cfg.ba_rx_wsize = rx_wsize;
	}
}

/*
*Get
*/
UCHAR wlan_config_get_ht_bw(struct wifi_dev *wdev)
{
	struct wlan_config *cfg = NULL;

	if (wdev == NULL)/*ALPS05330340*/
		return 0;
	cfg = (struct wlan_config *)wdev->wpf_cfg;
	if (cfg)
		return cfg->ht_conf.ht_bw;
	else
		return 0;
}

UCHAR wlan_config_get_ext_cha(struct wifi_dev *wdev)
{
	struct wlan_config *cfg = (struct wlan_config *)wdev->wpf_cfg;

	if (cfg)
		return cfg->ht_conf.ext_cha;
	else
		return 0;
}

UCHAR wlan_config_get_ht_stbc(struct wifi_dev *wdev)
{
	struct wlan_config *cfg = (struct wlan_config *)wdev->wpf_cfg;

	if (cfg)
		return cfg->ht_conf.ht_stbc;
	else
		return 0;
}

UCHAR wlan_config_get_ht_ldpc(struct wifi_dev *wdev)
{
	struct wlan_config *cfg = (struct wlan_config *)wdev->wpf_cfg;

	if (cfg)
		return cfg->ht_conf.ht_ldpc;
	else
		return 0;
}

BOOLEAN wlan_config_get_edca_valid(struct wifi_dev *wdev)
{
	struct wlan_config *cfg = (struct wlan_config *)wdev->wpf_cfg;
	if (cfg)
		return cfg->ht_conf.EdcaParm.bValid;
	else
		return FALSE;
}

struct _EDCA_PARM* wlan_config_get_ht_edca(struct wifi_dev *wdev)
{
	struct wlan_config *cfg = (struct wlan_config *)wdev->wpf_cfg;
	if (cfg)
		return &cfg->ht_conf.EdcaParm;
	else
		return NULL;
}

UCHAR wlan_config_get_ht_gi(struct wifi_dev *wdev)
{
	struct wlan_config *cfg = (struct wlan_config *)wdev->wpf_cfg;

	if (cfg)
		return cfg->ht_conf.ht_gi;
	else
		return 1;
}

UCHAR wlan_config_get_ht_protect_en(struct wifi_dev *wdev)
{
	struct wlan_config *cfg = (struct wlan_config *)wdev->wpf_cfg;

	if (cfg)
		return cfg->ht_conf.ht_protect_en;
	else
		return 1;
}

UCHAR wlan_config_get_ht_mode(struct wifi_dev *wdev)
{
	struct wlan_config *cfg = (struct wlan_config *)wdev->wpf_cfg;

	if (cfg)
		return cfg->ht_conf.ht_mode;
	return HTMODE_MM;
}

UCHAR wlan_config_get_greenfield(struct wifi_dev *wdev)
{
	struct wlan_config *cfg = (struct wlan_config *)wdev->wpf_cfg;

	if (cfg)
		return cfg->ht_conf.gf_support;
	return 0;
}

UCHAR wlan_config_get_40M_intolerant(struct wifi_dev *wdev)
{
	struct wlan_config *cfg = (struct wlan_config *)wdev->wpf_cfg;

	if (cfg)
		return cfg->ht_conf.ht40_intolerant;
	return 0;
}

UCHAR wlan_config_get_amsdu_en(struct wifi_dev *wdev)
{
	struct wlan_config *cfg = (struct wlan_config *)wdev->wpf_cfg;

	if (cfg)
		return cfg->ht_conf.amsdu_en;
	return 0;
}

UINT32 wlan_config_get_frag_thld(struct wifi_dev *wdev)
{
	struct wlan_config *cfg = (struct wlan_config *)wdev->wpf_cfg;

	if (cfg)
		return cfg->ht_conf.frag_thld;
	else
		return DEFAULT_FRAG_THLD;
}
EXPORT_SYMBOL(wlan_config_get_frag_thld);

UINT32 wlan_config_get_rts_len_thld(struct wifi_dev *wdev)
{
	struct wlan_config *cfg = (struct wlan_config *)wdev->wpf_cfg;

	if (cfg)
		return cfg->ht_conf.len_thld;
	else
		return DEFAULT_RTS_LEN_THLD;
}

UCHAR wlan_config_get_rts_pkt_thld(struct wifi_dev *wdev)
{
	struct wlan_config *cfg = (struct wlan_config *)wdev->wpf_cfg;

	if (cfg)
		return cfg->ht_conf.pkt_thld;
	else
		return DEFAULT_RTS_PKT_THLD;
}

UCHAR wlan_config_get_min_mpdu_start_space(struct wifi_dev *wdev)
{
	struct wlan_config *cfg = (struct wlan_config *)wdev->wpf_cfg;

	if (cfg)
		return cfg->ht_conf.min_mpdu_start_space;
	return 0;
}

UCHAR wlan_config_get_mmps(struct wifi_dev *wdev)
{
	struct wlan_config *cfg = (struct wlan_config *)wdev->wpf_cfg;

	if (cfg)
		return cfg->ht_conf.mmps;
	return MMPS_DISABLE;
}

UINT8 wlan_config_get_ba_decline(struct wifi_dev *wdev)
{
	struct wlan_config *cfg = (struct wlan_config *)wdev->wpf_cfg;

	if (cfg)
		return cfg->ht_conf.ba_cfg.ba_decline;
	return 0;
}

UINT8 wlan_config_get_ba_enable(struct wifi_dev *wdev)
{
	struct wlan_config *cfg = (struct wlan_config *)wdev->wpf_cfg;

	if (cfg)
		return cfg->ht_conf.ba_cfg.ba_enable;
	return 0;
}

UINT16 wlan_config_get_ba_tx_wsize(struct wifi_dev *wdev)
{
	struct wlan_config *cfg = (struct wlan_config *)wdev->wpf_cfg;

	if (cfg)
		return cfg->ht_conf.ba_cfg.ba_tx_wsize;
	return 0;
}

UINT16 wlan_config_get_ba_rx_wsize(struct wifi_dev *wdev)
{
	struct wlan_config *cfg = (struct wlan_config *)wdev->wpf_cfg;

	if (cfg)
		return cfg->ht_conf.ba_cfg.ba_rx_wsize;
	return 0;
}
