/*
 * GlobalConfig.h
 *
 *  Created on: Sep 7, 2014
 *      Author: root
 */

#ifndef GLOBALCONFIG_H_
#define GLOBALCONFIG_H_

#include <climits>
#include <sys/types.h>
#include <stdint.h>

using namespace std;

enum TIDS
{
	FREETID = 0,
	INVALIDTID = (int)((uint)(0 -1)), //TODO: Replaced by INT_MAX
};


enum CELLBLOCKCONSTS
{
	BLOCKHEADLEN = sizeof(int) + sizeof(int),
	CELLLEN = 1024 - BLOCKHEADLEN,
	CELLSIZE = 16,
	GLOBALBLOCKSIZE = 1024,
	GLOBALBLOCKMASK = GLOBALBLOCKSIZE - 1,
	BLOCKSIZE = 16,
	SIBLINGSIZE = BLOCKSIZE - 1,
	SIBLINGMASK = SIBLINGSIZE,
	BLOCKMAGICNUM = (int)(0xfefefefe),
	TOTALBLOCKSIZE = GLOBALBLOCKSIZE * BLOCKSIZE,
	GLOBALFREELISTSIZE = TOTALBLOCKSIZE,
	GLOBALFREELISTMASK = GLOBALFREELISTSIZE - 1,

	CELLCURRTIDMASK = (int)((uint)(0 -1)),
	CELLLASTTIDMASK = (int)((uint(0 - 1))) - CELLCURRTIDMASK,
	CELLLASTTIDSHIFT = sizeof(ushort) * 8,
};

enum STORAGECONSTS
{
	GLOBALCELLSIZE = GLOBALBLOCKSIZE  * CELLSIZE,
	GLOBALQUESIZE = 512,
	GLOBALAPPSIZE = GLOBALQUESIZE,
	GLOBALQUECAP = 64,
	GLOBALQUEMASK = GLOBALQUECAP - 1,
	GLOBALLOCALLISTSIZE = 1024,
	GLOBALLOCALLISTMASK = GLOBALLOCALLISTSIZE - 1,

	GLOBALLOCALINDXNUM = GLOBALQUESIZE,

	SUSPECTALLOCTIDSNUM = GLOBALCELLSIZE / 1024,

	GLOBALAPPNUM = GLOBALQUESIZE,
};

enum GLOBALFREELISTCONSTS
{
	CACHESIZE = 4,
	CACHEMASK = CACHESIZE - 1,
};
enum QUESLOTSTAT
{
	FREESLOT = 0xffffffff,
};

enum CELLFLAG
{
	FREECELL = 0,
	DELCELL = UINT_MAX,
	INVALIDCELL = UINT_MAX - 1,
};

enum APPCONSTS
{
	INVALIDAPPID = -1,
};

enum CMMQCONSTS
{
	INVALIDQID = -1,
};

//enum IndexConsts
//{
//	DATAMASK = USHRT_MAX,
//	COUNTERMASK = UINT_MAX - USHRT_MAX,
//	DATASTEP = 1,
//	COUNTERSTEP = (USHRT_MAX) + 1,
//	FREEDATA = DATAMASK,
//};

enum IndexConsts
{
	DATAMASK = UINT_MAX,
	COUNTERMASK = ULONG_MAX - UINT_MAX,
	DATASTEP = 1,
	COUNTERSTEP = COUNTERMASK & (UINT_MAX + 1L),
	FREEDATA = DATAMASK,
};

class GlobalConfig
{
public:
	inline static bool IsValidCell(int cellId) {return cellId >= 0 && cellId < GLOBALCELLSIZE;};
	inline static bool IsValidAppId(int appId) { return appId >= 0 && appId < GLOBALAPPNUM; };
	inline static bool IsValidQId(int cmmQId) {return cmmQId >= 0 && cmmQId < GLOBALQUESIZE; };
	inline static bool IsValidTCIndex(int index) {return index >= 0 && index < GLOBALLOCALINDXNUM; };
	inline static bool IsEmptySlot(const volatile ulong data) { return (data & DATAMASK) == FREEDATA;	};
	inline static ulong NextCounter(const volatile ulong counter) {return ((counter & COUNTERMASK) + COUNTERSTEP);};
	inline static bool IsFreeTid(uint tid) {return (tid & CELLCURRTIDMASK) == FREETID; }

	inline static int GetFreeListCellIndex(const ulong freeListCellId)
	{
		return freeListCellId & DATAMASK;
	}
};

static inline uint64_t
rte_rdtsc(void)
{
	union {
		uint64_t tsc_64;
		struct {
			uint32_t lo_32;
			uint32_t hi_32;
		};
	} tsc;

	asm volatile("rdtsc" :
		     "=a" (tsc.lo_32),
		     "=d" (tsc.hi_32));
	return tsc.tsc_64;
}

#endif /* GLOBALCONFIG_H_ */
