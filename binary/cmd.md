# benchmark test for memory access code

run these tests in host OS running on bare metal server with kvm virtualzation enabled.

the pretouch3 test requires huge page supported in the host OS.

## run unikraft application

root@kraft:/home/joehuang_sweden# time qemu-system-x86_64 -cpu host,+x2apic,-pmu -enable-kvm -kernel /home/joehuang_sweden/unikraft-memspeed/binary/memspeed_qemu-x86_64 -machine pc,accel=kvm -m size=3906M -name memspeed -rtc base=utc -smp cpus=1,threads=1,sockets=1 -serial stdio

## run linux native memspeed

root@kraft:/home/joehuang_sweden# time unikraft-memspeed/binary/memspeed

## run linux native pretouch

root@kraft:/home/joehuang_sweden# time unikraft-memspeed/binary/pretouch

## run linux native pretouch2

root@kraft:/home/joehuang_sweden# time unikraft-memspeed/binary/pretouch2

## run linux native pretouch3

root@kraft:/home/joehuang_sweden# time unikraft-memspeed/binary/pretouch3
