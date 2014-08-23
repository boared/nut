/** 
 * \file ArchitectureInfo.h
 * \brief Here you can get information about compiler, CPU architecture, machine
 * parameters, etc.
 * 
 * @author: Eder A. Perez.
 */

#ifndef __ARCHITECTUREINFO_H__
#define __ARCHITECTUREINFO_H__

#undef NUT_X86
#undef NUT_X64



// If the target architecture is x86
#if defined(_M_IX86) || defined(_X86_)

    #define NUT_X86

// If the target architecture is x64
#elif defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__)

    #define NUT_X64

#endif



#endif // __ARCHITECTUREINFO_H__
