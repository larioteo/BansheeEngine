using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace BansheeEngine
{
	/** @addtogroup Rendering
	 *  @{
	 */

	/// <summary>Light type that determines how is light information parsed by the renderer and other systems.</summary>
	public enum ReflectionProbeType
	{
		/// <summary>
		/// Reflection probe cubemap is generated, and box extents are used for calculating influence ranges and box  geometry.
		/// </summary>
		Box = 0,
		/// <summary>
		/// Reflection probe cubemap is generated, but sphere is used for calculating the influence radius and proxy geometry.
		/// </summary>
		Sphere = 1
	}

	/** @} */
}
