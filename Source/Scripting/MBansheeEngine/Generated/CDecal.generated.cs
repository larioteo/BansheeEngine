using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace BansheeEngine
{
	/** @addtogroup Rendering
	 *  @{
	 */

	/// <summary>Wraps Decal as a Component.</summary>
	public partial class Decal : Component
	{
		private Decal(bool __dummy0) { }
		protected Decal() { }

		/// <summary>Determines the material to use when rendering the decal.</summary>
		[ShowInInspector]
		public RRef<Material> Material
		{
			get { return Internal_getMaterial(mCachedPtr); }
			set { Internal_setMaterial(mCachedPtr, value); }
		}

		/// <summary>Size of the decal in world space units.</summary>
		[ShowInInspector]
		public Vector2 Size
		{
			get
			{
				Vector2 temp;
				Internal_getSize(mCachedPtr, out temp);
				return temp;
			}
			set { Internal_setSize(mCachedPtr, ref value); }
		}

		/// <summary>Determines the maximum distance (from its origin) at which the decal is displayed.</summary>
		[ShowInInspector]
		public float MaxDistance
		{
			get { return Internal_getMaxDistance(mCachedPtr); }
			set { Internal_setMaxDistance(mCachedPtr, value); }
		}

		/// <summary>
		/// Determines the layer bitfield that controls whether a system is considered visible in a specific camera.  Layer must 
		/// match camera layer in order for the camera to render the component.
		/// </summary>
		[ShowInInspector]
		public ulong Layer
		{
			get { return Internal_getLayer(mCachedPtr); }
			set { Internal_setLayer(mCachedPtr, value); }
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setMaterial(IntPtr thisPtr, RRef<Material> material);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern RRef<Material> Internal_getMaterial(IntPtr thisPtr);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setSize(IntPtr thisPtr, ref Vector2 size);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_getSize(IntPtr thisPtr, out Vector2 __output);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setMaxDistance(IntPtr thisPtr, float distance);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern float Internal_getMaxDistance(IntPtr thisPtr);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setLayer(IntPtr thisPtr, ulong layer);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern ulong Internal_getLayer(IntPtr thisPtr);
	}

	/** @} */
}
