using System;
using BansheeEngine;

namespace BansheeEditor
{
    partial class GUIVector3DistributionField
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
            Vector3Distribution distribution = Value;

            if (DistributionType == PropertyDistributionType.Curve)
            {
                AnimationCurve[] curves = AnimationUtility.SplitCurve3D(distribution.GetMinCurve());
                if (component < curves.Length)
                {
                    CurveEditorWindow.Show(curves[component], (success, curve) =>
                    {
                        if (!success)
                            return;

                        curves[component] = curve;

                        Vector3Curve compoundCurve = AnimationUtility.CombineCurve3D(curves);
                        Value = new Vector3Distribution(compoundCurve);
                        OnChanged?.Invoke();
                        OnConfirmed?.Invoke();
                    });
                }
            }
            else if (DistributionType == PropertyDistributionType.RandomCurveRange)
            {
                AnimationCurve[] minCurves = AnimationUtility.SplitCurve3D(distribution.GetMinCurve());
                AnimationCurve[] maxCurves = AnimationUtility.SplitCurve3D(distribution.GetMaxCurve());

                if (component < minCurves.Length && component < maxCurves.Length)
                {
                    CurveEditorWindow.Show(minCurves[component], maxCurves[component],
                        (success, minCurve, maxCurve) =>
                        {
                            if (!success)
                                return;

                            minCurves[component] = minCurve;
                            maxCurves[component] = maxCurve;

                            Vector3Curve minCompoundCurves = AnimationUtility.CombineCurve3D(minCurves);
                            Vector3Curve maxCompoundCurves = AnimationUtility.CombineCurve3D(maxCurves);

                            Value = new Vector3Distribution(minCompoundCurves, maxCompoundCurves);
                            OnChanged?.Invoke();
                            OnConfirmed?.Invoke();
                        });
                }
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
