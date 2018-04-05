using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace BansheeEngine
{
	/** @addtogroup Audio
	 *  @{
	 */

	/// <summary>Identifier for a device that can be used for playing audio.</summary>
	[StructLayout(LayoutKind.Sequential), SerializeObject]
	public partial struct AudioDevice
	{
		public string name;
	}

	/** @} */
}
