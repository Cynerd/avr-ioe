# vim:ts=4:sw=4:sts=4:noexpandtab

ifndef TOOL_PATH
$(error Before including kconfig.mk you have to define path to tools in variable TOOL_PATH)
endif
ifndef CONFIG
$(error Before including kconfig.mk you have to define variable CONFIG contaning name of configuration file)
endif

$(CONFIG):
	@echo Please generate configuration first using config or menuconfig target
	@exit 1

# We don't wont pass any variable to Kconfig. This is workaround for that.
# So include of this file should be last line in Makefile
MAKEOVERRIDES =

define callconfig
$(Q)[ ! -f "$(CONFIG)" ] || mv "$(CONFIG)" config
$(Q)+$(MAKE) -f "$(TOOL_PATH)/kconfig/GNUmakefile" --no-print-directory IOEROOT="$(IOEROOT)" TOPDIR=. SRCDIR="$(TOOL_PATH)/kconfig" $(1)
$(Q)[ ! -f config ] || mv config "$(CONFIG)"
$(Q)[ ! -f config.old ] || mv config.old "$(CONFIG).old"
endef
# Note about this file moving madness:
# avr-ioe is using Kconfig for configuration and it is not prepared too well for
# nested projects (at least I don't know way). This unfortunately means that to
# have configuration in parent project, We have to move it every time we are
# generating it. Also upper projects can't use Kconfig for its self configuration.

.PHONY: oldconfig
oldconfig: $(deps_config)
	$(call callconfig, oldconfig)

.PHONY: config
config: $(deps_config)
	$(call callconfig, config)

.PHONY: menuconfig
menuconfig: $(deps_config)
	$(call callconfig, menuconfig)

.PHONY: allyesconfig
allyesconfig: $(deps_config)
	$(call callconfig, allyesconfig)
