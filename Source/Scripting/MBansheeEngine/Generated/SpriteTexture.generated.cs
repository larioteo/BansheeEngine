using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace BansheeEngine
{
	/** @addtogroup Rendering
	 *  @{
	 */

	/// <summary>
	/// Texture interface that encapsulates underlying texture which allows us to create a sprite texture atlas (for example  
	/// multiple SpriteTexture%s referencing different parts of a single Texture).
	/// </summary>
	public partial class SpriteTexture : Resource
	{
		private SpriteTexture(bool __dummy0) { }
		protected SpriteTexture() { }

		/// <summary>Creates a new sprite texture that references the entire area of the provided texture.</summary>
		public SpriteTexture(Texture texture)
		{
			Internal_create(this, texture);
		}

		/// <summary>Creates a new sprite texture that references a sub-area of the provided texture.</summary>
		public SpriteTexture(Vector2 uvOffset, Vector2 uvScale, Texture texture)
		{
			Internal_create0(this, ref uvOffset, ref uvScale, texture);
		}

		/// <summary>Determines the internal texture that the sprite texture references.</summary>
		public Texture Texture
		{
			get { return Internal_getTexture(mCachedPtr); }
			set { Internal_setTexture(mCachedPtr, value); }
		}

		/// <summary>
		/// Determines the offset into the referenced texture where the sprite starts. The offset is in UV coordinates, in range 
		/// [0, 1].
		/// </summary>
		public Vector2 Offset
		{
			get
			{
				Vector2 temp;
				Internal_getOffset(mCachedPtr, out temp);
				return temp;
			}
			set { Internal_setOffset(mCachedPtr, ref value); }
		}

		/// <summary>
		/// Determines the size of the sprite in the referenced texture. Size is in UV coordinates, range [0, 1].
		/// </summary>
		public Vector2 Scale
		{
			get
			{
				Vector2 temp;
				Internal_getScale(mCachedPtr, out temp);
				return temp;
			}
			set { Internal_setScale(mCachedPtr, ref value); }
		}

		/// <summary>Returns width of the sprite texture in pixels.</summary>
		public uint Width
		{
			get { return Internal_getWidth(mCachedPtr); }
		}

		/// <summary>Returns height of the sprite texture in pixels.</summary>
		public uint Height
		{
			get { return Internal_getHeight(mCachedPtr); }
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setTexture(IntPtr thisPtr, Texture texture);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern Texture Internal_getTexture(IntPtr thisPtr);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setOffset(IntPtr thisPtr, ref Vector2 offset);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_getOffset(IntPtr thisPtr, out Vector2 __output);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setScale(IntPtr thisPtr, ref Vector2 scale);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_getScale(IntPtr thisPtr, out Vector2 __output);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern uint Internal_getWidth(IntPtr thisPtr);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern uint Internal_getHeight(IntPtr thisPtr);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_create(SpriteTexture managedInstance, Texture texture);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_create0(SpriteTexture managedInstance, ref Vector2 uvOffset, ref Vector2 uvScale, Texture texture);
	}

	/** @} */
}
