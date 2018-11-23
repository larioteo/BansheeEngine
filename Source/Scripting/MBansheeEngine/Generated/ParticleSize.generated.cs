using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace BansheeEngine
{
	/** @addtogroup Particles
	 *  @{
	 */

	/// <summary>Changes the size of the particles over the particle lifetime.</summary>
	public partial class ParticleSize : ParticleEvolver
	{
		private ParticleSize(bool __dummy0) { }
		protected ParticleSize() { }

		/// <summary>Options describing the evolver.</summary>
		public ParticleSizeOptions Options
		{
			get
			{
				ParticleSizeOptions temp;
				Internal_getOptions(mCachedPtr, out temp);
				return temp;
			}
			set { Internal_setOptions(mCachedPtr, ref value); }
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setOptions(IntPtr thisPtr, ref ParticleSizeOptions options);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_getOptions(IntPtr thisPtr, out ParticleSizeOptions __output);
	}

	/** @} */
}
