using System;
using BansheeEngine;

namespace BansheeEditor
{
    partial class GUIFloatDistributionField
    {
        /// <summary>
        /// Callback triggered when the user clicks on the curve display in the GUI element.
        /// </summary>
        partial void OnClicked()
        {
            FloatDistribution distribution = Value;

            if (distribution.DistributionType == PropertyDistributionType.Curve)
            {
                CurveEditorWindow.Show(distribution.GetMinCurve(), (success, curve) =>
                {
                    if(success)
                        Value = new FloatDistribution(curve);
                });
            }
            else if (distribution.DistributionType == PropertyDistributionType.RandomCurveRange)
            {
                CurveEditorWindow.Show(distribution.GetMinCurve(), distribution.GetMaxCurve(), 
                    (success, minCurve, maxCurve) =>
                {
                    if(success)
                        Value = new FloatDistribution(minCurve, maxCurve);
                });
            }
        }
    }
}
