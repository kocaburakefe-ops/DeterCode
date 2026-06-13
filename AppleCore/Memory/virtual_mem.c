#include <stdio.h>
#include <mach/mach.h>

void allocate_mach_memory() {
    mach_port_t task = mach_task_self();
    vm_address_t address;
    
    // Mach kernel seviyesinde 16KB temiz bellek sayfası talep et
    if (vm_allocate(task, &address, 16384, VM_FLAGS_ANYWHERE) == KERN_SUCCESS) {
        printf("[DeterCode::MachVM] Çekirdek seviyesinde bellek ayrıldı: 0x%lx\n", address);
    }
}

