using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace BansheeEngine
{
	/** @addtogroup Particles
	 *  @{
	 */

	/// <summary>
	/// Particle emitter shape that emits particles from a surface of a static (non-animated) mesh. Particles can be emitted 
	/// from mesh vertices, edges or triangles. If information about normals exists, particles will also inherit the normals.
	/// </summary>
	public partial class ParticleEmitterStaticMeshShape : ParticleEmitterShape
	{
		private ParticleEmitterStaticMeshShape(bool __dummy0) { }
		protected ParticleEmitterStaticMeshShape() { }

		/// <summary>Options describing the shape.</summary>
		public ParticleStaticMeshShapeOptions Options
		{
			get
			{
				ParticleStaticMeshShapeOptions temp;
				Internal_getOptions(mCachedPtr, out temp);
				return temp;
			}
			set { Internal_setOptions(mCachedPtr, ref value); }
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setOptions(IntPtr thisPtr, ref ParticleStaticMeshShapeOptions options);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_getOptions(IntPtr thisPtr, out ParticleStaticMeshShapeOptions __output);
	}

	/** @} */
}
