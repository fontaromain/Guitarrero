// Copyright (C) 2002-2008 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __I_IRRLICHT_CREATION_PARAMETERS_H_INCLUDED__
#define __I_IRRLICHT_CREATION_PARAMETERS_H_INCLUDED__

#include "EDriverTypes.h"
#include "dimension2d.h"

namespace irr
{
	class IEventReceiver;


	// Str to in
	static int convertToInt(irr::core::stringc str)
	{	
		int value = 0 ;
		
		for (int i = 0 ; i < str.size() ; i++)
		{
			int toAdd = str[i] - 48 ;
			for (int j = str.size()-1 ; j > i ; j--){ toAdd *= 10 ;}
			value += toAdd ;
		}
	
		return value ;
	}

	//! Structure for holding Irrlicht Device creation parameters.
	/** This structure is used in the createDeviceEx() function. */
	struct SIrrlichtCreationParameters
	{
		//! Constructs a SIrrlichtCreationParameters structure with default values.
		SIrrlichtCreationParameters() :
			DriverType(video::EDT_OPENGL),
			WindowSize(core::dimension2d<s32>(800, 600)),
			Bits(32),
			ZBufferBits(16),
			Fullscreen(false),
			Stencilbuffer(false),
			Vsync(false),
			AntiAlias(false),
			WithAlphaChannel(false),
			IgnoreInput(false),
			HighPrecisionFPU(false),
			EventReceiver(0),
			WindowId(0),
			SDK_version_do_not_use(IRRLICHT_SDK_VERSION)
		{
		}

		SIrrlichtCreationParameters(const SIrrlichtCreationParameters& other) :
			SDK_version_do_not_use(IRRLICHT_SDK_VERSION)
		{*this = other;}

		SIrrlichtCreationParameters& operator=(const SIrrlichtCreationParameters& other)
		{
			DriverType = other.DriverType;
			WindowSize = other.WindowSize;
			Bits = other.Bits;
			ZBufferBits = other.ZBufferBits;
			Fullscreen = other.Fullscreen;
			Stencilbuffer = other.Stencilbuffer;
			Vsync = other.Vsync;
			AntiAlias = other.AntiAlias;
			WithAlphaChannel = other.WithAlphaChannel;
			IgnoreInput = other.IgnoreInput;
			HighPrecisionFPU = other.HighPrecisionFPU;
			EventReceiver = other.EventReceiver;
			WindowId = other.WindowId;			
			return *this;
		}

		video::E_DRIVER_TYPE DriverType;
		core::dimension2d<s32> WindowSize;
		u8 					Bits;
		u8 					ZBufferBits;
		bool 				Fullscreen;
		bool				Stencilbuffer;
		bool 				Vsync;
		bool 				AntiAlias;
		bool 				WithAlphaChannel;
		bool 				IgnoreInput;
		bool 				HighPrecisionFPU;
		IEventReceiver* 	EventReceiver;
		void* 				WindowId;
		const c8* const 	SDK_version_do_not_use;
	};
}

#endif
