using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace BansheeEngine
{
	/** @addtogroup GUIEditor
	 *  @{
	 */

	/// <summary>Controls which elements should a GUICurves object draw.</summary>
	public enum CurveDrawOptions
	{
		/// <summary>Draws markers at specific time intervals.</summary>
		DrawMarkers = 1,
		/// <summary>Draws elements representing individual keyframes.</summary>
		DrawKeyframes = 2,
		/// <summary>Draws curves and the area between them. Only relevant if only two curves are provided for drawing.</summary>
		DrawRange = 4
	}

	/** @} */
}
