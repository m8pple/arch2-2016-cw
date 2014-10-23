/*! \file mips_mem.h
    Defines the functions used to interact with simulated memory.
    
    Note that the notions of "memory/address space" and "RAM" are actually
    two related but distinct things (we will explore this more later).
    A memory space is some kind of addressable space that the CPU can
    read and write to, where addressable locations are identified by
    integers. For the moment we will only deal with one address space,
    but later on we'll see others. In this API, abstract memory spaces
    are accessed using the functions in \ref mips_mem_core, but they
    must be intially created using a device specific API from \ref mips_mem_devices.
    
    RAM is a particular kind of memory device, which maps reads and
    writes transactions at particular addresses to corresponding
    storage locations. ROM is another kind of memory device that you
    saw earlier. It is extremely common for multiple types of memory
    device to exist in one address space, but for now we will stick
    with the simple idea of having one RAM, which is created using mips_mem_create_ram.
*/
#ifndef mips_mem_header
#define mips_mem_header

#include "mips_core.h"

/* This allows the header to be used from both C and C++, so
programs can be written in either (or both) languages. */
#ifdef __cplusplus
extern "C"{
#endif
    
/*! \defgroup mips_mem Memory
    \addtogroup mips_mem
    @{
    
    \defgroup mips_mem_core Abstract Memory Interface
    \addtogroup mips_mem_core
    @{
*/

/*! Represents some sort of memory, but without saying
anything about how it is represented. See \ref mips_mem_h.

\struct mips_mem_provider    
*/
struct mips_mem_provider;

/*! An opaque handle to a memory space.

    We can pass this around without knowing who or what provides the
    memory. This is an example of an "opaque data type" http://en.wikipedia.org/wiki/Opaque_data_type
    and is commonly used in embedded systems and operating
    systems. An example you might have come across includes the
    FILE data-type used by fopen and fprintf in the C standard
    library.

    Because this is a pointer, we can safely give it the
    known value of 0 or NULL in order to get a known empty
    state. For example:
        
        mips_mem_h myMem=0; // Declare an empty handle
        
        if(some_condition)
            myMem=get_a_handle();
        
        if(myMem)
            do_something_with mem(myMem);
    
    So even without knowing what the data-structure is, we can still
    tell whether or not a handle is currently pointing at a
    data-structure.
*/
typedef struct mips_mem_provider *mips_mem_h;


/*! Perform a read transaction on the memory
    
    The implementation is expected to check that the transaction
    matches the alignment and block size requirements, and return an
    error if they are violated.
    
    See \ref mips_mem_write for more detailed discussion of its use.
*/
mips_error mips_mem_read(
    mips_mem_h mem,		//!< Handle to target memory
    uint32_t address,	//!< Byte address to start transaction at
    uint32_t length,	//!< Number of bytes to transfer
    uint8_t *dataOut	//!< Receives the target bytes
);

/*! Perform a write transaction on the memory
    
    The implementation is expected to check that the transaction
    matches the alignment and block size requirements, and return an
    error if they are violated.
    
    The input pointer is a pointer to bytes, because the RAM is byte
    addressable, however the transaction size may consist of multiple
    bytes - indeed, for memories with a block size greater than one,
    all transactions must be multiple bytes. To write a larger piece
    of data, you can use pointer casting, or pass in an array. For
    example, if I want to write 0xFF001100 to address 12, I could do:
    
        uint32_t xv=0xFF001100;
        mips_error err=mips_mem_write(mem, 12, 4, (uint8_t*)&xv);
    
    alternatively, I could do:
    
        uint8_t xa[4];
        xa[0]=0x00;
        xa[1]=0x11;
        xa[2]=0x00;
        xa[3]=0xFF;
        mips_error err=mips_mem_write(mem, 12, 4, xa); 

    or more succinctly:
    
        uint8_t xa[4];
        xa[0]={0x00, 0x11, 0x00, 0xFF};
        mips_error err=mips_mem_write(mem, 12, 4, xa); 
    
    In the second two cases xa is an array of uint8_t, so can also be
    used as a pointer of type `uint8_t *`.
    
    This example assumes a little-endian architecture, such as x86. If
    the architecture running the  code was big-endian, the first example
    would need to be changed to:
    
        uint32_t xv=0x001100FF;
        mips_error err=mips_mem_write(mem, 12, 4, (uint8_t*)&xv);

    MIPS is a bi-endian architecture (like ARM), which can be configured
    to run in either little-endian or big-endian mode. The hardware translates
    on the fly (after all, endianess conversion is just re-ordering the bytes).
    
    For this work, we will have a little-endian (x86) processor running the
    simulator, but the thing being simulated (MIPS) is big-endian.
*/
mips_error mips_mem_write(
    mips_mem_h mem,	        //!< Handle to target memory
    uint32_t address,	    //!< Byte address to start transaction at
    uint32_t length,	    //!< Number of bytes to transfer
    const uint8_t *dataIn	//!< Receives the target bytes
);


/*! Release all resources associated with memory. The caller doesn't
    really know what is being released (it could be memory, it could
    be file handles), and shouldn't care. Calling mips_mem_free on an
    empty (zero) handle is legal. Calling mips_mem_free twice on the
    same non-empty handle is illegal, and the resulting behaviour is undefined
    (most likely a crash).
    
    A pattern that can be useful is:
    
        mips_mem_h h=0; // Initialise it to empty
        ...
        h=some_creator_function(...);
        ...
        use_memory_somehow(h);
        ...
        if(h){
            mips_mem_free(h);
            h=0; // Make sure it is never freed again
        }
*/
void mips_mem_free(mips_mem_h mem);

/*! @} */


/*! \defgroup mips_mem_devices Concrete Memory Devices
    \ingroup mips_mem_devices
    @{
*/

/*! Initialise a new RAM of the given size.

    The RAM will expect transactions to be at the granularity
    of the blockSize. This means any reads or writes must be aligned
    to the correct blockSize, and should consist of an integer number
    of blocks. For example, choosing blockSize=4 would result in a RAM
    that only supports aligned 32-bit reads and writes.
    
    You can think of the blockSize as being equivalent to the number
    of wires in the data-bus of the memory. If the only wires you
    have are readEnable, writeEnable, address, dataIn, and dataOut,
    then within one cycle you could do a write by asserting writeEnable=1,
    specifying the address, and driving the data to be written onto dataIn.
    Or you could perform a read by asserting readEnable=1, driving the
    address bus, and looking at the value that the RAM drives onto dataOut.
    If blockSize=4, then we would have 32 wires for both dataIn and dataOut,
    and any address would need to have the two least significant bits as zero.
    
    In MIPS the basic unit of transfer is 32-bits, so the granularity of the
    data bus is also 32-bits, and blockSize must be 4.
    
    "Why do we even have this blockSize if it is always 4?" : It is in
    anticipation of a future extension, and a mistake on my part (from
    a teaching point of view). I should have given it the simpler signature of:
    
        mips_mem_h mips_mem_create_ram(uint32_t cbMem);
    
    and stated that it creates a RAM of the given size with a granularity of 4.
    
    "How can MIPS do SH (store half) efficiently if this is the case?" - An
    actual MIPS implementation would have what are called "byte-enables",
    which are extra signals saying which bytes within the data bus are
    valid, but I didn't include them in the API as they complicate things.
*/
mips_mem_h mips_mem_create_ram(
    uint32_t cbMem,	//!< Total number of bytes of ram
    uint32_t blockSize	//!< Granularity of transactions supported by RAM
);

/*!
    @}
    @}
*/


#ifdef __cplusplus
};
#endif

#endif
