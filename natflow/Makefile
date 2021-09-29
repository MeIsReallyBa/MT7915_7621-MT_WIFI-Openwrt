#
# Copyright (C) 2017-2019 Chen Minqiang <ptpt52@gmail.com>
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=natflow
PKG_VERSION:=1.0.2
PKG_RELEASE:=20210525


PKG_SOURCE_URL:=https://github.com/ptpt52/natflow.git
PKG_SOURCE_PROTO:=git
PKG_SOURCE_DATE:=2021-06-17
PKG_SOURCE_VERSION:=23026998816d0e53e6b7dbf04c7e5251f5747ea0
PKG_MIRROR_HASH:=

include $(INCLUDE_DIR)/package.mk

define KernelPackage/natflow
  CATEGORY:=X
  SUBMENU:=Fast Forward Stacks
  TITLE:=natflow kernel driver
  KCONFIG:= \
	CONFIG_NETFILTER_INGRESS=y
  FILES:=$(PKG_BUILD_DIR)/natflow.ko
  AUTOLOAD:=$(call AutoLoad,96,natflow)
  DEPENDS:= +kmod-ipt-conntrack +kmod-ipt-nat +kmod-ipt-ipset
endef

define KernelPackage/natflow/description
  fast nat forward kmod
endef

include $(INCLUDE_DIR)/kernel-defaults.mk

define Build/Compile/natflow
	+$(MAKE) $(PKG_JOBS) -C "$(LINUX_DIR)" \
		$(KERNEL_MAKE_FLAGS) \
		M="$(PKG_BUILD_DIR)" \
		modules
endef

define Build/Compile
	$(call Build/Compile/natflow)
endef

define Package/natflow-boot
  CATEGORY:=X
  SUBMENU:=Fast Forward Stacks
  TITLE:=natflow boot init script
  DEPENDS:= +kmod-natflow
endef

define Package/natflow-boot/install
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_DIR) $(1)/sbin/
	$(INSTALL_BIN) ./files/natflow-boot.init $(1)/etc/init.d/natflow-boot
	$(INSTALL_BIN) ./files/taskset $(1)/sbin/
	$(INSTALL_DIR) $(1)/etc/init.d/
	$(INSTALL_DIR) $(1)/lib/wifi/
	$(INSTALL_DIR) $(1)/etc/wireless/mt7615/
	$(INSTALL_DIR) $(1)/etc_ro/Wireless/RT2860AP/
	$(INSTALL_BIN) ./files/l1profile.dat $(1)/etc/wireless/
	$(INSTALL_BIN) ./files/mt7615.1.2G.dat $(1)/etc/wireless/mt7615/
	$(INSTALL_BIN) ./files/mt7615.1.5G.dat $(1)/etc/wireless/mt7615/
	$(INSTALL_BIN) ./files/mt7615.lua $(1)/lib/wifi
	$(INSTALL_BIN) ./files/firmware.sh $(1)/etc/init.d/
endef

$(eval $(call KernelPackage,natflow))
$(eval $(call BuildPackage,natflow-boot))
