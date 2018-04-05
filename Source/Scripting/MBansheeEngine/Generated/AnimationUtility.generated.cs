using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace BansheeEngine
{
	/** @addtogroup Animation
	 *  @{
	 */

	/// <summary>Helper class for dealing with animations, animation clips and curves.</summary>
	public partial class AnimationUtility : ScriptObject
	{
		private AnimationUtility(bool __dummy0) { }
		protected AnimationUtility() { }

		/// <summary>Converts a curve in euler angles (in degrees) into a curve using quaternions.</summary>
		public static QuaternionCurve EulerToQuaternionCurve(Vector3Curve eulerCurve)
		{
			return Internal_eulerToQuaternionCurve(eulerCurve);
		}

		/// <summary>Converts a curve in quaternions into a curve using euler angles (in degrees).</summary>
		public static Vector3Curve QuaternionToEulerCurve(QuaternionCurve quatCurve)
		{
			return Internal_quaternionToEulerCurve(quatCurve);
		}

		/// <summary>Splits a Vector3 curve into three individual curves, one for each component.</summary>
		public static AnimationCurve[] SplitCurve(Vector3Curve compoundCurve)
		{
			return Internal_splitCurve(compoundCurve);
		}

		/// <summary>Combines three single component curves into a Vector3 curve.</summary>
		public static Vector3Curve CombineCurve(AnimationCurve[] curveComponents)
		{
			return Internal_combineCurve(curveComponents);
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern QuaternionCurve Internal_eulerToQuaternionCurve(Vector3Curve eulerCurve);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern Vector3Curve Internal_quaternionToEulerCurve(QuaternionCurve quatCurve);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern AnimationCurve[] Internal_splitCurve(Vector3Curve compoundCurve);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern Vector3Curve Internal_combineCurve(AnimationCurve[] curveComponents);
	}

	/** @} */
}
