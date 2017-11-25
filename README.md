# Evil Bit Netfilter Module
Linux netfilter module to toggle evil bit (RFC 3514) in all outgoing IPv4 packets.

The evil bit is an unused, reserved bit in the header of every IPv4 packet and as an April Fool's joke someone submitted an RFC to have it mark packets that have "evil" intentions. So if you're thinking of doing anything shady then make sure you insert this module into your kernel so that all your outgoing packets get marked as evil!

Warning, some websites and domains block packets using the evil bit! If you want to learn more then checkout out [the blog post and kernel patch](https://blog.benjojo.co.uk/post/evil-bit-RFC3514-real-world-usage) that inspired this module.

## Usage
How to compile, insert, and remove this netfilter module.

The following sections show the command followed by the expected output.

### Compile
Running just `make` should be enough.

You may need to install the header files for your current kernel via a package (such as core/linux-headers under Arch).
```
$ make
make -C /lib/modules/4.13.12-1-ARCH/build M=/git/evil modules
make[1]: Entering directory '/usr/lib/modules/4.13.12-1-ARCH/build'
  CC [M]  /git/evil/evil.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /git/evil/evil.mod.o
  LD [M]  /git/evil/evil.ko
make[1]: Leaving directory '/usr/lib/modules/4.13.12-1-ARCH/build'
```

### Insert Module
Use insmod to insert the netfilter module into the kernel:
```
$ sudo insmod evil.ko
<nothing>
```
Check that it worked:
```
$ lsmod | grep evil
evil                   16384  0
```

### Remove Module
Remove netfilter module from the kernel:
```
$ sudo rmmod evil
<nothing>
```
Check that it worked:
```
$ lsmod | grep evil
<nothing and hopefully no kernel panics!>
```

### Troubleshooting
After inserting and removing the module, you should see the following messages appear in the kernel log:
```
$ dmesg | tail
[183637.830951] Becoming evil!
[183643.542412] Repentance complete.
```
