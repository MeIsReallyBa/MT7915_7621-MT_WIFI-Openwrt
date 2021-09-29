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
#include "mgmt/be_internal.h"


/*
* he related
*/
VOID he_oper_init(struct wifi_dev *wdev, struct he_op *obj)
{
	struct ppdu_caps *ppdu = wlan_config_get_ppdu_caps(wdev);
	obj->bss_color = DEFAULT_COLOR;
	obj->bss_color_dis = 1;
	obj->partial_bss_color = 0;
	obj->txop_dur_rts_thld = wlan_config_get_he_txop_dur_rts_thld(wdev);
	obj->he_af = ppdu->he_max_ampdu_len_exp;
}

VOID he_oper_exit(struct he_op *obj)
{
	os_zero_mem(obj, sizeof(*obj));
}

/*
 * SET
 */
INT32 wlan_operate_set_he_bss_color(struct wifi_dev *wdev, UINT8 bss_color, UINT8 bss_color_dis)
{
	struct wlan_operate *op = NULL;
	INT32 ret = WLAN_OPER_OK;

	if (!wdev) {
		MTWF_LOG(DBG_CAT_CFG, DBG_SUBCAT_ALL, DBG_LVL_OFF,
				("%s: wdev is NULL!!!\n", __func__));
		return WLAN_OPER_FAIL;
	}

	op = (struct wlan_operate *)wdev->wpf_op;
	if (op) {
		op->he_oper.bss_color = bss_color;
		op->he_oper.bss_color_dis = bss_color_dis;
	}

	return ret;
}

INT32 wlan_operate_set_he_partial_bss_color(struct wifi_dev *wdev, UINT8 partial_bss_color)
{
	struct wlan_operate *op = NULL;
	INT32 ret = WLAN_OPER_OK;

	if (!wdev) {
		MTWF_LOG(DBG_CAT_CFG, DBG_SUBCAT_ALL, DBG_LVL_OFF,
				("%s: wdev is NULL!!!\n", __func__));
		return WLAN_OPER_FAIL;
	}

	op = (struct wlan_operate *)wdev->wpf_op;
	if (op)
		op->he_oper.partial_bss_color = partial_bss_color;

	return ret;
}

INT32 wlan_operate_set_he_bss_next_color(struct wifi_dev *wdev, UINT8 color, UINT8 count)
{
	struct wlan_operate *op = NULL;
	INT32 ret = WLAN_OPER_OK;

	if (!wdev) {
		MTWF_LOG(DBG_CAT_CFG, DBG_SUBCAT_ALL, DBG_LVL_OFF,
				("%s: wdev is NULL!!!\n", __func__));
		return WLAN_OPER_FAIL;
	}
	op = (struct wlan_operate *)wdev->wpf_op;
	if (op) {
		op->he_oper.next_bss_color = color;
		op->he_oper.bcc_count = count;
	}
	return ret;
}

INT32 wlan_operate_set_he_txop_dur_rts_thld(struct wifi_dev *wdev, UINT16 txop_dur_thld)
{
	struct wlan_operate *op = NULL;
	INT32 ret = WLAN_OPER_OK;

	if (!wdev) {
		MTWF_LOG(DBG_CAT_CFG, DBG_SUBCAT_ALL, DBG_LVL_OFF,
				("%s: wdev is NULL!!!\n", __func__));
		return WLAN_OPER_FAIL;
	}

	op = (struct wlan_operate *)wdev->wpf_op;
	if (op)
		op->he_oper.txop_dur_rts_thld = txop_dur_thld;

	return ret;
}

INT32 wlan_operate_set_he_af(struct wifi_dev *wdev, UINT8 he_af)
{
	struct wlan_operate *op = NULL;
	INT32 ret = WLAN_OPER_OK;

	if (!wdev) {
		MTWF_LOG(DBG_CAT_CFG, DBG_SUBCAT_ALL, DBG_LVL_OFF,
				("%s: wdev is NULL!!!\n", __func__));
		return WLAN_OPER_FAIL;
	}

	op = (struct wlan_operate *)wdev->wpf_op;
	if (op)
		op->he_oper.he_af = he_af;

	return ret;
}


/*
 * GET
 */
UINT8 wlan_operate_get_he_intra_bss_info(struct wifi_dev *wdev)
{
	UINT8 intra_bss_info = 0;
	struct wlan_operate *op = NULL;

	if (!wdev) {
		MTWF_LOG(DBG_CAT_CFG, DBG_SUBCAT_ALL, DBG_LVL_OFF,
				("%s: wdev is NULL!!!\n", __func__));
		return 0;
	}

	op = (struct wlan_operate *)wdev->wpf_op;
	if (!op) {
		MTWF_LOG(DBG_CAT_CFG, DBG_SUBCAT_ALL, DBG_LVL_OFF,
			("%s: op NULL\n", __func__));
		return 0;
	}

	MTWF_LOG(DBG_CAT_PROTO, CATPROTO_COLOR, DBG_LVL_INFO,
			("%s: color = %d, disabled = %d\n", __func__,
			 op->he_oper.bss_color, op->he_oper.bss_color_dis));
	intra_bss_info |= (op->he_oper.bss_color & INTRA_HE_BSS_COLOR_MASK);
	intra_bss_info |= (op->he_oper.bss_color_dis << INTRA_HE_BSS_COLOR_DIS_SHIFT);
	intra_bss_info |= (op->he_oper.partial_bss_color << INTRA_HE_PARTIAL_BSS_COLOR_SHIFT);

	return intra_bss_info;
}

INT32 wlan_operate_get_he_bss_next_color(struct wifi_dev *wdev, UINT8 *color, UINT8 *count)
{
	struct wlan_operate *op = NULL;
	INT32 ret = WLAN_OPER_OK;

	if (!wdev) {
		MTWF_LOG(DBG_CAT_CFG, DBG_SUBCAT_ALL, DBG_LVL_OFF,
				("%s: wdev is NULL!!!\n", __func__));
		return WLAN_OPER_FAIL;
	}

	op = (struct wlan_operate *)wdev->wpf_op;
	if (!op) {
		MTWF_LOG(DBG_CAT_CFG, DBG_SUBCAT_ALL, DBG_LVL_OFF,
				("%s: op is NULL!!!\n", __func__));
		return WLAN_OPER_FAIL;
	}

	*color = op->he_oper.next_bss_color;
	*count = op->he_oper.bcc_count;

	MTWF_LOG(DBG_CAT_PROTO, CATPROTO_COLOR, DBG_LVL_INFO,
			("%s: next color = %d, countdown = %d\n", __func__,
			 op->he_oper.next_bss_color, op->he_oper.bcc_count));
	return ret;
}

UINT16 wlan_operate_get_he_txop_dur_rts_thld(struct wifi_dev *wdev)
{
	struct wlan_operate *op = NULL;
	UINT16 ret = MAX_TXOP_DURATION_RTS_THRESHOLD;

	if (!wdev) {
		MTWF_LOG(DBG_CAT_CFG, DBG_SUBCAT_ALL, DBG_LVL_OFF,
				("%s: wdev is NULL!!!\n", __func__));
		return ret;
	}

	op = (struct wlan_operate *)wdev->wpf_op;
	if (op)
		ret = op->he_oper.txop_dur_rts_thld;

	MTWF_LOG(DBG_CAT_MLME, DBG_SUBCAT_ALL, DBG_LVL_INFO,
			("%s: txop_dur_rts_thld = %d\n",
			__func__,
			ret));
	return ret;
}

UINT8 wlan_operate_get_he_af(struct wifi_dev *wdev)
{
	struct wlan_operate *op = NULL;
	UINT8 he_af = 0;

	if (!wdev) {
		MTWF_LOG(DBG_CAT_CFG, DBG_SUBCAT_ALL, DBG_LVL_OFF,
				("%s: wdev is NULL!!!\n", __func__));
		return he_af;
	}

	op = (struct wlan_operate *)wdev->wpf_op;
	if (op)
		he_af = op->he_oper.he_af;

	return he_af;
}

