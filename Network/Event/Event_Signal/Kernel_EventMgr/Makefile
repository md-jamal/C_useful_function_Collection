obj-m += eventmgr.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/Kernel_EventMgr modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/Kernel_EventMgr clean
