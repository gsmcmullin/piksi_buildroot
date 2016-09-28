################################################################################
#
# sbp_settings_client
#
################################################################################

SBP_SETTINGS_CLIENT_VERSION = 0.1
SBP_SETTINGS_CLIENT_SITE = "${BR2_EXTERNAL}/package/sbp_settings_client/src"
SBP_SETTINGS_CLIENT_SITE_METHOD = local
SBP_SETTINGS_CLIENT_DEPENDENCIES = czmq libsbp

define SBP_SETTINGS_CLIENT_BUILD_CMDS
    $(MAKE) CC=$(TARGET_CC) LD=$(TARGET_LD) -C $(@D) all
endef

define SBP_SETTINGS_CLIENT_INSTALL_TARGET_CMDS
    $(INSTALL) -D -m 0755 $(@D)/sbp_settings_client $(TARGET_DIR)/usr/bin
endef

$(eval $(generic-package))
