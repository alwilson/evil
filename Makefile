obj-m := evil.o
KDIR  ?= /lib/modules/$(shell uname -r)/build

CFLAGS_evil.o := -DDEBUG

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
