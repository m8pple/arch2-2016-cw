#include "mips.h"

#include <stdlib.h>

struct mips_cpu_impl{

	uint32_t pc;
	uint32_t pcN;
	uint32_t regs[32];

	mips_mem_h mem;
};

mips_cpu_h mips_cpu_create(mips_mem_h mem)
{
	unsigned i;
	mips_cpu_h res=(mips_cpu_h)malloc(sizeof(struct mips_cpu_impl));

	res->mem=mem;

	res->pc=0;
	res->pcN=4;	// NOTE: why does this make sense?

	for( i=0;i<32;i++){
		res->regs[i]=0;
	}

	return res;
}

void mips_cpu_free(mips_cpu_h state)
{
	free(state);
}

mips_error mips_cpu_get_register(
	mips_cpu_h state,	//!< Valid (non-empty) handle to a CPU
	unsigned index,		//!< Index from 0 to 31
	uint32_t *value		//!< Where to write the value to
)
{
	if(state==0)
		return mips_ErrorInvalidHandle;
	if(index>=32)
		return mips_ErrorInvalidArgument;
	if(value==0)
		return mips_ErrorInvalidArgument;

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
	if(state==0)
		return mips_ErrorInvalidHandle;
	if(index>=32)
		return mips_ErrorInvalidArgument;

	// TODO : What about register zero?
	state->regs[index]=value;

	return mips_Success;
}

mips_error mips_cpu_step(mips_cpu_h state)
{
	uint32_t pc=state->pc;

	if(state==0)
		return mips_ErrorInvalidHandle;

	//TODO: Here is where the magic happens
	// - Fetch the instruction from memory (mips_mem_read)
	// - Decode the instruction (is it R, I, J)?
	// - Execute the instruction (do maths, access memory, ...)
	// - Writeback the results (update registers, advance pc)

	return mips_ErrorNotImplemented;
}
