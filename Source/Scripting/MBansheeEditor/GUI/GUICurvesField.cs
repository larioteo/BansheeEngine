using System;
using BansheeEngine;

namespace BansheeEditor
{
    partial class GUICurvesField
    {
        /// <summary>
        /// Triggered when the curve in the field changes.
        /// </summary>
        public event Action<AnimationCurve> OnChanged;

        /// <summary>
        /// Callback triggered when the user clicks on the GUI element.
        /// </summary>
        partial void OnClicked()
        {
            CurveEditorWindow.Show(Curve, (success, curve) =>
            {
                if (!success)
                    return;

                SetCurve(curve);
                OnChanged?.Invoke(curve);
            });
        }
    }
}
