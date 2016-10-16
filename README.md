Architecture II 2016, Coursework
================================

This is a living specification. Please feel free to post
questions as issues, or submit pull requests if you see
a chance for improvements.

Goals of this coursework
------------------------

There are three central aims of this coursework:

- Solidify your understanding of how an instruction
  processor actually functions. The overall functionality
  of how a processor works is relatively easy to grasp,
  but there is lots of interesting detail which gives
  you some insight (both into CPUs, but also into
  software and digital design).
  
- Understand the importance of having good specifications,
  in terms of functionality, APIs, and requirements. This
  is fundamental to CPU design and implementation, but is
  also true in the wider world (again) of software and
  digital design.
 
- Develop your skills in coding from scratch. There is
  not much scaffolding here, I am genuinely asking you
  to create your own CPU simulator from scratch. You
  will also hopefully learn some important lessons about
  reducing code repetition and automation.
  
Coursework Deliverables
-----------------------

There are two C++ [deliverables](https://en.wikipedia.org/wiki/Deliverable) for this coursework:

1. Create a MIPS software simulator

2. Develop a test suite for your MIPS simulator

The API for the simulator is given as a bare C header file,
defining the functions and data-types involved, along
with a functional specification of what a simulator
should do. The API acts as the interface between your
simulator and your test-suite, and indeed _any_ simulator
and test-suite.

Your submitted code will consist of a zip file, containing
the original directory structure and files, as well as the
files that you have contributed. The two key things you will
be adding are:

 - `src/[your_login]/mips_cpu.cpp`
 
 - `src/[your_login]/test_mips.cpp`
 
The first part is the implementation of a mips simulator, and
is essentially a library that implements the api found in [`include/mips_cpu.h`](include/mips_cpu.h).
If you want to split into multiple files, then feel free to do
so - anything which matches the pattern `src/[your_login]/mips_cpu_*.cpp`
or `src/[your_login]/mips_cpu_*/*.cpp` will also get compiled into your library.
So the three types of source file that will get compiled into your CPU are:

- `src/[your_login]/mips_cpu.cpp` (must exist)

- `src/[your_login]/mips_cpu_*.cpp` (if any)

- `src/[your_login]/mips_cpu_*/*.cpp` (if any)

The second part is the test suite which will drive your
simulator and make it do things. This is a C++ program
(so it will have a main function) in a file called `src/[your_login]/test_mips.cpp`.
Again, your can split it into multiple files, so anything
that matches these patterns will get compiled in:

- `src/[your_login]/test_mips.cpp` (must exist)

- `src/[your_login]/test_mips_*.cpp` (if any)

- `src/[your_login]/test_mips_*/*.cpp` (if any)

_Original makefile also included another pattern (thanks to @lorenzo2897, see
  [issue #21](https://github.com/m8pple/arch2-2016-cw/issues/21)._


You can also add your own private header files (often a good idea),
which should be part of the submitted zip file,
but they don't need to follow any specific pattern. However,
they should be completely located within the `src/[your_login]`
directory or a sub-directory of it. Note that your simulator
and your test suite are two different components, so do not
rely on the specific behaviour of _your_ simulator, it should
work with any simulator that follows the API.

The directory structure should look like:

    .
    +-readme.md  # This document
    |
    +-include    # A directory that you don't own. Don't put things here.
    | |
    | +-mips.h
    | +-mips_*.h  # Other mips headers
    |
    +-src
    | |
    | +-shared   # This is shared with everyone. Don't put things here.
    | | | 
    | | +-mips_mem_ram.cpp
    | | +-mips_test_framework.cpp
    | |
    | +-[your_login] # This is your private folder. Do whatever you like here.
    |   |
    |   +-mips_cpu.cpp
    |   +-mips_cpu_*.cpp (if you want them)
    |   +-mips_cpu_*/*.cpp (if you want them)
    |   |
    |   +-test_mips.cpp
    |   +-test_mips_*.cpp (if you want them)
    |   +-test_mips_*/*.cpp (if you want them)
    |   |
    |   +-(anything else you want, e.g. headers, docs)
    |
    +-doc # Used for doxygen (if generated)
    |
    +-fragments # Some simple shared examples of C, assembly, and binary code
    |
    +-(anything else you want, but it won't be available in the test environment)

Your submitted code will need to work within the
compilation environment specified later on (another
part of the specification). The file names and
structure _must_ match those mandated here.

If you're wondering why I'm being so prescriptive about this,
it is because I've already done all your marking, which required
me to know what your submission looks like and what I can do
with it. The given structure allows me to know exactly what
your code needs in order to compile (I need to tell the compiler
which source files to link together), and when I want to move
implementations around I need to know what is important (so
stuff in src/<your_login>).

Assessment criteria
-------------------

This is an exercise in both implementing specifications,
and in testing specifications, so the assessment
is weighted as follows:

- 20% Compilation and robustness: How much (manual) work
  was needed to make the submission compile in the target
  environment and run without crashing? The expectation
  is that everyone can get full marks here.

- 50% Functionality: What proportion of the CPU simulator's
  functions operate correctly? It is unlikely that many submissions
  will get all instructions working perfectly, but there is a core
  subset that everyone will be able to get fully working, a larger
  set that most people will be able to get partially working, and some
  instructions that are really quite difficult to get right and many
  people won't attempt. Some hints on that will appear later.

- 30% Testing: What proportion of the CPU simulator is
  exercised and tested by the submitted test suite? So _if_ an
  instruction is implemented, is it a) exercised, and b) is
  the result checked. You can still get a decent mark here
  even if you have a small number of instructions implemented,
  as long as they are tested well.
  
- (at most 10%) Bug reports: This specification will not be perfect, and
  I welcome bug reports. Things like spelling mistakes are
  welcome, but not quite as valuable. What is important
  are points of genuine ambiguity, or errors of implementation
  in the code spec. Bug reports should identify both the
  problem, and how to reproduce it, and particularly welcome are
  bug reports with suggested fixes. Note that "I don't know
  what to do" or "my program crashes" or "this is too hard" are
  not bugs, they need to be errors in the specification.
  
Except for the marks for compilation (where everyone
should really get full marks, but is down to me assessing
how much manual work I needed to put in) and bug reports
(which are subjective and more rare) the assessment is
quantitative and metric based.

There are two submission deadlines, one soft, one hard:

- Friday 21st October 22:00: deadline for formative (ungraded)
  assessment. If you submit a version by this deadline, it
  will be put through a subset of the assessment. The
  results (but not a grade), will be returned on Monday 24th.
  Submission is not required, but is obviously encouraged.

- Friday 28th October 22:00: deadline for summative (graded)
  assessment. Whether or not you submitted for the previous
  deadline, everyone must submit for this deadline. This
  will be the part which results in the grade for this
  coursework.

The idea of the first deadline is for you to test whatever
you have working. You might only have one or two
instructions working at that point, which is fine. Submit
that, and it will give you some confidence that the
way you are doing things is correct.

Compilation Environment
-----------------------

For most people it is sufficient to say: the target compilation
is plain C or C++, and the target environment is the C and/or
C++ standard library. It is easy to stay within platform independent
APIs, as no platform-specific interaction with the environment is
needed during execution. So it should work happily on both linux
and windows.

The actual target environment is the lab Linux environment,
and the version of gcc/g++ installed there. You can develop
in Windows, MacOS, or another linux, but you need to make sure
it works in that environment.

During compilation, the include directories will be set up
to have both the `include` directory (containing `mips.h`)
and the `src/[your_login]` directory on the include path.
The directory structure during compilation
will be the same as that required during submission, so the
relative location of things will stay the same.

When running your test suite, the executable will be launched
with its working directory as `src/[your_login]`, so if you
wish to read files you can place them there (or in sub-directories).

When your CPU simulator is executing, you can make no assumptions
about the working directory, or the presence or absence of other
files.

Managing expectations
---------------------

You may think that it is always possible to get 90-100% in
coursework if you just work hard enough. That is not
true here, and will usually not be true in your future
courseworks. The grade distribution for this coursework
should be roughly the same as exam grade distributions,
and certainly was last year. So 70% is a good mark, 80%+
is a great mark, and anything above 60% shows that you're
doing ok.

Some students will have more programming experience,
and so will find this exercise easier, and may well
end up with a higher grade. That's life I'm afraid,
just like some people turned up last year knowing more
of the maths curriculum. This mark goes into Computing Lab,
which is intended to encourage and recognise ability in the
practical application of programming and computing concepts.
For those students who are less experienced in programming
this kind of exercise is much more valuable, and they
will get more out of it. But everyone, no matter their
programming ability, should find it helps clarify their
current understanding of instruction processors, and supports
their learning through the rest of this module.

Guidance on instructions
------------------------

We are going to look at the MIPS-1 (or MIPS-I) instruction
set, in big endian mode. There are 47 instructions eligible for implementation,
as certain instructions such as SYSCALL are too complex to
handle here. The following table gives the mnemonics, the description,
and a rough guide to how complex they are. Note that the complexity is
based on both how easy it is to implement the base functionality,
but also how easy it is to deal with, and try to test, corner cases.


Code  |   Meaning                                 | Complexity  
------|-------------------------------------------|-----------
ADD   |  Add (with overflow)                      | 2  XX       
ADDI  |  Add immediate (with overflow)            | 2  XX       
ADDIU |  Add immediate unsigned (no overflow)     | 2  XX       
ADDU  |  Add unsigned (no overflow)               | 1  X        
AND   |  Bitwise and                              | 1  X         
ANDI  |  Bitwise and immediate                    | 2  XX       
BEQ   |  Branch on equal                          | 3  XXX      
BGEZ  |  Branch on greater than or equal to zero  | 3  XXX      
BGEZAL|  Branch on non-negative (>=0) and link    | 4  XXXX     
BGTZ  |  Branch on greater than zero              | 3  XXX      
BLEZ  |  Branch on less than or equal to zero     | 3  XXX      
BLTZ  |  Branch on less than zero                 | 3  XXX      
BLTZAL|  Branch on less than zero and link        | 4  XXXX     
BNE   |  Branch on not equal                      | 3  XXX      
DIV   |  Divide                                   | 4  XXXX     
DIVU  |  Divide unsigned                          | 4  XXXX     
J     |  Jump                                     | 3  XXX      
JALR  |  Jump and link register                   | 4  XXXX     
JAL   |  Jump and link                            | 4  XXXX     
JR    |  Jump register                            | 3  XXX      
LB    |  Load byte                                | 3  XXX       
LBU   |  Load byte unsigned                       | 3  XXX      
LH    |  Load half-word                           | 3  XXX       
LHU   |  Load half-word unsigned                  | 3  XXX       
LUI   |  Load upper immediate                     | 2  XX       
LW    |  Load word                                | 2  XX       
LWL   |  Load word left                           | 5  XXXXX    
LWR   |  Load word right                          | 5  XXXXX    
MFHI  |  Move from HI                             | 3  XXX     
MFLO  |  Move from LO                             | 3  XXX     
MTHI  |  Move to HI                               | 3  XXX     
MTLO  |  Move to LO                               | 3  XXX     
MULT  |  Multiply                                 | 4  XXXX     
MULTU |  Multiply unsigned                        | 4  XXXX     
OR    |  Bitwise or                               | 1  X        
ORI   |  Bitwise or immediate                     | 2  XX       
SB    |  Store byte                               | 3  XXX      
SH    |  Store half-word                          | 3  XXX      
SLL   |  Shift left logical                       | 2  XX       
SLLV  |  Shift left logical variable              | 3  XXX       
SLT   |  Set on less than (signed)                | 2  XX       
SLTI  |  Set on less than immediate (signed)      | 3  XXX       
SLTIU |  Set on less than immediate unsigned      | 3  XXX      
SLTU  |  Set on less than unsigned                | 1  X        
SRA   |  Shift right arithmetic                   | 2  XX       
SRAV  |  Shift right arithmetic                   | 2  XX       
SRL   |  Shift right logical                      | 2  XX       
SRLV  |  Shift right logical variable             | 3  XXX       
SUB   |  Subtract                                 | 2  XX       
SUBU  |  Subtract unsigned                        | 1  X        
SW    |  Store word                               | 2  XX       
XOR   |  Bitwise exclusive or                     | 1  X        
XORI  |  Bitwise exclusive or immediate           | 2  XX       

This is a not-quite an exhaustive list of MIPS-1 instructions.
Any instruction not covered in this list will not be tested
as part of the assessment, and any implementation defined
behaviour is fine (return an error, or actually implement
the instruction).

There are many instructions, but there is a lot of commonality
between some instructions. Think about the underlying
digital data-path in a real processor, and use that to identify
where there are similarities. 

You may get to the point where things start getting very boring,
and you seem to be doing the same thing over and over, possibly
by copying and pasting. This is generally an indication that you
are missing an opportunity to abstract or automate. For example,
how different are "and", "or", and "xor"? What is the shared
functionality between "lb", "lw", and "lh"? You may want to
re-factor your code every once in a while as you work out better
ways of testing them - the purpose of your test-bench is to
give you the confidence to do that.

As you move through the instructions you should find that
you have to think carefully about the first instruction of each type,
deciding how to implement and test it. The next of the same
type should be much quicker, then the next almost mechanical, 
and you'll probably find two-thirds of the instructions are
done in a minute each. However, you should still expect this to
take a substantial amount of time, particularly if you plan to do
all instructions.

I would expect most people to be able to implement and test all
the 1s and 2s fairly easily. Implementing the 3s is not so
difficult, but testing them can be more complex. The 4s are doable,
but have some complexity in implementation and testing. Implementing
the 5s correctly is really quite challenging.

Plagiarism
----------

Everyone is implementing the same CPU, with the same API, which
means that there will be a certain amount of similarity. However,
there will also be differences, and you might be surprised by
the amount of variation that ones sees. I do actually read your
code too, and you'd be surprised how well the human brain remembers
patterns and oddities, even across 40 submissions (particularly
if that brain has been programming for some years). There are
also ways of automatically looking for similarities for further
review by a human.

This coursework is also largely unchanged since last year, and
substantially similar to the year before. You may well be able
to get hold of someone's solution from a previous year. But
bear in mind that I have a copy of every solution ever submitted
for this coursework, in an easily searchable file structure.

Please note that discussion is not plagiarism, and even showing
each other your solutions is generally fine. It is interesting
to see how someone else has solved the same problem, and even
having seen their solution, you will not produce the same code
(unless you stare at it and type it in). The point where it
becomes plagiarism is when the code is shared between students - never
give someone a copy of your code on a USB or give them access
to a git repo.

By far the most common type of plagiarism is where one (well-meaning)
student give's another (well-meaning) student their submission so
that they can "have a look". The receiver may then face time
pressure, so despite the good intentions of all they end up using
some bits and pieces from the originator's submission.
Unfortunately, in such cases both students will be considered to
have plagiarised.


Getting Started
---------------

### Read this document

You have got to this point already. If you skipped to here, go back
and read the entire thing again.

### Get the source code

You can get the source code either by:

1. Downloading the zip file (see the link on the right hand side),
   which gives you a snapshot of the files in the repository.
 
2. Cloning the source code to your local directory, keeping the
   git information intact. You don't need a github account to do
   this, and your repository will be private.

3. Fork the code into your own repository. This assumes that you
   have your own account, and presumably the ability to keep
   that repository private. See the [Student Pack](https://education.github.com/pack)
   if you're interested in that direction.

While it is not required, I would highly recommend that you try
option 2 (I will use this route in class), and option 3 is even better.
It is good to get some experience of how source control works,
and acting as a consumer is a good way of understanding what is going on.
There are a number of GUI tools available which make things easier:

 - The github GUI is available for [Windows](https://windows.github.com/),
    [Mac](https://mac.github.com/).
    
 - There are third party GUI tools like [TortoiseGIT](https://code.google.com/p/tortoisegit/)
 
 - There is a default GUI called [git gui](https://www.kernel.org/pub/software/scm/git/docs/git-gui.html)
   from the main git people, that should be cross platform.

 - Or you can just use the command line. If you are only using git
   to get and update the code, then "git clone" and "git pull" are
   easy to use.

The submission itself is through blackboard as a zip, so there
is no requirement to use git. Even if I update the repository,
you can still just download the zip again and copy your current
work in - it is deliberately designed so that copying your
`src/<login>` directory into the updated source code will work.

### Read the source code

The source code is part of the specification, and is heavily
documented (it is much more important to document APIs than
it is to document implementation). Suggested reading order is:

 - `include/mips.h`
 - `include/mips_mem.h`
 - `include/mips_cpu.h`
 - `include/mips_test.h`

*Optional*: The comments follow the format for a well-known tool
called [doxygen](http://www.stack.nl/~dimitri/doxygen/). If you
apply doxygen to the file `doc/mips.doxygen`, then it will generate
some nice html formatted API documentation for you.

### Check you understand MIPS

The ISA we are using is a subset of the MIPS-1 (or MIPS-I)
instruction set in big endian mode. There is a lot of
discussion of MIPS in the course text book, and the MIPS
specification itself is available online, for example:
http://math-atlas.sourceforge.net/devel/assembly/mips-iv.pdf
There are multiple revisions or extensions of the instruction set,
so remember that we are only considering MIPS-1.

I think this is quite a nice break-down of the instructions,
but be careful about the details:
http://www.mrc.uidaho.edu/mrc/people/jff/digital/MIPSir.html

Another summarised version is the [QuickReference](https://www.lri.fr/~de/MIPS.pdf).
This one is particularly useful as it highlights the commonalities
between instructions, which both makes implementation clearer, and
helps to visualise how the hardware works.


Some Questions I've recieved
----------------------------

Note to 2016 students: I ran almost the same coursework
the last two years, so these are some questions from then. And
as I mentioned, I still have all of their
submissions in a readily accessible form should I choose
to diff them against this years submissions.

### What is the idea of splitting up the tests?

> I am confused about what we are expected to write in test_mips.cpp.
> In my experience, a test script executes the functions of the system
> it is testing and checks whether the output/state of the system was
> expected or not. My instinct would be to have a header file with a
> C++ function for each MIPS instruction defining the operations of
> the instruction, then in test_mips I would test those functions by
> calling them with various values to check they work properly. 
> 
> However, from reading the comments you left in the test_mips file
> you included, it seems like you want us to define the functionality
> of the different MIPS instructions in this file, which doesn't make
> it a test script to me.
> 
> Can you help clear up my confusion please?

The suggested approach, of decomposing the functionality into
multiple functions for each instruction then testing them
individually, makes perfect sense for the developer of a
particular MIPS implementation. I might choose to do that
during initial development of the CPU implementation, to
check the smallest components work. Equally, if I were building
a hardware cpu I would create test-benches for the ALU, where
there were different sets of waveforms which would cause
it to perform an add, a subtract, etc.

The problem is that even though the individual instruction
operations would be tested, we would not know whether they
are actually decoded correctly, whether interactions with
memory work correctly, whether it depends on a particular
kind of memory, whether each operation behaves correctly
if it appears after a jump, and so on.

So you are correct that the test_mips file should define the
functionality, but _only_ the functionality - it should say
nothing about the implementation of that functionality. If
you know the initial state of a MIPS, plus the memory it
is attached to, you should be able to predict precisely what
the effect of the next instruction executed should be. You could
do that prediction as a human, by reading the ISA spec and
thinking, or with the help of code, but it needs to be completely
seperate from the implementation being tested.

I could have mandated that you must implement one function
for each of the instructions, and put it in a header, but
then I would constrain any other implementer. Some people
may not want one function per operation, and there are good
reasons for doing that. Equally, it would now be impossible
to apply the test suite to a digital MIPS in a logic
simulator, as there is no equivalent way to implement
those functions in a digital implementation.

### Why is the pointer to mips_mem_read 8 bit?

> We need to read and write 32-bit values, but the argument to
> mips_mem_read is an 8-bit pointer. Do we need to cast it?

Yes, you need to cast to the type you want to read or write.

The minimum addressable unit for the memory is 8-bits, but
the block size (minimum transfer) for MIPS is 32-bits. So
you'll need to cast to and from the types you want to read
and write:

    uint32_t val;
    mips_error err=mips_mem_read(mem, 12, 4, (uint8_t*)&val);
    val=val+1;
    if(!err)
        err=mips_mem_write(mem, 12, 4, (uint8_t*)&val);

This should (I haven't compiled it) increment the 32-bit value
stored at byte address 12.

But... watch out for endianess!

I've put other examples in the documentation for mips_mem_write.

### How do I implement mips_mem_provider?

> How to define mips_mem_provider? I think that I need to set up an 
> array of 8 bit integers, and have a mips_cpu_h pointing to my CPU in 
> operation. My problem is that I am unsure how to choose an appropriate 
> initial size for the array given that the create_ram function decides 
> how large the array will be. Would I need to include the block size?

An implementation of mips_mem_provider is defined for you in the
`src/shared_mips_mem_ram.cpp` file, so you don't need to implement
that, just add it into the compilation (e.g. add as an existing
source file into eclipse).

As for memory size, you should create a RAM that is big enough
both to contain the instructions you want to test, and any
data that you want to be able to read/write (e.g. by LW or SW)
during those tests.

### What is the block size?

> What is the purpose of block size? As far as I can workout from the 
> comments in the code the block size is the smallest transfer one is able 
> to make, why does the limitation exist and is there a reason we should 
> pick a certain size?

The block size is equivalent to the number of bits in the address bus.
I've updated the documentation on mips_mem_create_ram to explain
this better.

### What exactly goes on inside mips_cpu_step?

> mips_error mips_cpu_step(mips_cpu_h state). Inside this function are 
> we looking to extract 32-bits from memory at a time, determine whether 
> it is an RIJ type, then pass on the appropriate segments of the 32 bit 
> words to a function that completes the operation, then continue 
> repeating the process until there is no longer anything left in memory?

Yes, for everything up to "continue repeating the process".
mips_cpu_step should fetch, decode, and execute just one
instruction, update its state, then return back to the caller.

If the caller wants to execute multiple instructions, they
must call mips_cpu_step once for each instruction.

### How is `mips_cpu_set_debug_level` supposed to be used?

It is really down to you - it can do nothing if you prefer. I've
updated the documentation for the function to give a
better idea why it might be useful.

## What is the point of `mips_cpu_get_pc`?

> Why is the mips_cpu_get_pc function necessary, can't you
> just get the value of the pc by doing state->pc, as you
> did in the skeleton file? 

You control the internals of the cpu state,
so on the `mips_cpu.cpp` side, you can totally
reach into `state->pc` and read it out. Or
you can use `mips_cpu_get_pc`. Either is fine,
because you are on the implementation side
of the API.

However, on the `mips_test.cpp` side you are not
allowed to know how or where the pc is stored,
so `mips_cpu_get_pc` exists in order to
allow the pc to be read from that side. I have
already written the code that will test your
CPU, and there is no way I could know whether
you will do:

    struct mips_cpu_impl{
      uint32_t pc;
      uint32_t regs[32];
    };

or

    struct mips_cpu_impl{
      uint32_t theseAreMyRegs[32];
      uint32_t thisIsMyPC;
    };

or something else.

But I do know that I can call `mips_cpu_get_pc`, and
no matter how or where you stored it I can find out
what the current PC is.
