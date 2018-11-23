using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace BansheeEngine
{
	/** @addtogroup Particles
	 *  @{
	 */

	/// <summary>
	/// Particle emitter shape that emits particles from a surface of a skinned (animated) mesh. Particles can be emitted from 
	/// mesh vertices, edges or triangles. If information about normals exists, particles will also inherit the normals.
	/// </summary>
	public partial class ParticleEmitterSkinnedMeshShape : ParticleEmitterShape
	{
		private ParticleEmitterSkinnedMeshShape(bool __dummy0) { }
		protected ParticleEmitterSkinnedMeshShape() { }

		/// <summary>Options describing the shape.</summary>
		public ParticleSkinnedMeshShapeOptions Options
		{
			get
			{
				ParticleSkinnedMeshShapeOptions temp;
				Internal_getOptions(mCachedPtr, out temp);
				return temp;
			}
			set { Internal_setOptions(mCachedPtr, ref value); }
		}

		/// <summary>Creates a new particle emitter skinned mesh shape.</summary>
		public static ParticleEmitterShape Create(ParticleSkinnedMeshShapeOptions desc)
		{
			return Internal_create(ref desc);
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setOptions(IntPtr thisPtr, ref ParticleSkinnedMeshShapeOptions options);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_getOptions(IntPtr thisPtr, out ParticleSkinnedMeshShapeOptions __output);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern ParticleEmitterShape Internal_create(ref ParticleSkinnedMeshShapeOptions desc);
	}

	/** @} */
}
