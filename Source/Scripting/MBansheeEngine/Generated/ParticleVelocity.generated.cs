using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace BansheeEngine
{
	/** @addtogroup Particles
	 *  @{
	 */

	/// <summary>Applies linear velocity to the particles.</summary>
	public partial class ParticleVelocity : ParticleEvolver
	{
		private ParticleVelocity(bool __dummy0) { }
		protected ParticleVelocity() { }

		/// <summary>Options describing the evolver.</summary>
		public ParticleVelocityOptions Options
		{
			get
			{
				ParticleVelocityOptions temp;
				Internal_getOptions(mCachedPtr, out temp);
				return temp;
			}
			set { Internal_setOptions(mCachedPtr, ref value); }
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setOptions(IntPtr thisPtr, ref ParticleVelocityOptions options);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_getOptions(IntPtr thisPtr, out ParticleVelocityOptions __output);
	}

	/** @} */
}
