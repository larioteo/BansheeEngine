using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace BansheeEngine
{
	/** @addtogroup Image
	 *  @{
	 */

	/// <summary>
	/// Represents a range of color values over some parameters, similar to a curve. Internally represented as a set of keys 
	/// that get interpolated between.
	/// </summary>
	public partial class ColorGradient : ScriptObject
	{
		private ColorGradient(bool __dummy0) { }

		public ColorGradient()
		{
			Internal_ColorGradient(this);
		}

		public ColorGradient(Color color)
		{
			Internal_ColorGradient0(this, ref color);
		}

		public ColorGradient(ColorGradientKey[] keys)
		{
			Internal_ColorGradient1(this, keys);
		}

		/// <summary>
		/// Keys that control the gradient, sorted by time from first to last. Key times should be in range [0, 1].
		/// </summary>
		public void SetKeys(ColorGradientKey[] keys, float duration = 1f)
		{
			Internal_setKeys(mCachedPtr, keys, duration);
		}

		/// <summary>
		/// Keys that control the gradient, sorted by time from first to last. Key times should be in range [0, 1].
		/// </summary>
		public ColorGradientKey[] GetKeys()
		{
			return Internal_getKeys(mCachedPtr);
		}

		/// <summary>Specify a "gradient" that represents a single color value.</summary>
		public void SetConstant(Color color)
		{
			Internal_setConstant(mCachedPtr, ref color);
		}

		/// <summary>Evaluates a color at the specified <paramref name="t"/>.</summary>
		public Color Evaluate(float t)
		{
			Color temp;
			Internal_evaluate(mCachedPtr, t, out temp);
			return temp;
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_ColorGradient(ColorGradient managedInstance);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_ColorGradient0(ColorGradient managedInstance, ref Color color);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_ColorGradient1(ColorGradient managedInstance, ColorGradientKey[] keys);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setKeys(IntPtr thisPtr, ColorGradientKey[] keys, float duration);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern ColorGradientKey[] Internal_getKeys(IntPtr thisPtr);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setConstant(IntPtr thisPtr, ref Color color);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_evaluate(IntPtr thisPtr, float t, out Color __output);
	}

	/** @} */
}
