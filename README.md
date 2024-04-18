# benchmark for memory speed

run these tests in host OS running on bare metal server with kvm virtualzation enabled.

all binaries could be compiled directly from the source code.

for unikraft-memspeed, build through:

```
kraft build --plat qemu --arch x86_64
```

for linux native binaries, build as follows:
```
 gcc memspeed.c -o memspeed
```

the pretouch3 test requires huge page supported in the host OS.

## run unikraft application

root@kraft:/home/joehuang_sweden/unikraft-memspeed# time qemu-system-x86_64 -cpu host,+x2apic,-pmu -enable-kvm -kernel /home/joehuang_sweden/unikraft-memspeed/binary/memspeed_qemu-x86_64 -machine pc,accel=kvm -m size=3906M -name memspeed -rtc base=utc -smp cpus=1,threads=1,sockets=1 -serial stdio

## run linux native memspeed

root@kraft:/home/joehuang_sweden/unikraft-memspeed# time binary/memspeed

## run linux native pretouch

root@kraft:/home/joehuang_sweden/unikraft-memspeed# time binary/pretouch

## run linux native pretouch2

root@kraft:/home/joehuang_sweden/unikraft-memspeed# time binary/pretouch2

## run linux native pretouch3

root@kraft:/home/joehuang_sweden/unikraft-memspeed# time binary/pretouch3
