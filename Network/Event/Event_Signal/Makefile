CURDIR=$(shell pwd)
PACKAGE_VERSION :=
PACKAGE_DIR :=
PACKAGE_CONF :=
first_rule: all

all: build

build:
	$(MAKE) -C $(CURDIR)/User_Space_Daemon_wait_for_signal      all
	$(MAKE) -C $(CURDIR)/User_Space_APP_send_signal             all
	$(MAKE) -C $(CURDIR)/Kernel_EventMgr                        all
	
	
config_rule:

install_rule install:

clean_rule distclean clean:
	$(MAKE) -C $(CURDIR)/User_Space_Daemon_wait_for_signal      clean
	$(MAKE) -C $(CURDIR)/User_Space_APP_send_signal             clean
	$(MAKE) -C $(CURDIR)/Kernel_EventMgr                        clean
	
uninstall_rule uninstall:
