// File.asm

if {defined __CE__} {
if !{defined __FILE__} {
define __FILE__()
print "included File.asm\n"


// @ Description
// DMA copy of filetable entires (.bin) into RAM @ 0x800D6310
constant unk_1_(0x800CD814)

// Filetable start
// 0x1AC870	in ROM

// Filetable entry length
// 0xC

// Filetable entry format
// ABBBBBBB CCCCDDDD EEEEFFFF
// A - ?0000000, ? =  bool isCompressed
// B - offset from end of file table (hardcoded ROM address, 0x1B2C6C)
// C - filetabl_offset / 4
// D - compressed_size / 4
// E - resource_offset / 4
// F - decompressed_size / 4

// 0xFFFF (aka -1) is used when a field is empty (applies to C and E)

} // __FILE__
} // __CE__

// file shit
// 1B2C6C - old file table end
// 1B33FC - new file table end
// 