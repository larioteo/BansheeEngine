using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using BansheeEngine;

namespace BansheeEditor
{
	/** @addtogroup GUIEditor
	 *  @{
	 */

	/// <summary>Curve and a color to draw it in.</summary>
	[StructLayout(LayoutKind.Sequential), SerializeObject]
	public partial struct CurveDrawInfo
	{
		public CurveDrawInfo(AnimationCurve curve, Color color)
		{
			this.curve = curve;
			this.color = color;
		}

		public AnimationCurve curve;
		public Color color;
	}

	/** @} */
}
