/*  Pcsx2 - Pc Ps2 Emulator
 *  Copyright (C) 2002-2008  Pcsx2 Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#include "PrecompiledHeader.h"

#include "Common.h"
#include "InterTables.h"
#include "ix86/ix86.h"
#include "iR5900.h"
#include "iMMI.h"
#include "iFPU.h"
#include "iCP0.h"
#include "VUmicro.h"
#include "iVUmicro.h"
#include "iVUops.h"
#include "VUops.h"

#include "iVUzerorec.h"

namespace Dynarec
{
void recExecuteVU0Block( void )
{
	if((VU0.VI[REG_VPU_STAT].UL & 1) == 0) {
		//SysPrintf("Execute block VU0, VU0 not busy\n");
		return;
	}

	//while( (VU0.VI[ REG_VPU_STAT ].UL&1) ) {
		if( CHECK_VU0REC) {		
			FreezeXMMRegs(1);
			SuperVUExecuteProgram(VU0.VI[ REG_TPC ].UL & 0xfff, 0);
			FreezeXMMRegs(0);
		}
		else ::R5900::Interpreter::intExecuteVU0Block();
	//}
}

void recClearVU0( u32 Addr, u32 Size )
{
	if( CHECK_VU0REC ) {
		SuperVUClear(Addr, Size*4, 0);
	}
}

void recResetVU0( void )
{
	SuperVUReset(0);
}

}