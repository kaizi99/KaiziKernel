#pragma once

typedef struct
{
    void* base;
    uint16_t limit;
    uint8_t type;
} GDTEntry;

void encodeGDTEntry(uint8_t* target, GDTEntry source);
void createDataSegment(uint16_t limit, uint16_t base);
void createCodeSegment(uint16_t limit, uint16_t base);

// Defined in gdt.s
extern void loadGDT(GDT* gdtAddress);