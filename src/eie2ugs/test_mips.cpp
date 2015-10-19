#include "mips.h"

int main()
{
    mips_mem_h mem=mips_mem_create_ram(4096, 4);
    
    mips_cpu_h cpu=mips_cpu_create(mem);
    
    mips_error e=mips_cpu_set_debug_level(cpu, 4, stderr);
    if(e!=mips_Success){
        fprintf(stderr, "mips_cpu_set_debug_level : failed.\n");
        exit(1);
    }
    
    
    mips_test_begin_suite();


    int testId = mips_test_begin_test("addu");    
    
    // 1 - Setup an instruction in ram
    // addu r3, r4, r5
    uint32_t instr =
        (0ul << 26) // opcode = 0
        |
        (4ul << 21) // srca = r4
        |
        (5ul << 16) // srcb = r5
        |
        (3ul << 11) // dst = r3
        |
        (0ul << 6) // shift = 0
        |
        (0x21 << 0);
    
    uint8_t buffer[4];
    buffer[0]=(instr>>24)&0xFF;
    buffer[1]=(instr>>16)&0xFF;
    buffer[2]=(instr>>8)&0xFF;
    buffer[3]=(instr>>0)&0xFF;
    
    e=mips_mem_write(
        mem,	        //!< Handle to target memory
        0,	            //!< Byte address to start transaction at
        4,	            //!< Number of bytes to transfer
        buffer	        //!< Receives the target bytes
    );
    if(e!=mips_Success){
        fprintf(stderr, "mips_mem_write : failed.\n");
        exit(1);
    }
    
    // 2 - put register values in cpu
    e=mips_cpu_set_register(cpu, 4, 40);
    e=mips_cpu_set_register(cpu, 5, 50);
    
    // 3 - step CPU
    e=mips_cpu_step(cpu);
    if(e!=mips_Success){
        fprintf(stderr, "mips_cpu_step : failed.\n");
        exit(1);
    }
    
    // 4 -Check the result
    uint32_t got;
    e=mips_cpu_get_register(cpu, 3, &got);
    
   
    int passed = got == 40+50;
    
    mips_test_end_test(testId, passed, "50 + 50 != 90");
    
    
    testId = mips_test_begin_test("addu");    
    
    // 1 - Setup an instruction in ram
    // addu r3, r4, r5
    instr =
        (0ul << 26) // opcode = 0
        |
        (4ul << 21) // srca = r4
        |
        (5ul << 16) // srcb = r5
        |
        (0ul << 11) // dst = r0
        |
        (0ul << 6) // shift = 0
        |
        (0x21 << 0);
    
    buffer[0]=(instr>>24)&0xFF;
    buffer[1]=(instr>>16)&0xFF;
    buffer[2]=(instr>>8)&0xFF;
    buffer[3]=(instr>>0)&0xFF;
    
    e=mips_mem_write(
        mem,	        //!< Handle to target memory
        0,	            //!< Byte address to start transaction at
        4,	            //!< Number of bytes to transfer
        buffer	        //!< Receives the target bytes
    );
    if(e!=mips_Success){
        fprintf(stderr, "mips_mem_write : failed.\n");
        exit(1);
    }
    
    // 2 - put register values in cpu
    e=mips_cpu_set_register(cpu, 4, 40);
    e=mips_cpu_set_register(cpu, 5, 50);
    
    // 3 - step CPU
    e=mips_cpu_step(cpu);
    if(e!=mips_Success){
        fprintf(stderr, "mips_cpu_step : failed.\n");
        exit(1);
    }
    
    // 4 -Check the result
    e=mips_cpu_get_register(cpu, 0, &got);
    
   
    passed = got == 0;
    
    mips_test_end_test(testId, passed, "r0 <> 0");
    
    
    
    mips_test_end_suite();
    
    return 0;
}
