using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace BansheeEngine
{
	/** @addtogroup Rendering
	 *  @{
	 */

	/// <summary>
	/// Contains definitions of GPU programs used for rendering, as well as a set of global parameters to control those  
	/// programs.
	/// </summary>
	public partial class Shader : Resource
	{
		private Shader(bool __dummy0) { }
		protected Shader() { }

		/// <summary>Returns information about all parameters available in the shader.</summary>
		public ShaderParameter[] Parameters
		{
			get { return Internal_getParameters(mCachedPtr); }
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern ShaderParameter[] Internal_getParameters(IntPtr thisPtr);
	}

	/** @} */
}
