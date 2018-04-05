using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace BansheeEngine
{
	/** @addtogroup Physics
	 *  @{
	 */

	/// <summary>A collider with plane geometry. Plane colliders cannot be a part of non-kinematic rigidbodies.</summary>
	public partial class PlaneCollider : Collider
	{
		private PlaneCollider(bool __dummy0) { }
		protected PlaneCollider() { }

		/// <summary>Normal vector that determines the local orientation of the plane.</summary>
		[ShowInInspector]
		public Vector3 Normal
		{
			get
			{
				Vector3 temp;
				Internal_getNormal(mCachedPtr, out temp);
				return temp;
			}
			set { Internal_setNormal(mCachedPtr, ref value); }
		}

		/// <summary>Determines the distance of the plane from the local origin, along its normal vector.</summary>
		[ShowInInspector]
		public float Distance
		{
			get { return Internal_getDistance(mCachedPtr); }
			set { Internal_setDistance(mCachedPtr, value); }
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setNormal(IntPtr thisPtr, ref Vector3 normal);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_getNormal(IntPtr thisPtr, out Vector3 __output);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setDistance(IntPtr thisPtr, float distance);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern float Internal_getDistance(IntPtr thisPtr);
	}

	/** @} */
}
