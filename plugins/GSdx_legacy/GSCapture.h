/*
 *	Copyright (C) 2007-2009 Gabest
 *	http://www.gabest.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with GNU Make; see the file COPYING.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#pragma once

#include "GSVector.h"
#include "GSPng.h"

#ifdef _WIN32
#include "GSCaptureDlg.h"
#endif

class GSCapture
{
	std::recursive_mutex m_lock;
	bool m_capturing;
	GSVector2i m_size;
	uint64 m_frame;
	std::string m_out_dir;
	int m_threads;

	#ifdef _WIN32

	CComPtr<IGraphBuilder> m_graph;
	CComPtr<IBaseFilter> m_src;

	#elif __linux__

	vector<GSPng::Worker*> m_workers;
	int m_compression_level;

	#endif

public:
	GSCapture();
	virtual ~GSCapture();

	bool BeginCapture(float fps, GSVector2i recomendedResolution, float aspect);
	bool DeliverFrame(const void* bits, int pitch, bool rgba);
	bool EndCapture();

	bool IsCapturing() {return m_capturing;}
	GSVector2i GetSize() {return m_size;}
};
