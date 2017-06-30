obj-m := evil.o
KDIR := /lib/modules/$(shell uname -r)/build

CFLAGS_evil.o := -DDEBUG

all:
	#make -C $(KDIR) SUBDIRS=$(PWD) modules $(VARS)
	make -C $(KDIR) M=`pwd` modules

clean:
	#make -C $(KDIR) SUBDIRS=$(PWD) clean
	make -C $(KDIR) M=`pwd` clean
