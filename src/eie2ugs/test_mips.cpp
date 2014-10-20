#include "mips_test.h"

int main()
{
	mips_mem_h mem=mips_mem_create_ram(
		1<<20,
		4
		);

	mips_cpu_h cpu=mips_cpu_create(mem);

	mips_test_begin_suite();

	int testId=mips_test_begin_test("and");
	int passed=0;

	
	mips_error err = mips_cpu_set_register(cpu, 8, 0x0000FFFFul);
	if(err==0)
		err = mips_cpu_set_register(cpu, 9, 0x00FFFF00ul);

	// and $10, $8, $9

	// TODO : work out the bit-wise encoding for the instruction.

	// TODO : Write it into mempory at a known address

	// TODO : Make sure the program-counter is at that address

	if(err==0)
		err=mips_cpu_step(cpu);

	uint32_t got;
	if(err==0)
		err = (mips_error)(err | mips_cpu_get_register(cpu, 10, &got));

	passed = (err == mips_Success) && (got==0x0000FF00);

	mips_test_end_test(testId, passed, NULL);

	mips_test_end_suite();

	mips_cpu_free(cpu);
	mips_mem_free(mem);

	return 0;
}