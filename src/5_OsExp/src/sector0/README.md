### To run this infinite loop

``qemu-system-x86_64 -drive file=sector0.bin,format=raw``

We need to explicitly inform the emulator of the format so it doesn't have to guess. This is the error produced without specificity:
```
osdev@2035fe969caa:/workspaces/2024-ikt218-os-exp-5/src/5_OsExp/src/sector0$ qemu-system-x86_64 sector0.bin
WARNING: Image format was not specified for 'sector0.bin' and probing guessed raw.
         Automatically detecting the format is dangerous for raw images, write operations on block 0 will be restricted.
         Specify the 'raw' format explicitly to remove the restrictions.
```