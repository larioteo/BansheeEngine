using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using BansheeEngine;

namespace BansheeEditor
{
	/** @addtogroup GUIEditor
	 *  @{
	 */

	/// <summary>
	/// A composite GUI object representing an editor field. Editor fields are a combination of a label and an input field. 
	/// Label is optional. This specific implementation displays an animation curve or a range between two animation curves.
	/// </summary>
	[ShowInInspector]
	public partial class GUICurvesField : GUIElement
	{
		private GUICurvesField(bool __dummy0) { }
		protected GUICurvesField() { }

		/// <summary>Creates a new GUI editor field with a label.</summary>
		/// <param name="labelContent">Content to display in the editor field label.</param>
		/// <param name="labelWidth">Width of the label in pixels.</param>
		/// <param name="style">
		/// Optional style to use for the element. Style will be retrieved from GUISkin of the GUIWidget the element is used on. 
		/// If not specified default style is used.
		/// </param>
		public GUICurvesField(GUIContent labelContent, uint labelWidth, string style = "")
		{
			Internal_create(this, ref labelContent, labelWidth, style);
		}

		/// <summary>Creates a new GUI editor field with a label.</summary>
		/// <param name="labelContent">Content to display in the editor field label.</param>
		/// <param name="style">
		/// Optional style to use for the element. Style will be retrieved from GUISkin of the GUIWidget the element is used on. 
		/// If not specified default style is used.
		/// </param>
		public GUICurvesField(GUIContent labelContent, string style = "")
		{
			Internal_create0(this, ref labelContent, style);
		}

		/// <summary>Creates a new GUI editor field with a label.</summary>
		/// <param name="labelText">String to display in the editor field label.</param>
		/// <param name="labelWidth">Width of the label in pixels.</param>
		/// <param name="style">
		/// Optional style to use for the element. Style will be retrieved from GUISkin of the GUIWidget the element is used on. 
		/// If not specified default style is used.
		/// </param>
		public GUICurvesField(LocString labelText, uint labelWidth, string style = "")
		{
			Internal_create1(this, labelText, labelWidth, style);
		}

		/// <summary>Creates a new GUI editor field with a label.</summary>
		/// <param name="labelText">String to display in the editor field label.</param>
		/// <param name="style">
		/// Optional style to use for the element. Style will be retrieved from GUISkin of the GUIWidget the element is used on. 
		/// If not specified default style is used.
		/// </param>
		public GUICurvesField(LocString labelText, string style = "")
		{
			Internal_create2(this, labelText, style);
		}

		/// <summary>Creates a new GUI editor field without a label.</summary>
		/// <param name="style">
		/// Optional style to use for the element. Style will be retrieved from GUISkin of the GUIWidget the element is used on. 
		/// If not specified default style is used.
		/// </param>
		public GUICurvesField(string style = "")
		{
			Internal_create3(this, style);
		}

		/// <summary>
		/// Returns the curve represented by the field. If the field represents a curve range this returns the minimal curve of 
		/// that range.
		/// </summary>
		[ShowInInspector]
		[NativeWrapper]
		public AnimationCurve Curve
		{
			get { return Internal_getCurve(mCachedPtr); }
		}

		/// <summary>
		/// Returns the minimal curve represented by the field containing a curve range. Returns the only available curve if the 
		/// field doesn't represent a range.
		/// </summary>
		[ShowInInspector]
		[NativeWrapper]
		public AnimationCurve MinCurve
		{
			get { return Internal_getMinCurve(mCachedPtr); }
		}

		/// <summary>
		/// Returns the maximal curve represented by the field containing a curve range. Returns the only available curve if the 
		/// field doesn't represent a range.
		/// </summary>
		[ShowInInspector]
		[NativeWrapper]
		public AnimationCurve MaxCurve
		{
			get { return Internal_getMaxCurve(mCachedPtr); }
		}

		/// <summary>Triggered when the user clicks on the GUI element.</summary>
		partial void OnClicked();

		/// <summary>Sets an animation curve to display on the field.</summary>
		public void SetCurve(AnimationCurve curve)
		{
			Internal_setCurve(mCachedPtr, curve);
		}

		/// <summary>Sets a set of animation curves and displays the difference (range) between them.</summary>
		public void SetCurveRange(AnimationCurve curveA, AnimationCurve curveB)
		{
			Internal_setCurveRange(mCachedPtr, curveA, curveB);
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setCurve(IntPtr thisPtr, AnimationCurve curve);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_setCurveRange(IntPtr thisPtr, AnimationCurve curveA, AnimationCurve curveB);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern AnimationCurve Internal_getCurve(IntPtr thisPtr);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern AnimationCurve Internal_getMinCurve(IntPtr thisPtr);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern AnimationCurve Internal_getMaxCurve(IntPtr thisPtr);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_create(GUICurvesField managedInstance, ref GUIContent labelContent, uint labelWidth, string style);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_create0(GUICurvesField managedInstance, ref GUIContent labelContent, string style);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_create1(GUICurvesField managedInstance, LocString labelText, uint labelWidth, string style);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_create2(GUICurvesField managedInstance, LocString labelText, string style);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_create3(GUICurvesField managedInstance, string style);
		private void Internal_onClicked()
		{
			OnClicked();
		}
	}

	/** @} */
}
