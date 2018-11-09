using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace BansheeEngine
{
	/** @addtogroup Particles
	 *  @{
	 */

	/// <summary>
	/// Represents a three dimensional field of vectors. It is represented by spatial bounds which are split into a grid of 
	/// values with user-defined density, where each grid cell is assigned a vector.
	/// </summary>
	public partial class VectorField : Resource
	{
		private VectorField(bool __dummy0) { }
		protected VectorField() { }

		/// <summary>Returns a reference wrapper for this resource.</summary>
		public RRef<VectorField> Ref
		{
			get { return Internal_GetRef(mCachedPtr); }
		}

		/// <summary>Returns a reference wrapper for this resource.</summary>
		public static implicit operator RRef<VectorField>(VectorField x)
		{ return Internal_GetRef(x.mCachedPtr); }

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern RRef<VectorField> Internal_GetRef(IntPtr thisPtr);
	}

	/** @} */
}
