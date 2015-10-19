#include "mips.h"

struct mips_cpu_impl
{
    uint32_t pc;
    uint32_t pcNext;
    
    uint32_t regs[32];
    
    mips_mem_h mem;
    
    unsigned logLevel;
    FILE *logDst;
};


mips_error mips_cpu_get_register(
	mips_cpu_h state,	//!< Valid (non-empty) handle to a CPU
	unsigned index,		//!< Index from 0 to 31
	uint32_t *value		//!< Where to write the value to
)
{
    // TODO : error handling
    *value = state->regs[index];
    return mips_Success;
}

/*! Modifies one of the 32 general purpose MIPS registers. */
mips_error mips_cpu_set_register(
	mips_cpu_h state,	//!< Valid (non-empty) handle to a CPU
	unsigned index,		//!< Index from 0 to 31
	uint32_t value		//!< New value to write into register file
)
{
    // TODO : error handling
    state->regs[index] = value;
    return mips_Success;
}

mips_error mips_cpu_set_debug_level(mips_cpu_h state, unsigned level, FILE *dest)
{
    state->logLevel = level;
    state->logDst = dest;
    return mips_Success;
}

mips_cpu_h mips_cpu_create(mips_mem_h mem)
{
    mips_cpu_impl *cpu=new mips_cpu_impl;
    
    cpu->pc=0;
    for(int i=0;i<32;i++){
        cpu->regs[i]=0;
    }
    cpu->mem=mem;
    
    return cpu;
}

/*! \param pData Array of 4 bytes
    \retval The big-endian equivlent
*/
uint32_t to_big(const uint8_t *pData)
{
    return
        (((uint32_t)pData[0])<<24)
        |
        (((uint32_t)pData[1])<<16)
        |
        (((uint32_t)pData[2])<<8)
        |
        (((uint32_t)pData[3])<<0);
}

mips_error mips_cpu_step(
	mips_cpu_h state	//! Valid (non-empty) handle to a CPU
)
{
    uint8_t buffer[4];
    
    mips_error err=mips_mem_read(
        state->mem,		//!< Handle to target memory
        state->pc,	//!< Byte address to start transaction at
        4,	//!< Number of bytes to transfer
        buffer	//!< Receives the target bytes
    );
    
    if(err!=0){
        return err;
    }
    
    uint32_t instruction= to_big(buffer);
    
    uint32_t opcode =  (instruction>>26) & 0x3F;
    uint32_t src1 = (instruction>> 21 ) & 0x1F;
    uint32_t src2 = (instruction>> 16 ) & 0x1F;   
    uint32_t dst = (instruction>> 11 ) & 0x1F;    
    uint32_t shift = (instruction>> 6 ) & 0x1F ;
    uint32_t function = (instruction>> 0 ) & 0x3F ;

    if(opcode == 0){
        // This is R-type
        if(state->logLevel >= 2){
            fprintf(state->logDst, "R-Type : dst=%u, src1=%u, src2=%u, shift=%u, function=%u.\n  instr=%08x\n",
                dst, src1, src2, shift, function, instruction
            );
        }
        
        if(function ==  0x21){
            if(state->logLevel >= 1){
                fprintf(state->logDst, "addu %u, %u, %u.\n", dst, src1, src2);
            }
            uint32_t va=state->regs[src1];
            uint32_t vb=state->regs[src2];
            
            uint32_t res=va+vb;
            
            state->regs[dst] = res; // NOTE: what about zero reg?
            
            // NOTE : What about updating the program counter
            return mips_Success;
        }else{
            return mips_ErrorNotImplemented;
        }
    }else{
        return mips_ErrorNotImplemented;
    }
}
