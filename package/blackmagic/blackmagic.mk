################################################################################
#
# blackmagic
#
################################################################################

BLACKMAGIC_VERSION = 82e125fb61891dccf94c97bd8afd8b2835d11162
BLACKMAGIC_SITE = https://github.com/blacksphere/blackmagic
BLACKMAGIC_SITE_METHOD = git

define BLACKMAGIC_BUILD_CMDS
    $(MAKE) CC=$(TARGET_CC) LD=$(TARGET_LD) -C $(@D)/src
endef

define BLACKMAGIC_INSTALL_TARGET_CMDS
    $(INSTALL) -D -m 0755 $(@D)/src/blackmagic $(TARGET_DIR)/usr/bin
endef

$(eval $(generic-package))
