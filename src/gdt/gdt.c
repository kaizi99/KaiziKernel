#include "gdt.h"

// Make room for 8 descriptors
uint8_t GDT[8*8];
uint8_t current = 0;

// From http://wiki.osdev.org/GDT_Tutorial
void encodeGDTEntry(uint8_t* target, GDTEntry source);
{
    // Check the limit to make sure that it can be encoded
    if ((source.limit > 65536) && (source.limit & 0xFFF) != 0xFFF)) {
        target = NULL;
        return;
    }
    if (source.limit > 65536) {
        // Adjust granularity if required
        source.limit = source.limit >> 12;
        target[6] = 0xC0;
    } else {
        target[6] = 0x40;
    }
 
    // Encode the limit
    target[0] = source.limit & 0xFF;
    target[1] = (source.limit >> 8) & 0xFF;
    target[6] |= (source.limit >> 16) & 0xF;
 
    // Encode the base 
    target[2] = source.base & 0xFF;
    target[3] = (source.base >> 8) & 0xFF;
    target[4] = (source.base >> 16) & 0xFF;
    target[7] = (source.base >> 24) & 0xFF;
 
    // And... Type
    target[5] = source.type;
}

void createDataSegment(uint16_t limit, uint16_t base)
{
    GDTEntry entry;
    entry.base = base;
    entry.limit = limit;
    entry.type = 0x92;
    
    encodeGDTEntry(GDT + (current * 8), entry);

    current++;
}

void createCodeSegment(uint16_t limit, uint16_t base)
{
    GDTEntry entry;
    entry.base = base;
    entry.limit = limit;
    entry.type = 0x9A;
    
    encodeGDTEntry(GDT + (current * 8), entry);

    current++;
}