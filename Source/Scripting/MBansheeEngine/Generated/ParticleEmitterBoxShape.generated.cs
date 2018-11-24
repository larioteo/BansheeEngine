using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace BansheeEngine
{
	/** @addtogroup Particles
	 *  @{
	 */

	/// <summary>
	/// Particle emitter shape that emits particles from an axis aligned box. Particles can be emitted from box volume, 
	/// surface or edges. All particles have their normals set to positive Z direction.
	/// </summary>
	public partial class ParticleEmitterBoxShape : ParticleEmitterShape
	{
		private ParticleEmitterBoxShape(bool __dummy0) { }
		protected ParticleEmitterBoxShape() { }

		/// <summary>Creates a new particle emitter box shape.</summary>
		public ParticleEmitterBoxShape(ParticleBoxShapeOptions desc)
		{
			Internal_create(this, ref desc);
		}

		/// <summary>Options describing the shape.</summary>
		public ParticleBoxShapeOptions Options
		{
			get
			{
				ParticleBoxShapeOptions temp;
				Internal_getOptions(mCachedPtr, out temp);
				return temp;
			}
			set { Internal_setOptions(mCachedPtr, ref value); }
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setOptions(IntPtr thisPtr, ref ParticleBoxShapeOptions options);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_getOptions(IntPtr thisPtr, out ParticleBoxShapeOptions __output);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_create(ParticleEmitterBoxShape managedInstance, ref ParticleBoxShapeOptions desc);
	}

	/** @} */
}
