using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace BansheeEngine
{
	/** @addtogroup Particles
	 *  @{
	 */

	/// <summary>Particle emitter shape that emits particles from a line segment.</summary>
	public partial class ParticleEmitterLineShape : ParticleEmitterShape
	{
		private ParticleEmitterLineShape(bool __dummy0) { }
		protected ParticleEmitterLineShape() { }

		/// <summary>Options describing the shape.</summary>
		public ParticleLineShapeOptions Options
		{
			get
			{
				ParticleLineShapeOptions temp;
				Internal_getOptions(mCachedPtr, out temp);
				return temp;
			}
			set { Internal_setOptions(mCachedPtr, ref value); }
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setOptions(IntPtr thisPtr, ref ParticleLineShapeOptions options);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_getOptions(IntPtr thisPtr, out ParticleLineShapeOptions __output);
	}

	/** @} */
}
