using System;
using BansheeEngine;

namespace BansheeEditor
{
    partial class GUIFloatDistributionField
    {
        /// <summary>
        /// Triggered when the distribution in the field changes.
        /// </summary>
        public event Action OnChanged;

        /// <summary>
        /// Triggered whenever user confirms input in one of the floating point fields.
        /// </summary>
        public event Action OnConfirmed;

        partial void OnClicked(int component)
        {
            FloatDistribution distribution = Value;

            if (DistributionType == PropertyDistributionType.Curve)
            {
                CurveEditorWindow.Show(distribution.GetMinCurve(), (success, curve) =>
                {
                    if (!success)
                        return;

                    Value = new FloatDistribution(curve);
                    OnChanged?.Invoke();
                });
            }
            else if (DistributionType == PropertyDistributionType.RandomCurveRange)
            {
                CurveEditorWindow.Show(distribution.GetMinCurve(), distribution.GetMaxCurve(), 
                    (success, minCurve, maxCurve) =>
                    {
                        if (!success)
                            return;

                        Value = new FloatDistribution(minCurve, maxCurve);
                        OnChanged?.Invoke();
                    });
            }
        }

        partial void OnConstantModified()
        {
            OnChanged?.Invoke();
        }

        partial void OnConstantConfirmed()
        {
            OnConfirmed?.Invoke();
        }
    }
}
