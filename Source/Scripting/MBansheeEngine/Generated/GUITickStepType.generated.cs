using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace BansheeEngine
{
	/** @addtogroup GUIEditor
	 *  @{
	 */

	/// <summary>Determines how should ticks reported by <see cref="GUIGraphTicks"/> be distributed.</summary>
	public enum GUITickStepType
	{
		/// <summary>Ticks represent time values (Multiples of 60).</summary>
		Time = 0,
		/// <summary>Ticks represent generic values (Multiples of 10).</summary>
		Generic = 1
	}

	/** @} */
}
