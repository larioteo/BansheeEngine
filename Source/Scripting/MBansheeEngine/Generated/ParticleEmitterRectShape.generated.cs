using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace BansheeEngine
{
	/** @addtogroup Particles
	 *  @{
	 */

	/// <summary>Particle emitter shape that emits particles from the surface of a rectangle.</summary>
	public partial class ParticleEmitterRectShape : ParticleEmitterShape
	{
		private ParticleEmitterRectShape(bool __dummy0) { }
		protected ParticleEmitterRectShape() { }

		/// <summary>Options describing the shape.</summary>
		public ParticleRectShapeOptions Options
		{
			get
			{
				ParticleRectShapeOptions temp;
				Internal_getOptions(mCachedPtr, out temp);
				return temp;
			}
			set { Internal_setOptions(mCachedPtr, ref value); }
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setOptions(IntPtr thisPtr, ref ParticleRectShapeOptions options);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_getOptions(IntPtr thisPtr, out ParticleRectShapeOptions __output);
	}

	/** @} */
}
