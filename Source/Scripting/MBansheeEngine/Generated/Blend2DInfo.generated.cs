using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace BansheeEngine
{
	/** @addtogroup Animation
	 *  @{
	 */

	/// <summary>
	/// Defines a 2D blend where two animation clips are blended between each other using bilinear interpolation.
	/// </summary>
	[StructLayout(LayoutKind.Sequential), SerializeObject]
	public partial struct Blend2DInfo
	{
		public AnimationClip topLeftClip;
		public AnimationClip topRightClip;
		public AnimationClip botLeftClip;
		public AnimationClip botRightClip;
	}

	/** @} */
}
