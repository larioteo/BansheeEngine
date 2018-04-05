using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace BansheeEngine
{
	/** @addtogroup Rendering
	 *  @{
	 */

	/// <summary>
	/// Material that controls how objects are rendered. It is represented by a shader and parameters used to set up that 
	/// shader. It provides a simple interface for manipulating the parameters.
	/// </summary>
	public partial class Material : Resource
	{
		private Material(bool __dummy0) { }

		/// <summary>Creates a new empty material.</summary>
		public Material()
		{
			Internal_create(this);
		}

		/// <summary>Creates a new material with the specified shader.</summary>
		public Material(Shader shader)
		{
			Internal_create0(this, shader);
		}

		/// <summary>
		/// Sets a shader that will be used by the material. Material will be initialized using all compatible techniques from 
		/// the shader. Shader must be set before doing any other operations with the material.
		/// </summary>
		public Shader Shader
		{
			get { return Internal_getShader(mCachedPtr); }
			set { Internal_setShader(mCachedPtr, value); }
		}

		/// <summary>Creates a deep copy of the material and returns the new object.</summary>
		public Material Clone()
		{
			return Internal_clone(mCachedPtr);
		}

		/// <summary>
		/// Assigns a float value to the shader parameter with the specified name.
		///
		/// Optionally if the parameter is an array you may provide an array index to assign the value to.
		/// </summary>
		public void SetFloat(string name, float value, uint arrayIdx = 0)
		{
			Internal_setFloat(mCachedPtr, name, value, arrayIdx);
		}

		/// <summary>
		/// Assigns a color to the shader parameter with the specified name.
		///
		/// Optionally if the parameter is an array you may provide an array index to assign the value to.
		/// </summary>
		public void SetColor(string name, Color value, uint arrayIdx = 0)
		{
			Internal_setColor(mCachedPtr, name, ref value, arrayIdx);
		}

		/// <summary>
		/// Assigns a 2D vector to the shader parameter with the specified name.
		///
		/// Optionally if the parameter is an array you may provide an array index to assign the value to.
		/// </summary>
		public void SetVector2(string name, Vector2 value, uint arrayIdx = 0)
		{
			Internal_setVec2(mCachedPtr, name, ref value, arrayIdx);
		}

		/// <summary>
		/// Assigns a 3D vector to the shader parameter with the specified name.
		///
		/// Optionally if the parameter is an array you may provide an array index to assign the value to.
		/// </summary>
		public void SetVector3(string name, Vector3 value, uint arrayIdx = 0)
		{
			Internal_setVec3(mCachedPtr, name, ref value, arrayIdx);
		}

		/// <summary>
		/// Assigns a 4D vector to the shader parameter with the specified name.
		///
		/// Optionally if the parameter is an array you may provide an array index to assign the value to.
		/// </summary>
		public void SetVector4(string name, Vector4 value, uint arrayIdx = 0)
		{
			Internal_setVec4(mCachedPtr, name, ref value, arrayIdx);
		}

		/// <summary>
		/// Assigns a 3x3 matrix to the shader parameter with the specified name.
		///
		/// Optionally if the parameter is an array you may provide an array index to assign the value to.
		/// </summary>
		public void SetMatrix3(string name, Matrix3 value, uint arrayIdx = 0)
		{
			Internal_setMat3(mCachedPtr, name, ref value, arrayIdx);
		}

		/// <summary>
		/// Assigns a 4x4 matrix to the shader parameter with the specified name.
		///
		/// Optionally if the parameter is an array you may provide an array index to assign the value to.
		/// </summary>
		public void SetMatrix4(string name, Matrix4 value, uint arrayIdx = 0)
		{
			Internal_setMat4(mCachedPtr, name, ref value, arrayIdx);
		}

		/// <summary>
		/// Returns a float value assigned with the parameter with the specified name.
		///
		/// Optionally if the parameter is an array you may provide an array index you which to retrieve.
		/// </summary>
		public float GetFloat(string name, uint arrayIdx = 0)
		{
			return Internal_getFloat(mCachedPtr, name, arrayIdx);
		}

		/// <summary>
		/// Returns a color assigned with the parameter with the specified name.
		///
		/// Optionally if the parameter is an array you may provide an array index you which to retrieve.
		/// </summary>
		public Color GetColor(string name, uint arrayIdx = 0)
		{
			Color temp;
			Internal_getColor(mCachedPtr, name, arrayIdx, out temp);
			return temp;
		}

		/// <summary>
		/// Returns a 2D vector assigned with the parameter with the specified name.
		///
		/// Optionally if the parameter is an array you may provide an array index you which to retrieve.
		/// </summary>
		public Vector2 GetVector2(string name, uint arrayIdx = 0)
		{
			Vector2 temp;
			Internal_getVec2(mCachedPtr, name, arrayIdx, out temp);
			return temp;
		}

		/// <summary>
		/// Returns a 3D vector assigned with the parameter with the specified name.
		///
		/// Optionally if the parameter is an array you may provide an array index you which to retrieve.
		/// </summary>
		public Vector3 GetVector3(string name, uint arrayIdx = 0)
		{
			Vector3 temp;
			Internal_getVec3(mCachedPtr, name, arrayIdx, out temp);
			return temp;
		}

		/// <summary>
		/// Returns a 4D vector assigned with the parameter with the specified name.
		///
		/// Optionally if the parameter is an array you may provide an array index you which to retrieve.
		/// </summary>
		public Vector4 GetVector4(string name, uint arrayIdx = 0)
		{
			Vector4 temp;
			Internal_getVec4(mCachedPtr, name, arrayIdx, out temp);
			return temp;
		}

		/// <summary>
		/// Returns a 3x3 matrix assigned with the parameter with the specified name.
		///
		/// Optionally if the parameter is an array you may provide an array index you which to retrieve.
		/// </summary>
		public Matrix3 GetMatrix3(string name, uint arrayIdx = 0)
		{
			Matrix3 temp;
			Internal_getMat3(mCachedPtr, name, arrayIdx, out temp);
			return temp;
		}

		/// <summary>
		/// Returns a 4x4 matrix assigned with the parameter with the specified name.
		///
		/// Optionally if the parameter is an array you may provide an array index you which to retrieve.
		/// </summary>
		public Matrix4 GetMatrix4(string name, uint arrayIdx = 0)
		{
			Matrix4 temp;
			Internal_getMat4(mCachedPtr, name, arrayIdx, out temp);
			return temp;
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setShader(IntPtr thisPtr, Shader shader);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern Material Internal_clone(IntPtr thisPtr);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern Shader Internal_getShader(IntPtr thisPtr);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setFloat(IntPtr thisPtr, string name, float value, uint arrayIdx);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setColor(IntPtr thisPtr, string name, ref Color value, uint arrayIdx);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setVec2(IntPtr thisPtr, string name, ref Vector2 value, uint arrayIdx);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setVec3(IntPtr thisPtr, string name, ref Vector3 value, uint arrayIdx);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setVec4(IntPtr thisPtr, string name, ref Vector4 value, uint arrayIdx);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setMat3(IntPtr thisPtr, string name, ref Matrix3 value, uint arrayIdx);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setMat4(IntPtr thisPtr, string name, ref Matrix4 value, uint arrayIdx);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern float Internal_getFloat(IntPtr thisPtr, string name, uint arrayIdx);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_getColor(IntPtr thisPtr, string name, uint arrayIdx, out Color __output);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_getVec2(IntPtr thisPtr, string name, uint arrayIdx, out Vector2 __output);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_getVec3(IntPtr thisPtr, string name, uint arrayIdx, out Vector3 __output);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_getVec4(IntPtr thisPtr, string name, uint arrayIdx, out Vector4 __output);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_getMat3(IntPtr thisPtr, string name, uint arrayIdx, out Matrix3 __output);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_getMat4(IntPtr thisPtr, string name, uint arrayIdx, out Matrix4 __output);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_create(Material managedInstance);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_create0(Material managedInstance, Shader shader);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setTexture(IntPtr thisPtr, string name, Texture value, uint mipLevel, uint numMipLevels, uint arraySlice, uint numArraySlices);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern Texture Internal_getTexture(IntPtr thisPtr, string name);
	}

	/** @} */
}
