/**
 * ARM Generic Interrupt Controller Driver
 */
#include "gic.h"
#include "kernel.h"
#include "mm.h"
#include "config.h"

#define GIC_INTERRUPT_COUNT 1024 /* a random guess lol */

static gic_distributor_registers *gic_dregs;
static gic_cpu_interface_registers *gic_ifregs;
static isr_t gic_handlers[GIC_INTERRUPT_COUNT];
static char *gic_names[GIC_INTERRUPT_COUNT];

void gic_init(void)
{
	uint32_t i;

	for (i = 0; i < GIC_INTERRUPT_COUNT; i++) {
		gic_handlers[i] = NULL;
		gic_names[i] = NULL;
	}

	gic_dregs = (gic_distributor_registers *)kmem_map_periph(
		CONFIG_GIC_DIST_BASE, 0x1000);
	gic_ifregs = (gic_cpu_interface_registers *)kmem_map_periph(
		CONFIG_GIC_IF_BASE, 0x1000);

	WRITE32(gic_ifregs->CCPMR, 0xFF); /* enable all interrupt priorities */
	WRITE32(gic_ifregs->CCTLR,
	        3u); /* enable interrupt forwarding to this cpu */
	WRITE32(gic_dregs->DCTLR, 3u); /* enable distributor */
}

void gic_enable_interrupt(uint8_t int_id)
{
	uint8_t reg32 = int_id >> 5;
	uint8_t bit32 = int_id & 0x1F;
	uint8_t reg8 = int_id >> 2;
	uint8_t bit8 = (int_id & 0x3) << 3;
	uint32_t reg_val;

	/*
	 * Write 1 to the set-enable bit for this interrupt. Note that it's a
	 * "set-enable" so writing zeros to the other bits is not a problem.
	 */
	WRITE32(gic_dregs->DISENABLER[reg32], (1 << bit32));

	/*
	 * For SPI interrupt IDs, we further need to set the target to CPU 0.
	 * For SGI/PPI interrupts, that's not necessary, and in fact the
	 * register could be RO, triggering a fault.
	 */
	if (int_id >= 32) {
		reg_val = READ32(gic_dregs->DITARGETSR[reg8]);
		reg_val &= ~(0xFF << bit8);
		reg_val |= 1 << bit8;
		WRITE32(gic_dregs->DITARGETSR[reg8], reg_val);
	}
}

uint32_t gic_interrupt_acknowledge(void)
{
	return gic_ifregs->CIAR;
}

void gic_end_interrupt(uint32_t int_id)
{
	WRITE32(gic_ifregs->CEOIR, int_id);
}

void gic_register_isr(uint32_t intid_start, uint32_t intid_count, isr_t isr,
                      char *name)
{
	uint8_t i;
	for (i = 0; i < intid_count; i++) {
		gic_handlers[intid_start + i] = isr;
		gic_names[intid_start + i] = name;
	}
}

isr_t gic_get_isr(uint32_t intid)
{
	return gic_handlers[intid];
}

char *gic_get_name(uint32_t intid)
{
	return gic_names[intid];
}
