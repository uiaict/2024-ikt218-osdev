https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf 

Relevant page: 30 and onwards.

The global descriptor table (GDT) is a complex data structure that handles memory segments in terms of access rights, among other things.

It is needed to go from 16-bit real mode into 32-bit protected mode. The GDT is programmed using Assembly language. Since the BIOS is 16-bit mode we cannot make use of any BIOS routines, meaning that we need to make them ourselves for the 32-bit protected mode.

Segment Descriptor: 
- 8-byte structure
- Base address 32 bits
- Segment limit 20 bits
- Remaining bits represent various flags, privilege level, read/write only, etc...
Segment descriptor model used will be the _basic flat model_ from Intel.
It is made of two overlapping segments over the whole 4GB of addressable memory in 32-bit systems, one for code and one for data.

The first entry will be an invalid NULL descriptor, that is a sector of eight 0 bytes. Any addressing attempt with 0x0 makes the CPU then raise an exception.

#### Resource
Graphical image of segment descriptor on page 34.

