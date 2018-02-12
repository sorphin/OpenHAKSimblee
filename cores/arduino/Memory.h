/*
 * Copyright (c) 2015 RF Digital Corp. All Rights Reserved.
 *
 * The source code contained in this file and all intellectual property embodied in
 * or covering the source code is the property of RF Digital Corp. or its licensors.
 * Your right to use this source code and intellectual property is non-transferable,
 * non-sub licensable, revocable, and subject to terms and conditions of the
 * SIMBLEE SOFTWARE LICENSE AGREEMENT.
 * http://www.simblee.com/licenses/SimbleeSoftwareLicenseAgreement.txt
 *
 * THE SOURCE CODE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND.
 *
 * This heading must NOT be removed from this file.
 */

/*
The Simblee contains 256KB of usable flash memory organized into 256 1K pages.
An entire 1K pages has to be erased before it can be written too.  The flash
resets the page to all 0xff.  The flash is rated for 10,000 erase/write cycles.

The first 123 pages of flash contain the RFDSTACK, and should never be erased.
Pages 252 thru 255 are reserved for the stack data storage.

Pages 124 through 251 are open and available for use, however, your sketch also
occupies flash memory (starting from Page 124), so it is recommended that you
start using flash pages from 251 downwards.

The flash functions below ensure that reserved pages are not written too, and
that your sketch is not erased or overwritten.

Following is the memory layout of the Simblee:

// flash:
// 00000 - 1EFFF -> RFDSTACK
// 1F000 - 3EFFF -> application and flash space (flash page 124 to 251)
// 3F000 - EFFFF -> stack data storage

// ram:
// 20000000 - 20001FFF -> stack RAM storage
// 20002000 - 20003FFF -> application RAM storage
*/

#ifndef Memory_h
#define Memory_h

#ifdef __cplusplus
extern "C" {
#endif

// divide the address by 1024
#define  PAGE_FROM_ADDRESS(address)  ((uint8_t)((uint32_t)address >> 10))

// multiple the page by 1024
#define  ADDRESS_OF_PAGE(page)  ((uint32_t*)(page << 10))

// generated by Simblee.ld linker script
extern uint32_t _sfixed;
extern uint32_t _efixed;
extern uint32_t _etext;
extern uint32_t _srelocate;
extern uint32_t _erelocate;
extern uint32_t _etextrelocate;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _sstack;
extern uint32_t _estack;
extern uint32_t _end;
extern uint32_t _sflash;
extern uint32_t _eflash;

// return the amount of RAM being used by the sketch
extern int ramUsed(void);

// return the amount of FLASH being used by the sketch
extern int flashUsed(void);

// erase 1K flash page
// inputs:
//   page: must be between 124 and 251
// returns;
//   0 = success
//   1 = reserved page (< 124 or >251)
//   2 = page contains sketch
int flashPageErase( uint8_t page );

// write to a 1K flash page that has been previously erased
// returns:
//   0 = success
//   1 = reserved page (< 124 or >251)
//   2 = page contains sketch
int flashWrite( uint32_t *address, uint32_t value );

// write to a 1K flash page a block cb bytes long from src to dst
int flashWriteBlock( void *dst, const void *src, int cb );

#ifdef __cplusplus
}
#endif

#endif // Memory_h