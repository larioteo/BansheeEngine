using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace BansheeEngine
{
	/** @addtogroup Particles
	 *  @{
	 */

	/// <summary>
	/// Particle emitter shape that emits particles from a sphere. Particles can be emitted from sphere surface, the entire 
	/// volume or a proportion of the volume depending on the thickness parameter. All particles will have normals pointing 
	/// outwards in a spherical direction.
	/// </summary>
	public partial class ParticleEmitterSphereShape : ParticleEmitterShape
	{
		private ParticleEmitterSphereShape(bool __dummy0) { }
		protected ParticleEmitterSphereShape() { }

		/// <summary>Creates a new particle emitter sphere shape.</summary>
		public ParticleEmitterSphereShape(ParticleSphereShapeOptions desc)
		{
			Internal_create(this, ref desc);
		}

		/// <summary>Options describing the shape.</summary>
		public ParticleSphereShapeOptions Options
		{
			get
			{
				ParticleSphereShapeOptions temp;
				Internal_getOptions(mCachedPtr, out temp);
				return temp;
			}
			set { Internal_setOptions(mCachedPtr, ref value); }
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setOptions(IntPtr thisPtr, ref ParticleSphereShapeOptions options);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_getOptions(IntPtr thisPtr, out ParticleSphereShapeOptions __output);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_create(ParticleEmitterSphereShape managedInstance, ref ParticleSphereShapeOptions desc);
	}

	/** @} */
}
