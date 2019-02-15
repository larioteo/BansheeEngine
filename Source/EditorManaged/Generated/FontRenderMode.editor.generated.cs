//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//************** Copyright (c) 2016-2019 Marko Pintera (marko.pintera@gmail.com). All rights reserved. *******************//
using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using BansheeEngine;

namespace BansheeEditor
{
	/** @addtogroup Text
	 *  @{
	 */

	/// <summary>Determines how is a font rendered into the bitmap texture.</summary>
	public enum FontRenderMode
	{
		Smooth = 0,
		Raster = 1,
		HintedSmooth = 2,
		HintedRaster = 3
	}

	/** @} */
}
